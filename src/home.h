#ifndef HOME_H
#define HOME_H

#include <Arduino.h>

using namespace std;

class Home {
public:
    class Device;
private:
    float temperature;
    float humidity;
    int light;
    Device* led;
    Device* tv;
    Device* air_conditioner;
    Device* speaker;
public:
    Home() : temperature(0.0), humidity(0.0), light(0), led(nullptr), tv(nullptr), air_conditioner(nullptr), speaker(nullptr) {} 
    Home(String led, String tv, String air_conditioner, String speaker, float temperature = 0.0, float humidity = 0.0, int light = 0) {
        this->temperature = temperature;
        this->humidity = humidity;
        this->light = light;
        this->led = new Device(led);
        this->tv = new Device(tv);
        this->air_conditioner = new Device(air_conditioner);
        this->speaker = new Device(speaker);
    }
    ~Home() {
        this->temperature = 0.0;
        this->humidity = 0.0;
        this->light = 0;
        delete this->led;
        delete this->tv;
        delete this->air_conditioner;
        delete this->speaker;
    }

    float getTemperature() {
        return this->temperature;
    }

    float getHumidity() {
        return this->humidity;
    }

    int getLight() {
        return this->light;
    }

    void setTemperature(float temperature) {
        this->temperature = temperature;
    }

    void setHumidity(float humidity) {
        this->humidity = humidity;
    }

    void setLight(int light) {
        this->light = light;
    }

    void controlLed(int status) { 
        if (led && status) led->turnOnDevice();
        else if (led && !status) led->turnOffDevice();
    }
    void controlTv(int status) { 
        if (tv && status) tv->turnOnDevice();
        else if (tv && !status) tv->turnOffDevice(); 
    }
    void controlAirConditioner(int status) { 
        if (air_conditioner && status) air_conditioner->turnOnDevice(); 
        else if (air_conditioner && !status) air_conditioner->turnOffDevice();
    }

    void controlSpeaker(int status) {
        if (speaker && status) speaker->turnOnDevice();
        else if (speaker && !status) speaker->turnOffDevice();
    }

    class Device {
    private:
        String name;
        int status;  
        friend class Home;
    public:
        Device() : name(""), status(0) {}
        Device(String name, int status = 0) {
            this->name = name;
            this->status = status;
        }
        ~Device() {}

        void turnOnDevice() {
            this->status = 1;
            Serial.println("Turn on " + this->name);
            Serial.println("========================================");
        }

        void turnOffDevice() {
            this->status = 0;
            Serial.println("Turn off " + this->name);
            Serial.println("========================================");
        }
    };
};


#endif