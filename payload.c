/*
 * File:   paylaod.c
 * Author: erik
 *
 * Created on December 20, 2018
 */

#include "payload.h"


void handle_rx_packet(void)
{
    // define packet object
    PACKET_pkt_t *pkt_p;

    // get settings
    SETTINGS_payload_t *stgs_pld_p;
    STATUS_payload_t *status_pld_p;

    // get packet handle
    pkt_p = PACKET_get_rx_packet_ptr();

    // if packet is not for me, ignore it
    if (pkt_p->dest_address != 0x01) // 0x01 is temporary address
    {
        return;
    }

    if (pkt_p->payload_type == PACKET_PAYLOAD_TYPE_ECHO)
    { // type echo
        PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x02); // MUST CHANGE SRC ADDRESS
        PACKET_UpdateAndSend(pkt_p);
    }
    else if (pkt_p->payload_type == PACKET_PAYLOAD_TYPE_SETTING)
    { // setting - format: [operation, command, setting_low_byte, setting_high_byte]
        if (pkt_p->payload_len < 4)
        { // malformed
            // send packet bad message
            return;
        }

        stgs_pld_p = &(pkt_p->stgs_payload);

        if (stgs_pld_p->operation == STGS_PLD_OP_LOAD)
        { // operation load_from_eeprom
            if (stgs_pld_p->load_command == STGS_PLD_CMD_LOAD_ALL)
            { // load all 
                //SETTINGS_load_all_from_eeprom(&settings);
                EEPROM_load_all_settings(&settings);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_LOAD_ONE)
            { // load specific setting
                //SETTINGS_load_from_eeprom(&settings, stgs_pld_p->load_setting_num);
                EEPROM_load_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
        }
        else if (stgs_pld_p->operation == STGS_PLD_OP_SAVE)
        {
            if (stgs_pld_p->load_command == STGS_PLD_CMD_SAVE_ALL)
            { // store all
                //SETTINGS_save_all_to_eeprom(&settings);
                EEPROM_store_all_settings(&settings);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_SAVE_ONE)
            { // store specific setting
                //SETTINGS_save_to_eeprom(&settings, stgs_pld_p->load_setting_num);
                EEPROM_store_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            
        }

        else if (stgs_pld_p->operation == STGS_PLD_OP_WRITE)
        { // write values to settings
            SETTINGS_write(&settings, stgs_pld_p->write_setting_num, stgs_pld_p->setting_value);
            // TODO: maybe verify?

            // respond that it is done
            PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
            PACKET_UpdateAndSend(pkt_p);
        }
        else if (stgs_pld_p->operation == STGS_PLD_OP_READ)
        { // read values from settings.
            stgs_pld_p->setting_value = SETTINGS_read(&settings, stgs_pld_p->read_setting_num);
            // respond with setting
            PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
            PACKET_UpdateAndSend(pkt_p);
        }


    }
    else if (pkt_p->payload_type == PACKET_PAYLOAD_TYPE_STATUS)
    { // type status - format: [operation, command, status_low_byte, status_high_byte]

        status_pld_p = &(pkt_p->status_payload);

        if (status_pld_p->operation == STATUS_PLD_OP_READ)
        { // read status


            if (status_pld_p->status_num == STATUS_CURR_TEMP)
            { // get current temp
                status_pld_p->status_value = curr_status.arr[STATUS_CURR_TEMP];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            else if (status_pld_p->status_num == STATUS_CURR_TANK_LEVEL)
            { // get current tank level
                status_pld_p->status_value = curr_status.arr[STATUS_CURR_TANK_LEVEL];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            else if (status_pld_p->status_num == STATUS_FILLING)
            { // get current tank level
                status_pld_p->status_value = curr_status.arr[STATUS_FILLING];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }
            else if (status_pld_p->status_num == STATUS_PUMPING)
            { // get current tank level
                status_pld_p->status_value = curr_status.arr[STATUS_PUMPING];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
            }

            
        }
        else if (status_pld_p->operation == STATUS_PLD_OP_WRITE)
        { // write status
            if (status_pld_p->status_num == STATUS_FILLING)
            {
                curr_status.arr[STATUS_FILLING] = status_pld_p->status_value;
                status_pld_p->status_value = curr_status.arr[STATUS_FILLING];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
                
            }
            if (status_pld_p->status_num == STATUS_PUMPING)
            {
                curr_status.arr[STATUS_PUMPING] = status_pld_p->status_value;
                status_pld_p->status_value = curr_status.arr[STATUS_PUMPING];
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, 0x01); // MUST CHANGE SRC ADDRESS
                PACKET_UpdateAndSend(pkt_p);
                
            }
            
        }
    }


}
