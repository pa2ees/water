/*
 * File:   packet.c
 * Author: erik
 *
 * Created on March 3, 2018, 4:45 PM
 */


#include "packet.h"

uint8_t PACKET_RxPacket[PACKET_MAX_SIZE];
uint8_t *PACKET_RxPtr;
uint16_t PACKET_Len;

PACKET_RxState_t PACKET_RxState;

void PACKET_Initialize(void)
{
    PACKET_RxState = PACKET_State_idle;
    
}

/* PACKET_CreatePacket
 * send_str_length  the length of the string to send
 * send_str         the string to send
 * *packet          pointer to an array that will become the packet to send
 * type             the type of packet
 * 
 * return value     the length of packet
 */
uint16_t PACKET_CreatePacket(uint16_t send_data_length, uint8_t *send_data, uint8_t *packet, PACKET_Type_t packet_type)
{
    uint8_t *packet_ptr;
    uint8_t i = 0;
    
    packet_ptr = packet;

    // Loading start flag
    *packet_ptr = PACKET_START_FLAG;
    packet_ptr++;
    
    // Loading Type
    *packet_ptr = (uint8_t)packet_type;
    packet_ptr++;
    
    // Loading Payload Length high byte
    *packet_ptr = (send_data_length >> 8) & 0xFF;
    packet_ptr++;
    
    // Loading Payload Length low byte
    *packet_ptr = (send_data_length) & 0xFF;
    packet_ptr++;
    
    // Loading Header Checksum
    *packet_ptr = PACKET_calculate_checksum(packet, 4);
    packet_ptr++;
    
    // Loading Payload
    for (i = 0; i < send_data_length; i++)
    {
        *packet_ptr = send_data[i];
        packet_ptr++;
    }
    
    // Loading Checksum
    *packet_ptr = PACKET_calculate_checksum(packet, send_data_length + 5);
    packet_ptr++;
    
    // Loading end flag
    *packet_ptr = PACKET_END_FLAG;
    
    return send_data_length + 7;
  
  
}

uint8_t PACKET_calculate_checksum(uint8_t *data, uint16_t data_len)
{
    uint16_t i = 0;
    uint8_t checksum = 0;
    for (i = 0; i < data_len; i++)
    {        
        checksum += data[i];
        DEBUG_PRINT(("%d, %d\n", data[i], checksum));
    }
    
    return (uint8_t)((~checksum + 0x01) & 0xFF);
}

uint8_t PACKET_Available(void)
{
    uint8_t b;
    if (PACKET_EUSART_Bytes_Available())
    {
        b = EUSART_Read();
        DEBUG_PRINT(("Read %d\n", b));
        return PACKET_handle_byte(b);
    }

    return 0;
}

uint8_t PACKET_EUSART_Bytes_Available(void)
{
    return EUSART_RxBytesAvailable();
}

/* get_packet_from_bytes
 * This function is intended to be called with each byte received
 * It will return a number greater than 0 (the length of the packet)
 * if a packet is received, and the packet is available
 * in the *packet array
 */
uint8_t PACKET_handle_byte(uint8_t data_byte)
{
    uint8_t cksm;
    uint16_t len;

    if (PACKET_RxState == PACKET_State_idle)
    {
        PACKET_RxPtr = PACKET_RxPacket;
        PACKET_RxState = PACKET_State_start;
        DEBUG_PRINT(("idle\n"));
    }
    
    if (PACKET_RxState == PACKET_State_start)
    { // looking for start byte
        DEBUG_PRINT(("start\n"));
        if (data_byte != PACKET_START_FLAG)
        {
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_type;
        DEBUG_PRINT(("start ok\n"));
    }
    
    // else if (PACKET_RxState == PACKET_State_start)
    // { // looking for type byte
    //     *PACKET_RxPtr = data_byte;
    //     PACKET_RxPtr++;
    //     PACKET_RxState = PACKET_State_type;
    //     
    // }

    else if (PACKET_RxState == PACKET_State_type)
    { // looking for type byte
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_length_h;
        DEBUG_PRINT(("type %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_length_h)
    { // looking for length high byte
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_length_l;
        DEBUG_PRINT(("lenh %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_length_l)
    { // looking for length low byte
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_header_checksum;
        DEBUG_PRINT(("lenl %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_header_checksum)
    { // looking for header checksum
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        DEBUG_PRINT(("cksm %d\n", data_byte));
        len = PACKET_RxPtr - PACKET_RxPacket;
        DEBUG_PRINT(("len %d\n", len));
        cksm = PACKET_calculate_checksum(PACKET_RxPacket, len);
        DEBUG_PRINT(("cksm %d\n", cksm));
        if (cksm != PACKET_CHECKSUM_OK)
        { // if the checksum is not right, return to idle state.
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }
        PACKET_Len = (uint16_t)((PACKET_RxPacket[2] << 8) | (PACKET_RxPacket[3]));
        PACKET_RxState = PACKET_State_payload;
        DEBUG_PRINT(("cksm ok\n"));
    }

    else if (PACKET_RxState == PACKET_State_payload)
    {
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;

        DEBUG_PRINT(("payload %d\n", data_byte));

        if ((PACKET_RxPtr - PACKET_RxPacket) >= (PACKET_Len + PACKET_HEADER_LEN))
        {
            PACKET_RxState = PACKET_State_checksum;
        }
    }

    else if (PACKET_RxState == PACKET_State_checksum)
    {
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;

        DEBUG_PRINT(("cksm %d\n", data_byte));

        if (PACKET_calculate_checksum(PACKET_RxPacket, (uint16_t)(PACKET_RxPtr - PACKET_RxPacket)) != PACKET_CHECKSUM_OK)
        { // if the checksum is not right, return to idle state.
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }

        PACKET_RxState = PACKET_State_end_flag;
        DEBUG_PRINT(("cksm ok\n"));
    }

    else if (PACKET_RxState == PACKET_State_end_flag)
    {
        *PACKET_RxPtr = data_byte;
        DEBUG_PRINT(("end flag\n"));
        if (data_byte != PACKET_END_FLAG)
        {
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }

        DEBUG_PRINT(("end flag ok\n"));
        PACKET_RxState = PACKET_State_idle;
        return PACKET_RX_OK;

    }
    else
    {
        DEBUG_PRINT(("else\n"));
        PACKET_RxState = PACKET_State_idle;
        return 0;
        
    }
    
    return 0;
    
}
