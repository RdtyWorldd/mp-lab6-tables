#include <gtest/gtest.h>
#include "ArrayHashTable.h"

class ArrayHashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new ArrayHashTable<int, std::string>(5);
    }

    void TearDown() override {
        delete table;
    }

    ArrayHashTable<int, std::string>* table;
};

// Тест конструктора и базовых свойств
TEST_F(ArrayHashTableTest, ConstructorAndBasicProperties) {
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_FALSE(table->is_full());
    EXPECT_TRUE(table->is_empty());
}

// Тест вставки элементов 
// надо уменьшить размер или вставлять до конца
TEST_F(ArrayHashTableTest, InsertOperations) {
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

    // Заполнение таблицы
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_TRUE(table->insert(4, "four"));
    EXPECT_TRUE(table->insert(5, "five"));
    //EXPECT_TRUE(table->is_full());
    
    // Попытка вставить в полную таблицу
    EXPECT_FALSE(table->insert(6, "six"));
    EXPECT_EQ(table->get_el_count(), 5);
}

// Тест поиска элементов
TEST_F(ArrayHashTableTest, FindOperations) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Поиск существующего элемента
    EXPECT_TRUE(table->find(2));
    EXPECT_EQ(table->get_curr_val(), "two");

    // Поиск несуществующего элемента
    EXPECT_FALSE(table->find(4));
}

// Тест удаления элементов
TEST_F(ArrayHashTableTest, DeleteOperations) {
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

// Тест работы с удаленными элементами
TEST_F(ArrayHashTableTest, DeletedElementsHandling) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Удаление элемента
    table->del(2);

    // Проверка, что удаленный элемент не находится
    EXPECT_FALSE(table->find(2));

    // Вставка нового элемента на место удаленного
    EXPECT_TRUE(table->insert(4, "four"));
    EXPECT_EQ(table->get_el_count(), 3);
    EXPECT_TRUE(table->find(4));
}

// Тест итерационных методов
TEST_F(ArrayHashTableTest, IterationMethods) {
    table->insert(1, "one");
    table->insert(2, "two");
    table->insert(3, "three");

    // Проверка итерации
    table->reset();
    EXPECT_FALSE(table->is_end());

    // Собираем все ключи через итерацию
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

// Тест коллизий
TEST_F(ArrayHashTableTest, CollisionHandling) {
    // Создаем таблицу с маленьким размером для гарантии коллизий
    ArrayHashTable<int, std::string> smallTable(3);
    
    // Вставляем элементы, которые могут вызвать коллизии
    EXPECT_TRUE(smallTable.insert(1, "one"));
    EXPECT_TRUE(smallTable.insert(4, "four")); // Возможная коллизия с 1
    EXPECT_TRUE(smallTable.insert(7, "seven")); // Возможная коллизия

    // Проверяем, что все элементы доступны
    EXPECT_TRUE(smallTable.find(1));
    EXPECT_TRUE(smallTable.find(4));
    EXPECT_TRUE(smallTable.find(7));

    //Проверка если удалить начальный элемент цепочки
    smallTable.del(1);
    EXPECT_TRUE(smallTable.find(4));
    EXPECT_TRUE(smallTable.find(7));


    //Проверка если удалить элемент цепочки в центре
    smallTable.insert(1, "one");
    smallTable.del(4);
    EXPECT_TRUE(smallTable.find(7));
}
