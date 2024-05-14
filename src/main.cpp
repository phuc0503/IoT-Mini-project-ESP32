// #include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

enum DeviceType {
    LED,  
    TV,
    AC,   //* air conditioner
    SP    //* speaker
};
// put function declarations here:
void sendData(float temperature, float humidity, int light);
void receiveData();
void controlDevices(DeviceType type, int status);
float getAverageTemperature();
float getAverageHumidity();
int getAverageLight();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);   //* Initialize serial communication
  SerialPort.begin(9600, SERIAL_8N1, 16, 17); //* Initialize serial port communication
  Wire.begin();
  Serial.println(F("DHT11 Test!!"));
  dht.begin();
  Serial.println(F("BH1750 Test!!"));
  lightMeter.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  //* Wait a few seconds between measurements.
  receiveData();

  delay(1000);
  timer++;

  if (timer == 10) {
    float humidity = getAverageHumidity();
    float temperature = getAverageTemperature();
    int light = getAverageLight();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }   

    // !1:T:30##!2:H:47##
    Serial.print(F("Humidity: "));
    Serial.print(myHome.getHumidity());
    Serial.print(F("%  Temperature: "));
    Serial.print(myHome.getTemperature());
    Serial.print(F("°C  "));
    Serial.print("Light: ");
    Serial.print(myHome.getLight());
    Serial.println(" lx");

    sendData(myHome.getTemperature(), myHome.getHumidity(), myHome.getLight());
    
    timer = 0;
  }
  
}

// put function definitions here:
void sendData(float temperature,float humidity, int light) {
  String datasent = "!1:T:" + String (temperature) + "#" + "!2:H:"+ String (humidity) + "#" + "!3:L:" + String(light) + "#";
  SerialPort.println(datasent);
  // Serial.println(datasent);
  Serial.println("========================================");
}

void receiveData() {
  JsonDocument doc;
  if (SerialPort.available() > 0) {
    String incomingData = SerialPort.readStringUntil('n');

    DeserializationError error = deserializeJson(doc, incomingData);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    String device = doc["device"];
    int status = doc["status"];

    if (device == "led") {
      controlDevices(LED, status);
    } else if (device == "tv") {
      controlDevices(TV, status);
    } else if (device == "ac") {
      controlDevices(AC, status);
    } else {
      controlDevices(SP, status);
    }
  }
}

float getAverageTemperature() {
  float temp = 0.0;
  float avgTemp = 0.0;

  for (int i = 0; i < 9; i++) {
    temp += dht.readTemperature();
  }

  avgTemp = temp/10;
  myHome.setTemperature(avgTemp);
  return avgTemp;
}

float getAverageHumidity() {
  float humid = 0.0;
  float avgHumid = 0.0;

  for (int i = 0; i < 9; i++) {
    humid += dht.readHumidity();
  }

  avgHumid = humid/10;
  myHome.setHumidity(avgHumid);
  return avgHumid;
}

int getAverageLight() {
  float light = 0.0;
  int avgLight = 0;
  
  for (int i = 0; i < 9; i++) {
    light += lightMeter.readLightLevel();
  }

  avgLight = static_cast<int>(light/10);
  myHome.setLight(avgLight);
  return avgLight;
}

void controlDevices(DeviceType type, int status) {
  switch (type)
  {
    case LED:
      myHome.controlLed(status);
      break;
    case TV:
      myHome.controlTv(status);
      break;
    case AC:
      myHome.controlAirConditioner(status);
      break;
    case SP:
      myHome.controlSpeaker(status);
    default:
      break;
  }
}