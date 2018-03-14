/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC16F1829
        Driver Version    :  2.00
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "packet.h"
#include "common.h"
#include "eeprom.h"
#include "settings.h"

#define TANK_MIN_LEVEL 200
#define V_TEMP_MIN 500
#define INITIAL_TANK_PUMP_TURN_ON_LEVEL 167 + TANK_MIN_LEVEL
#define INITIAL_TANK_PUMP_TURN_OFF_LEVEL 267 + TANK_MIN_LEVEL
void handle_rx_packet(void);

settings_t settings;
uint16_t curr_tank_level, curr_temp_f;

/*
                         Main application
 */
void main(void)
{
    uint16_t temp, temp_f, level, level_ft;
    uint8_t send_data[8], *send_data_ptr;
    uint8_t send_packet[32], *send_packet_ptr;
    uint16_t send_packet_len;
    uint16_t i;
    
    // retrieve settings from eeprom
    //SETTINGS_load_all_from_eeprom(&settings);
    EEPROM_load_all_settings(&settings);

    // initialize the device
    SYSTEM_Initialize();
    
    PACKET_Initialize();

    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        //__delay_ms(10);
        temp = ADC_GetConversion(V_Temp);
        
        // convert adc count to millivolts
        temp = temp * 2;
        
        // subtract min temp offset and convert millivolts to degrees C
        temp = (temp - V_TEMP_MIN) / 10;
        
        // convert deg C to deg F
        temp_f = (uint16_t) (temp * (9.0 / 5.0) + 32);

        curr_temp_f = temp_f;
        //ADC_SelectChannel(channel_Temp);
        //ADC_TemperatureAcquisitionDelay();
        //temp_int = ADC_GetConversion(channel_Temp);
        
        level = ADC_GetConversion(V_TankLevel);
        //level = 2;
        // adjust adc count to millivolts
        level = level * 2; 
        
        // don't go negative
        if (level < TANK_MIN_LEVEL) {level = TANK_MIN_LEVEL;} 
        if (level < settings.tank_pump_turn_on_level)
        {
            // Turn on fill valves
            Fill_SW_SetHigh();
        }
        else if (level > settings.tank_pump_turn_off_level)
        {
            Fill_SW_SetLow();
        }
        
        // convert millivolts to water height in inches (11.25 per inch))
        level_ft = ((level) - TANK_MIN_LEVEL) / 45 * 4;
        curr_tank_level = level_ft;


        
        //RS485_TX_EN_SetHigh();
        
        send_data_ptr = send_data;
        *send_data_ptr = (temp_f >> 8) & 0xFF;
        send_data_ptr++;
        *send_data_ptr = temp_f & 0xFF;
        
        //send_packet_len = PACKET_CreatePacket(2, send_data, send_packet, PACKET_Type_temp);
        //for (i = 0; i < send_packet_len; i++)
        //{
            //EUSART_Write(send_packet[i]);
        //}

        send_data_ptr = send_data;
        *send_data_ptr = (level_ft >> 8) & 0xFF;
        send_data_ptr++;
        *send_data_ptr = level_ft & 0xFF;
        
        //send_packet_len = PACKET_CreatePacket(2, send_data, send_packet, PACKET_Type_level);
        //for (i = 0; i < send_packet_len; i++)
        //{
            //EUSART_Write(send_packet[i]);
        //}


        if (PACKET_Available())
        {
            //DEBUG_PRINT(("packet available"));
            DEBUG_PRINT_OFF(("packet available\n"));
            handle_rx_packet();
            //for (i = 0; i < send_packet_len; i++)
            //{
            //    EUSART_Write(send_packet[i]);
            //}

        }
        
        
        //printf("T:%d|L:%d\r\n", temp_f, level_ft);
        //RS485_TX_EN_SetLow();
        //__delay_ms(500);
        


    }
}


void handle_rx_packet(void)
{
    PACKET_pkt_t *pkt_p;

    SETTINGS_payload_t *stgs_pld_p;
    
    pkt_p = PACKET_get_rx_packet_ptr();

    if (pkt_p->payload_type == 0x00)
    { // type echo
        PACKET_SendPacket(pkt_p);
    }
    else if (pkt_p->payload_type == 0x01)
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
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_LOAD_ONE)
            { // load specific setting
                //SETTINGS_load_from_eeprom(&settings, stgs_pld_p->load_setting_num);
                EEPROM_load_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
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
                PACKET_UpdateAndSend(pkt_p);
            }
            if (stgs_pld_p->load_command == STGS_PLD_CMD_SAVE_ONE)
            { // store specific setting
                //SETTINGS_save_to_eeprom(&settings, stgs_pld_p->load_setting_num);
                EEPROM_store_setting(&settings, stgs_pld_p->load_setting_num);
                // TODO: maybe verify?

                // respond that it is done
                PACKET_UpdateAndSend(pkt_p);
            }
            
        }

        else if (stgs_pld_p->operation == STGS_PLD_OP_WRITE)
        { // write values to settings
            SETTINGS_write(&settings, stgs_pld_p->write_setting_num, stgs_pld_p->setting_value);
            // TODO: maybe verify?

            // respond that it is done
            PACKET_UpdateAndSend(pkt_p);
        }
        else if (stgs_pld_p->operation == STGS_PLD_OP_READ)
        { // read values from settings.
            stgs_pld_p->setting_value = SETTINGS_read(&settings, stgs_pld_p->read_setting_num);
            // respond with setting
            PACKET_UpdateAndSend(pkt_p);
        }


    }
    else if (pkt_p->payload_type == 0x02)
    { // type status
        if (pkt_p->packet_arr[5] == 0x00)
        { // read status

            if (pkt_p->packet_arr[6] == 0x00)
            { // get current temp
                pkt_p->packet_arr[7] = curr_temp_f & 0xFF;
                pkt_p->packet_arr[8] = (curr_temp_f >> 8) & 0xFF;
                PACKET_UpdateAndSend(pkt_p);
            }
            else if (pkt_p->packet_arr[6] == 0x01)
            { // get current tank level
                pkt_p->packet_arr[7] = curr_tank_level & 0xFF;
                pkt_p->packet_arr[8] = (curr_tank_level >> 8) & 0xFF;
                PACKET_UpdateAndSend(pkt_p);
            }
        }
    }


}
/**
 End of File
*/
