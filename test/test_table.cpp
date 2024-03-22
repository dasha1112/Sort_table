#include "TTable.h"
#include "TTableIterator.h"
#include "gtests.h"

TEST(TTableConstructor, Constructor) // Тест конструктора
{
  TTable<int, double> table(5);
  int a = table.GetSize();
  int b = table.GetCount();
  EXPECT_EQ(5, a);
  EXPECT_EQ(0, b);
}

TEST(TTableConstructor, Push) // Тест конструктора
{
  TTable<int, double> table(5);
  int a = table.GetSize();
  int b = table.GetCount();
  EXPECT_EQ(5, a);
  EXPECT_EQ(0, b);
}

TEST(TTableTest, CopyConstructor) // Тест на метод Push()
{
  TTable<int, double> table(5);
  table.Push(1, 23);
  table.Push(2, 56);
  int key = 1;
  int key2 = 2;
  EXPECT_EQ(23, table[key]);
  EXPECT_EQ(56, table[key2]);
  EXPECT_EQ(5, table.GetSize());
  EXPECT_EQ(2, table.GetCount());
}

TEST(TTableConstructor, CopyConstructor2) // Тест конструктора копирования 2
{
  TTable<int, int> table(5);
  table.Push(1, 23);
  table.Push(2, 56);
  TTable<int, int> table1(table);
  EXPECT_EQ(5, table1.GetSize());
  EXPECT_EQ(2, table1.GetCount());
}

TEST(TTableTest, DestructorTest) // Тест деструктора
{
  TTable<int, int> table (5);
  table.Push(1, 123);
  table.Push(2, 456);
  int count = table.GetCount();
  table.~TTable();
  EXPECT_EQ(2, count);
  EXPECT_EQ(0, table.GetCount());
}

TEST(TTableTest, IndexOperatorTest) // Тест оператора []
{
  TTable<int, int> table(5);
  table.Push(1, 123);
  table.Push(2, 456);
  int key = 1;
  EXPECT_EQ(123, table[key]);
  key = 2;
  EXPECT_EQ(456, table[key]); 
}

TEST(TTableTest, FindTest) // Тест метода Find()
{
  TTable<int, int> table(5);
  table.Push(1, 123);
  table.Push(2, 456);
  int key = 1;
  int key2 = 2;
  EXPECT_EQ(123, table.Find(key));
  EXPECT_EQ(456, table.Find(key2));
}

TEST(TTableTest, DelTest) // Тест метода Del()
{
  TTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  int key1 = 1;
  int key2 = 2;
  table.Del(key1);
  EXPECT_EQ(1, table.GetCount());
  EXPECT_EQ(456, table.Find(key2));
}

TEST(TTableTest, DelExceptionTest) // Тест на обработку исключения в методе Del()
{
  TTable<int, int> table;
  table.Push(1, 123);
  int key1 = 2;
  bool exceptionThrown = false;
  try {
    table.Del(key1);
  }
  catch (const char* error) {
    EXPECT_STREQ(error, "Error");
    exceptionThrown = true;
  }
  EXPECT_TRUE(exceptionThrown);
}

TEST(TTableTest, ResizeTest) // Тест метода Resize()
{
  TTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  int key1 = 1;
  int key2 = 2;
  table.Resize(4); 
  EXPECT_EQ(4, table.GetSize());
  EXPECT_EQ(123, table.Find(key1));
  EXPECT_EQ(456, table.Find(key2));
}

TEST(TTableIteratorTest, ProstoTest) // Тест на конструктор итератора
{
  TTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  TTableIterator<int, int> iterator(&table, 0);
  EXPECT_EQ(0, iterator.index);
}

TEST(TTableIteratorTest, AssignmentOperatorTest) // Тест на оператор =
{
  TTable<int, int> table1;
  table1.Push(1, 123);
  TTable<int, int> table2;
  table2.Push(2, 456);
  TTableIterator<int, int> iterator1(&table1, 0);
  TTableIterator<int, int> iterator2(&table2, 0);
  iterator2 = iterator1;
  EXPECT_EQ(iterator1.index, iterator2.index);
  EXPECT_EQ(iterator1.table, iterator2.table);
}

TEST(TTableIteratorTest, InequalityOperatorTest) // Тест на оператор !=
{
  TTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  TTableIterator<int, int> iterator1(&table, 0);
  TTableIterator<int, int> iterator2(&table, 1);
  EXPECT_TRUE(iterator1 != iterator2);
}

TEST(TTableIteratorTest, EqualityOperatorTest) // Тест на оператор ==
{
  TTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator1(&table, 0);
  TTableIterator<int, int> iterator2(&table, 0);
  EXPECT_TRUE(iterator1 == iterator2);
}

TEST(TTableIteratorTest, IncrementOperatorTest) // Тест на оператор ++
{
  TTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator(&table, 0);
  TTableIterator<int, int> original_iterator = iterator;
  ++iterator;
  int expected_index = original_iterator.index + 1;
  EXPECT_EQ(iterator.index, expected_index);
}

TEST(TTableIteratorTest, DereferenceOperatorTest) // Тест на оператор *
{
  TTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator(&table, 0);
  int& value = *iterator;
  EXPECT_EQ(value, 123);
}