#ifndef TIME_BOMB_USER_TYPES_H
#define TIME_BOMB_USER_TYPES_H

#include <stdint.h>

typedef struct
{
    uint8_t timer_cntr;
} tb_user_data_t;

#define TB_USER_DATA(ptr)   ((tb_user_data_t *) ptr)

#endif  // TIME_BOMB_USER_TYPES_H