#include "TSortTable.h"

template <class TKEY, class TVAL>
class TSortTable;

template <class TKEY, class TVAL>
class TTableIterator
{
protected:
	TSortTable<TKEY, TVAL>* table;
	int index;
public:
	TTableIterator(TSortTable<TKEY, TVAL>* _table, int _index) : table(_table), index(_index) {}

	TTableIterator& operator = (const TTableIterator& p)
	{
		if (this == &p) { return *this; }
		else
		{
			index = p.index;
			table = p.table;
		}
		return *this;
	}

	bool operator != (const TTableIterator& p) const
	{
		return index != p.index;
	}

	bool operator == (const TTableIterator& p) const
	{
		return index == p.index;
	}

	TTableIterator& operator++ ()
	{
		index++;
		return *this;
	}

	TVAL& operator* ()
	{
		return table->values[index];
	}

	int GetIndex() 
	{
		return index;
	}
};