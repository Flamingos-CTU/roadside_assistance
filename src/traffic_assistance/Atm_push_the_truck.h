#pragma once

#include <Automaton.h>
#include "Atm_follow_the_line.h"

class Atm_push_the_truck: public Machine {

 public:
  enum { IDLE, GOING_TO_ROAD, TURNING_RIGHT, FOLLOWING_THE_ROAD, PUSHING_THE_TRUCK, FINISHED }; // STATES
  enum { EVT_LEFT_LINE_2, EVT_LEFT_LINE_1, EVT_TURNED, EVT_BLACK, ELSE }; // EVENTS
  Atm_push_the_truck( void ) : Machine() {};
  Atm_push_the_truck& begin( void );
  Atm_push_the_truck& trace( Stream & stream );
  Atm_push_the_truck& trigger( int event );
  int state( void );

 private:
  enum { ENT_GOING_TO_ROAD, ENT_TURNING_RIGHT, ENT_FOLLOWING_THE_ROAD, EXT_FOLLOWING_THE_ROAD, ENT_PUSHING_THE_TRUCK, ENT_FINISHED }; // ACTIONS
  int event( int id ); 
  void action( int id ); 
  void Going_to_road();
  Atm_follow_the_line follower;
  long leftRoadMillis=0;
};

/*
Automaton::ATML::begin - Automaton Markup Language

<?xml version="1.0" encoding="UTF-8"?>
<machines>
  <machine name="Atm_push_the_truck">
    <states>
      <IDLE index="0">
        <EVT_LEFT_LINE_2>GOING_TO_ROAD</EVT_LEFT_LINE_2>
        <EVT_LEFT_LINE_1>GOING_TO_ROAD</EVT_LEFT_LINE_1>
        <EVT_TURNED>GOING_TO_ROAD</EVT_TURNED>
        <EVT_BLACK>GOING_TO_ROAD</EVT_BLACK>
        <ELSE>GOING_TO_ROAD</ELSE>
      </IDLE>
      <GOING_TO_ROAD index="1" on_enter="ENT_GOING_TO_ROAD">
        <EVT_BLACK>TURNING_RIGHT</EVT_BLACK>
      </GOING_TO_ROAD>
      <TURNING_RIGHT index="2" on_enter="ENT_TURNING_RIGHT">
        <EVT_TURNED>FOLLOWING_THE_ROAD</EVT_TURNED>
      </TURNING_RIGHT>
      <FOLLOWING_THE_ROAD index="3" on_enter="ENT_FOLLOWING_THE_ROAD" on_exit="EXT_FOLLOWING_THE_ROAD">
        <EVT_LEFT_LINE_1>PUSHING_THE_TRUCK</EVT_LEFT_LINE_1>
      </FOLLOWING_THE_ROAD>
      <PUSHING_THE_TRUCK index="4" on_enter="ENT_PUSHING_THE_TRUCK">
        <EVT_LEFT_LINE_2>FINISHED</EVT_LEFT_LINE_2>
      </PUSHING_THE_TRUCK>
      <FINISHED index="5" on_enter="ENT_FINISHED">
        <EVT_LEFT_LINE_2>FINISHED</EVT_LEFT_LINE_2>
        <EVT_LEFT_LINE_1>FINISHED</EVT_LEFT_LINE_1>
        <EVT_TURNED>FINISHED</EVT_TURNED>
        <EVT_BLACK>FINISHED</EVT_BLACK>
        <ELSE>FINISHED</ELSE>
      </FINISHED>
    </states>
    <events>
      <EVT_LEFT_LINE_2 index="0" access="PRIVATE"/>
      <EVT_LEFT_LINE_1 index="1" access="PRIVATE"/>
      <EVT_TURNED index="2" access="PRIVATE"/>
      <EVT_BLACK index="3" access="PRIVATE"/>
    </events>
    <connectors>
    </connectors>
    <methods>
    </methods>
  </machine>
</machines>

Automaton::ATML::end
*/

