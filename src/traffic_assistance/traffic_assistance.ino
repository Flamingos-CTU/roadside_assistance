#include <Automaton.h>
#include "Atm_traffic_assistance.h"

// Basic Arduino sketch - instantiates the state machine and nothing else

Atm_traffic_assistance traffic_assistance;

void setup() {

  Serial.begin( 9600 );
  traffic_assistance.trace( Serial );

  traffic_assistance.begin();

}

void loop() {
  automaton.run();
}


