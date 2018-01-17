#ifndef NONOGRAM_H
#define NONOGRAM_H

#include <vector>

#include "linesolver.h"
#include "playground.h"

class Nonogram {

public:
	Nonogram();
	~Nonogram();
	void initPlayGround();
    void setOption(std::vector<std::vector<short>> options);
    void run(int questionNumber);
    void propagate(PlayGround &playGround);
    void getColumn(int index, unsigned int &definedLine, unsigned int &valueLine);
    void setColumn(int index, unsigned int definedLine, unsigned int valueLine);
    void fp1(PlayGround &playGround);
    void backtracking(PlayGround &playGround);
    bool probe(PlayGround &playGround, int row, int col);
private:

    std::vector<std::vector<short>> m_options;
    LineSolver m_solver;
    PlayGround m_playGround;

};

#endif // NONOGRAM_H
