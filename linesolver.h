#ifndef LINESOVER_H
#define LINESOVER_H

#include <vector>

#include "fixcache.h"

class LineSolver {
public:
	
	LineSolver();
	~LineSolver();
    void init();
    bool sovle(unsigned int &definedLine, unsigned int &valueLine);

    bool paint(int i, int j, unsigned int &definedLine, unsigned int &valueLine);
    bool paintp(int i, int j, unsigned int &definedLine, unsigned int &valueLine);
    void paint0(int i, int j, unsigned int &definedLine, unsigned int &valueLine);
    void paint1(int i, int j, unsigned int &definedLine, unsigned int &valueLine);

    bool fix(int i, int j, unsigned int definedLine, unsigned int valueLine);
    bool fix0(int i, int j, unsigned int definedLine, unsigned int valueLine);
    bool fix1(int i, int j, unsigned int definedLine, unsigned int valueLine);

    void merge(unsigned int &targetDefinedLine, unsigned int &targetValueLine,
               unsigned int &definedLine0, unsigned int &valueLine0,
               unsigned int &definedLine1, unsigned int &valueLine1);

    void setOptions(std::vector<short> options);

    void printLine(unsigned int definedLine, unsigned int valueLine);
    void printBit(unsigned int data);
    bool isCompleted() { return m_complete; }
private:
    std::vector<short> m_options;
    int m_definedLine;
    int m_valueLine;
    bool m_complete;
    FixCache m_fix1Cache;
    FixCache m_fix0Cache;
};

#endif
