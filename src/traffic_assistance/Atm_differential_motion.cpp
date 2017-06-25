#include "Atm_differential_motion.h"
#include "Pin_layout.h"
/* Add optional parameters for the state machine to begin()
 * Add extra initialization code
 */

extern sens_environment environment;

Atm_differential_motion& Atm_differential_motion::begin( void ) {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*             ON_ENTER  ON_LOOP    ON_EXIT  EVT_COMMAND_CHANGED  EVT_NO_OPPONENT  EVT_OPPONENT_DETECTED  EVT_GO_IDLE  EVT_TIMEOUT  ELSE */
    /*   IDLE */   ENT_IDLE,      -1,  EXT_IDLE,              MOVING,              -1,                    -1,          -1,          -1,   -1,
    /* MOVING */ ENT_MOVING,      -1,        -1,              MOVING,              -1,                 PAUSE,        IDLE,        IDLE,   -1,
    /*  PAUSE */  ENT_PAUSE,      -1, EXT_PAUSE,              MOVING,          MOVING,                    -1,        IDLE,        IDLE,   -1,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  left.begin(servo_left,leftServoZeroPos).step(1,30);
  right.begin(servo_right, rightServoZeroPos).step(1,30);
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_differential_motion::event( int id ) {
  switch ( id ) {
    case EVT_COMMAND_CHANGED:
      return 0;
    case EVT_NO_OPPONENT:
      return 1-event(EVT_OPPONENT_DETECTED);
    case EVT_OPPONENT_DETECTED:
      if(lspeed > 0 && rspeed < 0 && environment.obstacleFront)
          return 1;
      if(lspeed < 0 && rspeed > 0 && environment.obstacleBack)
          return 1;
      if((environment.obstacleLeft || environment.obstacleRight) && ((lspeed >0 && rspeed>0)||(lspeed<0&&rspeed<0)))
          return 1;
      return 0;
    case EVT_GO_IDLE:
      return 0;
    case EVT_TIMEOUT:
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_differential_motion::action( int id ) {
  switch ( id ) {
    case ENT_IDLE:
      return;
    case EXT_IDLE:
      return;
    case ENT_MOVING:
      return;
    case ENT_PAUSE:
      left.step(180,0).position(leftServoZeroPos);
      right.step(180,0).position(rightServoZeroPos);
      return;
    case EXT_PAUSE:
      left.step(1,30).position(leftServoZeroPos + lspeed);
      right.step(1,30).position(rightServoZeroPos + rspeed);
      return;
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_differential_motion& Atm_differential_motion::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_differential_motion::state( void ) {
  return Machine::state();
}

Atm_differential_motion& Atm_differential_motion::forward(int speed){
  lspeed = speed;
  rspeed = -speed;
  left.step(1,30).position(leftServoZeroPos + speed);
  right.step(1,30).position(rightServoZeroPos - speed);
  trigger(EVT_COMMAND_CHANGED);
  return *this;
}

Atm_differential_motion& Atm_differential_motion::turn(int speed){
  lspeed = speed;
  rspeed = speed;
  
  left.step(1,30).position(leftServoZeroPos + speed);
  right.step(1,30).position(rightServoZeroPos + speed);
  trigger(EVT_COMMAND_CHANGED);
  return *this;
}

Atm_differential_motion& Atm_differential_motion::stop(){
  lspeed = 0;
  rspeed = 0;
  left.step(180,0).position(leftServoZeroPos);
  right.step(180,0).position(rightServoZeroPos);
  trigger(EVT_GO_IDLE);
  return *this;
}

/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_differential_motion& Atm_differential_motion::command_changed() {
  trigger( EVT_COMMAND_CHANGED );
  return *this;
}

Atm_differential_motion& Atm_differential_motion::no_opponent() {
  trigger( EVT_NO_OPPONENT );
  return *this;
}

Atm_differential_motion& Atm_differential_motion::opponent_detected() {
  trigger( EVT_OPPONENT_DETECTED );
  return *this;
}

Atm_differential_motion& Atm_differential_motion::go_idle() {
  trigger( EVT_GO_IDLE );
  return *this;
}

Atm_differential_motion& Atm_differential_motion::timeout() {
  trigger( EVT_TIMEOUT );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_differential_motion& Atm_differential_motion::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "DIFFERENTIAL_MOTION\0EVT_COMMAND_CHANGED\0EVT_NO_OPPONENT\0EVT_OPPONENT_DETECTED\0EVT_GO_IDLE\0EVT_TIMEOUT\0ELSE\0IDLE\0MOVING\0PAUSE" );
  return *this;
}





