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

#include "mcc_generated_files/mcc.h"
#include "packet.h"
#include "common.h"

#define TANK_MIN_LEVEL 200
#define V_TEMP_MIN 500
#define TANK_FULL_LEVEL 267 + TANK_MIN_LEVEL

/*
                         Main application
 */
void main(void)
{
    uint16_t temp, temp_f, level, level_ft, temp_int;
    uint8_t send_data[8], *send_data_ptr;
    uint8_t send_packet[32], *send_packet_ptr;
    uint16_t send_packet_len;
    uint16_t i;
    
    
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
        
        //ADC_SelectChannel(channel_Temp);
        //ADC_TemperatureAcquisitionDelay();
        //temp_int = ADC_GetConversion(channel_Temp);
        
        level = ADC_GetConversion(V_TankLevel);
        //level = 2;
        // adjust adc count to millivolts
        level = level * 2; 
        
        // don't go negative
        if (level < TANK_MIN_LEVEL) {level = TANK_MIN_LEVEL;} 
        if (level < TANK_FULL_LEVEL)
        {
            // Turn on fill valves
            Fill_SW_SetHigh();
        }
        else
        {
            Fill_SW_SetLow();
        }
        
        // convert millivolts to water height in inches (11.25 per inch))
        level_ft = ((level) - TANK_MIN_LEVEL) / 45 * 4; 
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
            printf("packet available\n");
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
/**
 End of File
*/
