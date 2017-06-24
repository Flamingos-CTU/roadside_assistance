#include "Atm_push_the_truck.h"
#include "Pin_layout.h"
/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

extern struct sens_environment environment;

Atm_push_the_truck& Atm_push_the_truck::begin() {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                                     ON_ENTER  ON_LOOP  ON_EXIT  EVT_LEFT_LINE_2    EVT_LEFT_LINE_1          EVT_TURNED      EVT_BLACK           ELSE */
    /*               IDLE */                     -1,      -1,      -1,   GOING_TO_ROAD,     GOING_TO_ROAD,      GOING_TO_ROAD, GOING_TO_ROAD, GOING_TO_ROAD,
    /*      GOING_TO_ROAD */      ENT_GOING_TO_ROAD,      -1,      -1,              -1,                -1,                 -1, TURNING_RIGHT,            -1,
    /*      TURNING_RIGHT */      ENT_TURNING_RIGHT,      -1,      -1,              -1,                -1, FOLLOWING_THE_ROAD,            -1,            -1,
    /* FOLLOWING_THE_ROAD */ ENT_FOLLOWING_THE_ROAD,      -1,      -1,              -1, PUSHING_THE_TRUCK,                 -1,            -1,            -1,
    /*  PUSHING_THE_TRUCK */  ENT_PUSHING_THE_TRUCK,      -1,      -1,        FINISHED,                -1,                 -1,            -1,            -1,
    /*           FINISHED */           ENT_FINISHED,      -1,      -1,        FINISHED,          FINISHED,           FINISHED,      FINISHED,      FINISHED,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_push_the_truck::event( int id ) {
  switch ( id ) {
    case EVT_LEFT_LINE_2:
      return environment.blackLM?0:1;
    case EVT_LEFT_LINE_1:
      return environment.blackLL?0:1;
    case EVT_TURNED:
      return environment.blackLMR?1:0;
    case EVT_BLACK:
      return environment.blackLM?1:0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_push_the_truck::action( int id ) {
  switch ( id ) {
    case ENT_GOING_TO_ROAD:
      
      return;
    case ENT_TURNING_RIGHT:
      return;
    case ENT_FOLLOWING_THE_ROAD:
      return;
    case ENT_PUSHING_THE_TRUCK:
      return;
    case ENT_FINISHED:
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_push_the_truck& Atm_push_the_truck::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_push_the_truck::state( void ) {
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_push_the_truck& Atm_push_the_truck::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "PUSH_THE_TRUCK\0EVT_LEFT_LINE_2\0EVT_LEFT_LINE_1\0EVT_TURNED\0EVT_BLACK\0ELSE\0IDLE\0GOING_TO_ROAD\0TURNING_RIGHT\0FOLLOWING_THE_ROAD\0PUSHING_THE_TRUCK\0FINISHED" );
  return *this;
}




