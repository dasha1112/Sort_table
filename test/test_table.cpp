#include "TTableIterator.h"
#include "TSortTable.h"
#include "gtests.h"


TEST(TTableConstructor, Constructor) // Тест конструктора
{
  TSortTable<int, double> table(5);
  int a = table.GetSize();
  int b = table.GetCount();
  EXPECT_EQ(5, a);
  EXPECT_EQ(0, b);
}

TEST(TTableTest, CopyConstructor) // Тест на конструктор копирования 1
{
  TSortTable<int, double> table(5);
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
  TSortTable<int, int> table(5);
  table.Push(1, 23);
  table.Push(2, 56);
  TSortTable<int, int> table1(table);
  EXPECT_EQ(5, table1.GetSize());
  EXPECT_EQ(2, table1.GetCount());
}

TEST(TTableTest, DestructorTest) // Тест деструктора
{
  TSortTable<int, int> table (5);
  table.Push(1, 123);
  table.Push(2, 456);
  int count = table.GetCount();
  table.~TSortTable();
  EXPECT_EQ(2, count);
  EXPECT_EQ(0, table.GetCount());
}

TEST(TTableTest, IndexOperatorTest) // Тест оператора []
{
  TSortTable<int, int> table(10);
  table.Push(3, 832);
  table.Push(5, 702);
  table.Push(1, 123);
  table.Push(2, 456);
  int key = 1;
  EXPECT_EQ(123, table[key]);
  key = 2;
  EXPECT_EQ(456, table[key]); 
}

TEST(TTableTest, FindTest) // Тест метода Find()
{
  TSortTable<int, int> table;
  table.Push(9, 123);
  table.Push(3, 304);
  table.Push(8, 102);
  table.Push(39, 1034);
  table.Push(2, 456);
  table.Push(28, 1063);
  table.Push(1, 145);
  int key = 8;
  int key2 = 9;
  EXPECT_EQ(102, table.Find(key));
  EXPECT_EQ(123, table.Find(key2)); 
}

TEST(TTableTest, DelTest) // Тест метода Del()
{
  TSortTable<int, int> table;
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
  TSortTable<int, int> table;
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
  TSortTable<int, int> table;
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
  TSortTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  TTableIterator<int, int> iterator(&table, 0);
  EXPECT_EQ(0, iterator.GetIndex());
}

TEST(TTableIteratorTest, AssignmentOperatorTest) // Тест на оператор =
{
  TSortTable<int, int> table1;
  table1.Push(1, 123);
  TSortTable<int, int> table2;
  table2.Push(2, 456);
  TTableIterator<int, int> iterator1(&table1, 0);
  TTableIterator<int, int> iterator2(&table2, 0);
  iterator2 = iterator1;
  EXPECT_EQ(iterator1.GetIndex(), iterator2.GetIndex());
  EXPECT_EQ(iterator1.GetIndex(), iterator2.GetIndex());
}

TEST(TTableIteratorTest, InequalityOperatorTest) // Тест на оператор !=
{
  TSortTable<int, int> table;
  table.Push(1, 123);
  table.Push(2, 456);
  TTableIterator<int, int> iterator1(&table, 0);
  TTableIterator<int, int> iterator2(&table, 1);
  EXPECT_TRUE(iterator1 != iterator2);
}

TEST(TTableIteratorTest, EqualityOperatorTest) // Тест на оператор ==
{
  TSortTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator1(&table, 0);
  TTableIterator<int, int> iterator2(&table, 0);
  EXPECT_TRUE(iterator1 == iterator2);
}

TEST(TTableIteratorTest, IncrementOperatorTest) // Тест на оператор ++
{
  TSortTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator(&table, 0);
  TTableIterator<int, int> original_iterator = iterator;
  ++iterator;
  int expected_index = original_iterator.GetIndex() + 1;
  EXPECT_EQ(iterator.GetIndex(), expected_index);
}

TEST(TTableIteratorTest, DereferenceOperatorTest) // Тест на оператор *
{
  TSortTable<int, int> table;
  table.Push(1, 123);
  TTableIterator<int, int> iterator(&table, 0);
  int& value = *iterator;
  EXPECT_EQ(value, 123);
}