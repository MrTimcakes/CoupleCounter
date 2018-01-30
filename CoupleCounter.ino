#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

#include "Phrases.h"

#include "SSD1306.h"
SSD1306  display(0x3c, 4, 5); // SDA, SCL    NodeMCU: D2, D1

#include "RTClib.h"
RTC_DS1307 rtc;
//RTC_DS3231 rtc;

void setup(){
  Serial.begin(115200);
  DisplayInit();

  if (! rtc.begin()) {
    DisplayRTCError();
  }else{
    DisplayPhrase();
  }
  

  ESP.deepSleep(3600e6);
}

void loop(){
  
}

void DisplayInit(){
  display.init();
  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void DisplayRTCError(){
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(64, 32, "NO RTC DETECTED");
  display.display();
}

void DisplayPhrase(){
  int EventID = random( arr_len(EventTimes) );
  String Message = EventDesc[EventID];
  
  DateTime now = rtc.now();
  Message.replace("[x]", String((now.unixtime() - EventTimes[EventID]) / 86400) + " Days");
  
  display.drawString(0, 0, Aliases[random(arr_len(Aliases))] + ",");
  display.drawStringMaxWidth( 0, 10, 128, Message );
  display.display();
}

