#include "fixcache.h"

#include <iostream>

#include "macro.h"

/**
 * 簡單來說就是把兩個cache區塊疊在一起，只有當hasResult回傳true的時候才有必要call fixResult()
 * 因此m_definedTable存的內容就是"是否這個快取中存的位置是有效的"。
 * 而m_fixTable存的內容才是實際的cache值。
 */
FixCache::FixCache()
{
	this->m_definedTable = new unsigned int [PLAYGROUND_SIZE + 1];
	this->m_fixTable = new unsigned int [PLAYGROUND_SIZE + 1];
}

void FixCache::init()
{
	for (int i = 0; i < PLAYGROUND_SIZE + 1; i ++) {
		this->m_definedTable[i] = 0;
		this->m_fixTable[i] = 0;
	}
}

FixCache::~FixCache()
{
	delete [] this->m_definedTable;
	delete [] this->m_fixTable;
}

/**
 * 因為這個程式的nonogram找點是從1~25
 * 為了減少每次近來之前還要-1
 * 所以使用了26個int做為一個cache區塊。
 * 理論上這個cache能存到32*32個，但由於只有用26的row存，所以實際上只能容許25*25的盤面快取。
 */
void FixCache::setFixResult(int row, int col, bool result)
{
	row --;
	col --;
	if (row < 0 || col < 0) return;
	unsigned int offset = 1;
	offset <<= col;
	/**
     * 就是將處於相對位置的那個bit設為1，使其成為有效資料。
	 */
	this->m_definedTable[row] |= offset;
	/**
     * 只有當要設定cache實際值為true的時候才會去做or運算。
     * 因為offset變數永遠都是0..1..0，
     * 因此如果要設定的實際值為false的時候其實整個都是0，但or一個為0的值毫無意義。
	 */
	if (result) {
		this->m_fixTable[row] |= offset;
	}
}

/**
 * 以下兩個function的原理就是setFixResult()的逆操作而已。
 */
bool FixCache::hasResult(int row, int col)
{
	row --;
	col --;
	if (row < 0 || col < 0) return false;
	unsigned int record = this->m_definedTable[row];
	
	return (record >> col) & 1;
}

bool FixCache::fixResult(int row, int col)
{
	row --;
	col --;
	unsigned int record = this->m_fixTable[row];

	return ((record >> col) & 1);
}