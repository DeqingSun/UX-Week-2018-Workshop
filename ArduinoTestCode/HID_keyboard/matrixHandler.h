#ifndef _MATRIX_HANDLER_H_
#define _MATRIX_HANDLER_H_

#include <Arduino.h>

void IRQ_MATRIX_HANDLER(void);

class MatrixHandler {
  public:
    MatrixHandler();
    ~MatrixHandler(void);
    boolean   begin(void);
    void      fillScreen(uint16_t color),
              clear(void),
              rowHandler(void);
    void      show(const uint8_t bitmap[]);
    void      scroll(const uint32_t bitmap[],int offset);

    static const uint8_t EMPTYHEART[5],  HEART[5], NO[5], YES[5], SIGNAL[8][5];
    static const uint32_t UXWEEK[5];
  private:
    void startTimer();

    uint8_t matrix_buffer[3][9];
};

#endif
