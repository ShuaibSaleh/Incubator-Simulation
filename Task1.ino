

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor 



#define DHTTYPE    DHT11     // DHT 11




DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


///////////////////////////////////////////
int ldr = A0;
float ldrValue = 0.0;
float lightIntenstiy = 0.0;
int fan = 6 ;
int led1 = 7 ; 
int led2 = 8 ; 
int led3 = 9 ; 




//////////////////////////////////////////////////////







void setup() {
  Serial.begin(9600);

  pinMode(ldr , INPUT) ;
  pinMode(fan, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  
  
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  
  

  

  
  /////////////////////////////////////////////////////////
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

    // around 36 C
    if(event.temperature > 23.4 || event.temperature < 22.0)
    {
      digitalWrite(led2,HIGH);
      if(event.temperature > 23.4)
      {
        
        digitalWrite(fan,HIGH);
        }
        else{
          digitalWrite(fan,LOW);
          }

       
      
     }
     else{
      digitalWrite(led2,LOW);
      digitalWrite(fan,LOW);
      }
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    //from 40 to 60 percect
    if(event.relative_humidity > 6 || event.relative_humidity < 5)
    {
      digitalWrite(led3,HIGH);
      
     }
     else{
      digitalWrite(led3,LOW);
      }
  }
////////////////////////////////////////////////////////////////////////////////////////

  ldrValue = (5*analogRead(ldr))/1024;//Reads the Value of LDR(light).
  lightIntenstiy = ( ( ( 2500 / ldrValue ) - 500 ) / 1.6 );
  
  //Serial.print("Ldr value :");//Prints the Light Intenstiy to Serial Monitor.
  //Serial.println(ldrValue);
  Serial.println("Light Intenstiy :");//Prints the Light Intenstiy to Serial Monitor.
  Serial.print(lightIntenstiy);
  Serial.println("   Lux");
  

   
  
  if(lightIntenstiy > 600 || lightIntenstiy < 10 )
  {
    digitalWrite(led1,HIGH);//Makes the LED glow in high or low light intensity.
  }
  else
  {
    digitalWrite(led1,LOW);//Turns the LED OFF in the desire range of light intensity.
  }
}
