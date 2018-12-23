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
