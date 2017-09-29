#ifndef OS_LIB_INTERFACE
#define OS_LIB_INTERFACE

#include "Os_DataTypes.h"

void OsMoveMemory(_IN_ PVoid dest, 
                  _IN_ PVoid src, 
                  _IN_ size_t length);

void OsAwaitSecond(_IN_ size_t secondsToSleep);

//ms, 1 s = 1000 ms
void OsAwaitMillisecond(_IN_ size_t sillisecondsToSleep);

//us, 1 ms = 1000 us
void OsAwaitMicrosecond(_IN_ size_t microsecondsToSleep);

#endif