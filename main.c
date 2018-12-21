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
#include "status.h"
#include "payload.h"

#define TANK_MIN_LEVEL 200
#define V_TEMP_MIN 500
#define INITIAL_TANK_PUMP_TURN_ON_LEVEL 167 + TANK_MIN_LEVEL
#define INITIAL_TANK_PUMP_TURN_OFF_LEVEL 267 + TANK_MIN_LEVEL

void update_statuses(void);

// extern settings_t settings;
// extern STATUS_curr_status_t curr_status;


/*
                         Main application
 */
void main(void)
{
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
        update_statuses();
        
        if (curr_status.arr[STATUS_FILLING])
        {
            Fill_SW_SetHigh();
        }
        else
        {
            Fill_SW_SetLow();
        }

        if (curr_status.arr[STATUS_PUMPING])
        {
            Pump_SW_SetHigh();
        }
        else
        {
            Pump_SW_SetLow();
        }

        if (PACKET_Available())
        {
            //DEBUG_PRINT(("packet available"));
            DEBUG_PRINT_OFF(("packet available\n"));
            handle_rx_packet();

        }
        
        
    }
}

void update_statuses(void)
{
    uint16_t temp, level;
    
    temp = ADC_GetConversion(V_Temp);
        
    // convert adc count to millivolts
    temp = temp * 2;
    
    curr_status.arr[STATUS_CURR_TEMP] = temp;
    
    //ADC_SelectChannel(channel_Temp);
    //ADC_TemperatureAcquisitionDelay();
    //temp_int = ADC_GetConversion(channel_Temp);
    
    level = ADC_GetConversion(V_TankLevel);
    // adjust adc count to millivolts
    level = level * 2; 
    
    // don't go negative
    if (level < TANK_MIN_LEVEL) {level = TANK_MIN_LEVEL;} 
    
    curr_status.arr[STATUS_CURR_TANK_LEVEL] = level;

    return;

}



/**
 End of File
*/
