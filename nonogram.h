#ifndef NONOGRAM_H
#define NONOGRAM_H

class Nonogram {

public:
	Nonogram();
	~Nonogram();
	void initPlayGround();
	void run();
private:

	unsigned int *m_definedPlayGround;
	unsigned int *m_valuePlayGround;

};

#endif // NONOGRAM_H