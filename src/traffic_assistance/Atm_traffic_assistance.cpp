#include "Atm_traffic_assistance.h"
#include "Atm_differential_motion.h"

constexpr long matchTimeMs = 128000;

extern Atm_differential_motion motion;
/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_traffic_assistance& Atm_traffic_assistance::begin() {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                     ON_ENTER  ON_LOOP   ON_EXIT  EVT_PUSH_TRUCK_FINISHED   EVT_START  EVT_MATCH_END  ELSE */
    /*      IDLE  */             -1,      -1, EXT_IDLE,                      -1, PUSH_TRUCK,            -1,   -1,
    /* PUSH_TRUCK */ ENT_PUSH_TRUCK,      -1,       -1,                FINISHED,         -1,      FINISHED,   -1,
    /*   FINISHED */   ENT_FINISHED,      -1,       -1,                      -1,         -1,            -1,   -1,
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

Atm_timer timer;

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_traffic_assistance::action( int id ) {
  switch ( id ) {
    case EXT_IDLE:
      timer.trace( Serial );
      timer.begin( matchTimeMs ).start().onFinish(*this, EVT_MATCH_END);
      return;
    case ENT_PUSH_TRUCK:
      push_truck.begin().trace(Serial);
      return;
    case ENT_FINISHED:
      motion.stop();
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
    "TRAFFIC_ASSISTANCE\0EVT_PUSH_TRUCK_FINISHED\0EVT_START\0EVT_MATCH_END\0ELSE\0IDLE\0PUSH_TRUCK\0FINISHED" );
  return *this;
}



