#include <stdio.h>

struct DeltaEncoder {
  int32_t sum;
};

void InitDeltaEncoder(struct DeltaEncoder* del, int32_t sum0);

int8_t UpdateDelta(struct DeltaEncoder* del, uint16_t cur);
