#ifndef _TABLE_
#define _TABLE_
#include <algorithm>
#include <iostream>
using namespace std;

template <class TKEY, class TVAL>
class TTable 
{
protected:
	TKEY* keys;
	int size;
	int count;
public:
	TVAL* values;
	TTable(int s = 100);
	TTable(const TTable <TKEY, TVAL>& p);
	TTable(const TTable <TKEY, TVAL>&& p);
	~TTable();
	TVAL& operator [] (TKEY& k);
	int GetSize();
	int GetCount();
	void Push(TKEY k, TVAL v);
	TVAL Find(TKEY& k);
	void Del(TKEY& k);
	void Resize(int new_size);
	template <class T1, class T2>
	friend ostream& operator<<(ostream& output, const TTable<T1, T2>& table);
	template <class T1, class T2>
	friend istream& operator >> (istream& istr, TTable<T1, T2>& table);
};
template <class T1, class T2>
ostream& operator<<(ostream& output, const TTable<T1, T2>& table)
{
	for (int i = 0; i < table.GetCount(); ++i) {
		output << "Key: " << table.keys[i] << ", Value: " << table.values[i] << endl;
	}
	return output;
}

template <class T1, class T2>
istream& operator >> (istream& istr, TTable<T1, T2>& table) 
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
inline TTable<TKEY, TVAL>::TTable(int s) // Конструктор
{
	if (s > 0) { size = s; }
	else { throw "Ошибка"; }
	count = 0;
	keys = new TKEY[size];
	values = new TVAL[size];
}

template<class TKEY, class TVAL>
inline TTable<TKEY, TVAL>::TTable(const TTable<TKEY, TVAL>& p) // Конструктор копирования
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
inline TTable<TKEY, TVAL>::TTable(const TTable<TKEY, TVAL>&& p) // Конструктор перемещения
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
inline TTable<TKEY, TVAL>::~TTable() // Деструктор
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
inline TVAL& TTable<TKEY, TVAL>::operator[](TKEY& k) // Получить значение по ключу
{
	for (int i = 0; i < count; i++) 
	{
		if (keys[i] == k) 
		{
			return values[i];
		}
	}
	Push(k, TVAL());
	return values[count - 1];
}

template<class TKEY, class TVAL>
inline int TTable<TKEY, TVAL>::GetSize()
{
	return size;
}

template<class TKEY, class TVAL>
inline int TTable<TKEY, TVAL>::GetCount()
{
	return count;
}

template<class TKEY, class TVAL>
inline void TTable<TKEY, TVAL>::Push(TKEY k, TVAL v) // Положить значение
{
	if (count >= size) { Resize(count); }
	keys[count] = k;
	values[count] = v;
	count++;
}

template<class TKEY, class TVAL>
inline TVAL TTable<TKEY, TVAL>::Find(TKEY& k) // Найти значение
{
	for (int i = 0; i < count; i++) 
	{
		if (keys[i] == k) { return values[i]; }
	}
}

template<class TKEY, class TVAL>
inline void TTable<TKEY, TVAL>::Del(TKEY& k) // Удалить значение
{
	for (int i = 0; i < count; i++)
	{
		if (keys[i] == k) 
		{
			keys[i] = keys[count - 1];
			values[i] = values[count - 1];
			count--;
			break;
		}
		else { throw "Error"; }
	}
}
template<class TKEY, class TVAL>
inline void TTable<TKEY, TVAL>::Resize(int new_size) // Поменять размер
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