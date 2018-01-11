#ifndef NONOGRAM_H
#define NONOGRAM_H

#include <vector>

#include "linesolver.h"

class Nonogram {

public:
	Nonogram();
	~Nonogram();
	void initPlayGround();
    void setOption(std::vector<std::vector<short>> options);
    void run();
    void propagate();
private:

	unsigned int *m_definedPlayGround;
	unsigned int *m_valuePlayGround;
    std::vector<std::vector<short>> m_options;
    LineSolver m_solver;

};

#endif // NONOGRAM_H
