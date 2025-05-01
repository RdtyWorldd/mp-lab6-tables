#include <gtest/gtest.h>
#include <SortTable.h>

#include <gtest/gtest.h>
#include "SortTable.h"

class SortTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new SortTable<int, std::string>(5);
    }

    void TearDown() override {
        delete table;
    }

    SortTable<int, std::string>* table;
};

// Тест конструкторов
TEST_F(SortTableTest, Constructors) {
    // Тест конструктора по умолчанию
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_FALSE(table->is_full());

    // Тест конструктора копирования
    table->insert(3, "three");
    table->insert(1, "one");
    SortTable<int, std::string> *copyTable = new SortTable<int, std::string>(*table);
    EXPECT_EQ(copyTable->get_el_count(), 2);
    EXPECT_TRUE(copyTable->find(1));
    EXPECT_TRUE(copyTable->find(3));

    delete copyTable;
    EXPECT_NO_THROW(table->find(1));

    // Тест конструктора из ScanTable
    ScanTable<int, std::string> scanTable(5);
    scanTable.insert(5, "five");
    scanTable.insert(2, "two");
    SortTable<int, std::string> fromScanTable(scanTable);
    EXPECT_EQ(fromScanTable.get_el_count(), 2);
    EXPECT_TRUE(fromScanTable.find(2));
    EXPECT_TRUE(fromScanTable.find(5));
}

// Тест бинарного поиска
TEST_F(SortTableTest, BinarySearch) {
    table->insert(1, "one");
    table->insert(3, "three");
    table->insert(5, "five");

    // Поиск существующих элементов
    EXPECT_TRUE(table->find(1));
    EXPECT_EQ(table->get_curr_val(), "one");
    EXPECT_TRUE(table->find(3));
    EXPECT_EQ(table->get_curr_val(), "three");
    EXPECT_TRUE(table->find(5));
    EXPECT_EQ(table->get_curr_val(), "five");

    // Поиск несуществующих элементов
    EXPECT_FALSE(table->find(0));
    EXPECT_FALSE(table->find(2));
    EXPECT_FALSE(table->find(4));
    EXPECT_FALSE(table->find(6));
}

// Тест вставки элементов с сохранением порядка
TEST_F(SortTableTest, InsertMaintainsOrder) {
    // Вставка в разном порядке
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_TRUE(table->insert(1, "one"));
    EXPECT_TRUE(table->insert(4, "four"));
    EXPECT_TRUE(table->insert(2, "two"));

    // Проверка порядка элементов
    table->reset();
    EXPECT_EQ(table->get_curr_key(), 1);
    table->go_next();
    EXPECT_EQ(table->get_curr_key(), 2);
    table->go_next();
    EXPECT_EQ(table->get_curr_key(), 3);
    table->go_next();
    EXPECT_EQ(table->get_curr_key(), 4);

    // Попытка вставить дубликат
    EXPECT_FALSE(table->insert(2, "two_duplicate"));
}



// Тест удаления элементов
TEST_F(SortTableTest, DeleteOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");
    table->insert(4, "four");

    // Удаление существующего элемента
    table->del(2);
    EXPECT_EQ(table->get_el_count(), 3);
    EXPECT_FALSE(table->find(2));

    // Проверка порядка после удаления
    table->reset();
    EXPECT_EQ(table->get_curr_key(), 1);
    table->go_next();
    EXPECT_EQ(table->get_curr_key(), 3);
    table->go_next();
    EXPECT_EQ(table->get_curr_key(), 4);

    // Попытка удалить несуществующий элемент
    EXPECT_NO_THROW(table->del(5));

    // Удаление всех элементов таблицы
    table->del(1);
    table->del(3);
    table->del(4);
    EXPECT_TRUE(table->is_empty());
}

// Тест заполнения таблицы
TEST_F(SortTableTest, FullTable) {
    // Заполнение таблицы
    EXPECT_TRUE(table->insert(1, "one"));
    EXPECT_TRUE(table->insert(2, "two"));
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_TRUE(table->insert(4, "four"));
    EXPECT_TRUE(table->insert(5, "five"));

    EXPECT_TRUE(table->is_full());

    // Попытка вставить в полную таблицу
    EXPECT_THROW(table->insert(6, "six"), std::length_error);
}

// Тест сортировки
TEST_F(SortTableTest, Sorting) {
    // Создаем неотсортированную таблицу
    ScanTable<int, std::string> scanTable(5);
    scanTable.insert(5, "five");
    scanTable.insert(1, "one");
    scanTable.insert(3, "three");

    // Конвертируем в SortTable (должна произойти сортировка)
    SortTable<int, std::string> sortTable(scanTable);

    // Проверяем порядок элементов
    sortTable.reset();
    EXPECT_EQ(sortTable.get_curr_key(), 1);
    sortTable.go_next();
    EXPECT_EQ(sortTable.get_curr_key(), 3);
    sortTable.go_next();
    EXPECT_EQ(sortTable.get_curr_key(), 5);
}

// Тест эффективности (eff)
TEST_F(SortTableTest, EfficiencyCounter) {
    // Вставка элементов
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");
    table->insert(4, "four");

    // Поиск должен увеличивать eff
    int initialEff = table->get_eff();
    table->find(3);
    EXPECT_GT(table->get_eff(), initialEff);

    // Удаление также увеличивает eff
    initialEff = table->get_eff();
    table->del(2);
    EXPECT_GT(table->get_eff(), initialEff);
}

// Тест оператора присваивания
TEST_F(SortTableTest, AssignmentOperator) {
    table->insert(1, "one");
    table->insert(3, "three");

    SortTable<int, std::string> *assignedTable = new SortTable<int, std::string>();
    *assignedTable = *table;

    EXPECT_EQ(assignedTable->get_el_count(), 2);
    EXPECT_TRUE(assignedTable->find(1));
    EXPECT_TRUE(assignedTable->find(3));

    delete assignedTable;
    ASSERT_NO_THROW(table->find(1));
}
