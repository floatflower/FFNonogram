#include "nonogram.h"

#include <iostream>

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
#include "worklist.h"

Nonogram::Nonogram()
{
	this->m_definedPlayGround = new unsigned int [PLAYGROUND_SIZE];
	this->m_valuePlayGround = new unsigned int [PLAYGROUND_SIZE];
    m_isComplete = true;
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
    m_isComplete = true;
    WorkList::instance()->init();
}

void Nonogram::setOption(std::vector<std::vector<short>> options)
{
    m_options = options;
}

void Nonogram::run()
{
    fp1();
    std::cout << "=========================================================================" << std::endl;
}

void Nonogram::propagate()
{
    // Do init playground rows
    // pass 1 ~ playground size
    m_isComplete = true;
    for (int i = 0; i < INPUTDATA_ROWS; i ++) {
        m_solver.init();
        if (i < PLAYGROUND_SIZE) {
            m_solver.setOptions(m_options.at(i));
            m_solver.sovle(this->m_definedPlayGround[i], this->m_valuePlayGround[i]);
        }
        else {
            m_solver.setOptions(m_options.at(i));
            unsigned int definedLine;
            unsigned int valueLine;
            getColumn(i, definedLine, valueLine);
            m_solver.sovle(definedLine, valueLine);
            setColumn(i, definedLine, valueLine);
        }
        m_isComplete &= m_solver.isCompleted();
    }
    printPlayGround();
    // flips
    // Do playground columns
    // flips back

    // Start to solve workList
}

void Nonogram::getColumn(int index, unsigned int &definedLine, unsigned int &valueLine)
{
    definedLine = valueLine = 0;
    int tmp_index = index - PLAYGROUND_SIZE;
    for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
        if (GET_BIT(this->m_definedPlayGround[i], tmp_index)) {
            definedLine |= bitGetter[i];
        }
        if (GET_BIT(this->m_valuePlayGround[i], tmp_index)) {
            valueLine |= bitGetter[i];
        }
    }
}

void Nonogram::setColumn(int index, unsigned int definedLine, unsigned int valueLine)
{
    int tmp_index = index - PLAYGROUND_SIZE;
    for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
        if (GET_BIT(definedLine, i)) {
            this->m_definedPlayGround[i] |= bitGetter[tmp_index];
        }
        if (GET_BIT(valueLine, i)) {
            this->m_valuePlayGround[i] |= bitGetter[tmp_index];
        }
    }
}

void Nonogram::printPlayGround()
{
    for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
        m_solver.printLine(this->m_definedPlayGround[i], this->m_valuePlayGround[i]);
    }
    m_isComplete ? std::cout << "Result: Finished" << std::endl : std::cout << "Result: UnFinished" << std::endl;
    
}

void Nonogram::fp1()
{
    while (true) {
        propagate();
        if (m_isComplete) break;
    }
}