#include "settings.h"

/*
void SETTINGS_save_to_eeprom(settings_t *stgs, uint8_t setting_num)
{
    EEPROM_store_setting(stgs, setting_num);
}

void SETTINGS_load_from_eeprom(settings_t *stgs, uint8_t setting_num)
{
    EEPROM_load_setting(stgs, setting_num);
}

void SETTINGS_save_all_to_eeprom(settings_t *stgs)
{
    EEPROM_store_all_settings(stgs);
}

void SETTINGS_load_all_from_eeprom(settings_t *stgs)
{
    EEPROM_load_all_settings(stgs);
}
*/

SETTINGS_settings_t settings;

void SETTINGS_write(SETTINGS_settings_t *stgs, uint8_t setting_num, uint16_t setting_val)
{
    stgs->arr[setting_num] = setting_val;
}

uint16_t SETTINGS_read(SETTINGS_settings_t *stgs, uint8_t setting_num)
{
    return stgs->arr[setting_num];
}
