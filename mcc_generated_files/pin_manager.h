/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC16F1829
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set V_Temp aliases
#define V_Temp_TRIS               TRISAbits.TRISA2
#define V_Temp_LAT                LATAbits.LATA2
#define V_Temp_PORT               PORTAbits.RA2
#define V_Temp_WPU                WPUAbits.WPUA2
#define V_Temp_ANS                ANSELAbits.ANSA2
#define V_Temp_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define V_Temp_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define V_Temp_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define V_Temp_GetValue()           PORTAbits.RA2
#define V_Temp_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define V_Temp_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define V_Temp_SetPullup()      do { WPUAbits.WPUA2 = 1; } while(0)
#define V_Temp_ResetPullup()    do { WPUAbits.WPUA2 = 0; } while(0)
#define V_Temp_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define V_Temp_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set V_TankLevel aliases
#define V_TankLevel_TRIS               TRISAbits.TRISA4
#define V_TankLevel_LAT                LATAbits.LATA4
#define V_TankLevel_PORT               PORTAbits.RA4
#define V_TankLevel_WPU                WPUAbits.WPUA4
#define V_TankLevel_ANS                ANSELAbits.ANSA4
#define V_TankLevel_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define V_TankLevel_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define V_TankLevel_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define V_TankLevel_GetValue()           PORTAbits.RA4
#define V_TankLevel_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define V_TankLevel_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define V_TankLevel_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define V_TankLevel_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define V_TankLevel_SetAnalogMode()  do { ANSELAbits.ANSA4 = 1; } while(0)
#define V_TankLevel_SetDigitalMode() do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set SDI1 aliases
#define SDI1_TRIS               TRISBbits.TRISB4
#define SDI1_LAT                LATBbits.LATB4
#define SDI1_PORT               PORTBbits.RB4
#define SDI1_WPU                WPUBbits.WPUB4
#define SDI1_ANS                ANSELBbits.ANSB4
#define SDI1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SDI1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SDI1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SDI1_GetValue()           PORTBbits.RB4
#define SDI1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SDI1_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define SDI1_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define SDI1_SetAnalogMode()  do { ANSELBbits.ANSB4 = 1; } while(0)
#define SDI1_SetDigitalMode() do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set SDA2 aliases
#define SDA2_TRIS               TRISBbits.TRISB5
#define SDA2_LAT                LATBbits.LATB5
#define SDA2_PORT               PORTBbits.RB5
#define SDA2_WPU                WPUBbits.WPUB5
#define SDA2_ANS                ANSELBbits.ANSB5
#define SDA2_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SDA2_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SDA2_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SDA2_GetValue()           PORTBbits.RB5
#define SDA2_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SDA2_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SDA2_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define SDA2_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define SDA2_SetAnalogMode()  do { ANSELBbits.ANSB5 = 1; } while(0)
#define SDA2_SetDigitalMode() do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SCK1 aliases
#define SCK1_TRIS               TRISBbits.TRISB6
#define SCK1_LAT                LATBbits.LATB6
#define SCK1_PORT               PORTBbits.RB6
#define SCK1_WPU                WPUBbits.WPUB6
#define SCK1_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SCK1_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SCK1_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SCK1_GetValue()           PORTBbits.RB6
#define SCK1_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SCK1_SetPullup()      do { WPUBbits.WPUB6 = 1; } while(0)
#define SCK1_ResetPullup()    do { WPUBbits.WPUB6 = 0; } while(0)

// get/set SCL2 aliases
#define SCL2_TRIS               TRISBbits.TRISB7
#define SCL2_LAT                LATBbits.LATB7
#define SCL2_PORT               PORTBbits.RB7
#define SCL2_WPU                WPUBbits.WPUB7
#define SCL2_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SCL2_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SCL2_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SCL2_GetValue()           PORTBbits.RB7
#define SCL2_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SCL2_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SCL2_SetPullup()      do { WPUBbits.WPUB7 = 1; } while(0)
#define SCL2_ResetPullup()    do { WPUBbits.WPUB7 = 0; } while(0)

// get/set RS485_TX_EN aliases
#define RS485_TX_EN_TRIS               TRISCbits.TRISC0
#define RS485_TX_EN_LAT                LATCbits.LATC0
#define RS485_TX_EN_PORT               PORTCbits.RC0
#define RS485_TX_EN_WPU                WPUCbits.WPUC0
#define RS485_TX_EN_ANS                ANSELCbits.ANSC0
#define RS485_TX_EN_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RS485_TX_EN_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RS485_TX_EN_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RS485_TX_EN_GetValue()           PORTCbits.RC0
#define RS485_TX_EN_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RS485_TX_EN_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RS485_TX_EN_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define RS485_TX_EN_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define RS485_TX_EN_SetAnalogMode()  do { ANSELCbits.ANSC0 = 1; } while(0)
#define RS485_TX_EN_SetDigitalMode() do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set RS485_nRX_EN aliases
#define RS485_nRX_EN_TRIS               TRISCbits.TRISC1
#define RS485_nRX_EN_LAT                LATCbits.LATC1
#define RS485_nRX_EN_PORT               PORTCbits.RC1
#define RS485_nRX_EN_WPU                WPUCbits.WPUC1
#define RS485_nRX_EN_ANS                ANSELCbits.ANSC1
#define RS485_nRX_EN_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define RS485_nRX_EN_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define RS485_nRX_EN_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define RS485_nRX_EN_GetValue()           PORTCbits.RC1
#define RS485_nRX_EN_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define RS485_nRX_EN_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define RS485_nRX_EN_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define RS485_nRX_EN_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define RS485_nRX_EN_SetAnalogMode()  do { ANSELCbits.ANSC1 = 1; } while(0)
#define RS485_nRX_EN_SetDigitalMode() do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set Pump_SW aliases
#define Pump_SW_TRIS               TRISCbits.TRISC2
#define Pump_SW_LAT                LATCbits.LATC2
#define Pump_SW_PORT               PORTCbits.RC2
#define Pump_SW_WPU                WPUCbits.WPUC2
#define Pump_SW_ANS                ANSELCbits.ANSC2
#define Pump_SW_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Pump_SW_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Pump_SW_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Pump_SW_GetValue()           PORTCbits.RC2
#define Pump_SW_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Pump_SW_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Pump_SW_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define Pump_SW_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define Pump_SW_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define Pump_SW_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set Fill_SW aliases
#define Fill_SW_TRIS               TRISCbits.TRISC3
#define Fill_SW_LAT                LATCbits.LATC3
#define Fill_SW_PORT               PORTCbits.RC3
#define Fill_SW_WPU                WPUCbits.WPUC3
#define Fill_SW_ANS                ANSELCbits.ANSC3
#define Fill_SW_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define Fill_SW_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define Fill_SW_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define Fill_SW_GetValue()           PORTCbits.RC3
#define Fill_SW_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define Fill_SW_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define Fill_SW_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define Fill_SW_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define Fill_SW_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define Fill_SW_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()    do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()   do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()   do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()         PORTCbits.RC4
#define RC4_SetDigitalInput()   do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()  do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()     do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()   do { WPUCbits.WPUC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()    do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()   do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()   do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()         PORTCbits.RC5
#define RC5_SetDigitalInput()   do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()  do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()     do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()   do { WPUCbits.WPUC5 = 0; } while(0)

// get/set nSPI_CS aliases
#define nSPI_CS_TRIS               TRISCbits.TRISC6
#define nSPI_CS_LAT                LATCbits.LATC6
#define nSPI_CS_PORT               PORTCbits.RC6
#define nSPI_CS_WPU                WPUCbits.WPUC6
#define nSPI_CS_ANS                ANSELCbits.ANSC6
#define nSPI_CS_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define nSPI_CS_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define nSPI_CS_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define nSPI_CS_GetValue()           PORTCbits.RC6
#define nSPI_CS_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define nSPI_CS_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define nSPI_CS_SetPullup()      do { WPUCbits.WPUC6 = 1; } while(0)
#define nSPI_CS_ResetPullup()    do { WPUCbits.WPUC6 = 0; } while(0)
#define nSPI_CS_SetAnalogMode()  do { ANSELCbits.ANSC6 = 1; } while(0)
#define nSPI_CS_SetDigitalMode() do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set SDO1 aliases
#define SDO1_TRIS               TRISCbits.TRISC7
#define SDO1_LAT                LATCbits.LATC7
#define SDO1_PORT               PORTCbits.RC7
#define SDO1_WPU                WPUCbits.WPUC7
#define SDO1_ANS                ANSELCbits.ANSC7
#define SDO1_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SDO1_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SDO1_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SDO1_GetValue()           PORTCbits.RC7
#define SDO1_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SDO1_SetPullup()      do { WPUCbits.WPUC7 = 1; } while(0)
#define SDO1_ResetPullup()    do { WPUCbits.WPUC7 = 0; } while(0)
#define SDO1_SetAnalogMode()  do { ANSELCbits.ANSC7 = 1; } while(0)
#define SDO1_SetDigitalMode() do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/