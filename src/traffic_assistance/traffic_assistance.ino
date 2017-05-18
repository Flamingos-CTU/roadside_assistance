#include <Automaton.h>
#include "Atm_traffic_assistance.h"
#include "Pin_layout.h"

// Basic Arduino sketch - instantiates the state machine and nothing else

Atm_traffic_assistance traffic_assistance;
Atm_button button;
void setup() {
  
  Serial.begin( 9600 );
  traffic_assistance.trace( Serial );
  button.trace( Serial );
  traffic_assistance.begin();
  button.begin( startButton ).onPress( traffic_assistance, traffic_assistance.EVT_START );
  
  
}

void loop() {
  automaton.run();
}


