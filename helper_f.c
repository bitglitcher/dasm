/*
Author: Benjamin Herrera Navarro
Date: 10/2/2020
2:39AM

Helper functions for backend description files
*/

#include <stdint.h>



int16_t swap_16(int16_t data)
{
    return (data >> 8) | (data << 8);
}