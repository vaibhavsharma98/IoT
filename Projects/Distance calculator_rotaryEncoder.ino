#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int val; 
int PinCLK = 4;
int PinDT = 5;
int PinSW = 0;
static long encoderPos = -1;     
int PinCLKLast = LOW;
int nbPas = 100;                 
int n = LOW;
 #define outputA 10
 #define outputB 11

 #define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
 int counter = 0;
 int angle = 0; 
 int aState;
 int aLastState; 
 int a=1; 
 void testdrawchar(void);
void setup() {
  // Sets the two pins as Outputs
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
   pinMode (PinCLK,INPUT);
  pinMode (PinDT,INPUT);
  pinMode (PinSW,INPUT);
  Serial.begin (9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);
  aState = digitalRead(outputA);
}
void loop() {
   if (!(digitalRead(PinSW))) {      
     encoderPos = 0;
   }
   n = digitalRead(PinCLK);
   
   if ((PinCLKLast == LOW) && (n == HIGH)) {
     
     if (digitalRead(PinDT) == LOW) {
       encoderPos--;
       if ( encoderPos < 0 ) {
         encoderPos = nbPas;
       }
     } else {
       encoderPos++;
       if ( encoderPos > ( nbPas - 1 ) ) {
         encoderPos = 0;
       }
     }
     Serial.print (encoderPos); 
      display.clearDisplay();
  testdrawchar();
     Serial.println(counter);
     display.println("Distance: ");
     display.print(encoderPos);
     display.println("  cm");
  display.display();
  delay(100);
   } 
   PinCLKLast = n;

   }
void testdrawchar(void)
{
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(5, 5);     // Start at top-left corner
}
