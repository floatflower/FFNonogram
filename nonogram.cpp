#include "nonogram.h"

/** ========================================================

PLAYGROUND_SIZE is the size of playground,
and its width and height should be real width + 1 and real height + 1.

It is because that the fix function will check the row whether match pattern (01*)*0?
But in this case, this first bit is 1 also can be accepted,
So create a one-bit bigger playground can handle this case.

Also, we can access data with real index, point(1, 1) will access [1][1].
(n, 0) and (0, n) is for extra hidden bits.

========================================================= */
#define PLAYGROUND_SIZE 6

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

void Nonogram::run()
{

}