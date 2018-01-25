#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

#include "Phrases.h"

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  int EventID = random( arr_len(EventTimes) );
  Serial.println(Aliases[ random(arr_len(Aliases)) ]); // Random Alias
  Serial.println(EventTimes[EventID]); // Time of Event
  Serial.println(EventDesc[EventID]); // Event Description
}

void loop(){
  
}

