#ifndef FIXCACHE_H
#define FIXCACHE_H

class FixCache
{
public:
	FixCache();
	~FixCache();
	void setFixResult(int row, int col, bool result);
	bool hasResult(int row, int col);
	bool fixResult(int row, int col);
	void init();
private:
	unsigned int *m_definedTable;
	unsigned int *m_fixTable;
};

#endif // FIXCACHE_H