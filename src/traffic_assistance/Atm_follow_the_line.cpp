#include "Atm_follow_the_line.h"
#include "Pin_layout.h"
#include "Atm_differential_motion.h"

extern sens_environment environment;
extern Atm_differential_motion motion;

/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

Atm_follow_the_line& Atm_follow_the_line::begin() {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*                     ON_ENTER  ON_LOOP  ON_EXIT  EVT_IN_MIDDLE  EVT_STOP  EVT_ON_BLACK  EVT_ON_WHITE  EVT_START  ELSE */
    /*       IDLE */       ENT_IDLE,      -1,      -1,            -1,     IDLE,           -1,           -1,   FORWARD,   -1,
    /*    FORWARD */    ENT_FORWARD,      -1,      -1,            -1,     IDLE,   TURN_RIGHT,    TURN_LEFT,        -1,   -1,
    /*  TURN_LEFT */  ENT_TURN_LEFT,      -1,      -1,       FORWARD,     IDLE,           -1,           -1,        -1,   -1,
    /* TURN_RIGHT */ ENT_TURN_RIGHT,      -1,      -1,       FORWARD,     IDLE,           -1,           -1,        -1,   -1,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_follow_the_line::event( int id ) {
  switch ( id ) {
    case EVT_IN_MIDDLE:
      if(environment.blackLL && environment.blackLML && !environment.blackLMR && !environment.blackLR)
          return 1;
      return 0;
    case EVT_ON_BLACK:
      if(environment.blackLMR)
          return 1;
      return 0;
    case EVT_ON_WHITE:
      if(!environment.blackLML)
          return 1;
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_follow_the_line::action( int id ) {
  switch ( id ) {
    case ENT_IDLE:
      motion.stop();
      return;
    case ENT_FORWARD:
      motion.forward(default_speed);
      return;
    case ENT_TURN_LEFT:
      motion.turn(-default_speed/2);
      return;
    case ENT_TURN_RIGHT:
      motion.turn(default_speed/2);
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_follow_the_line& Atm_follow_the_line::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_follow_the_line::state( void ) {
  return Machine::state();
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_follow_the_line& Atm_follow_the_line::stop() {
  trigger( EVT_STOP );
  return *this;
}

Atm_follow_the_line& Atm_follow_the_line::start() {
  trigger( EVT_START );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_follow_the_line& Atm_follow_the_line::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "FOLLOW_THE_LINE\0EVT_IN_MIDDLE\0EVT_STOP\0EVT_ON_BLACK\0EVT_ON_WHITE\0EVT_START\0ELSE\0IDLE\0FORWARD\0TURN_LEFT\0TURN_RIGHT" );
  return *this;
}





