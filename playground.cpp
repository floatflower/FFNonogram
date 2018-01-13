#include "playground.h"

#include <iostream>

#include "macro.h"

PlayGround::PlayGround()
{
	this->m_definedPlayGround = new unsigned int [PLAYGROUND_SIZE];
	this->m_valuePlayGround = new unsigned int [PLAYGROUND_SIZE];

	this->m_solvedTable = new bool* [PLAYGROUND_SIZE];
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_solvedTable[i] = new bool [PLAYGROUND_SIZE];
	}

	init();
}

void PlayGround::init()
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_definedPlayGround[i] = 0;
		this->m_valuePlayGround[i] = 0;
	}
	m_workList.init();
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j ++) {
			m_solvedTable[i][j] = false;
		}
	}
}

PlayGround::~PlayGround()
{
	delete [] this->m_definedPlayGround;
	delete [] this->m_valuePlayGround;

	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		delete [] this->m_solvedTable[i];
	}
	delete [] this->m_solvedTable;
}

void PlayGround::copy(PlayGround &playGround)
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		this->m_definedPlayGround[i] = playGround.m_definedPlayGround[i];
		this->m_valuePlayGround[i] = playGround.m_valuePlayGround[i];
	}

	this->m_workList.copy(playGround.m_workList);

	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j ++) {
			this->m_solvedTable[i][j] = playGround.m_solvedTable[i][j];
		}
	}
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
	int row = 0;
	int col = 0;
	if (index >= PLAYGROUND_SIZE) { 
		offset = 0;
		col = index - PLAYGROUND_SIZE;
	}
	else {
		row = index;
	}

	if (prev_definedLine) {
		for (int i = 0; i < PLAYGROUND_SIZE; i ++) {

			index >= PLAYGROUND_SIZE ? row = i : col = i;

			/**
			* Iterate all bits to check whick bit been modified.
			*/

			if (GET_BIT(prev_definedLine, i)) {
				// 
				m_workList.setQueued(offset + i);
				m_solvedTable[row][col] = true;
			}
		}
	}
	
	if ((definedLine | completeChecker[PLAYGROUND_SIZE]) == 0xFFFFFFFF) {
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

void PlayGround::setBit(int row, int col, bool painted)
{
	// vertical is the index of integer
	// horizon is the index of bit
	row --;
	col --;
	m_workList.setQueued(row);
	m_workList.setQueued(col + PLAYGROUND_SIZE);
	this->m_definedPlayGround[row] |= bitGetter[col];
	m_solvedTable[row][col] = true;

	if (painted)
		this->m_valuePlayGround[row] |= bitGetter[col];
	else
		this->m_valuePlayGround[row] &= bitCancel[col];
}

void PlayGround::merge(PlayGround &playGround0, PlayGround &playGround1)
{
	for (int lineNumber = 1; lineNumber <= PLAYGROUND_SIZE; lineNumber ++) {
		
		unsigned int currentLine0DefinedLine;
		unsigned int currentLine0ValueLine;
		unsigned int currentLine1DefinedLine;
		unsigned int currentLine1ValueLine;
		
		for (int bitIndex = 0; bitIndex < PLAYGROUND_SIZE; bitIndex ++) {
				
			playGround0.getLine(lineNumber, currentLine0DefinedLine, currentLine0ValueLine);
			playGround1.getLine(lineNumber, currentLine1DefinedLine, currentLine1ValueLine);

			currentLine0DefinedLine &= currentLine1DefinedLine;

			if (GET_BIT(currentLine0DefinedLine, bitIndex)) {
				if (!(GET_BIT(currentLine0ValueLine, bitIndex) ^ GET_BIT(currentLine0ValueLine, bitIndex))) {
					
					playGround0.m_workList.setQueued(lineNumber - 1);
					playGround0.m_workList.setQueued(PLAYGROUND_SIZE + bitIndex);
				
				}
				else {
					currentLine0DefinedLine &= bitCancel[bitIndex];
				}
			}

		}

		playGround0.setLine(lineNumber, currentLine0DefinedLine, currentLine0ValueLine);
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

	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

	for (int i = 0; i <PLAYGROUND_SIZE; i ++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j ++) {
			std::cout << m_solvedTable[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

void PlayGround::setSolved()
{
	m_status = PlayGround::SOLVED;
}

void PlayGround::setConflict()
{
	m_status = PlayGround::CONFLICT;
}

void PlayGround::setIncomplete()
{
	m_status = PlayGround::INCOMPLETE;
}

bool PlayGround::isSolved()
{
	return (!m_workList.hasUnsolved());
}

bool PlayGround::isConflict()
{
	return m_status == PlayGround::CONFLICT;
}

bool PlayGround::isIncomplete()
{
	return m_status == PlayGround::INCOMPLETE;
}

void PlayGround::getNextUnsolvedPoint(int &ver, int &hor)
{
	for (int i = 0; i < PLAYGROUND_SIZE; i ++) {
		for (int j = 0; j < PLAYGROUND_SIZE; j ++) {
			if (!m_solvedTable[i][j]) {
				ver = i + 1;
				hor = j + 1;
				return;
			}
		}
	}
}