#ifndef _TABLE_
#define _TABLE_
#include <algorithm>
#include <iostream>
using namespace std;

template <class TKEY, class TVAL>
class TSortTable 
{
	template <class TKEY, class TVAL>
	friend class TTableIterator;

protected:
	TKEY* keys;
	int size;
	int count;
	TVAL* values;
public:
	TSortTable(int s = 100);
	TSortTable(const TSortTable <TKEY, TVAL>& p);
	TSortTable(const TSortTable <TKEY, TVAL>&& p);
	~TSortTable();
	TVAL& operator [] (TKEY& k);
	int GetSize();
	int GetCount();
	void Push(TKEY k, TVAL v);
	TVAL Find(const TKEY& k);
	void Del(TKEY& k);
	void Resize(int new_size);
	template <class T1, class T2>
	friend ostream& operator<<(ostream& output, const TSortTable<T1, T2>& table);
	template <class T1, class T2>
	friend istream& operator >> (istream& istr, TSortTable<T1, T2>& table);
};
template <class T1, class T2>
ostream& operator<<(ostream& output, const TSortTable<T1, T2>& table)
{
	for (int i = 0; i < table.GetCount(); ++i) {
		output << "Key: " << table.keys[i] << ", Value: " << table.values[i] << endl;
	}
	return output;
}

template <class T1, class T2>
istream& operator >> (istream& istr, TSortTable<T1, T2>& table) 
{
	for (int i = 0; i < table.GetCount(); ++i) 
	{
		cout << "Enter key: ";
		input >> table.keys[i];
		cout << "Enter value: ";
		input >> table.values[i];
	}
	return input;
}

template<class TKEY, class TVAL>
inline TSortTable<TKEY, TVAL>::TSortTable(int s) // Конструктор
{
	if (s > 0) { size = s; }
	else { throw "Ошибка"; }
	count = 0;
	keys = new TKEY[size];
	values = new TVAL[size];
}

template<class TKEY, class TVAL>
inline TSortTable<TKEY, TVAL>::TSortTable(const TSortTable<TKEY, TVAL>& p) // Конструктор копирования
{
	size = p.size;
	count = p.count;
	keys = new TKEY[size];
	values = new TVAL[size];
	for (int i = 0; i < count; i++)
	{
		keys[i] = p.keys[i];
		values[i] = p.values[i];
	}
}

template<class TKEY, class TVAL>
inline TSortTable<TKEY, TVAL>::TSortTable(const TSortTable<TKEY, TVAL>&& p) // Конструктор перемещения
{
	keys = p.keys;
	values = p.values;
	p.keys = nullptr;
	p.values = nullptr;
	size = p.size;
	count = p.count;
	p.count = 0;
	p.size = 0;
}

template<class TKEY, class TVAL>
inline TSortTable<TKEY, TVAL>::~TSortTable() // Деструктор
{
	if (keys != 0 && values != 0) 
	{
		delete[] keys;
		delete[] values;
	}
	keys = nullptr;
	values = nullptr;
	size = 0;
	count = 0;
}

template<class TKEY, class TVAL>
inline TVAL& TSortTable<TKEY, TVAL>::operator[](TKEY& k) // Получить значение по ключу
{
	int left = 0;
	int right = count;
	while (left <= right) //бинарный поиск
	{
		int mid = (left + right) / 2;
		if (keys[mid] == k)
		{
			return values[mid];
			break;
		}
		if (k < keys[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	Push(k, TVAL());
	return values[count - 1];
}

template<class TKEY, class TVAL>
inline int TSortTable<TKEY, TVAL>::GetSize()
{
	return size;
}

template<class TKEY, class TVAL>
inline int TSortTable<TKEY, TVAL>::GetCount()
{
	return count;
}

template<class TKEY, class TVAL>
inline void TSortTable<TKEY, TVAL>::Push(TKEY k, TVAL v) // Положить значение
{
	if (count >= size) { Resize(size * 2); }
	int left = 0;
	int right = count - 1;
	int insertPos = 0;  //переменная для хранения позиции вставки
	while (left <= right) //бинарный поиск
	{
		int mid = (left + right) / 2;
		if (keys[mid] == k)
		{
			values[mid] = v;
			return;  //возвращаемся после обновления значения
		}
		if (k < keys[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
		insertPos = left;  //обновляем позицию вставки
	}

	//передвигаем оставшиеся элементы и вставляем новую пару ключ-значение в правильную позицию
	for (int i = count - 1; i >= insertPos; i--)
	{
		keys[i + 1] = keys[i];
		values[i + 1] = values[i];
	}
	keys[insertPos] = k;
	values[insertPos] = v;
	count++;
}

template<class TKEY, class TVAL>
inline TVAL TSortTable<TKEY, TVAL>::Find(const TKEY& k) // Найти значение
{
	int left = 0;
	int right = count - 1;
	while (left <= right) // бинарный поиск
	{
		int mid = (left + right) / 2;
		if (keys[mid] == k)
		{
			return values[mid];
		}
		if (k < keys[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return TVAL();
}

template<class TKEY, class TVAL>
inline void TSortTable<TKEY, TVAL>::Del(TKEY& k) // Удалить значение
{
	int left = 0;
	int right = count - 1;
	bool flag = false;
	while (left <= right) //бинарный поиск
	{
		int mid = (left + right) / 2;
		if (keys[mid] == k)
		{
			keys[mid] = keys[count-1];
			values[mid] = values[count-1];
			count--;
			flag = true;
			break;
		}
		if (k < keys[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	if (flag == false) { throw "Error"; }
}

template<class TKEY, class TVAL>
inline void TSortTable<TKEY, TVAL>::Resize(int new_size) // Поменять размер
{
	if (new_size <= 0) { throw "Error"; }
	TKEY* new_keys = new TKEY[new_size];
	TVAL* new_values = new TVAL[new_size];
	for (int i = 0; i < std::min(new_size, size); i++)
	{
		new_keys[i] = keys[i];
		new_values[i] = values[i];
	}
	delete[] keys;
	delete[] values;
	keys = new_keys;
	values = new_values;
	size = new_size;
}

#endif