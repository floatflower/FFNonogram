#ifndef WORKLIST_H
#define WORKLIST_H


class WorkList
{
public:
	enum STATUS {
		SOLVED,
		QUEUED,
		UNSOLVED
	};
    WorkList();
    ~WorkList();

    void copy(const WorkList &workList);
    void init();
    
    bool hasNext();
    short next();

    void setUnsolved(int lineNumber);
    void setQueued(int lineNumber);
    void setSolved(int lineNumber);

    void printWorkList();
    bool hasUnsolved();
    /**
	 * instance(), WorkList object is a singleton.
	 * 
	 * @return WorkList*
	 */
private:
	WorkList::STATUS *m_statusTable;
	short *m_queued;
	short m_head;
	short m_tail;
};

#endif // WORKLIST_H