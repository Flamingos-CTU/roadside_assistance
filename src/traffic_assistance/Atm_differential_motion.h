#pragma once

#include <Automaton.h>
#include <Atm_servo.h>

class Atm_differential_motion: public Machine {

 public:
  enum { IDLE, MOVING, PAUSE }; // STATES
  enum { EVT_COMMAND_CHANGED, EVT_NO_OPPONENT, EVT_OPPONENT_DETECTED, EVT_GO_IDLE, EVT_TIMEOUT, ELSE }; // EVENTS
  Atm_differential_motion( void ) : Machine() {};
  Atm_differential_motion& begin( void );
  Atm_differential_motion& trace( Stream & stream );
  Atm_differential_motion& trigger( int event );
  int state( void );
  Atm_differential_motion& forward(int speed);
  Atm_differential_motion& turn(int speed);
  Atm_differential_motion& stop( void);
  Atm_differential_motion& command_changed( void );
  Atm_differential_motion& no_opponent( void );
  Atm_differential_motion& opponent_detected( void );
  Atm_differential_motion& go_idle( void );
  Atm_differential_motion& timeout( void );

 private:
  enum { ENT_IDLE, EXT_IDLE, ENT_MOVING, ENT_PAUSE, EXT_PAUSE }; // ACTIONS
  int event( int id ); 
  void action( int id ); 

  Atm_servo left;
  Atm_servo right;
  int lspeed=0;
  int rspeed=0;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_differential_motion">
    <states>
      <IDLE index="0" on_enter="ENT_IDLE" on_exit="EXT_IDLE">
        <EVT_COMMAND_CHANGED>MOVING</EVT_COMMAND_CHANGED>
      </IDLE>
      <MOVING index="1" on_enter="ENT_MOVING">
        <EVT_COMMAND_CHANGED>MOVING</EVT_COMMAND_CHANGED>
        <EVT_OPPONENT_DETECTED>PAUSE</EVT_OPPONENT_DETECTED>
        <EVT_GO_IDLE>IDLE</EVT_GO_IDLE>
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
      </MOVING>
      <PAUSE index="2" on_enter="ENT_PAUSE" on_exit="EXT_PAUSE">
        <EVT_COMMAND_CHANGED>MOVING</EVT_COMMAND_CHANGED>
        <EVT_NO_OPPONENT>MOVING</EVT_NO_OPPONENT>
        <EVT_GO_IDLE>IDLE</EVT_GO_IDLE>
        <EVT_TIMEOUT>IDLE</EVT_TIMEOUT>
      </PAUSE>
    </states>
    <events>
      <EVT_COMMAND_CHANGED index="0" access="MIXED"/>
      <EVT_NO_OPPONENT index="1" access="MIXED"/>
      <EVT_OPPONENT_DETECTED index="2" access="MIXED"/>
      <EVT_GO_IDLE index="3" access="MIXED"/>
      <EVT_TIMEOUT index="4" access="MIXED"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

