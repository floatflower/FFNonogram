#include "worklist.h"

#include <iostream>

#include "macro.h"

WorkList::WorkList()
	: m_unsolvedCount(0)
{

}

WorkList::~WorkList()
{
	delete [] m_queued;
	delete [] m_statusTable;
}

void WorkList::copy(const WorkList &workList)
{
	for (int i = 0; i < 64; i ++) {
		this->m_statusTable[i] = workList.m_statusTable[i];
		this->m_queued[i] = workList.m_queued[i];
	}
	this->m_head = workList.m_head;
	this->m_tail = workList.m_tail;
}

void WorkList::init()
{
	/**
	* 為什麼使用64?
	* 因為我們使用 unsigned int 作為盤面儲存的單位，理論上可以支援 32*32 的 Nonogram 盤面。
	* 此外 64 是 2 的冪次，我們這個 WorkList Queue 其實是一個固定大小的 circular queue,
	* 所以當 tail 走到最邊界的時候必須回到頭，
	* 若不是 2 的冪次就必須使用 %，比起位元運算%的較為耗費效能，
	* 因此如果我們要 %64 其實可以 and 0x3F(00111111) 就可成功進行 % 操作。
	* 例如 67(01000011) and 0x3F 就能得到 3 是不是美滋滋。
	*/
	m_queued = new short[64];
	m_statusTable = new WorkList::STATUS [64];
	for (int i = 0; i < INPUTDATA_ROWS; i ++) {
		/**
		* 將所有初始欄位預設為 QUEUED，
		* 以免在解前 50 個 propagate 時重複將 Line number 推入 Queue.
		*/
		m_statusTable[i] = WorkList::QUEUED;
		/**
		* 將初始尚未開始解的所有Line推入Queue中。
		*/
		m_queued[i] = i;		
	}
	/**
	 * Preset the useless table record as SOLVED
 	*/	
	for (int i = INPUTDATA_ROWS; i < 64; i ++) {
		m_statusTable[i] = WorkList::SOLVED;
	}

	m_head = 0;
	// std::cout << "Head is at" << m_head << std::endl;

	// if we have n line then m_tail will be set to n,
	// for example we have 10 line then m_tail point to m_queued[10]
	m_tail = INPUTDATA_ROWS;
	// std::cout << "Tail is at" << m_tail << std::endl;
}

/**
 * 必須先call hasNext() 才能 call next()，確保還有下一個節點在queued裡等待的成員。
 */
bool WorkList::hasNext()
{
	return m_head != m_tail;
}

short WorkList::next()
{
	short result = m_queued[m_head];
	m_statusTable[result] = WorkList::UNSOLVED;
	result ++;
	m_head = (m_head + 1) & 0x3F;
	// std::cout << "Head is at" << m_head << std::endl;

	return result;
}

void WorkList::setQueued(int lineNumber)
{
	// lineNumber --;

	if (m_statusTable[lineNumber == WorkList::UNSOLVED]) m_unsolvedCount --;
	if (m_statusTable[lineNumber] != WorkList::QUEUED) {

		m_statusTable[lineNumber] = WorkList::QUEUED;
		m_queued[m_tail] = lineNumber; 
		m_tail = (m_tail + 1) & 0x3F;
		// std::cout << "Tail is at" << m_tail << std::endl;
	}

}

void WorkList::setSolved(int lineNumber)
{
	// lineNumber --;
	if (m_statusTable[lineNumber == WorkList::UNSOLVED]) m_unsolvedCount --;
	m_statusTable[lineNumber] = WorkList::SOLVED;
}

void WorkList::setUnsolved(int lineNumber) {
	
	// lineNumber --;
	m_statusTable[lineNumber] = WorkList::UNSOLVED;
	m_unsolvedCount ++;

}

void WorkList::printWorkList()
{
	std::cout << "Queued: " << std::endl;
	for (short start = m_head; start != m_tail; start = ((start + 1) & 0x3F)) {
		std::cout << m_queued[start] + 1 << " ";
	}
	std::cout << std::endl;
	std::cout << m_unsolvedCount << " Unsolved: " << std::endl;
	for (short i = 0; i <= INPUTDATA_ROWS; i ++) {
		if (m_statusTable[i] == WorkList::UNSOLVED) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
	std::cout << m_unsolvedCount << " Solved: " << std::endl;
	for (short i = 0; i <= INPUTDATA_ROWS; i ++) {
		if (m_statusTable[i] == WorkList::SOLVED) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}