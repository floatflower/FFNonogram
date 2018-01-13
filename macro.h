#ifndef MACRO_H
#define MACRO_H

#define PLAYGROUND_SIZE 25
#define INPUTDATA_ROWS PLAYGROUND_SIZE*2

const unsigned int bitGetter[32] = {
    0x80000000, // 0
    0x40000000, // 1
    0x20000000, // 2
    0x10000000, // 3
    0x08000000, // 4
    0x04000000, // 5
    0x02000000, // 6
    0x01000000, // 7
    0x00800000, // 8
    0x00400000, // 9
    0x00200000, // 10
    0x00100000, // 11
    0x00080000, // 12
    0x00040000, // 13
    0x00020000, // 14
    0x00010000, // 15
    0x00008000, // 16
    0x00004000, // 17
    0x00002000, // 18
    0x00001000, // 19
    0x00000800, // 20
    0x00000400, // 21
    0x00000200, // 22
    0x00000100, // 23
    0x00000080, // 24
    0x00000040, // 25
    0x00000020, // 26
    0x00000010, // 27
    0x00000008, // 28
    0x00000004, // 29
    0x00000002, // 30
    0x00000001, // 31
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

const unsigned int completeChecker[32] = {
    0xFFFFFFFF, // 0
    0x7FFFFFFF, // 1
    0x3FFFFFFF, // 2
    0x1FFFFFFF, // 3
    0x0FFFFFFF, // 4
    0x07FFFFFF, // 5
    0x03FFFFFF, // 6
    0x01FFFFFF, // 7
    0x00FFFFFF, // 8
    0x007FFFFF, // 9
    0x003FFFFF, // 10
    0x001FFFFF, // 11
    0x000FFFFF, // 12
    0x0007FFFF, // 13
    0x0003FFFF, // 14
    0x0001FFFF, // 15
    0x0000FFFF, // 16
    0x00007FFF, // 17
    0x00003FFF, // 18
    0x00001FFF, // 19
    0x00000FFF, // 20
    0x000007FF, // 21
    0x000003FF, // 22
    0x000001FF, // 23
    0x000000FF, // 24
    0x0000007F, // 25
    0x0000003F, // 26
    0x0000001F, // 27
    0x0000000F, // 28
    0x00000007, // 29
    0x00000003, // 30
    0x00000001, // 31
}; // if definedLine & COMPLETE == definedLine then COMPLETE

#endif // MACRO_H
