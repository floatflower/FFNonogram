#include "linesolver.h"

#include <iostream>

#include <macro.h>

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

LineSolver::LineSolver()
{

}

LineSolver::~LineSolver()
{

}

bool LineSolver::sovle(unsigned int &definedLine, unsigned int &valueLine)
{
    int lineLength = PLAYGROUND_SIZE - 1;
    int optionsAmount = m_options.size();
    unsigned int tmp_definedLine = definedLine;
    unsigned int tmp_valueLine = valueLine;
    bool result = paint(lineLength, optionsAmount, tmp_definedLine, tmp_valueLine);
    definedLine = tmp_definedLine;
    valueLine = tmp_valueLine;
    return result;
}

bool LineSolver::paint(int i, int j, unsigned int &definedLine, unsigned int &valueLine)
{
    std::cout << "paint(" << i << ", " << j << ");" << std::endl;
    if (i == 0) return true;

    return paintp(i, j, definedLine, valueLine);
}

bool LineSolver::paintp(int i, int j, unsigned int &definedLine, unsigned int &valueLine)
{
    std::cout << "paintp(" << i << ", " << j << ");" << std::endl;
    bool f0Result = fix0(i, j, definedLine, valueLine);
    bool f1Result = fix1(i, j, definedLine, valueLine);

    unsigned int tmp_definedLine1 = definedLine;
    unsigned int tmp_definedLine0 = definedLine;
    unsigned int tmp_value1 = valueLine;
    unsigned int tmp_value0 = valueLine;

    if (f0Result && !f1Result) {
        std::cout << "fix0 is accepted" << std::endl;
        paint0(i, j, tmp_definedLine0, tmp_value0);
        definedLine = tmp_definedLine0;
        valueLine = tmp_value0;

    }
    else if (f1Result && !f0Result) {
        std::cout << "fix1 is accepted" << std::endl;
        paint1(i, j, tmp_definedLine1, tmp_value1);
        definedLine = tmp_definedLine1;
        valueLine = tmp_value1;

    }
    else if (f1Result && f0Result) {
        std::cout << "merge fix1(" << i << "," << j << ") and fix0(" << i << "," << j << ")" << std::endl;
        paint0(i, j, tmp_definedLine0, tmp_value0);
        paint1(i, j, tmp_definedLine1, tmp_value1);
        merge(definedLine, valueLine, tmp_definedLine0, tmp_value0, tmp_definedLine1, tmp_value1);
    }
    else {
        return false;
    }
    return true;
}

void LineSolver::paint0(int i, int j, unsigned int &definedLine, unsigned int &valueLine)
{
    /**
    * Because all of bits have been set to 0 at initial stage,
    * So, just set defined row to 1.
    */
    std::cout << "paint0(" << i << ", " << j << ");" << std::endl;
    definedLine |= bitGetter[i - 1];
    paint(i - 1, j, definedLine, valueLine);
}

void LineSolver::paint1(int i, int j, unsigned int &definedLine, unsigned int &valueLine)
{
    std::cout << "paint1(" << i << ", " << j << ");" << std::endl;
    int option = m_options.at(j - 1);
    for (int k = i - 1; k >= i - option; k --) {
        definedLine |= bitGetter[k];
        valueLine |= bitGetter[k];
    }
    i -= option;
    if (i > 0) {
        i -= 1;
        definedLine |= bitGetter[i];
    }
    j -= 1;
    paint(i, j, definedLine, valueLine);
}

bool LineSolver::fix(int i, int j, unsigned int definedLine, unsigned int valueLine)
{
    std::cout << "fix(" << i << ", " << j << ");" << std::endl;
    if (i == 0 && j == 0) return true;
    if (i == 0 && j >= 1) return false;
    if (i < 0) return false;
    else return fix0(i, j, definedLine, valueLine) || fix1(i, j, definedLine, valueLine);
}

bool LineSolver::fix0(int i, int j, unsigned int definedLine, unsigned int valueLine)
{
    std::cout << "fix0(" << i << ", " << j << ");" << std::endl;
    int prev = i - 1;
    if (!getBit(definedLine, prev) // element not defined
        || (getBit(definedLine, prev)) && getBit(valueLine, prev)) // element defined but set 0
    {
        // element not defined
        return fix(prev, j, definedLine, valueLine);
    }
    else return false;
}

bool LineSolver::fix1(int i, int j, unsigned int definedLine, unsigned int valueLine)
{
    std::cout << "fix1(" << i << ", " << j << ");" << std::endl;
    if (j == 0) return false;

    bool currentOption = m_options.at(j - 1);
    if (i - currentOption < 0) return false;

    for (int currentFix = i - 1; currentFix >= i - currentOption; currentFix --) {
        if (getBit(definedLine, currentFix) && !getBit(valueLine, currentFix)) {
            return false;
        }
    }
    i -= currentOption;
    if (i > 0) {
        i --;
        if (getBit(definedLine, i) && getBit(valueLine, i)) {
            return false;
        }
    }

    j -= 1;
    return fix(i, j, definedLine, valueLine);
}

void LineSolver::merge(unsigned int &targetDefinedLine, unsigned int &targetValueLine,
           unsigned int &definedLine0, unsigned int &valueLine0,
           unsigned int &definedLine1, unsigned int &valueLine1)
{
    targetDefinedLine = definedLine0 & definedLine1;
    targetValueLine = valueLine0 & valueLine1;
}

void LineSolver::setOptions(std::vector<short> options)
{
    m_options = options;
}

bool LineSolver::getBit(unsigned int data, int position)
{
    return (data >> (32 - position)) & 1;
}

void LineSolver::printLine(unsigned int definedLine, unsigned int valueLine)
{
    for (int i = 1; i < PLAYGROUND_SIZE; i ++) {
        if (getBit(definedLine, i))
        {
            getBit(valueLine, i) ? std::cout << "1 " : std::cout << "0 ";
        }
        else {
            std::cout << "-1 ";
        }
        std::cout << std::endl;
    }
}
