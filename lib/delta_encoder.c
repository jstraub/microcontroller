
#include "delta_encoder.h"

void InitDeltaEncoder(struct DeltaEncoder* del, int32_t sum0) {
  del->sum = sum0;
}

int8_t UpdateDelta(struct DeltaEncoder* del, uint16_t cur) {
  int32_t delta = (int32_t)cur - del->sum;
  int8_t delta8 = 0;
  if (delta < -127) {
    delta8 = (int8_t)-127;
  } else if (delta > 127) {
    delta8 = (int8_t)127;
  } else {
    delta8 = (int8_t) delta;
  }
  del->sum += (int32_t)delta8;
  return delta8;
}
