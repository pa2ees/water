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

PACKET_pkt_t PACKET_pkt;

PACKET_RxState_t PACKET_RxState;

void PACKET_Initialize(void)
{
    PACKET_RxState = PACKET_State_idle;
    
}

void PACKET_SendPacket(PACKET_pkt_t *pkt)
{
    uint16_t i;
    DEBUG_PRINT(("Payload Len: %d", pkt->payload_len));
    for (i = 0; i < PACKET_HEADER_LEN + pkt->payload_len + PACKET_PAYLOAD_EXTRA; i++)
    {
        EUSART_Write(pkt->packet_arr[i]);
    }
}

void PACKET_UpdateAndSend(PACKET_pkt_t *pkt)
{
    pkt->checksum = PACKET_calculate_checksum(pkt->packet_arr, pkt->payload_len + PACKET_HEADER_LEN);
    PACKET_SendPacket(pkt);
}

/* PACKET_CreatePacket
 * send_str_length  the length of the string to send
 * send_str         the string to send
 * *packet          pointer to an array that will become the packet to send
 * type             the type of packet
 * 
 * return value     the length of packet
 */
void PACKET_CreatePacket(PACKET_pkt_t *pkt, uint16_t send_data_length, uint8_t *send_data, PACKET_Type_t packet_type)
{
    uint8_t *packet_ptr;
    uint8_t i = 0;
    
    //packet_ptr = packet;

    // Loading start flag
    pkt->start_flag = PACKET_START_FLAG;
    
    // Loading Type
    pkt->payload_type = (uint8_t)packet_type;
    
    // Loading Payload Length high byte
    pkt->payload_len = send_data_length;
    
    // Loading Header Checksum
    pkt->header_checksum = PACKET_calculate_checksum(pkt->packet_arr, PACKET_HEADER_LEN-1);
    
    // Loading Payload
    for (i = 0; i < send_data_length; i++)
    {
        pkt->payload[i] = send_data[i];

    }
    
    // Loading Checksum
    pkt->checksum = PACKET_calculate_checksum(pkt->packet_arr, send_data_length + PACKET_HEADER_LEN);
    
    // Loading end flag
    pkt->end_flag = PACKET_END_FLAG;
      
}


PACKET_pkt_t * PACKET_get_rx_packet_ptr(void)
{
    return &PACKET_pkt;
}

uint8_t PACKET_calculate_checksum(uint8_t *data, uint16_t data_len)
{
    uint16_t i = 0;
    uint8_t checksum = 0;
    for (i = 0; i < data_len; i++)
    {        
        checksum += data[i];
        DEBUG_PRINT_OFF(("%d, %d\n", data[i], checksum));
    }
    
    return (uint8_t)((~checksum + 0x01) & 0xFF);
}

uint8_t PACKET_Available(void)
{
    uint8_t b;
    if (PACKET_EUSART_Bytes_Available())
    {
        b = EUSART_Read();
        DEBUG_PRINT_OFF(("Read %d\n", b));
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
    uint16_t i;

    if (PACKET_RxState == PACKET_State_idle)
    {
        PACKET_RxPtr = PACKET_RxPacket;
        PACKET_RxState = PACKET_State_start;
        DEBUG_PRINT_OFF(("idle\n"));
    }
    
    if (PACKET_RxState == PACKET_State_start)
    { // looking for start byte
        DEBUG_PRINT_OFF(("start\n"));
        if (data_byte != PACKET_START_FLAG)
        {
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_type;
        DEBUG_PRINT_OFF(("start ok\n"));
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
        PACKET_RxState = PACKET_State_length_l;
        DEBUG_PRINT_OFF(("type %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_length_l)
    { // looking for length high byte
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_length_h;
        DEBUG_PRINT_OFF(("lenh %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_length_h)
    { // looking for length low byte
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        PACKET_RxState = PACKET_State_header_checksum;
        DEBUG_PRINT_OFF(("lenl %d\n", data_byte));
    }

    else if (PACKET_RxState == PACKET_State_header_checksum)
    { // looking for header checksum
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;
        DEBUG_PRINT_OFF(("cksm %d\n", data_byte));
        len = PACKET_RxPtr - PACKET_RxPacket;
        DEBUG_PRINT_OFF(("len %d\n", len));
        cksm = PACKET_calculate_checksum(PACKET_RxPacket, len);
        DEBUG_PRINT_OFF(("cksm %d\n", cksm));
        if (cksm != PACKET_CHECKSUM_OK)
        { // if the checksum is not right, return to idle state.
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }
        PACKET_Len = (uint16_t)((PACKET_RxPacket[3] << 8) | (PACKET_RxPacket[2]));
        PACKET_RxState = PACKET_State_payload;
        DEBUG_PRINT_OFF(("cksm ok\n"));
    }

    else if (PACKET_RxState == PACKET_State_payload)
    {
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;

        DEBUG_PRINT_OFF(("payload %d\n", data_byte));

        if ((PACKET_RxPtr - PACKET_RxPacket) >= (PACKET_Len + PACKET_HEADER_LEN))
        {
            PACKET_RxState = PACKET_State_checksum;
        }
    }

    else if (PACKET_RxState == PACKET_State_checksum)
    {
        *PACKET_RxPtr = data_byte;
        PACKET_RxPtr++;

        DEBUG_PRINT_OFF(("cksm %d\n", data_byte));

        if (PACKET_calculate_checksum(PACKET_RxPacket, (uint16_t)(PACKET_RxPtr - PACKET_RxPacket)) != PACKET_CHECKSUM_OK)
        { // if the checksum is not right, return to idle state.
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }

        PACKET_RxState = PACKET_State_end_flag;
        DEBUG_PRINT_OFF(("cksm ok\n"));
    }

    else if (PACKET_RxState == PACKET_State_end_flag)
    {
        *PACKET_RxPtr = data_byte;
        DEBUG_PRINT_OFF(("end flag\n"));
        if (data_byte != PACKET_END_FLAG)
        {
            PACKET_RxState = PACKET_State_idle;
            return 0;
        }

        DEBUG_PRINT_OFF(("end flag ok\n"));
        PACKET_RxState = PACKET_State_idle;

        for (i = 0; i < PACKET_HEADER_LEN + PACKET_Len + PACKET_PAYLOAD_EXTRA; i++)
        {
            PACKET_pkt.packet_arr[i] = PACKET_RxPacket[i];
        }

        //PACKET_pkt.start_flag = *PACKET_RxPacket[0];
        //PACKET_pkt.packet_type = *PACKET_RxPacket[1];
        //PACKET_pkt.packet_len = PACKET_len;
        //for (i = 0; i < PACKET_len; i++)
        // {
        //    PACKET_pkt.packet[i] = PACKET_RxPacket[i+5];
        // }
        return PACKET_RX_OK;

    }
    else
    {
        DEBUG_PRINT_OFF(("else\n"));
        PACKET_RxState = PACKET_State_idle;
        return 0;
        
    }
    
    return 0;
    
}
