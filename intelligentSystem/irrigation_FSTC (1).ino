
/************************************************************************************
 *  Preferences--> Aditional boards Manager URLs : 
 *  For ESP32:
 *  https://dl.espressif.com/dl/package_esp32_index.json
 *  https://blynk.cloud/external/api/logEvent?token=YourAuthToken&code=hello for loging the events using rest API
 *  You can send only 100 events per devices per day
    When the limit is reached you'll see the notification on the UI in the Device Timeline section
    The maximum description length for the event is 300 chars
 *  *********************************************************************************/
//Your blynk template id
#define BLYNK_TEMPLATE_ID ""
//Your blynk device name
#define BLYNK_DEVICE_NAME ""
//Your blynk auth_token
#define BLYNK_AUTH_TOKEN ""


#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <Blynk.h>
 //#include <NewPing.h>
 //#include <DHTesp.h>
 //#include <BlynkSimpleEsp32.h>
#include<DHT.h>
#define DHTPIN 32
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int Soil_Moisture=25;
int motion_sensor=33;
int motion_data=0;


 BLYNK_WRITE(V4)
{
  int pinvalue = param.asInt();
  digitalWrite(13,pinvalue);
}  

 BLYNK_WRITE(V5)
{
  int pinvalue = param.asInt();
  digitalWrite(27,pinvalue);
} 

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "";  // type your wifi name
char pass[] = "";  // type your wifi password

BlynkTimer timer;

void sendSensor()
{
  //Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  int moisture_sensor= analogRead(Soil_Moisture);

 int motion_data=digitalRead(motion_sensor);
 Serial.println(motion_data);

//please don't send more than 10 values per second.
 Blynk.virtualWrite(V3, motion_data);
 delay(300);
  
  // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // You can send any value at any time.
  // Please don't send more than 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V6, h);
    Blynk.virtualWrite(V1, Soil_Moisture);
    delay(500);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("Humidity : ");
    Serial.print("h");

   /* this is the conditional statement, but its optional in this project.
    *  if (Soil_Moisture > 2500) {
    *  Blynk.LogEvent("i am testing blynk event man");
    *  }
    */
}
void setup()
{   
  
   Serial.begin(9600);
   pinMode (Soil_Moisture, INPUT);
   pinMode (motion_sensor, INPUT);
   pinMode (13,OUTPUT);
   pinMode (27,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
