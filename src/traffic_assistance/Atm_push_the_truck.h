#pragma once

#include <Automaton.h>

class Atm_push_the_truck: public Machine {

 public:
  enum { IDLE, GOING_TO_ROAD, TURNING_RIGHT, FOLLOWING_THE_ROAD, PUSHING_THE_TRUCK, FINISHED }; // STATES
  enum { ELSE }; // EVENTS
  Atm_push_the_truck( void ) : Machine() {};
  Atm_push_the_truck& begin( void );
  Atm_push_the_truck& trace( Stream & stream );
  Atm_push_the_truck& trigger( int event );
  int state( void );

 private:
  enum { ENT_GOING_TO_ROAD, ENT_TURNING_RIGHT, ENT_FOLLOWING_THE_ROAD, ENT_PUSHING_THE_TRUCK, ENT_FINISHED }; // ACTIONS
  int event( int id ); 
  void action( int id ); 

};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_push_the_truck">
    <states>
      <IDLE index="0">
      </IDLE>
      <GOING_TO_ROAD index="1" on_enter="ENT_GOING_TO_ROAD">
      </GOING_TO_ROAD>
      <TURNING_RIGHT index="2" on_enter="ENT_TURNING_RIGHT">
      </TURNING_RIGHT>
      <FOLLOWING_THE_ROAD index="3" on_enter="ENT_FOLLOWING_THE_ROAD">
      </FOLLOWING_THE_ROAD>
      <PUSHING_THE_TRUCK index="4" on_enter="ENT_PUSHING_THE_TRUCK">
      </PUSHING_THE_TRUCK>
      <FINISHED index="5" on_enter="ENT_FINISHED">
      </FINISHED>
    </states>
    <events>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

