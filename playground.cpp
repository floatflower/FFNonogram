#include "playground.h"

#include <iostream>

#include "macro.h"

PlayGround::PlayGround()
{
	this->m_definedPlayGround = new unsigned int [PLAYGROUND_SIZE];
	this->m_valuePlayGround = new unsigned int [PLAYGROUND_SIZE];

	init();
}

void PlayGround::init()
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_definedPlayGround[i] = 0;
		this->m_valuePlayGround[i] = 0;
	}
	m_workList.init();
}

PlayGround::~PlayGround()
{
	delete [] this->m_definedPlayGround;
	delete [] this->m_valuePlayGround;
}

void PlayGround::copy(PlayGround &playGround)
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_definedPlayGround[i] = playGround.m_definedPlayGround[i];
		this->m_valuePlayGround[i] = playGround.m_valuePlayGround[i];
	}
	this->m_workList.copy(playGround.m_workList);
}

void PlayGround::getColumn(int index, unsigned int &definedLine, unsigned int &valueLine)
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

void PlayGround::setColumn(int index, unsigned int definedLine, unsigned int valueLine)
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

void PlayGround::getLine(int index, unsigned int &definedLine, unsigned int &valueLine)
{
	index --;
	if (index < PLAYGROUND_SIZE) {
		definedLine = this->m_definedPlayGround[index];
		valueLine = this->m_valuePlayGround[index];
	}
	else {
		getColumn(index, definedLine, valueLine);
	}
}

void PlayGround::setLine(int index, unsigned int definedLine, unsigned int valueLine)
{
	
	index --;
	
	unsigned int prev_definedLine;
	unsigned int prev_valueLine;

	/**
     * Before setting line:
     * get origin line -> prev_definedLine
     * get line we want to set -> definedLine
     * 
     * For example:
     * prev_definedLine -> 1 0 1 0 1 1
     * definedLine      -> 1 1 1 0 1 1
     * xor
     *                  -> 0 1 0 0 0 0
     * the bit set to 1 is modified
	*/

	getLine(index + 1, prev_definedLine, prev_valueLine);

	prev_definedLine ^= definedLine;
	
	/**
	* if the definedLine not be modified, which means no new pixel be painted,
	* and the result of xor operation will be set to 0
	*/
	int offset = PLAYGROUND_SIZE;
	if (index >= PLAYGROUND_SIZE) offset = 0;
	if (prev_definedLine) {
		for (int i = 0; i < PLAYGROUND_SIZE; i ++) {

			/**
			* Iterate all bits to check whick bit been modified.
			*/

			if (GET_BIT(prev_definedLine, i)) {
				m_workList.setQueued(offset + i);
			}
		}
	}
	
	if ((definedLine & completeChecker[PLAYGROUND_SIZE]) == definedLine) {
		m_workList.setSolved(index);
	}
	else {
		m_workList.setUnsolved(index);
	}

	if (index < PLAYGROUND_SIZE) {
		this->m_definedPlayGround[index] = definedLine;
		this->m_valuePlayGround[index] = valueLine;
	}
	else {
		setColumn(index, definedLine, valueLine);
	}
}

void PlayGround::print()
{
	for (int lineNumber = 0; lineNumber < PLAYGROUND_SIZE; lineNumber ++) {
		for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
        if (GET_BIT(this->m_definedPlayGround[lineNumber], i))
        {
            GET_BIT(this->m_valuePlayGround[lineNumber], i) ? 
            	std::cout << "1\t" : std::cout << "0\t";
        }
        else {
            std::cout << "-1\t";
        }
    }
    std::cout << std::endl;	
	}
}

void PlayGround::setSolved()
{
	m_status = PlayGround::SOLVED;
}

void PlayGround::setConflict()
{
	m_status = PlayGround::CONFLICT;
}

bool PlayGround::isSolved()
{
	return m_status == PlayGround::SOLVED;
}

bool PlayGround::isConflict()
{
	return m_status == PlayGround::CONFLICT;
}