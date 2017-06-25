#pragma once

#include <Automaton.h>

class Atm_follow_the_line: public Machine {

 public:
  enum { IDLE, FORWARD, TURN_LEFT, TURN_RIGHT }; // STATES
  enum { EVT_IN_MIDDLE, EVT_STOP, EVT_ON_BLACK, EVT_ON_WHITE, EVT_START, ELSE }; // EVENTS
  Atm_follow_the_line( void ) : Machine() {};
  Atm_follow_the_line& begin( void );
  Atm_follow_the_line& trace( Stream & stream );
  Atm_follow_the_line& trigger( int event );
  int state( void );
  Atm_follow_the_line& stop( void );
  Atm_follow_the_line& start( void );

 private:
  enum { ENT_IDLE, ENT_FORWARD, ENT_TURN_LEFT, ENT_TURN_RIGHT }; // ACTIONS
  int event( int id ); 
  void action( int id ); 

};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_follow_the_line">
    <states>
      <IDLE index="0" on_enter="ENT_IDLE">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_START>FORWARD</EVT_START>
      </IDLE>
      <FORWARD index="1" on_enter="ENT_FORWARD">
        <EVT_STOP>IDLE</EVT_STOP>
        <EVT_ON_BLACK>TURN_RIGHT</EVT_ON_BLACK>
        <EVT_ON_WHITE>TURN_LEFT</EVT_ON_WHITE>
      </FORWARD>
      <TURN_LEFT index="2" on_enter="ENT_TURN_LEFT">
        <EVT_IN_MIDDLE>FORWARD</EVT_IN_MIDDLE>
        <EVT_STOP>IDLE</EVT_STOP>
      </TURN_LEFT>
      <TURN_RIGHT index="3" on_enter="ENT_TURN_RIGHT">
        <EVT_IN_MIDDLE>FORWARD</EVT_IN_MIDDLE>
        <EVT_STOP>IDLE</EVT_STOP>
      </TURN_RIGHT>
    </states>
    <events>
      <EVT_IN_MIDDLE index="0" access="PRIVATE"/>
      <EVT_STOP index="1" access="PUBLIC"/>
      <EVT_ON_BLACK index="2" access="PRIVATE"/>
      <EVT_ON_WHITE index="3" access="PRIVATE"/>
      <EVT_START index="4" access="PUBLIC"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

