#ifndef LINESOVER_H
#define LINESOVER_H

class LineSolver {
public:
	
	LineSolver();
	~LineSolver();
	void setLine(int definedLine, int valueLine);
	bool sovle();

	bool paint(int row, int col, int line);
	bool paintp(int row, int col, int line);
	int paint0(int row, int col, int line);
	int paint1(int row, int col, int line);

	bool fix(int row, int col, int line);
	bool fix0(int row, int col, int line);
	bool fix1(int row, int col, int line);

	int merge(int line1, int line2); 
};

#endif LINESOVER_H