const int sevenSegmentPin = 13;
const int sevenSegmentClock = 12;
const int sevenSegmentLatch = 8;
const int sliderPin = A1;

// old compiler...
typedef unsigned char uint_8;

class SevenSegmentDisplay {
    int serial;
    int clock;
    int latch;
    static const uint_8 segmentDigits[10];
  public:
    SevenSegmentDisplay(int serial, int clock, int latch) : serial(serial), clock(clock), latch(latch) {
      pinMode(serial, OUTPUT);
      pinMode(clock, OUTPUT);
      pinMode(latch, OUTPUT);
      disable();
    }
    /**
     * Change the display to digit [0, 9]
     */
    void setDigit(int digit) {
      if(digit < 0 || digit > 9) return; // would rather throw here...
      writeValue(segmentDigits[digit]);
    }
    void disable() {
      writeValue(0);
    }
  private:
    void writeValue(uint_8 value) {
      digitalWrite(latch, LOW); // freeze display (avoid flicking)
      shiftOut(serial, clock, LSBFIRST, value);
      digitalWrite(latch, HIGH); // unfreeze
    }
};
const uint_8 SevenSegmentDisplay::segmentDigits[10] = {
      0b11111100, // 0
      0b01100000, // 1
      0b11011010, // 2
      0b11110010, // 3
      0b01100110, // 4
      0b10110110, // 5
      0b10111110, // 6
      0b11100000, // 7
      0b11111110, // 8
      0b11110110  // 9
    };

SevenSegmentDisplay sevenSegmentDisplay(sevenSegmentPin, sevenSegmentClock, sevenSegmentLatch);

void setup() {
  // nothing to set up explicitly
}

void loop() {
  int sliderValue = analogRead(sliderPin); // [0, 1023]
  int digit = sliderValue / 102;
  if(digit > 9) digit = 9; // introduces slight bias towards 9 (for 1020-1023)

  sevenSegmentDisplay.setDigit(digit);
}
