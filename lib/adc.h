void initAdc();
uint16_t readAdc(uint8_t adc);
float toVoltage(uint16_t adc, float maxVoltage);
