#include "Atm_traffic_assistance.h"

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_traffic_assistance& Atm_traffic_assistance::begin() {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                     ON_ENTER  ON_LOOP   ON_EXIT  EVT_PUSH_TRUCK_FINISHED   EVT_START  ELSE */
    /*       IDLE */             -1,      -1, EXT_IDLE,                      -1, PUSH_TRUCK,   -1,
    /* PUSH_TRUCK */ ENT_PUSH_TRUCK,      -1,       -1,                FINISHED,         -1,   -1,
    /*   FINISHED */   ENT_FINISHED,      -1,       -1,                      -1,         -1,   -1,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_traffic_assistance::event( int id ) {
  switch ( id ) {
    case EVT_PUSH_TRUCK_FINISHED:
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_traffic_assistance::action( int id ) {
  switch ( id ) {
    case EXT_IDLE:
      return;
    case ENT_PUSH_TRUCK:
      return;
    case ENT_FINISHED:
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_traffic_assistance& Atm_traffic_assistance::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_traffic_assistance::state( void ) {
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_traffic_assistance& Atm_traffic_assistance::push_truck_finished() {
  trigger( EVT_PUSH_TRUCK_FINISHED );
  return *this;
}

Atm_traffic_assistance& Atm_traffic_assistance::start() {
  trigger( EVT_START );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_traffic_assistance& Atm_traffic_assistance::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "TRAFFIC_ASSISTANCE\0EVT_PUSH_TRUCK_FINISHED\0EVT_START\0ELSE\0IDLE\0PUSH_TRUCK\0FINISHED" );
  return *this;
}



