#pragma once

#include <Automaton.h>
#include "Atm_push_the_truck.h"

class Atm_traffic_assistance: public Machine {

 public:
  enum { IDLE, PUSH_TRUCK, FINISHED }; // STATES
  enum { EVT_PUSH_TRUCK_FINISHED, EVT_START, EVT_MATCH_END, ELSE }; // EVENTS
  Atm_traffic_assistance( void ) : Machine() {};
  Atm_traffic_assistance& begin( void );
  Atm_traffic_assistance& trace( Stream & stream );
  Atm_traffic_assistance& trigger( int event );
  int state( void );
  Atm_traffic_assistance& push_truck_finished( void );
  Atm_traffic_assistance& start( void );

 private:
  enum { EXT_IDLE, ENT_PUSH_TRUCK, ENT_FINISHED }; // ACTIONS
  int event( int id ); 
  void action( int id );
  Atm_push_the_truck push_truck;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_traffic_assistance">
    <states>
      <IDLE index="0" on_exit="EXT_IDLE">
        <EVT_START>PUSH_TRUCK</EVT_START>
      </IDLE>
      <PUSH_TRUCK index="1" on_enter="ENT_PUSH_TRUCK">
        <EVT_PUSH_TRUCK_FINISHED>FINISHED</EVT_PUSH_TRUCK_FINISHED>
      </PUSH_TRUCK>
      <FINISHED index="2" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
      <EVT_PUSH_TRUCK_FINISHED index="0" access="MIXED"/>
      <EVT_START index="1" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

