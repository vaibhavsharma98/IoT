import streamlit as st
import pandas as pd
import re
from datetime import datetime, timedelta

# Set Streamlit page config for wide layout
st.set_page_config(layout="wide")

# Load data
def load_data():
    file_path = 'Crusher Report.xlsx'  # Adjust this path for deployment
    df = pd.read_excel(file_path, sheet_name='Sheet1', header=None)

    # Initialize variables
    cleaned_data = []
    current_date = None
    detail_type = None

    # Process the file line by line
    for index, row in df.iterrows():
        if isinstance(row[1], str) and "Crusher detail as on dated" in row[1]:
            match = re.search(r'\d{2}/\d{2}/\d{4}', row[1])
            if match:
                current_date = match.group(0)
                detail_type = 'Crusher'
                continue

        if isinstance(row[1], str) and "Plant detail as on dated" in row[1]:
            match = re.search(r'\d{2}/\d{2}/\d{4}', row[1])
            if match:
                current_date = match.group(0)
                detail_type = 'Plant'
                continue

        if pd.isna(row[1]) or row[1] in ["Site Name", "HMP Status", ""]:
            continue

        if current_date and detail_type and pd.notna(row[1]):
            cleaned_data.append({
                'Date': current_date,
                'Detail_Type': detail_type,
                'Site_Name': row[1],
                'Diesel_Consumption': row[22],
                'Aggregate_Output': row[14],
                'Supply_Total': row[21],  # Ensure the correct column index for Supply Total
                'Remarks': row[7] if len(row) > 7 else None
            })

    cleaned_df = pd.DataFrame(cleaned_data)
    cleaned_df['Date'] = pd.to_datetime(cleaned_df['Date'], format='%d/%m/%Y', errors='coerce')
    numeric_columns = ['Diesel_Consumption', 'Aggregate_Output', 'Supply_Total']
    cleaned_df[numeric_columns] = cleaned_df[numeric_columns].apply(pd.to_numeric, errors='coerce').fillna(0)

    # Correct the Supply_vs_Output calculation
    cleaned_df['Supply_vs_Output'] = cleaned_df['Aggregate_Output'] - cleaned_df['Supply_Total']

    # Calculate L/Cubic Meter and replace invalid or zero values with 1
    cleaned_df['L_Cubic_Meter'] = cleaned_df.apply(
        lambda row: row['Diesel_Consumption'] / row['Aggregate_Output']
        if row['Aggregate_Output'] > 0 else 1, axis=1
    )
    cleaned_df['L_Cubic_Meter'] = cleaned_df['L_Cubic_Meter'].replace([float('inf'), 0], 1).fillna(1)

    return cleaned_df

# Load cleaned data
try:
    data = load_data()
    if data.empty:
        st.error("No data was extracted. Please check the input file structure and ensure the correct format.")
except Exception as e:
    st.error(f"An error occurred while loading the data: {e}")
    data = pd.DataFrame()

# Streamlit App
st.title("Crusher and Plant Data Analysis")

if not data.empty:
    # CSS for responsiveness
    st.markdown("""
        <style>
        .responsive-chart {
            height: 100%;
            width: 100%;
        }
        .stApp {
            overflow: hidden;
        }
        </style>
    """, unsafe_allow_html=True)

    st.header("Detailed Analysis by Date")
    available_dates = data['Date'].dropna().unique()
    selected_date = st.selectbox("Select a Date", options=available_dates)

    if selected_date:
        filtered_data = data[data['Date'] == selected_date]

        # Responsive Layout for Graphs
        col1, col2, col3 = st.columns(3)

        with col1:
            st.subheader("Diesel Consumption by Site")
            diesel_consumption_html = f"""
            <div id="diesel-consumption" class="responsive-chart"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('diesel-consumption', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'Diesel Consumption by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'Diesel Consumption (Liters)' }} }},
                    series: [{{
                        name: 'Diesel Consumption',
                        data: {filtered_data['Diesel_Consumption'].fillna(0).tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(diesel_consumption_html, height=500)

        with col2:
            st.subheader("Aggregate Output by Site")
            aggregate_output_html = f"""
            <div id="aggregate-output" class="responsive-chart"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('aggregate-output', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'Aggregate Output by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'Aggregate Output (Cubic Meters)' }} }},
                    series: [{{
                        name: 'Aggregate Output',
                        data: {filtered_data['Aggregate_Output'].fillna(0).tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(aggregate_output_html, height=500)

        with col3:
            st.subheader("L/Cubic Meter by Site")
            efficiency_html = f"""
            <div id="efficiency" class="responsive-chart"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('efficiency', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'L/Cubic Meter by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'L/Cubic Meter' }} }},
                    series: [{{
                        name: 'L/Cubic Meter',
                        data: {filtered_data['L_Cubic_Meter'].tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(efficiency_html, height=500)

            # Remarks section
        st.subheader("Remarks")
        remarks = filtered_data.dropna(subset=['Remarks'])
        if not remarks.empty:
            for _, row in remarks.iterrows():
                st.write(f"**{row['Site_Name']} ({row['Detail_Type']})**: {row['Remarks']}")
        else:
            st.write("No remarks available for this date.")
    else:
        st.warning("No date selected.")

    st.header("Aggregate Output vs Supply Total Analysis")
    st.subheader("Filter by Time Period")
    time_period = st.radio("Select Time Period", options=["Daily", "Weekly", "Monthly", "Custom Time Frame"])

    # Prepare data for graph
    filtered_data = data.copy()
    if time_period == "Daily":
        filtered_data = filtered_data[filtered_data['Date'] >= (datetime.now() - timedelta(days=15))]
    elif time_period == "Weekly":
        filtered_data['Week'] = filtered_data['Date'].dt.to_period('W').apply(lambda r: r.start_time)
        filtered_data = filtered_data.groupby('Week').agg({
            'Aggregate_Output': 'sum',
            'Supply_Total': 'sum',
            'Supply_vs_Output': 'sum'
        }).reset_index()
    elif time_period == "Monthly":
        filtered_data['Month'] = filtered_data['Date'].dt.to_period('M').apply(lambda r: r.start_time)
        filtered_data = filtered_data.groupby('Month').agg({
            'Aggregate_Output': 'sum',
            'Supply_Total': 'sum',
            'Supply_vs_Output': 'sum'
        }).reset_index()
    elif time_period == "Custom Time Frame":
        st.write("Select a custom time frame:")
        custom_start_date = st.date_input("Start Date", value=data['Date'].min().date())
        custom_end_date = st.date_input("End Date", value=data['Date'].max().date())
        custom_start_date = pd.to_datetime(custom_start_date)
        custom_end_date = pd.to_datetime(custom_end_date)
        filtered_data = filtered_data[(filtered_data['Date'] >= custom_start_date) & (filtered_data['Date'] <= custom_end_date)]

    # Handle empty filtered data
    if filtered_data.empty:
        st.warning("No data available for the selected time period.")
    else:
        # Graph for Supply_vs_Output
        categories = (
            filtered_data.iloc[:, 0].dt.strftime('%Y-%m-%d').tolist()
            if time_period in ["Daily", "Custom Time Frame"] else
            filtered_data.iloc[:, 0].dt.strftime('%Y-%m').tolist()
        )
        graph_html = f"""
        <div id="supply-vs-output" style="height: 500px;"></div>
        <script src="https://code.highcharts.com/highcharts.js"></script>
        <script>
        document.addEventListener('DOMContentLoaded', function () {{
            Highcharts.chart('supply-vs-output', {{
                chart: {{ type: 'column' }},
                title: {{ text: 'Supply vs Output (Difference: Output - Supply)' }},
                xAxis: {{
                    categories: {categories},
                    title: {{ text: 'Date' }}
                }},
                yAxis: {{
                    title: {{ text: 'Output - Supply' }},
                    plotLines: [{{
                        value: 0,
                        color: 'red',
                        width: 2,
                        dashStyle: 'ShortDash',
                        label: {{ text: 'Zero Line' }}
                    }}]
                }},
                series: [{{
                    name: 'Output - Supply',
                    data: {filtered_data['Supply_vs_Output'].tolist()}
                }}]
            }});
        }});</script>"""
        st.components.v1.html(graph_html, height=600)
