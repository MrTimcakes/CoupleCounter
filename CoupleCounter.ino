#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

#include "Phrases.h"

#include "SSD1306.h"
SSD1306  display(0x3c, 4, 5); // SDA, SCL    NodeMCU: D2, D1


void setup(){
  DisplayInit();
  DisplayPhrase();

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

void DisplayPhrase(){
  int EventID = random( arr_len(EventTimes) );
  String Message = EventDesc[EventID];
  Message.replace("[x]", "TIMESINCE");
  display.drawString(0, 0, Aliases[random(arr_len(Aliases))] + ",");
  display.drawStringMaxWidth( 0, 10, 128, Message );
  display.display();
}

