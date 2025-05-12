#include <gtest/gtest.h>
#include "myListHashTable.h"
#include <string>
#include <vector>

class ListHashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new ListHashTable<int, std::string>(10);
    }

    void TearDown() override {
        delete table;
    }

    ListHashTable<int, std::string>* table;
};

// Тест конструктора и базовых свойств
TEST_F(ListHashTableTest, ConstructorAndBasicProperties) {
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_FALSE(table->is_full());
    EXPECT_TRUE(table->is_empty());
}

// Тест вставки элементов
TEST_F(ListHashTableTest, InsertOperations) {
    // Вставка первого элемента
    EXPECT_TRUE(table->insert(1, "one"));
    EXPECT_EQ(table->get_el_count(), 1);
    EXPECT_FALSE(table->is_empty());

    // Вставка второго элемента
    EXPECT_TRUE(table->insert(2, "two"));
    EXPECT_EQ(table->get_el_count(), 2);

    // Попытка вставить дубликат
    EXPECT_FALSE(table->insert(1, "one_duplicate"));
    EXPECT_EQ(table->get_el_count(), 2);
}

// Тест поиска элементов
TEST_F(ListHashTableTest, FindOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Поиск существующего элемента
    EXPECT_TRUE(table->find(2));
    
    // Поиск несуществующего элемента
    EXPECT_FALSE(table->find(4));
}

// Тест удаления элементов
TEST_F(ListHashTableTest, DeleteOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Удаление существующего элемента
    table->del(2);
    EXPECT_EQ(table->get_el_count(), 2);
    EXPECT_FALSE(table->find(2)); // Проверка, что элемент удален

    // Попытка удалить несуществующий элемент
    EXPECT_NO_THROW(table->del(4));
    EXPECT_EQ(table->get_el_count(), 2);
}

// Тест обработки коллизий
TEST_F(ListHashTableTest, CollisionHandling) {
    // Создаем таблицу с маленьким размером для гарантии коллизий
    ListHashTable<int, std::string> smallTable(3);
    
    // Вставляем элементы, которые могут вызвать коллизии
    EXPECT_TRUE(smallTable.insert(1, "one"));
    EXPECT_TRUE(smallTable.insert(4, "four")); // Возможная коллизия
    EXPECT_TRUE(smallTable.insert(7, "seven")); // Возможная коллизия

    // Проверяем, что все элементы доступны
    EXPECT_TRUE(smallTable.find(1));
    EXPECT_TRUE(smallTable.find(4));
    EXPECT_TRUE(smallTable.find(7));

    //Проверка если удалить элемент цепочки в центре
    smallTable.del(4);
    EXPECT_TRUE(smallTable.find(1));
    EXPECT_TRUE(smallTable.find(7));

    //Проверка если удалить начальный элемент цепочки
    smallTable.del(1);
    EXPECT_TRUE(smallTable.find(7));
}

// Тест итерационных методов
TEST_F(ListHashTableTest, IterationMethods) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Проверка итерации
    std::vector<int> keys;
    for (table->reset(); !table->is_end(); table->go_next()) {
        keys.push_back(table->get_curr_key());
    }

    // Проверяем, что все ключи присутствуют
    EXPECT_EQ(keys.size(), 3);
    EXPECT_NE(std::find(keys.begin(), keys.end(), 1), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), 2), keys.end());
    EXPECT_NE(std::find(keys.begin(), keys.end(), 3), keys.end());
}

// Тест копирования и присваивания
TEST_F(ListHashTableTest, CopyAndAssignment) {
    table->insert(1, "one");
    table->insert(2, "two");

    // Тест конструктора копирования
    ListHashTable<int, std::string> copyTable(*table);
    EXPECT_EQ(copyTable.get_el_count(), 2);
    EXPECT_TRUE(copyTable.find(1));
    EXPECT_TRUE(copyTable.find(2));

    // Тест оператора присваивания
    ListHashTable<int, std::string> assignedTable;
    assignedTable = *table;
    EXPECT_EQ(assignedTable.get_el_count(), 2);
    EXPECT_TRUE(assignedTable.find(1));
    EXPECT_TRUE(assignedTable.find(2));

    // Проверка глубокого копирования
    table->insert(3, "three");
    EXPECT_EQ(copyTable.get_el_count(), 2); // Копия не должна измениться
    EXPECT_EQ(assignedTable.get_el_count(), 2); // Присвоенная таблица не должна измениться
}

// Тест граничных условий
TEST_F(ListHashTableTest, EdgeCases) {
    // Работа с пустой таблицей
    EXPECT_FALSE(table->find(1));
    EXPECT_NO_THROW(table->del(1));

    // Вставка и удаление одного элемента
    EXPECT_TRUE(table->insert(5, "five"));
    EXPECT_EQ(table->get_el_count(), 1);
    table->del(5);
    EXPECT_TRUE(table->is_empty());
}
