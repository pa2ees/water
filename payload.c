/*
 * File:   paylaod.c
 * Author: erik
 *
 * Created on December 20, 2018
 */

#include "payload.h"
#include "status.h"


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
    if (pkt_p->dest_address != SETTINGS_read(&settings, STGS_ADDRESS)) // 0x01 is temporary address
    {
        return;
    }

    if (pkt_p->payload_type == PACKET_PAYLOAD_TYPE_ECHO)
    { // type echo
        PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
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
                EEPROM_load_all_settings(&settings);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_LOAD_ONE)
            { // load specific setting
                EEPROM_load_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
            }
        }
        else if (stgs_pld_p->operation == STGS_PLD_OP_SAVE)
        {
            if (stgs_pld_p->load_command == STGS_PLD_CMD_SAVE_ALL)
            { // store all
                EEPROM_store_all_settings(&settings);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_SAVE_ONE)
            { // store specific setting
                EEPROM_store_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
            }
            
        }

        else if (stgs_pld_p->operation == STGS_PLD_OP_WRITE)
        { // write values to settings
            SETTINGS_write(&settings, stgs_pld_p->write_setting_num, stgs_pld_p->setting_value);
            // TODO: maybe verify?

            // respond that it is done
            PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
            PACKET_UpdateAndSend(pkt_p);
        }
        else if (stgs_pld_p->operation == STGS_PLD_OP_READ)
        { // read values from settings.
            stgs_pld_p->setting_value = SETTINGS_read(&settings, stgs_pld_p->read_setting_num);
            // respond with setting
            PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
            PACKET_UpdateAndSend(pkt_p);
        }


    }
    else if (pkt_p->payload_type == PACKET_PAYLOAD_TYPE_STATUS)
    { // type status - format: [operation, command, status_low_byte, status_high_byte]

        status_pld_p = &(pkt_p->status_payload);

        if (status_pld_p->operation == STATUS_PLD_OP_READ)
        { // read status

            status_pld_p->status_value = STATUS_read(&curr_status, status_pld_p->status_num);
            PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
            PACKET_UpdateAndSend(pkt_p);
            
        }
        else if (status_pld_p->operation == STATUS_PLD_OP_WRITE)
        { // write status
            if (STATUS_write(&curr_status, status_pld_p->status_num, status_pld_p->status_value))
            { // got error, unwritable status
                status_pld_p->status_num = STATUS_ERROR;
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
            }
            else
            { // wrote status ok
                status_pld_p->status_value = STATUS_read(&curr_status, status_pld_p->status_num);
                PACKET_UpdateAddresses(pkt_p, pkt_p->src_address, SETTINGS_read(&settings, STGS_ADDRESS));
                PACKET_UpdateAndSend(pkt_p);
                STATUS_update_failsafe_timer();
            }
            
        }
    }


}
