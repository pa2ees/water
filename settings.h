#ifndef SETTINGS_H
#define SETTINGS_H


#include <xc.h>
#include <stdint.h>
#include "common.h"
//#include "eeprom.h"

// settings payload operations
#define STGS_PLD_OP_LOAD 0
#define STGS_PLD_OP_SAVE 1
#define STGS_PLD_OP_WRITE 2
#define STGS_PLD_OP_READ 3

// load commands
#define STGS_PLD_CMD_LOAD_ALL 0
#define STGS_PLD_CMD_LOAD_ONE 1

// save commands
#define STGS_PLD_CMD_SAVE_ALL 0
#define STGS_PLD_CMD_SAVE_ONE 1

// settings numbers
#define STGS_TANK_PUMP_TURN_ON_LEVEL 0
#define STGS_TANK_PUMP_TURN_OFF_LEVEL 1

#define STGS_NUM_OF_SETTINGS 2

typedef union{
    struct{
        uint16_t tank_pump_turn_on_level;
        uint16_t tank_pump_turn_off_level;
    };
    uint16_t arr[2];
}settings_t;

/**************
 * operations
 *
 * load from eeprom
 * save to eeprom
 * write setting
 * read setting
 *
 **************/

/**************
 * load from eeprom commands
 * -------------------------
 * load all
 * load specific
 *
 * save to eeprom commands
 * -----------------------
 * save all
 * save one
 *
 ***************/

typedef union {
    __pack struct {
        uint8_t operation;
        union { //second byte
            uint8_t load_command;
            uint8_t save_command;
            uint8_t write_setting_num;
            uint8_t read_setting_num;
        };
        union { // thrid and fourth bytes
            uint16_t load_setting_num;
            uint16_t save_setting_num;
            uint16_t setting_value;
        };
    };
    uint8_t arr[4];
        

}SETTINGS_payload_t;

/*
void SETTINGS_save_to_eeprom(settings_t *stgs, uint8_t setting_num);
void SETTINGS_load_from_eeprom(settings_t *stgs, uint8_t setting_num);
void SETTINGS_save_all_to_eeprom(settings_t *stgs);
void SETTINGS_load_all_from_eeprom(settings_t *stgs);
*/

void SETTINGS_write(settings_t *stgs, uint8_t setting_num, uint16_t setting_val);
uint16_t SETTINGS_read(settings_t *stgs, uint8_t setting_num);



#endif /* SETTINGS_H */
