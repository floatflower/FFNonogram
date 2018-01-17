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
    std::cout << "Bye" << std::endl;
}

void Nonogram::initPlayGround()
{
    m_playGround.init();
    m_solver.init();
}

void Nonogram::setOption(std::vector<std::vector<short>> options)
{
    m_options = options;
}

void Nonogram::run()
{
    backtracking(m_playGround);
    // std::cout << "=========================================================================" << std::endl;
}

void Nonogram::propagate(PlayGround &playGround)
{
    // Do init playground rows
    // pass 1 ~ playground size
    while(playGround.workList()->hasNext()) {
        m_solver.init();

        short lineNumber = playGround.workList()->next();
        // std::cout << lineNumber << std::endl;
        m_solver.setOptions(m_options.at(lineNumber - 1));
        unsigned int definedLine;
        unsigned int valueLine;
        playGround.getLine(lineNumber, definedLine, valueLine);
        bool result = m_solver.sovle(definedLine, valueLine);

        if (!result) {
            // std::cout << "Propagate conflict at: " << lineNumber << std::endl;
            // m_solver.printLine(definedLine, valueLine);
            playGround.setConflict();
            return;
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
            // playGround.print();
            return;
        }
        if (playGround.isSolved()) {
            std::cout << "Solved" << std::endl;
            // playGround.print();
            return;
        }
        
        int i = -1;
        int j = -1;

        while (true) {
            //playGround.print();
            playGround.getNextUnsolvedPoint(i, j);
            
            if (i == -1 && j == -1) {
                std::cout << "No unsolved point" << std::endl;
                return;
            }

            // if i j get first point reget the point

            probe(playGround, i, j);

            // if get new point painted

            if (playGround.isSolved()) {
                std::cout << "Solved" << std::endl;
                // playGround.print();
                return;
            } else if (playGround.isConflict()) {
                std::cout << "Conflict" << std::endl;
                // playGround.print();
                return;
            }
        }

    }
}

void Nonogram::backtracking(PlayGround &playGround)
{
    fp1(playGround);
}

bool Nonogram::probe(PlayGround &playGround, int row, int col)
{
    // std::cout << "set " << row << ", " << col << std::endl;
    //playGround.print();
    PlayGround p0;
    PlayGround p1;
    p0.init();
    p1.init();
    p0.copy(playGround);
    p1.copy(playGround);
    // std::cout << "P0: " << std::endl;
    // p0.print();
    // std::cout << "P1: " << std::endl;
    // p1.print();
    p0.setBit(row, col, false);
    p1.setBit(row, col, true);
    // std::cout << "Propagate p0: " << p0.isConflict() << ", Propagate p1: " << p1.isConflict() << std::endl;
    
    // std::cout << "P0: " << std::endl;
    // p0.print();
    
    // p1.print();
    propagate(p0);
    // std::cout << "P1: " << std::endl;
    propagate(p1);
    // std::cout << "Propagate p0: " << p0.isConflict() << ", Propagate p1: " << p1.isConflict() << std::endl;
    // std::cout << "P0: " << std::endl;
    // p0.print();
    // std::cout << "P1: " << std::endl;
    // p1.print();
    /*std::cout << std::endl;
    std::cout << "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" << std::endl;
    std::cout << std::endl;*/

    if (p0.isConflict() && p1.isConflict()) {
        // std::cout << "all conflict" << std::endl;
        playGround.setConflict();
        return false;
    }
    else if (p0.isConflict() && !p1.isConflict()) {
        // std::cout << "Use p1" << std::endl;
        // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        playGround.copy(p1);
        playGround.initUnsolvedPointSkip();
        return true;
    }
    else if (p1.isConflict() && !p0.isConflict()) {
        // std::cout << "Use p0" << std::endl;
        // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        playGround.copy(p0);
        playGround.initUnsolvedPointSkip();
        return true;
    }
    else {
        // std::cout << "merge" << std::endl;
        // std::cout << "P0: " << std::endl;
        // p0.print();
        // std::cout << "P1: " << std::endl;
        // p1.print();
        
        bool mergeResult = PlayGround::merge(p0, p1);
        
        int firstUnsolvedJ;
        int firstUnsolvedI;
        playGround.getFirstUnsolvedPoint(firstUnsolvedI, firstUnsolvedJ);

        if ((row != firstUnsolvedI && col != firstUnsolvedJ) && mergeResult) {
            playGround.initUnsolvedPointSkip();
        }

        playGround.copy(p0);
        // std::cout << "Merge result: " << std::endl;
        // playGround.print();
        return mergeResult;
    }
}