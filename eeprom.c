#include "eeprom.h"

__eeprom settings_t SETTINGS_stgs;

void EEPROM_load_all_settings(settings_t *s)
{
    uint8_t i;
    for (i = 0; i < STGS_NUM_OF_SETTINGS; i++)
    {
        s->arr[i] = SETTINGS_stgs.arr[i];
    }
    //s->tank_pump_turn_on_level = settings.tank_pump_turn_on_level;
    //s->tank_pump_turn_off_level = settings.tank_pump_turn_off_level;
}

void EEPROM_load_setting(settings_t *s, uint8_t num)
{
    s->arr[num] = SETTINGS_stgs.arr[num];
}

void EEPROM_store_all_settings(settings_t *s)
{
    uint8_t i;
    for (i = 0; i < STGS_NUM_OF_SETTINGS; i++)
    {
        SETTINGS_stgs.arr[i] = s->arr[i];
    }
    //settings.tank_pump_turn_on_level = s->tank_pump_turn_on_level;
    //settings.tank_pump_turn_off_level = s->tank_pump_turn_off_level;
}

void EEPROM_store_setting(settings_t *s, uint8_t num)
{
    SETTINGS_stgs.arr[num] = s->arr[num];
}
