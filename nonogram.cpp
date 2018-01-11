#include "nonogram.h"

#include <iostream>

#include "macro.h"

/** ========================================================

PLAYGROUND_SIZE is the size of playground,
and its width and height should be real width + 1 and real height + 1.

It is because that the fix function will check the row whether match pattern (01*)*0?
But in this case, this first bit is 1 also can be accepted,
So create a one-bit bigger playground can handle this case.

Also, we can access data with real index, point(1, 1) will access [1][1].
(n, 0) and (0, n) is for extra hidden bits.

========================================================= */
#include "macro.h"

Nonogram::Nonogram()
{
	this->m_definedPlayGround = new unsigned int [PLAYGROUND_SIZE];
	this->m_valuePlayGround = new unsigned int [PLAYGROUND_SIZE];
}

Nonogram::~Nonogram()
{
	delete [] this->m_definedPlayGround;
	delete [] this->m_valuePlayGround;
}

void Nonogram::initPlayGround()
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_definedPlayGround[i] = 0;
		this->m_valuePlayGround[i] = 0;
	}
}

void Nonogram::setOption(std::vector<std::vector<short>> options)
{
    m_options = options;
}

void Nonogram::run()
{
    propagate();
    std::cout << "---------------------" << std::endl;
}

void Nonogram::propagate()
{
    // Do init playground rows
    // pass 1 ~ playground size
    for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
        m_solver.setOptions(m_options.at(i));
        m_solver.sovle(this->m_definedPlayGround[i], this->m_valuePlayGround[i]);
        m_solver.printLine(this->m_definedPlayGround[i], this->m_valuePlayGround[i]);
    }
    // flips
    // Do playground columns
    // flips back

    // Start to solve workList
}
