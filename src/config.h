#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "home.h"

//DHT define
#define DHTPIN  26
#define DHTTYPE DHT11

//LCD
#define COLUMNS           16
#define ROWS              2
#define LCD_SPACE_SYMBOL  0x27
#define SDA               21
#define SCL               22

//UART
#define RXD2 16
#define TXD2 17

#define SMART_LED "Smart LED bulb 3W"
#define SMART_TV  "LG Ultrasonic TV"
#define AIR_CONDITIONER "SamSung Inverter 1HP"
#define SPEAKER "JBL Wireless Speaker"

const uint8_t heart[8]   PROGMEM = {0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};

int timer = 0;
String led = "LED bulb 3W MPE";
String tv = "LG Ultrasonic TV";
String air_conditioner = "SamSung Inverter 1HP";
Home myHome(SMART_LED, SMART_TV, AIR_CONDITIONER, SPEAKER);
HardwareSerial SerialPort(2);
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

#endif