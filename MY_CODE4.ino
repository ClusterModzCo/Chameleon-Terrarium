#include "DHT.h"
#include "RTClib.h"
#include "Nextion.h"

int WaterLevelBar;
                    //----- WATER LEVEL SENSOR LED 
int red=A7;
int green=A8;
int blue=A9;
                    //---- DIGITAL PINS ---
#define DHTPIN A0                           // sensor pin 
#define DHTTYPE DHT22                       // define sensor type
#define WATERFALL 6                         // constant unless turned off BLUE LED 12V PUMP
#define FAN 9                               // fan pin 

                    //---- ANALOG PINS ---
DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;                             // pins A4 A5

char daysOfTheWeek[7][12] = {" Sunday ", " Monday ", " Tuesday ", " Wednesday ", " Thursday ", " Friday ", " Saturday "};


//-----------------------------waterfall pin 8 coding on and off-----------------------
void DataFromNextionWATERFALL(String data_from_display) {
  if(data_from_display == "WATERFALLON") {                         //Actions for ON command
    Serial.println("ON command recieved");
    digitalWrite(8, HIGH);
  }
  
  if(data_from_display == "WATERFALLOFF") {                        //Actions for OFF command
    Serial.println("OFF command recieved");
    digitalWrite(8, LOW);
  }
}

//-----------------------------wfan pin 9 coding on and off-----------------------

void DataFromNextionFAN(String data_from_display) {
  if(data_from_display == "FANON") {                         //Actions for ON command
    Serial.println("ON command recieved");
    digitalWrite(9, HIGH);
  }
  
  if(data_from_display == "FANOFF") {                        //Actions for OFF command
    Serial.println("OFF command recieved");
    digitalWrite(9, LOW);
  }
}

void setup() {
    Serial.begin(115200);              //-------------The default baud rate of the Nextion TFT is 9600.
    Serial1.begin(9600);
    dht.begin();

    pinMode(8, OUTPUT);               //------------------------- Waterfall relay pin D8
    pinMode(9, OUTPUT);               //------------------------- Fan relay pin D9
    
                    //--------WATERFALL LEVEL LED ------------------------
    pinMode (red,OUTPUT);             //------------------------- Waterfall level pin A7
    pinMode (green,OUTPUT);           //------------------------- Waterfall level pin A8
    pinMode (blue,OUTPUT);            //------------------------- Waterfall level pin A9   

  if (! rtc.begin()) {
    Serial.println("NO RTC3231");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__TIME__), F(__DATE__)));
  }
                                  //----------------------Define pin as OUTPUT
  pinMode (WATERFALL,OUTPUT);
}

void loop() {
    if(Serial1.available()) {                                       //Check For Recieved Data
    String data_from_display = "";                                  //Declare Empty String
    delay(30);                                                      //Make Sure all data is recieved
    while(Serial1.available()){               
      data_from_display += char(Serial1.read());                     //Place recieved data in string

    //Serial Monitor Send
    Serial.print("Recieved Data: ");    Serial.print(data_from_display);    Serial.println();
    DataFromNextionWATERFALL(data_from_display);                             //Function Switch For Data
    DataFromNextionFAN(data_from_display);
  }


  void readDHT22();
  float h = dht.readHumidity();             // Read the humidity in %:
  float f = dht.readTemperature(true);      // Read the temperature as Fahrenheit:

  if (isnan(h) || isnan(f)) {          // Check if any reads failed and exit early (to try again):
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hif = dht.computeHeatIndex(f, h);    // Compute heat index in Fahrenheit (default):
  float hic = dht.computeHeatIndex(h, false);
  
  Serial.print("Humidity: ");  Serial.print(h);  Serial.print(" % ");
  Serial.print("Temperature: ");  Serial.print(f);  Serial.print(" \xC2\xB0");  Serial.print("F ");  
  Serial.print("Heat index: ");  Serial.print(hif);  Serial.print(" \xC2\xB0");  Serial.println("F");

  void readRTC(); {
  DateTime now = rtc.now();

  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  Serial.print(now.hour(), DEC); Serial.print(':');
  Serial.print(now.minute(), DEC); Serial.print(':');  Serial.println(now.second(), DEC);
  }
 
void readWATERLEVEL();  {
  int value = analogRead(A1);   // read the input on analog pin A1:
  Serial.print ("Water Level  ");

  if (value > 550) {
    Serial.println("Full");    digitalWrite (red,HIGH);    digitalWrite(green,LOW);    digitalWrite(blue,LOW);
    }
    
  else if ((value > 500) && (value <= 600)) {
    Serial.println("Good");    digitalWrite (green,HIGH);    digitalWrite (red,LOW);    digitalWrite(blue,LOW);
    }
    
  else  {
    Serial.println("Refill");    digitalWrite (blue,HIGH);    digitalWrite (red,LOW);    digitalWrite (green,LOW);
  }
}
    
void readHumiditynext(); {
    Serial1.print("n1.val=" + String(Serial.print(h)));       //humidity value
    Serial1.write(0xFF);    Serial1.write(0xFF);    Serial1.write(0xFF);
}
    //---------------------------------------------------------------------------- 
    
void readWaterlevelnext(); {    
    Serial1.print("j0.val=" + String(WaterLevelBar));         //Progress Bar Setting pin A1 lvl sensor
    Serial1.write(0xFF);    Serial1.write(0xFF);    Serial1.write(0xFF);
    }
  }
}
