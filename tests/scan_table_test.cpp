#include <gtest/gtest.h>
#include "ScanTable.h"

class ScanTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new ScanTable<int, std::string>(5);
    }

    void TearDown() override {
        delete table;
    }

    ScanTable<int, std::string>* table;
};

// Тест конструктора и базовых свойств
TEST_F(ScanTableTest, ConstructorAndBasicProperties) {
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_EQ(table->get_eff(), 0);
    EXPECT_TRUE(table->is_empty());
    EXPECT_FALSE(table->is_full());
    EXPECT_THROW( (ScanTable<int, std::string>(-1)), std::exception); // Проверка исключения при отрицательном размере
}

// Тест поиска элементов
TEST_F(ScanTableTest, FindOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Поиск существующего элемента
    EXPECT_TRUE(table->find(2));
    EXPECT_EQ(table->get_curr_key(), 2);
    EXPECT_EQ(table->get_curr_val(), "two");
    EXPECT_GT(table->get_eff(), 0);

    // Поиск несуществующего элемента
    EXPECT_FALSE(table->find(4));
    
    //EXPECT_EQ(table->get_curr(), 3); // curr должен указывать на позицию после последнего элемента
}

// Тест вставки элементов
TEST_F(ScanTableTest, InsertOperations) {
    // Вставка первого элемента
    EXPECT_TRUE(table->insert(1, "one"));
    EXPECT_EQ(table->get_el_count(), 1);
    EXPECT_FALSE(table->is_empty());
    EXPECT_FALSE(table->is_full());

    // Вставка второго элемента
    EXPECT_TRUE(table->insert(2, "two"));
    EXPECT_EQ(table->get_el_count(), 2);

    // Попытка вставить дубликат
    EXPECT_FALSE(table->insert(1, "one_duplicate"));
    EXPECT_EQ(table->get_el_count(), 2);

    // Заполнение таблицы
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_TRUE(table->insert(4, "four"));
    EXPECT_TRUE(table->insert(5, "five"));
    EXPECT_TRUE(table->is_full());

    // Попытка вставить в полную таблицу
    EXPECT_FALSE(table->insert(6, "six"));
    EXPECT_EQ(table->get_el_count(), 5);
}

// Тест удаления элементов
TEST_F(ScanTableTest, DeleteOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");
    table->insert(4, "four");

    // Удаление существующего элемента
    table->del(2);
    EXPECT_EQ(table->get_el_count(), 3);
    EXPECT_FALSE(table->find(2)); // Проверка, что элемент удален
    //EXPECT_TRUE(table->find(4)); // Проверка, что другие элементы остались

    // Попытка удалить несуществующий элемент
    ASSERT_NO_THROW(table->del(5));
    EXPECT_EQ(table->get_el_count(), 3);

    // Удаление всех элементов
    table->del(1);
    table->del(3);
    table->del(4);
    EXPECT_TRUE(table->is_empty());
}

// Тест итерационных методов
TEST_F(ScanTableTest, IterationMethods) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Проверка итерации
    table->reset();
    EXPECT_FALSE(table->is_end());
    EXPECT_EQ(table->get_curr_key(), 1);
    EXPECT_EQ(table->get_curr_val(), "one");

    table->go_next();
    EXPECT_FALSE(table->is_end());
    EXPECT_EQ(table->get_curr_key(), 2);
    EXPECT_EQ(table->get_curr_val(), "two");

    table->go_next();
    EXPECT_FALSE(table->is_end());
    EXPECT_EQ(table->get_curr_key(), 3);
    EXPECT_EQ(table->get_curr_val(), "three");

    table->go_next();
    EXPECT_TRUE(table->is_end());
}

// Тест оператора вывода
// TEST_F(ScanTableTest, OutputOperator) {
//     table->insert(1, "one");
//     table->insert(2, "two");
//
//     std::ostringstream oss;
//     oss << *table;
//    
//     // Проверяем, что вывод содержит все элементы
//     std::string output = oss.str();
//     EXPECT_NE(output.find("1 one"), std::string::npos);
//     EXPECT_NE(output.find("2 two"), std::string::npos);
//     EXPECT_EQ(output.size(), 12); // "1 one\n2 two\n" - 12 символов
// }

// Тест копирования и присваивания
TEST_F(ScanTableTest, CopyAndAssignment) {
    table->insert(1, "one");
    table->insert(2, "two");

    // Тест конструктора копирования
    ScanTable<int, std::string> *copyTable = new ScanTable<int, std::string>(*table);
    EXPECT_EQ(copyTable->get_el_count(), 2);
    EXPECT_TRUE(copyTable->find(1));
    EXPECT_TRUE(copyTable->find(2));

    // Тест оператора присваивания
    ScanTable<int, std::string> *assignedTable = new ScanTable<int, std::string>(10);
    *assignedTable = *table;
    EXPECT_EQ(assignedTable->get_el_count(), 2);
    EXPECT_TRUE(assignedTable->find(1));
    EXPECT_TRUE(assignedTable->find(2));

    // Проверка глубокого копирования
    table->insert(3, "three");
    EXPECT_EQ(copyTable->get_el_count(), 2); // Копия не должна измениться
    EXPECT_EQ(assignedTable->get_el_count(), 2); // Присвоенная таблица не должна измениться

    delete copyTable;
    ASSERT_NO_THROW(table->find(1));

    delete assignedTable;
    ASSERT_NO_THROW(table->find(1));
}    

// Тест эффективности (eff)
TEST_F(ScanTableTest, EfficiencyCounter) {
    // Вставка элементов
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Поиск должен увеличивать eff
    int initialEff = table->get_eff();
    table->find(2);
    EXPECT_GT(table->get_eff(), initialEff);

    // Поиск несуществующего элемента также увеличивает eff
    initialEff = table->get_eff();
    table->find(4);
    EXPECT_GT(table->get_eff(), initialEff);

    // Удаление также использует find и увеличивает eff
    initialEff = table->get_eff();
    table->del(2);
    EXPECT_GT(table->get_eff(), initialEff);
}
