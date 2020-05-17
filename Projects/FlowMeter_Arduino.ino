volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_min; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
unsigned long totalLitre = 0,totalMins=0;
void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}
int avgLitre =0, avgCount=0;
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour

   if(currentTime >= (cloopTime + 3000)) // measure after 2500 msec
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_min = (flow_frequency * 1 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
       Serial.print( "  count "  ); Serial.print(avgCount);
      Serial.print( "  time :  "  ); Serial.print(currentTime/1000);
       Serial.print( "  water :  "  );
      Serial.print(l_min, DEC); // Print litres/hour
      Serial.println(" L/min");
      avgCount++;
      avgLitre += l_min; 
      if (avgCount >40 ) { // one minute elaspsed
        Serial.print( " time :  "  );Serial.print(currentTime);
        Serial.print( " Avg water :  "  );
        Serial.print(avgLitre/avgCount, DEC); // Print litres/hour
        Serial.print(" Litre in last one minute  ");
        // cumulative total print 
        totalLitre +=( avgLitre/avgCount);
        totalMins++;
        Serial.print( "     " ) ; 
        Serial.print(totalLitre, DEC);  
        Serial.print(" Litre in last " );
        Serial.print(totalMins, DEC); 
        Serial.println(" minutes");
        avgLitre =0; avgCount=0;
      }
   }
   
}
