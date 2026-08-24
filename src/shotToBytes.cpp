#include "shotToBytes.h"

namespace Stopwatch {

ShotBytes shotToBytes(Shot s) {
    ShotBytes bytes{
        .one = 0,
        .two = 0
    };
    // mask position to 2 bits and shift 6 places to leading 2 bits of byte 1
    bytes.one |= (s.position & 0b11) << 6;
    // mask zone to 4 bits and shift 1 place to left in byte 1, leaving a gap between position
    bytes.one |= (s.zone & 0b1111) << 1;
    
    // convert float to unsigned fixed point
    unsigned int fixedPointSplit = static_cast<unsigned int>(s.split*100 + 0.5f);
    // shift bit 9 of split to LSB, mask, and place into byte 1
    bytes.one |= (fixedPointSplit >> 8) & 0b1;
    // mask split to 8 bits and place into byte 2
    bytes.two |= fixedPointSplit & 0b11111111;
    return bytes;
}

}