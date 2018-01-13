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
}

Nonogram::~Nonogram()
{
}

void Nonogram::initPlayGround()
{
	m_playGround.init();
}

void Nonogram::setOption(std::vector<std::vector<short>> options)
{
    m_options = options;
}

void Nonogram::run()
{
    backtracking(m_playGround);
    std::cout << "=========================================================================" << std::endl;
}

void Nonogram::propagate(PlayGround &playGround)
{
    // Do init playground rows
    // pass 1 ~ playground size
    while(playGround.workList()->hasNext()) {
        m_solver.init();
        short lineNumber = playGround.workList()->next();
        m_solver.setOptions(m_options.at(lineNumber - 1));
        unsigned int definedLine;
        unsigned int valueLine;
        playGround.getLine(lineNumber, definedLine, valueLine);
        bool result = m_solver.sovle(definedLine, valueLine);
        
        if (!result) {
            playGround.setConflict();
            break;
        }

        playGround.setLine(lineNumber, definedLine, valueLine);

    }
    playGround.print();
    playGround.workList()->printWorkList();

}

void Nonogram::fp1(PlayGround &playGround)
{

    while(playGround.workList()->hasUnsolved()) {
        propagate(playGround); 
        
        if (playGround.isConflict() || playGround.isSolved()) {
            return;
        }
        

    }
}

void Nonogram::backtracking(PlayGround &playGround)
{
    fp1(playGround);
}