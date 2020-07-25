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

    // computation memory
    millis_t last_active; 
    millis_t last_duration;

    Partition* next;      // for prio/linking
};

#endif