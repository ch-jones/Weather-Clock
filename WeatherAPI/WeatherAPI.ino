
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LedControl.h>   //include LEDControl library
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int Position = 0;


const char* ssid     = "Blayne";                 // SSID of local network
const char* password = "Blayno77";                    // Password on network
String APIKEY = "2ea52ea69bb86a52c1b559ddfd447b2b";                                 
String CityID = "4839921";                                 //Your City ID

//Light control pinout
int r = 0;
int b = 1;
int w = 2;
//PWM Settings
int rValue = 0;
int bValue = 0;
int wValue = 0;


WiFiClient client;
char servername[]="api.openweathermap.org";              // remote server we will connect to
String result;

int  counter = 60;                                      

String weatherDescription ="";
String weatherLocation = "";
String Country;
String Weather;
float Temperature;
float Humidity;
float Pressure;
float Sunset;
float Sunrise;
float CurrentTime;

//Servo


//Matrix Setup
unsigned long delaytime=500;    //set delay between display updates

int DIN = 3;   // DIN pin of MAX7219 module
int CLK = 4;   // CLK pin of MAX7219 module
int CS = 5;    // CS pin of MAX7219 module
int maxInUse = 1;
LedControl lc2=LedControl(DIN,CLK,CS,1);


void setup() {
  Serial.begin(115200);
 //LED Matrix 2
  lc2.shutdown(0,false);  //Wake up MAX7219 (in power-saving mode on startup)
  lc2.setIntensity(0,8);  //Set the brightness
  lc2.clearDisplay(0);    //Clear the display

//WiFi
 // Serial.println("   Connecting");  
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  
             while (WiFi.status() != WL_CONNECTED) 
            {
            delay(500);
            //lcd.setCursor(cursorPosition,2); 
            Serial.println(".");
            }
  Serial.println("Connected");
  delay(1000);
}

void loop() {
//DataIntake
    if(counter == 60)  //Get new data every 10 minutes
    {
      counter = 0;
      displayGettingData();
      delay(1000);
      getWeatherData();
    }else
    {
      counter++;
      displayWeather(weatherLocation,weatherDescription);
      delay(5000);
      //displayConditions(Temperature,Humidity,Pressure);
     // delay(5000);
    }
  //Visuals
   if (weatherDescription = "Clear") {
    sunny();
  } else if (weatherDescription = "Snow") {
    snow();
  } else if (weatherDescription = "Clouds") {
    cloud();
  } else {
    rain();
  }
  colourSet();
}

void getWeatherData()   //client function to send/receive GET request data.
{
  if (client.connect(servername, 80))   
          { //starts client connection, checks for connection
          client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&APPID="+APIKEY);
          client.println("Host: api.openweathermap.org");
          client.println("User-Agent: ArduinoWiFi/1.1");
          client.println("Connection: close");
          client.println();
          } 
  else {
         Serial.println("connection failed");        //error message if no client connect
          Serial.println();
       }

  while(client.connected() && !client.available()) 
  delay(1);                                          //waits for data
  while (client.connected() || client.available())    
       {                                             //connected or data available
         char c = client.read();                     //gets byte from ethernet buffer
         result = result+c;
       }

client.stop();                                      //stop client
result.replace('[', ' ');
result.replace(']', ' ');
Serial.println(result);
char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';
StaticJsonBuffer<1024> json_buf;

JsonObject &root = json_buf.parseObject(jsonArray);

if (!root.success())
  {
    Serial.println("parseObject() failed");
  }

String location = root["name"];
String country = root["sys"]["country"];
float sunrise = root["sys"]["sunrise"];
float sunset = root["sys"]["sunset"];
float currentTime = root["dt"];



float temperature = root["main"]["temp"];
float temperatureMin = root["main"]["temp_min"];
float temperatureMax = root["main"]["temp_max"];


float humidity = root["main"]["humidity"];
String weather = root["weather"]["main"];
String description = root["weather"]["description"];
float pressure = root["main"]["pressure"];

weatherDescription = description;
weatherLocation = location;
Weather= weather;
Sunrise= sunrise;
Sunset= sunset;
CurrentTime= currentTime;
Country = country;
Temperature = temperature;
Humidity = humidity;
Pressure = pressure;
Position = round(map(CurrentTime,Sunrise,Sunset,0,180));
}

void displayWeather(String location,String description)
{
   Serial.println(" ");
  //Serial.println(location);
  Serial.println(Weather);
}

void displayConditions(float Temperature,float Humidity, float Pressure)
{
//Temperature
 Serial.println(" ");
 Serial.println("Temperature Data"); 
 Serial.print("T:"); 
 Serial.print(Temperature,1);
 Serial.print("C "); 
 Serial.println(" ");
 Serial.println("Humidity Data");                      
 Serial.print(" H:");                       //Printing Humidity
 Serial.print(Humidity,0);
 Serial.print("%"); 
 
  delay(2000);
}

void displayGettingData()
{
  Serial.println("Getting data");
}
//Lighting
//Set the colour of the LED
void colourSet() {
    if ((Position>0 && Position< 26)||(Position>155 && Position<= 180)){
      riseSet();
    } else if ((Position>=26 && Position< 52)||(Position>129 && Position<=155)){
      risingSetting();
    } else if ((Position>=52 && Position< 77)||(Position>103 && Position<= 129)){
      day();
    } else if (Position>=77 && Position<= 103){
      midday();
    } else {
      twilight();
    }
    analogWrite(r,rValue);
    analogWrite(w,wValue);
    analogWrite(b,bValue);
}

//Colour choices
void twilight(){
  rValue=248;
  wValue=0;
  bValue=157;
}

void riseSet(){
  rValue=255;
  wValue=10;
  bValue=10;
}
 
void risingSetting(){
  rValue=255;
  wValue=50;
  bValue=10;
}
 
void day(){
  rValue=50;
  wValue=200;
  bValue=0;
}

void midday(){
  rValue=0;
  wValue=255;
  bValue=20;
}



// Matrix Characters
void sunny() {
  //Byte data for icons
  byte a[8] = {
    B10010001,
    B01000010,
    B00011000,
    B00111101,
    B10111100,
    B00011000,
    B01000010,
    B10001001
  };

  //Display icon with delay
  lc2.setRow(0,0,a[0]);
  lc2.setRow(0,1,a[1]);
  lc2.setRow(0,2,a[2]);
  lc2.setRow(0,3,a[3]);
  lc2.setRow(0,4,a[4]);
  lc2.setRow(0,5,a[5]);
  lc2.setRow(0,6,a[6]);
  lc2.setRow(0,7,a[7]);
  lc2.setRow(0,8,a[8]);
  delay(delaytime);
 }

 void snow() {
  //Byte data for icons
  byte a[8] = {
    B10011001,
    B01011010,
    B00111100,
    B11100111,
    B11100111,
    B00111100,
    B01011010,
    B10011001
  };

  //Display icon with delay
  lc2.setRow(0,0,a[0]);
  lc2.setRow(0,1,a[1]);
  lc2.setRow(0,2,a[2]);
  lc2.setRow(0,3,a[3]);
  lc2.setRow(0,4,a[4]);
  lc2.setRow(0,5,a[5]);
  lc2.setRow(0,6,a[6]);
  lc2.setRow(0,7,a[7]);
  lc2.setRow(0,8,a[8]);
  delay(delaytime);
 }

void cloud() {
  //Byte data for icons
  byte a[8] = {
    B00000000,
    B00000000,
    B00010100,
    B00111110,
    B01111111,
    B00000000,
    B00000000,
    B00000000
  };

  //Display icon with delay
  lc2.setRow(0,0,a[0]);
  lc2.setRow(0,1,a[1]);
  lc2.setRow(0,2,a[2]);
  lc2.setRow(0,3,a[3]);
  lc2.setRow(0,4,a[4]);
  lc2.setRow(0,5,a[5]);
  lc2.setRow(0,6,a[6]);
  lc2.setRow(0,7,a[7]);
  lc2.setRow(0,8,a[8]);
  delay(delaytime);
 }

void rain() {
  //Byte data for icons
  byte a[8] = {
    B00101000,
    B01111100,
    B11111110,
    B00010000,
    B00100100,
    B10001000,
    B00100000,
    B01000000
  };

  //Display icon with delay
  lc2.setRow(0,0,a[0]);
  lc2.setRow(0,1,a[1]);
  lc2.setRow(0,2,a[2]);
  lc2.setRow(0,3,a[3]);
  lc2.setRow(0,4,a[4]);
  lc2.setRow(0,5,a[5]);
  lc2.setRow(0,6,a[6]);
  lc2.setRow(0,7,a[7]);
  lc2.setRow(0,8,a[8]);
  delay(delaytime);
 }


