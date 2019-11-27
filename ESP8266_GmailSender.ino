#include "ESP8266WiFi.h"
#include "Gsender.h"
#pragma region Globals
const char* ssid = "redmi6";                           // WIFI network name
const char* password = "12345678";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000; // If not connected wait time to try again
#pragma endregion Globals
const int pinApi = D0;
const int pinAlarm = D2;
const int redLED = D8;
const int smokeA0 = A0;
// inialisasi variabel data
int data;
int dataAsap;
float datasuhu;
//Nilai threshold
int sensorThres = 90;

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);  
        Serial.println(nSSID);
    } else {
        WiFi.begin(ssid, password);
        Serial.println(ssid);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void setup()
{
  // inialisasi status I/O pin
 pinMode(pinApi, INPUT); // pin sebagai input
 pinMode(smokeA0, INPUT); // pin sebagai input
 pinMode(pinAlarm, OUTPUT); // pin sebagai output
 pinMode(redLED, OUTPUT);
     connection_state = WiFiConnect();
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect
    Serial.begin(115200);
    
}

void loop()
{
  // variabel data adalah hasil dari pembacaan sensor
 // berupa logic LOW/HIGH
 data = digitalRead(pinApi);
 //datasuhu = analogRead(lm35);
 //datasuhu = data*0.488;
 int analogSensor = analogRead(smokeA0);
 int analogSensor1= analogRead(pinApi);
 //float lmvalue = analogRead(lm35);
 //float tempr = (lmvalue * 500)/1023; 
 Serial.print("Pin SmokeA0: ");
 Serial.println(analogSensor);
 Serial.print("Pin Api: ");
 Serial.println(analogSensor1);
 //Serial.print("Pin Suhu: ");
 //Serial.println(tempr);


 // jika data pada sensor API LOW
 if (data == LOW )
 {
 // alarm dinyalakan
// digitalWrite(pinAlarm, HIGH);
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Alarm kebakaran!";
 gsender->Subject(subject)->Send("rahardianjordie@gmail.com", "KEBAKARAN!"); 
 Serial.println("Message send.");

 }

 else if (analogSensor > sensorThres)
 {
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Pertanda Asap!";
 gsender->Subject(subject)->Send("rahardianjordie@gmail.com", "ADA ASEP!"); 
 Serial.println("Message send.");
 }

 if (data == LOW )
 {
 // alarm dinyalakan
// digitalWrite(pinAlarm, HIGH);
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Alarm kebakaran!";
 gsender->Subject(subject)->Send("hadirivaldi26@gmail.com", "KEBAKARAN!"); 
 Serial.println("Message send.");

 }

 else if (analogSensor > sensorThres)
 {
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Pertanda Asap!";
 gsender->Subject(subject)->Send("hadirivaldi26@gmail.com", "ADA ASEP!"); 
 Serial.println("Message send.");
 }

  if (data == LOW )
 {
 // alarm dinyalakan
// digitalWrite(pinAlarm, HIGH);
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Alarm kebakaran!";
 gsender->Subject(subject)->Send("renaldispt123@gmail.com", "KEBAKARAN!"); 
 Serial.println("Message send.");

 }

 else if (analogSensor > sensorThres)
 {
 digitalWrite(redLED, HIGH);
 tone(pinAlarm,1000,200);
 delay(100);
 Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
 String subject = "Pertanda Asap!";
 gsender->Subject(subject)->Send("renaldispt123@gmail.com", "ADA ASEP!"); 
 Serial.println("Message send.");
 }

 // jika data tidak bernilai logic LOW
 else
 {
  //Lampu Dimatikan
  digitalWrite(redLED, LOW);
 // alarm dimatikan
 digitalWrite(pinAlarm, LOW);
 delay(100);
 }
  }
