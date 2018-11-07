/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PACKET_H
#define	PACKET_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/eusart.h"
#include "common.h"
#include "settings.h"
#include "status.h"

/*
 * Packet structure
 * Header:
 *  Description         No. Bytes
 *  -----------         ---------
 *  start_flag          1
 *  dest_addr           1
 *  src_addr            1
 *  payload_len         2
 *  payload_type        1
 *  header_checksum     1
 * 
 * Payload:
 *  Description         No. Bytes
 *  -----------         ---------
 *  payload             payload_len
 *  checksum            1
 *  end_flag            1
 */

#define PACKET_START_FLAG      0xAB
#define PACKET_END_FLAG        0xBA
#define PACKET_PAYLOAD_MAX_LEN 128
#define PACKET_HEADER_LEN      7
#define PACKET_PAYLOAD_EXTRA   2
#define PACKET_MAX_SIZE		   PACKET_HEADER_LEN + PACKET_PAYLOAD_MAX_LEN + PACKET_PAYLOAD_EXTRA

#define PACKET_CHECKSUM_OK 	   0
#define PACKET_RX_OK           1

#define PACKET_PAYLOAD_TYPE_ECHO 0x00
#define PACKET_PAYLOAD_TYPE_SETTING 0x01
#define PACKET_PAYLOAD_TYPE_STATUS 0x02


typedef enum {PACKET_State_idle,
              PACKET_State_start,
              PACKET_State_dest_addr,
              PACKET_State_src_addr,
              PACKET_State_length_l,
              PACKET_State_length_h,
              PACKET_State_payload_type,
              PACKET_State_header_checksum,
              PACKET_State_getting_payload,
              PACKET_State_payload,
              PACKET_State_checksum,
              PACKET_State_end_flag
}PACKET_RxState_t;

typedef enum {
    PACKET_Type_temp = 0,
    PACKET_Type_level = 1
}PACKET_Type_t;


typedef union {
    uint8_t packet_arr[PACKET_MAX_SIZE];
    __pack struct {
        uint8_t start_flag;
        uint8_t dest_address;
        uint8_t src_address;
        uint16_t payload_len;
        uint8_t payload_type;
        uint8_t header_checksum;
        union {
            uint8_t payload[PACKET_PAYLOAD_MAX_LEN];
            struct {
                union {
                    SETTINGS_payload_t stgs_payload;
                    STATUS_payload_t status_payload;
                };
                uint8_t checksum; // can ONLY be used in conjunction with stgs_payload or status_payload!!
                uint8_t end_flag; // this also
            };
        };
    };
}PACKET_pkt_t;


void PACKET_Initialize(void);
void PACKET_SendPacket(PACKET_pkt_t *pkt);
void PACKET_UpdateAndSend(PACKET_pkt_t *pkt);
void PACKET_UpdateAddresses(PACKET_pkt_t *pkt, uint8_t dest_address, uint8_t src_address);
void PACKET_CreatePacket(PACKET_pkt_t *pkt, uint16_t send_data_length, uint8_t *send_data, PACKET_Type_t packet_type, uint8_t dest_addr, uint8_t src_addr);
PACKET_pkt_t * PACKET_get_rx_packet_ptr(void);
uint8_t PACKET_calculate_checksum(uint8_t *packet, uint16_t len);
uint8_t PACKET_Available(void);
uint8_t PACKET_EUSART_Bytes_Available(void);
uint8_t PACKET_handle_byte(uint8_t data_byte);
#endif	/* PACKET_H */

