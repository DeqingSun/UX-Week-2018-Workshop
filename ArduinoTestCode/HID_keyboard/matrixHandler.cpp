#include "matrixHandler.h"


#define MATRIX_ROWS 3
#define MATRIX_COLS 9
uint8_t rowpins[MATRIX_ROWS] = {26, 27, 28};
uint8_t colpins[MATRIX_COLS] = {3, 4, 10, 23, 24, 25, 9, 7, 6};

uint8_t pixel_to_row[25] = {0, 1, 0, 1, 0,
                            2, 2, 2, 2, 2,
                            1, 0, 1, 2, 1,
                            0, 0, 0, 0, 0,
                            2, 1, 2, 1, 2
                           };

uint8_t pixel_to_col[25] = {0, 3, 1, 4, 2,
                            3, 4, 5, 6, 7,
                            1, 8, 2, 8, 0,
                            7, 6, 5, 4, 3,
                            2, 6, 0, 5, 1
                           };

volatile uint8_t currentRow = 0;


MatrixHandler *handle = NULL;

/** TIMTER2 peripheral interrupt handler. This interrupt handler is called whenever there it a TIMER2 interrupt
   Don't mess with this line. really.
*/
extern "C"  {
  void TIMER2_IRQHandler(void) {
    IRQ_MATRIX_HANDLER();
  }
}



MatrixHandler::MatrixHandler() {
  memset(matrix_buffer, 0x0, MATRIX_COLS * MATRIX_ROWS);
}

MatrixHandler::~MatrixHandler(void) {}

boolean MatrixHandler::begin(void) {
  handle = this;

  for (uint8_t c = 0; c < MATRIX_COLS ; c++) {
    pinMode(colpins[c], OUTPUT);
    digitalWrite(colpins[c], HIGH);
  }


  for (uint8_t r = 0; r < MATRIX_ROWS ; r++) {
    pinMode(rowpins[r], OUTPUT);
    digitalWrite(rowpins[r], LOW);
  }

  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      matrix_buffer[r][c] = 0;
    }
  }

  currentRow = 0;

  startTimer();

  return true;
}

// Matrix object function called by IRQ handler for each row
// This is not optimized at all but its not so bad either!
void MatrixHandler::rowHandler(void) {
  // disable current row
  digitalWrite(rowpins[currentRow], LOW);
  for (uint8_t c = 0; c < MATRIX_COLS; c++) {
    digitalWrite(colpins[c], HIGH);
  }

  // go to next row
  if (++currentRow >= MATRIX_ROWS) {
    currentRow = 0;
  }

  //Serial.print("Row: "); Serial.println(currentRow);

  for (uint8_t c = 0; c < MATRIX_COLS; c++) {
    if (matrix_buffer[currentRow][c]) {
      digitalWrite(colpins[c], LOW);    // Change column states for new row
    }
  }
  digitalWrite(rowpins[currentRow], HIGH);
}


// This sets up the IRQ for timer 2 to run the matrix refresh.
void MatrixHandler::startTimer(void)
{
  NRF_TIMER2->MODE = TIMER_MODE_MODE_Timer;              // Set the timer in Counter Mode
  NRF_TIMER2->TASKS_CLEAR = 1;                           // clear the task first to be usable for later
  NRF_TIMER2->PRESCALER   = 4;
  NRF_TIMER2->BITMODE = TIMER_BITMODE_BITMODE_16Bit;     //Set counter to 16 bit resolution
  NRF_TIMER2->CC[0] = 1000;                               //Set value for TIMER2 compare register 0
  NRF_TIMER2->CC[1] = 0;                                   //Set value for TIMER2 compare register 1

  // Enable interrupt on Timer 2, both for CC[0] and CC[1] compare match events
  NRF_TIMER2->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos) ;
  NVIC_EnableIRQ(TIMER2_IRQn);

  NRF_TIMER2->TASKS_START = 1;               // Start TIMER2
}


void IRQ_MATRIX_HANDLER(void) {
  if ((NRF_TIMER2->EVENTS_COMPARE[0] != 0) && ((NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk) != 0))
  {
    NRF_TIMER2->EVENTS_COMPARE[0] = 0;         //Clear compare register 0 event
    handle->rowHandler();
    NRF_TIMER2->CC[0] += 1000;
  }
}

void MatrixHandler::clear(void) {
  fillScreen(0);
}

void MatrixHandler::fillScreen(uint16_t color) {
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      matrix_buffer[r][c] = color;
    }
  }
}

void MatrixHandler::show(const uint8_t bitmap[]) {
  clear();

  uint8_t counter = 0;
  for (int i = 0; i < 5; i++) {
    uint8_t lineContent = bitmap[i];
    for (int j = 0; j < 5; j++) {
      if (lineContent & (1 << (4 - j))) {
        matrix_buffer[pixel_to_row[counter]][pixel_to_col[counter]] = 1;
      }
      counter++;
    }
  }
}

void MatrixHandler::setPixel(int x, int y, int c) {
  int counter = y * 5 + x;
  matrix_buffer[pixel_to_row[counter]][pixel_to_col[counter]] = c;
}

void MatrixHandler::scroll(const uint32_t bitmap[], int offset) {
  clear();

  uint8_t counter = 0;
  for (int i = 0; i < 5; i++) {
    uint32_t lineContent = bitmap[i];
    for (int j = 0; j < 5; j++) {
      if (lineContent & (1 << (4 - j + offset))) {
        matrix_buffer[pixel_to_row[counter]][pixel_to_col[counter]] = 1;
      }
      counter++;
    }
  }
}\

/*************************************************************************************************/
const uint32_t MatrixHandler::UXWEEK[5] =
{ 0b1001010100010001011110111101001,
  0b1001010100010001010000100001010,
  0b1001001000010101011110111101100,
  0b1001010100010101010000100001010,
  0b0110010100001010011110111101001,
};

const uint8_t MatrixHandler::EMPTYHEART[5] =
{ B01010,
  B10101,
  B10001,
  B01010,
  B00100,
};

const uint8_t MatrixHandler::HEART[5] =
{ B01010,
  B11111,
  B11111,
  B01110,
  B00100,
};

const uint8_t MatrixHandler::NO[5] =
{ B10001,
  B01010,
  B00100,
  B01010,
  B10001,
};

const uint8_t MatrixHandler::YES[5] =
{ B00001,
  B00010,
  B10100,
  B01000,
  B00000,
};

const uint8_t MatrixHandler::SIGNAL[8][5] =
{
  { B00000,
    B00000,
    B00000,
    B00100,
    B01110,
  },
  { B00000,
    B00000,
    B00000,
    B01110,
    B10101,
  },
  { B00000,
    B00000,
    B01110,
    B10001,
    B00100,
  },
  { B00000,
    B01110,
    B10001,
    B00000,
    B00100,
  },
  { B01110,
    B10001,
    B00000,
    B00000,
    B00100,
  },
  {
    B00000,
    B01110,
    B10001,
    B00000,
    B00100,
  },
  {
    B00000,
    B00000,
    B01110,
    B10001,
    B00100,
  },
  { B00000,
    B00000,
    B00000,
    B01110,
    B10101,
  },
};
