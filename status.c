#include "status.h"

uint16_t STATUS_failsafe_timer = 0;
STATUS_curr_status_t curr_status = {0};


void STATUS_update_failsafe_timer(void)
{
    curr_status.arr[STATUS_FAILSAFE_TIMER] = STATUS_FAILSAFE_TIMER_SET_VAL;
}

void STATUS_tick_failsafe_timer(void)
{
    if (curr_status.arr[STATUS_FAILSAFE_TIMER] > 0)
    {
        curr_status.arr[STATUS_FAILSAFE_TIMER] -= 1;
        
    }
}

uint16_t STATUS_write(STATUS_curr_status_t *status, uint8_t status_num, uint16_t status_val)
{
    if ((STATUS_WRITABLE >> status_num) & 0x01)
    {
        status->arr[status_num] = status_val;
        return 0;
    }
    return 1;
}

uint16_t STATUS_read(STATUS_curr_status_t *status, uint8_t status_num)
{
    return status->arr[status_num];
}
