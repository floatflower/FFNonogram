#ifndef LINESOVER_H
#define LINESOVER_H

#include <vector>

class LineSolver {
public:
	
	LineSolver();
	~LineSolver();
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
private:
    std::vector<short> m_options;
    int m_definedLine;
    int m_valueLine;
};

#endif LINESOVER_H
