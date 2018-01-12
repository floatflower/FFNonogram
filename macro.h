#ifndef MACRO_H
#define MACRO_H

#define PLAYGROUND_SIZE 5
#define INPUTDATA_ROWS PLAYGROUND_SIZE*2

const unsigned int bitGetter[32] = {
    0x80000000, // 0
    0x40000000, // 1
    0x20000000, // 2
    0x10000000, // 3
    0x8000000,  // 4
    0x4000000,  // 5
    0x2000000,  // 6
    0x1000000,  // 7
    0x800000,   // 8
    0x400000,   // 9
    0x200000,   // 10
    0x100000,   // 11
    0x80000,    // 12
    0x40000,    // 13
    0x20000,    // 14
    0x10000,    // 15
    0x8000,     // 16
    0x4000,     // 17
    0x2000,     // 18
    0x1000,     // 19
    0x800,      // 20
    0x400,      // 21
    0x200,      // 22
    0x100,      // 23
    0x80,       // 24
    0x40,       // 25
    0x20,       // 26
    0x10,       // 27
    0x8,        // 28
    0x4,        // 29
    0x2,        // 30
    0x1,        // 31
};

const unsigned int bitCancel[32] = {
    0x7FFFFFFF, // 0
    0xBFFFFFFF, // 1
    0xDFFFFFFF, // 2
    0xEFFFFFFF, // 3
    0xF7FFFFFF, // 4
    0xFBFFFFFF, // 5
    0xFDFFFFFF, // 6
    0xFEFFFFFF, // 7
    0xFF7FFFFF, // 8
    0xFFBFFFFF, // 9
    0xFFDFFFFF, // 10
    0xFFEFFFFF, // 11
    0xFFF7FFFF, // 12
    0xFFFBFFFF, // 13
    0xFFFDFFFF, // 14
    0xFFFEFFFF, // 15
    0xFFFF7FFF, // 16
    0xFFFFBFFF, // 17
    0xFFFFDFFF, // 18
    0xFFFFEFFF, // 19
    0xFFFFF7FF, // 20
    0xFFFFFBFF, // 21
    0xFFFFFDFF, // 22
    0xFFFFFEFF, // 23
    0xFFFFFF7F, // 24
    0xFFFFFFBF, // 25
    0xFFFFFFDF, // 26
    0xFFFFFFEF, // 27
    0xFFFFFFF7, // 28
    0xFFFFFFFB, // 29
    0xFFFFFFFD, // 30
    0xFFFFFFFE, // 31
};

#define GET_BIT(data, position) (data & bitGetter[position])

#endif // MACRO_H
