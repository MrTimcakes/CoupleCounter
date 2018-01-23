#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Version 4 UUIDs (Basically Random)
#define SERVICE_UUID             "3efad57b-7510-46b9-ad7d-6a4411b66a53" // Generic CoupleCounter Service
#define TIME_CHARACTERISTIC_UUID "8852eb13-b7d2-4bca-a8a7-0ed21bc1d0c8" // Current Time Characteristic

BLECharacteristic *pTimeCharacteristic; // Global So I can Updated It 

void setup() {
  pinMode(0, INPUT);
  Serial.begin(115200);
  Serial.println(esp_sleep_get_wakeup_cause());

  if(!digitalRead(0)){ // If Boot BTN Pressed, start BLE
    BLESetup();
  }
  
  Serial.println("Sleeping!");
  esp_sleep_enable_timer_wakeup(10 * 1000000);
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
      }
    }
};

void BLESetup(){
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


