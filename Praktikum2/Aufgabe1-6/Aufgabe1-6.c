typedef uint8_t byte;

/**
 * Aufgabe 1+2
 */
enum BITS uint_8 {
    BIT0 = 0b10000000,
    BIT1 = 0b01000000,
    BIT2 = 0b00100000,
    BIT3 = 0b00010000,
    BIT4 = 0b00001000,
    BIT5 = 0b00000100,
    BIT6 = 0b00000010,
    BIT7 = 0b00000001
}

int main(int, char**) {
    byte test = 0;

    // Aufgabe 3
    test |= BIT0;

    // Aufgabe 4
    test &= ~BIT0;

    // Aufgabe 5
    test |= (BIT1|BIT2|BIT3);

    // Aufgabe 6
    test &= ~(BIT1|BIT2|BIT3);
}
