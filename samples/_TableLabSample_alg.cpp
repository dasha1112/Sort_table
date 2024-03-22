#include "TTable.h"
#include "TTableIterator.h"

int main() 
{
	TTable <int, int> my_table(10);
	my_table.Push(1, 7999555);
	my_table.Push(2, 7888000);

	int c = my_table.GetCount();
	int a = my_table.GetSize();

	int k = 5;
	int n = 6;
	std::cout << k;
	return 0;
}