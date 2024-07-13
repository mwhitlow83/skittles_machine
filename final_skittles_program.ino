//EML 4804L - Mechatronic Systems Lab 
//Programed by Matthew Whitlow
//Open Design project "Taste the Rainbow"

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h> 

Servo next;         //servo is attached to mechanism that allows one skittle at a time to pass in front of color sensor
Servo bin;          //servo is attached to a slide that directs skittle to selected coler bin.

//identifies frequency from sensor. sorted blue, red, green and clear
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); 

const byte interruptPin = 2;        //button input to start skittle sorting process 
volatile byte state = LOW;

int redled = 12; //red led
int greenled = 8; //green led

void setup() {
  
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  
    next.attach(9);
    bin.attach(10);
    
       Serial.begin(9600);
       Serial.println("Taste the Rainbow!");

     if (tcs.begin()) {
        digitalWrite(greenled, HIGH);
        Serial.println("Clear Blue Skys");
       }
        
      else {
         digitalWrite(redled, HIGH);
         Serial.println("Cloudy Outside, No Rainbow");
        while (1); // halt!
      }
  
  pinMode(interruptPin, INPUT_PULLUP); //at anytime process can be stopped with button press
  attachInterrupt(digitalPinToInterrupt(interruptPin), getColor, CHANGE);
   
   bin.write(87); //position servos on startup
   next.write(91);      
}

void loop(){
  
  int i=0;
  int color=0;
  int off=1;
   
      while (state == 1){     //starts processing color
    
          digitalWrite(greenled, HIGH);
          digitalWrite(redled, LOW);
  
          uint16_t clear, red, green, blue;

          delay(700);  //allow time for color processing  
  
          tcs.getRawData(&red, &green, &blue, &clear);

                if((red<9728)&&(red>8400)&&(green<10774)&&(green>10100)&&(blue<10281)&&(blue>9400)){  //conditions for red skittle
                    Serial.print("red\n");
                          color=1;
                    }
  
                else if((red<9570)&&(red>8500)&&(green<14440)&&(green>13000)&&(blue<11217)&&(blue>10200)){   //conditions for green skittle
                    Serial.print("green\n");
                          color=2;
                    }

                else if((red<19000)&&(red>13900)&&(green<18800)&&(green>15300)&&(blue<12700)&&(blue>10900)){ //conditions for yellow skittle
                    Serial.print("yellow\n");
                          color=3;
                    }
    
                else if ((red<8200)&&(red>7100)&&(green<10900)&&(green>10000)&&(blue<10300)&&(blue>9200)){ //conditions for purple skittle
                    Serial.print("purple\n");
                          color=4;
                    }
    
                else if((red<15600)&&(red>9126)&&(green<13100)&&(green>10800)&&(blue<11400)&&(blue>9900)){
                     Serial.print("orange\n");                                                   // conditions forced for orange skittle
                          color=5;
                    }

                else if((red<8200)&&(red>8000)&&(green<11100)&&(green>11000)&&(blue<10300)&&(blue>10100)){
                     Serial.print("out of skittles\n");
                          off=0;
 
                              while((off==0)&&(state==1)){  //flashes red led for user to reload
                                        
                                          bin.write(90);
                                        digitalWrite(greenled, LOW);
                                        digitalWrite(redled, HIGH);
                                          delay(500);
                                        digitalWrite(redled, LOW);
                                          delay(500);
                                  }
                         
                    }

   
  Serial.print("C:"); Serial.print(clear);             //print used for determining skittle colors
  Serial.print("\t\tR:"); Serial.print(red);
  Serial.print("\t\tG:"); Serial.print(green);
  Serial.print("\t\tB:"); Serial.print(blue);
  Serial.println();
  Serial.println();
                                   
 state=0;
 
        }   
        
            while(color!=0){             //directs skittle to bin
    
                  if (color==1){               // bin locations
                         bin.write(0);}
    
                  else if (color==2){
                        bin.write(45);}

                  else if (color==3){
                        bin.write(87);}

                  else if (color==4){
                        bin.write(133);}

                  else if (color==5){   //orange bin
                        bin.write(176);}
      
                    delay(1200);  //allow time for servo to reach bin destinatin
        
            state=off; //skips servo cycle if no skittles are in shoot
   
        next.write(115);         //servo postion to drop skittle on to slide
          delay(500);
        next.write(91);          //servo position to load next skittle in front of color sensor
          delay(200);
        
        color=0;                 //reset color for next 
        state=1;                 //process next skittle
   
       }
}     
  void getColor() {     //interupt function changes state at anytime button is pressed
  state = !state;
}

