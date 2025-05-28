#include <gtest/gtest.h>
#include "TreeTable.h"
#include <sstream>
#include <vector>

class TreeTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new TreeTable<int, std::string>();
    }

    void TearDown() override {
        delete table;
    }

    TreeTable<int, std::string>* table;
};

// Тест конструктора и базовых свойств
TEST_F(TreeTableTest, ConstructorAndBasicProperties) {
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_TRUE(table->is_empty());
}

// Тест вставки элементов
TEST_F(TreeTableTest, InsertOperations) {
    // Вставка первого элемента
    EXPECT_TRUE(table->insert(5, "five"));
    EXPECT_EQ(table->get_el_count(), 1);
    EXPECT_FALSE(table->is_empty());

    // Вставка меньшего элемента
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_EQ(table->get_el_count(), 2);

    // Вставка большего элемента
    EXPECT_TRUE(table->insert(7, "seven"));
    EXPECT_EQ(table->get_el_count(), 3);

    // Попытка вставить дубликат
    EXPECT_FALSE(table->insert(5, "five_duplicate"));
    EXPECT_EQ(table->get_el_count(), 3);
}

// Тест поиска элементов
TEST_F(TreeTableTest, FindOperations) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");

    // Поиск существующих элементов
    EXPECT_TRUE(table->find(5));
    EXPECT_TRUE(table->find(3));
    EXPECT_TRUE(table->find(1));

    // Поиск несуществующих элементов
    EXPECT_FALSE(table->find(2));
    EXPECT_FALSE(table->find(6));
}

// Тест удаления элементов (все три случая)
TEST_F(TreeTableTest, DeleteOperations) {
    // Создаем дерево:      5
    //                    /   \
    //                   3     7
    //                  / \   /
    //                 1   4 6
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");

    // Случай 1: Удаление листа (нет потомков)
    table->del(1);
    EXPECT_EQ(table->get_el_count(), 5);
    EXPECT_FALSE(table->find(1));

    // Случай 2: Удаление узла с одним потомком
    table->del(7); // У 7 есть только левый потомок 6
    EXPECT_EQ(table->get_el_count(), 4);
    EXPECT_FALSE(table->find(7));
    EXPECT_TRUE(table->find(6)); // Проверяем, что 6 остался в дереве

    // Случай 3: Удаление узла с двумя потомками
    table->del(3); // У 3 есть оба потомка (1 уже удален, теперь 4)
    EXPECT_EQ(table->get_el_count(), 3);
    EXPECT_FALSE(table->find(3));
    EXPECT_TRUE(table->find(4)); // Проверяем, что 4 остался в дереве

    // Попытка удалить несуществующий элемент
    EXPECT_NO_THROW(table->del(10));
}

// Тест итерационных методов
TEST_F(TreeTableTest, IterationMethods) {
    // Создаем дерево:      5
    //                    /   \
    //                   3     7
    //                  / \   /
    //                 1   4 6
    // ожидаемый порядок обхода 1 3 4 5 6 7
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");

    // Проверка порядка обхода (должен быть отсортированным)
    std::vector<int> expected_order = {1, 3, 4, 5, 6, 7};
    std::vector<int> actual_order;

    for (table->reset(); !table->is_end(); table->go_next()) {
        actual_order.push_back(table->get_curr_key());
    }

    EXPECT_EQ(actual_order, expected_order);
}

// Тест сериализации дерева
TEST_F(TreeTableTest, SerializationTest) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");

    std::ostringstream oss;
    table->serialize(oss);
    std::string output = oss.str();

    // Проверяем, что вывод содержит все ключи
    EXPECT_NE(output.find("5"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
    EXPECT_NE(output.find("7"), std::string::npos);
}

// Тест граничных условий
TEST_F(TreeTableTest, EdgeCases) {
    // Работа с пустым деревом
    EXPECT_FALSE(table->find(1));
    EXPECT_NO_THROW(table->del(1));
    EXPECT_TRUE(table->is_end());

    // Вставка и удаление единственного элемента
    EXPECT_TRUE(table->insert(10, "ten"));
    EXPECT_EQ(table->get_el_count(), 1);
    table->del(10);
    EXPECT_TRUE(table->is_empty());

    // Проверка is_end после reset для пустого дерева
    table->reset();
    EXPECT_TRUE(table->is_end());
}

// Тест с последовательным удалением всех элементов
TEST_F(TreeTableTest, SequentialDeletion) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");

    // Удаляем все элементы в произвольном порядке
    table->del(5);
    table->del(1);
    table->del(7);
    table->del(3);
    table->del(6);
    table->del(4);

    EXPECT_TRUE(table->is_empty());
    EXPECT_EQ(table->get_el_count(), 0);
}