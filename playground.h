#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "worklist.h"

class PlayGround {
public:
	enum STATUS {
		INCOMPLETE,
		SOLVED,
		CONFLICT
	};
	PlayGround();
	~PlayGround();

	void init();

	void copy(const PlayGround &playGround);

	void getColumn(int index, unsigned int &definedLine, unsigned int &valueLine);
	void setColumn(int index, unsigned int definedLine, unsigned int valueLine);

	void getLine(int index, unsigned int &definedLine, unsigned int &valueLine);
	void setLine(int index, unsigned int definedLine, unsigned int valueLine);
	void setBit(int ver, int hor, bool painted);
	static bool merge(PlayGround &playGround0, PlayGround &playGround1);

	void print();

	void setSolved();
	void setConflict();
	void setIncomplete();

	bool isSolved();
	bool isConflict();
	bool isIncomplete();
	WorkList* workList() { return &m_workList; }

	void getNextUnsolvedPoint(int &ver, int &hor);
	void initUnsolvedPointSkip() { m_unsolvedPointSkip = 0; }
private:
	unsigned int *m_definedPlayGround;
	unsigned int *m_valuePlayGround;
	PlayGround::STATUS m_status;

	WorkList m_workList;
	int m_unsolvedPointSkip;
};

#endif