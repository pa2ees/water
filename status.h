#ifndef STATUS_H
#define STATUS_H

#include <xc.h>
#include <stdint.h>


// status payload operations
// #define STATUS_PLD_OP_LOAD 0
// #define STATUS_PLD_OP_SAVE 1
#define STATUS_PLD_OP_WRITE 2
#define STATUS_PLD_OP_READ 3

// status numbers
#define STATUS_FAILSAFE_TIMER 0
#define STATUS_CURR_TEMP 1
#define STATUS_CURR_TANK_LEVEL 2
#define STATUS_FILLING 3
#define STATUS_PUMPING 4
#define STATUS_FILLING_VALVE_CURRENT 5
#define STATUS_PUMP_CURRENT 6
#define STATUS_NUM_OF_STATUSES 7
#define STATUS_ERROR 255
// status writable mask
#define STATUS_WRITABLE // not sure how to do this

#define STATUS_FAILSAFE_TIMER_SET_VAL 0xA000;

typedef union {
    __pack struct {
        uint8_t operation;
        union { //second byte
            uint8_t status_num;
        };
        union { // thrid and fourth bytes
            uint16_t status_value;
        };
    };
    uint8_t arr[4];
        

}STATUS_payload_t;


typedef union {
    struct{
        uint16_t failsafe_timer;
        uint16_t curr_temp;
        uint16_t curr_tank_level;
        uint16_t filling;
        uint16_t pumping;
        uint16_t filling_valve_current;
        uint16_t pump_current;
    };
    uint16_t arr[STATUS_NUM_OF_STATUSES];

}STATUS_curr_status_t;


void STATUS_update_failsafe_timer(void);
void STATUS_tick_failsafe_timer(void);

// extern STATUS_curr_status_t curr_status;

#endif /* STATUS_H */
