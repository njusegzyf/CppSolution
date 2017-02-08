#ifndef OS_LIB_INTERFACE
#define OS_LIB_INTERFACE

#include "Os_DataTypes.h"

void OSMoveMemory(_IN_ PVoid dest, 
                  _IN_ PVoid src, 
                  _IN_ size_t length);

void OSAwaitSecond(_IN_ size_t secondsToSleep);

//ms, 1 s = 1000 ms
void OSAwaitMillisecond(_IN_ size_t sillisecondsToSleep);

//us, 1 ms = 1000 us
void OSAwaitMicrosecond(_IN_ size_t microsecondsToSleep);

#endif