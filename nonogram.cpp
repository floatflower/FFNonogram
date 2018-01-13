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
    //std::cout << "=========================================================================" << std::endl;
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
            std::cout << "Conflict at: " << lineNumber << std::endl;
            std::cout << "conflict!!" << std::endl;
            playGround.setConflict();
            break;
        }

        playGround.setLine(lineNumber, definedLine, valueLine);

    }
    // playGround.print();
    // playGround.workList()->printWorkList();

}

void Nonogram::fp1(PlayGround &playGround)
{

    while(playGround.workList()->hasUnsolved()) {
        propagate(playGround); 
        
        if (playGround.isConflict()) {
            std::cout << "Conflict" << std::endl;
            playGround.print();
            return;
        }
        if (playGround.isSolved()) {
            std::cout << "Solved" << std::endl;
            playGround.print();
            return;
        }
        
        int i;
        int j;
        while (true) {
            i = j = -1;
            playGround.getNextUnsolvedPoint(i, j);
            
            if (i == -1 || j == -1) {
                // no unsolved point;
                std::cout << "no unsolved points" << std::endl;
                return;
            }

            probe(playGround, i, j);
            if (playGround.isSolved()) {
                std::cout << "Solved" << std::endl;
                playGround.print();
                return;
            } else if (playGround.isConflict()) {
                std::cout << "Conflict" << std::endl;
                playGround.print();
                return;
            }
        }

    }
}

void Nonogram::backtracking(PlayGround &playGround)
{
    fp1(playGround);
}

void Nonogram::probe(PlayGround &playGround, int row, int col)
{
    // std::cout << "set " << row << ", " << col << std::endl;
    PlayGround p0;
    PlayGround p1;
    p0.copy(playGround);
    p1.copy(playGround);
    /*std::cout << "P0: " << std::endl;
    p0.print();
    std::cout << "P1: " << std::endl;
    p1.print();*/
    p0.setBit(row, col, false);
    p1.setBit(row, col, true);
    /*std::cout << "P0: " << std::endl;
    p0.print();
    std::cout << "P1: " << std::endl;
    p1.print();*/
    propagate(p0);
    propagate(p1);
    /*std::cout << "P0: " << std::endl;
    p0.print();
    std::cout << "P1: " << std::endl;
    p1.print();*/
    /*std::cout << std::endl;
    std::cout << "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" << std::endl;
    std::cout << std::endl;*/

    if (p0.isConflict() && p1.isConflict()) {
        // std::cout << "all conflict" << std::endl;
        playGround.setConflict();
    }
    else if (p0.isConflict() && !p1.isConflict()) {
        // std::cout << "p1" << std::endl;
        playGround.copy(p1);
    }
    else if (p1.isConflict() && !p0.isConflict()) {
        // std::cout << "p0" << std::endl;
        playGround.copy(p0);
    }
    else {
        // std::cout << "merge" << std::endl;  
        PlayGround::merge(p0, p1);
        playGround.copy(p0);
        propagate(playGround);
    }
}