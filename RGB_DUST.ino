/*
 DUST SENSOR DISPLAY WITH RGB LED
*/

#include <Adafruit_NeoPixel.h>
 
#define PIN 15
#define NUMPIXELS 3 

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


#define RXD2 16
#define TXD2 17

int arr[32]={0};
int value = 0;
int inc=0;
int dust=0;


void RGB_LED(int dust_val){
int X=0;
int Y=0;
int Z=0;
pixels.clear(); // Set all pixel colors to 'off'


 if(dust_val>=0 && dust_val<=150){

  X=map(dust_val,0,150,0,255);
  Y=map(dust_val,0,150,255,0);
  Z=0;
  
  
  }

  if(dust_val>150){
    
    X=255;
    Y=0;
    Z=0;
    }
 
    
     

  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...


    pixels.setPixelColor(i, pixels.Color(X, Y, Z));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(200); // Pause before next pass through loop
  }
    
    
  
  

  
  }



void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
 pixels.begin(); // This initializes the NeoPixel library.
}

void loop() { //Choose Serial1 or Serial2 as required
inc=0;
 
  while (Serial2.available()) {
    Serial.println("hi****************************************");
        while(inc<32){
   value = Serial2.read();
    Serial.println(value);
    arr[inc]=value;
    
   
    inc++;
    }
    dust=arr[12]<<8|arr[13];
    Serial.println("");
 Serial.print("DUST :");
  Serial.println(dust);
  }
  RGB_LED(dust);
}
