#ifndef PARTITION_H
#define PARTITION_H

#include <max6675.h>
#include "./config.h"
#include "./macros.h"
#include "./time.h"

/***
 * The heating cell
 */
class Partition
{
public:
    ushort state;         // type: PARTITION_STATE
private:
    ushort pin;           // GPIO
    ushort id;            
    const char name[124]; // for logging

    millis_t last_active; //
};

#endif