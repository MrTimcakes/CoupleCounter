#define SLEEP_TIME 10

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <TimeLib.h>

// Version 4 UUIDs (Basically Random)
#define SERVICE_UUID             "3efad57b-7510-46b9-ad7d-6a4411b66a53" // Generic CoupleCounter Service
#define TIME_CHARACTERISTIC_UUID "8852eb13-b7d2-4bca-a8a7-0ed21bc1d0c8" // Current Time Characteristic

BLECharacteristic *pTimeCharacteristic; // Global So I can Updated It 

RTC_DATA_ATTR time_t UnixTime = 0;

void setup() {
  setTime(UnixTime);
  pinMode(0, INPUT);
  Serial.begin(115200);
  Serial.println(esp_sleep_get_wakeup_cause());

  if(!digitalRead(0)){ // If Boot BTN Pressed, start BLE
    BLESetup();
  }

  String timenow = twoDigits(hour()) + ":" + twoDigits(minute()) + ":" + twoDigits(second());
  Serial.println(timenow);
  Serial.println(millis());
  
  Serial.println("Sleeping!");
  UnixTime = now();
  UnixTime += SLEEP_TIME;
  esp_sleep_enable_timer_wakeup(SLEEP_TIME * 1000000);
  esp_deep_sleep_start();
}

void loop() {
  // Never Executed
}

class TimeCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) {
        Serial.print("New value: ");
        Serial.println(value.c_str());
        UnixTime = atol(value.c_str());
        setTime(UnixTime);
      }
    }
};

void BLESetup(){
  Serial.print("BLE Started");
  BLEDevice::init("CoupleCounter");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pTimeCharacteristic = pService->createCharacteristic(TIME_CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pTimeCharacteristic->setCallbacks(new TimeCallbacks());
  pTimeCharacteristic->setValue("Initial Value");
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  while(!digitalRead(0)){ // While Boot BTN Pressed
    delay(1000);
  }
}

String twoDigits(int d){
  return (d<10) ? '0'+String(d) : String(d);
}

