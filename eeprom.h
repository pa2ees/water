#ifndef EEPROM_H
#define EEPROM_H

#include <xc.h>
#include <stdint.h>
#include "common.h"
#include "settings.h"

#define EE_STG_TANK_PUMP_TURN_ON_LEVEL 0
#define EE_STG_TANK_PUMP_TURN_OFF_LEVEL 1

#define EE_PKT_OP_LOAD 0
#define EE_PKT_CMD_LOAD_ALL 0
#define EE_PKT_CMD_LOAD_ONE 1

#define EE_PKT_OP_STORE 1
#define EE_PKT_CMD_STORE_ALL 0
#define EE_PKT_CMD_STORE_ONE 1
#define EE_PKT_CMD_STORE_NUM 3


void EEPROM_load_all_settings(settings_t *s);
void EEPROM_load_setting(settings_t *s, uint8_t num);
void EEPROM_store_all_settings(settings_t *s);
void EEPROM_store_setting(settings_t *s, uint8_t num);


#endif /* EEPROM_H */
