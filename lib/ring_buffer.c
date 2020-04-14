#include <stdio.h>
#include "ring_buffer.h"

void Init(struct RingBuffer* buf) {
  buf->i = 0;
  buf->N = 60;
  for (uint16_t i=0; i< buf->N; ++i) {
    buf->data[i] = 0xffff;
  }
}

void Insert(struct RingBuffer* buf, uint16_t x) {
  buf->i = (buf->i + 1) % buf->N;
  buf->data[buf->i] = x;
}

uint16_t Mean(struct RingBuffer* buf) {
  uint32_t sum = 0;
  uint32_t N = 0;
  for (uint16_t i=0; i< buf->N; ++i) {
    if (buf->data[i] < 0xffff) {
      sum += buf->data[i];
      N ++;
    }
  }
  return (uint16_t) (sum/N);
}

float MeanFloat(struct RingBuffer* buf) {
  float sum = 0;
  float N = 0;
  for (uint16_t i=0; i< buf->N; ++i) {
    if (buf->data[i] < 0xffff) {
      sum += buf->data[i];
      N ++;
    }
  }
  return sum / N;
}

uint16_t GetCur(struct RingBuffer* buf) {
  return buf->data[buf->i];
}

