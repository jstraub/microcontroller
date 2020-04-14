struct RingBuffer {
  uint16_t data[60];
  uint16_t N;
  uint16_t i;
};

void Init(struct RingBuffer* buf);
void Insert(struct RingBuffer* buf, uint16_t x);
uint16_t GetCur(struct RingBuffer* buf);
uint16_t Mean(struct RingBuffer* buf);
float MeanFloat(struct RingBuffer* buf);


