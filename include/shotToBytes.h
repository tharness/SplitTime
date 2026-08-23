#ifndef SHOT_TO_BYTES_H
#define SHOT_TO_BYTES_H

#include "data.h"

namespace Stopwatch {

/* 
fit 8 * 8 + 8 shots in 256 bytes of EEPROM
leaves 3 bytes per shot to represent position, split, and zone
position from 0-3 requires 2 bits
split can be treated as fixed point x.yz
values typlically between 3.30-4.30
if we assume minimum of 3.00 and 4.27 and offset by 3,
in fixed point we get values of 0-127 requiring 7 bits
zone from -1-11 requires 4 bits (offset with 1)
therefore minimum of 13 bits with sacrificed split range

if we do not do an offset, the nearest power of 2 to 430 is 512,
requiring 9 bits. 2 + 4 + 9 = 15 bits 
*/

/* 

encoding:
BYTE ONE | BYTE TWO
PP0ZZZZS   SSSSSSSS

where P = position, Z = zone, S = split, 0 = 0
P range: 0-3
Z range: 0-12 (+1 offset, therefore 0 represents -1 HOG and 12 is 11 THROUGH)
S range: 0-512 (fixed point 0.00-5.12)

*/ 
struct ShotBytes {
    unsigned char one;
    unsigned char two;
};

ShotBytes shotToBytes(Stopwatch::Shot s);

}

#endif // SHOT_TO_BYTES_H