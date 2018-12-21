#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <xc.h>
#include <stdint.h>
#include "settings.h"
#include "status.h"

extern SETTINGS_settings_t settings;
extern STATUS_curr_status_t curr_status;
void handle_rx_packet(void);

#endif
