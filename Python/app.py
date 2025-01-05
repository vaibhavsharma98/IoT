import streamlit as st
import pandas as pd
import re
from datetime import datetime, timedelta

# Set Streamlit page config for wide layout
st.set_page_config(layout="wide")

# Load data
def load_data():
    file_path = 'Python/Crusher Report.xlsx'  # Adjust this path for deployment
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
                'Supply_Total': row[21],
                'RBM': row[5],
                'Running Hours': row[2],
                'Maintainance Hours': row[3],
                'Actual Working Hours': row[4],
                'Remarks': row[23] if len(row) > 7 else None
            })

    cleaned_df = pd.DataFrame(cleaned_data)
    cleaned_df['Date'] = pd.to_datetime(cleaned_df['Date'], format='%d/%m/%Y', errors='coerce')
    numeric_columns = ['Diesel_Consumption', 'Aggregate_Output', 'Supply_Total', 'RBM', 'Running Hours', 'Maintainance Hours', 'Actual Working Hours']
    cleaned_df[numeric_columns] = cleaned_df[numeric_columns].apply(pd.to_numeric, errors='coerce').fillna(0)
    cleaned_df['RBM'] = cleaned_df['RBM']*8.5

    # Calculate L/Cubic Meter
    cleaned_df['L_Cubic_Meter'] = cleaned_df.apply(
        lambda row: row['Diesel_Consumption'] / row['Aggregate_Output'] if row['Aggregate_Output'] > 0 else 0,
        axis=1
    )

    # Correct the Supply_vs_Output calculation
    cleaned_df['Supply_vs_Output'] = cleaned_df['Aggregate_Output'] - cleaned_df['Supply_Total']
    cleaned_df['RBM_vs_Output'] = cleaned_df['RBM'] - cleaned_df['Aggregate_Output']

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
    st.header("Detailed Analysis by Date")
    available_dates = data['Date'].dropna().unique()
    selected_date = st.selectbox("Select a Date", options=available_dates)

    if selected_date:
        filtered_data = data[data['Date'] == selected_date]

        # Ensure L_Cubic_Meter exists in the filtered data
        if 'L_Cubic_Meter' not in filtered_data.columns:
            filtered_data['L_Cubic_Meter'] = filtered_data.apply(
                lambda row: row['Diesel_Consumption'] / row['Aggregate_Output'] if row['Aggregate_Output'] > 0 else 0,
                axis=1
            )

        # Arrange charts in columns
        col1, col2, col3 = st.columns(3)

        # Diesel Consumption Chart
        with col1:
            st.subheader("Diesel Consumption by Site")
            diesel_consumption_html = f"""
            <div id="diesel-consumption" style="height: 400px;"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('diesel-consumption', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'Diesel Consumption by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'Diesel Consumption (Liters)' }} }},
                    plotOptions: {{
                        column: {{
                            dataLabels: {{
                                enabled: true,
                                formatter: function() {{
                                    return this.y.toFixed(2);  // Format the label to show two decimal places
                                }}
                            }}
                        }}
                    }},
                    series: [{{
                        name: 'Diesel Consumption',
                        data: {filtered_data['Diesel_Consumption'].fillna(0).tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(diesel_consumption_html, height=400)

        # Aggregate Output Chart
        with col2:
            st.subheader("Aggregate Output by Site")
            aggregate_output_html = f"""
            <div id="aggregate-output" style="height: 400px;"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('aggregate-output', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'Aggregate Output by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'Aggregate Output (Cubic Meters)' }} }},
                    plotOptions: {{
                        column: {{
                            dataLabels: {{
                                enabled: true,
                                formatter: function() {{
                                    return this.y.toFixed(2);  // Format the label to show two decimal places
                                }}
                            }}
                        }}
                    }},
                    series: [{{
                        name: 'Aggregate Output',
                        data: {filtered_data['Aggregate_Output'].fillna(0).tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(aggregate_output_html, height=400)

        # L/Cubic Meter Chart
        with col3:
            st.subheader("L/Cubic Meter by Site")
            efficiency_html = f"""
            <div id="efficiency" style="height: 400px;"></div>
            <script src="https://code.highcharts.com/highcharts.js"></script>
            <script>
            document.addEventListener('DOMContentLoaded', function () {{
                Highcharts.chart('efficiency', {{
                    chart: {{ type: 'column' }},
                    title: {{ text: 'L/Cubic Meter by Site' }},
                    xAxis: {{ categories: {filtered_data['Site_Name'].tolist()} }},
                    yAxis: {{ title: {{ text: 'L/Cubic Meter' }} }},
                    plotOptions: {{
                        column: {{
                            dataLabels: {{
                                enabled: true,
                                formatter: function() {{
                                    return this.y.toFixed(2);  // Format the label to show two decimal places
                                }}
                            }}
                        }}
                    }},
                    series: [{{
                        name: 'L/Cubic Meter',
                        data: {filtered_data['L_Cubic_Meter'].tolist()}
                    }}]
                }});
            }});
            </script>
            """
            st.components.v1.html(efficiency_html, height=400)

        # Remarks section
        st.subheader("Remarks")
        remarks = filtered_data.dropna(subset=['Remarks'])
        if not remarks.empty:
            for _, row in remarks.iterrows():
                st.write(f"**{row['Site_Name']} ({row['Detail_Type']})**: {row['Remarks']}")
        else:
            st.write("No remarks available for this date.")

        
        # Supply vs Output Analysis
        st.subheader("Supply vs Output Analysis")
        st.header("Aggregate Output vs Supply Total Analysis")
        st.subheader("Filter by Time Period")
        time_period = st.radio("Select Time Period", options=["Daily", "Weekly", "Monthly", "Custom Time Frame"])

        # Prepare data for graph
        filtered_data_site = data.copy()
        if time_period == "Daily":
            filtered_data_site = filtered_data_site[filtered_data_site['Date'] >= (datetime.now() - timedelta(days=15))]
        elif time_period == "Weekly":
            filtered_data_site['Week'] = filtered_data_site['Date'].dt.to_period('W').apply(lambda r: r.start_time)
            filtered_data_site = filtered_data_site.groupby('Week').agg({
                'Aggregate_Output': 'sum',
                'Supply_Total': 'sum',
                'Supply_vs_Output': 'sum',
                'RBM_vs_Output': 'sum',
                'RBM': 'sum',   # <--- add this line
                'Diesel_Consumption': 'sum',  # <--- and others if needed
                'Running Hours': 'sum',
                'Maintainance Hours': 'sum',
                'Actual Working Hours': 'sum',
                'Site_Name': lambda x: ', '.join(x)
            }).reset_index()
        elif time_period == "Monthly":
            filtered_data_site['Month'] = filtered_data_site['Date'].dt.to_period('M').apply(lambda r: r.start_time)
            filtered_data_site = filtered_data_site.groupby('Month').agg({
                'Aggregate_Output': 'sum',
                'Supply_Total': 'sum',
                'Supply_vs_Output': 'sum',
                'RBM_vs_Output': 'sum',
                'RBM': 'sum',   # <--- add this line
                'Diesel_Consumption': 'sum',  # <--- and others if needed
                'Running Hours': 'sum',
                'Maintainance Hours': 'sum',
                'Actual Working Hours': 'sum',
                'Site_Name': lambda x: ', '.join(x)
            }).reset_index()
        elif time_period == "Custom Time Frame":
            st.write("Select a custom time frame:")
            custom_start_date = st.date_input("Start Date", value=data['Date'].min().date())
            custom_end_date = st.date_input("End Date", value=data['Date'].max().date())
            custom_start_date = pd.to_datetime(custom_start_date)
            custom_end_date = pd.to_datetime(custom_end_date)
            filtered_data_site = filtered_data_site[(filtered_data_site['Date'] >= custom_start_date) & (filtered_data_site['Date'] <= custom_end_date)]

        # Filter for Site Selection
        st.subheader("Select a Site")
        site_options = data['Site_Name'].dropna().unique()
        selected_site = st.selectbox("Choose a Site", options=["All"] + list(site_options))

        # Apply site filter
        if selected_site != "All":
            filtered_data_site = filtered_data_site[filtered_data_site['Site_Name'].str.contains(selected_site, na=False)]

        # Calculate total values for detailed calculation
        total_aggregate_output = filtered_data_site['Aggregate_Output'].sum()
        total_supply_total = filtered_data_site['Supply_Total'].sum()
        total_supply_vs_output = total_aggregate_output - total_supply_total

        #calculation for RBM
        total_RBM_total = filtered_data_site['RBM'].sum()
        total_RBM_vs_output = total_RBM_total - total_aggregate_output

        #calculation of diesel 
        total_diesel = filtered_data_site['Diesel_Consumption'].sum()

        #running hours
        total_running_hours = filtered_data_site['Running Hours'].sum()

        #Maintainance Hours
        total_maintainance_hours = filtered_data_site['Maintainance Hours'].sum()

        #Actual Working Hours
        total_actual_working_hours = filtered_data_site['Actual Working Hours'].sum()

        col3,col4 = st.columns(2)

        with col3:
            # Handle empty filtered data
            if filtered_data_site.empty:
                st.warning("No data available for the selected site and time period.")
            else:
                # Graph for Supply_vs_Output
                categories = (
                    filtered_data_site.iloc[:, 0].dt.strftime('%Y-%m-%d').tolist()
                    if time_period in ["Daily", "Custom Time Frame"] else
                    filtered_data_site.iloc[:, 0].dt.strftime('%Y-%m').tolist()
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
                        plotOptions: {{
                        column: {{
                            dataLabels: {{
                                enabled: true,
                                formatter: function() {{
                                    return this.y.toFixed(2);  // Format the label to show two decimal places
                                }}
                            }}
                        }}
                    }},
                        series: [{{
                            name: 'Output - Supply',
                            data: {filtered_data_site['Supply_vs_Output'].tolist()}
                        }}]
                    }});
                }});</script>"""
                st.components.v1.html(graph_html, height=600)
                # Display full calculation below the graph
                st.markdown(f"""
                ### Detailed Calculation:
                - **Total Aggregate Output**: {total_aggregate_output:.2f}
                - **Total Supply Total**: {total_supply_total:.2f}
                - **Total Submission (Output - Supply)**: {total_supply_vs_output:.2f}
                """)

            with col4:
                # Handle empty filtered data
                if filtered_data_site.empty:
                    st.warning("No data available for the selected site and time period.")
                else:
                    # Graph for RBM_vs_Output
                    categories = (
                        filtered_data_site.iloc[:, 0].dt.strftime('%Y-%m-%d').tolist()
                        if time_period in ["Daily", "Custom Time Frame"] else
                        filtered_data_site.iloc[:, 0].dt.strftime('%Y-%m').tolist()
                    )
                    graph_html = f"""
                    <div id="RBM-vs-output" style="height: 500px;"></div>
                    <script src="https://code.highcharts.com/highcharts.js"></script>
                    <script>
                    document.addEventListener('DOMContentLoaded', function () {{
                        Highcharts.chart('RBM-vs-output', {{
                            chart: {{ type: 'column' }},
                            title: {{ text: 'RBM vs Output (Difference: RBM - Output)' }},
                            xAxis: {{
                                categories: {categories},
                                title: {{ text: 'Date' }}
                            }},
                            yAxis: {{
                                title: {{ text: 'RBM - Output' }},
                                plotLines: [{{
                                    value: 0,
                                    color: 'red',
                                    width: 2,
                                    dashStyle: 'ShortDash',
                                    label: {{ text: 'Zero Line' }}
                                }}]
                            }},
                            plotOptions: {{
                        column: {{
                            dataLabels: {{
                                enabled: true,
                                formatter: function() {{
                                    return this.y.toFixed(2);  // Format the label to show two decimal places
                                }}
                            }}
                        }}
                    }},
                            series: [{{
                                name: 'RBM - Output',
                                data: {filtered_data_site['RBM_vs_Output'].tolist()}
                            }}]
                        }});
                    }});</script>"""
                    st.components.v1.html(graph_html, height=600)

                    # Display full calculation below the graph
                    st.markdown(f"""
                    ### Detailed Calculation:
                    - **Total Aggregate Output**: {total_aggregate_output:.2f}
                    - **Total RBM Total**: {total_RBM_total:.2f}
                    - **Total Submission (RBM - Output)**: {total_RBM_vs_output:.2f}
                    - **Total Diesel**: {total_diesel:.2f}
                    - **Total Running Hours**: {total_running_hours:.2f}
                    - **Total Maintainance Hours**: {total_maintainance_hours:.2f}
                    - **Total Actual Working Hours**: {total_actual_working_hours:.2f}
                    """)
    else:
        st.warning("No date selected.")
