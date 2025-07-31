#include <gtest/gtest.h>
#include "AVLTree.h"
#include <vector>
#include <sstream>
#include <iostream>

class AVLTreeTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        table = new AVLTreeTable<int, std::string>();
    }

    void TearDown() override {
        delete table;
    }

    AVLTreeTable<int, std::string>* table;
};

// Тест конструктора и базовых свойств
TEST_F(AVLTreeTableTest, ConstructorAndBasicProperties) {
    EXPECT_EQ(table->get_el_count(), 0);
    EXPECT_TRUE(table->is_empty());
    EXPECT_FALSE(table->is_full());
}

// Тест вставки элементов и балансировки
TEST_F(AVLTreeTableTest, InsertAndBalance) {
    // Простая вставка
    EXPECT_TRUE(table->insert(5, "five"));
    EXPECT_EQ(table->get_el_count(), 1); //this->el_count++
    
    // Вставка с левым поворотом
    EXPECT_TRUE(table->insert(3, "three"));
    EXPECT_TRUE(table->insert(1, "one")); // Должен вызвать LL-поворот
    
    // Вставка с правым поворотом
    EXPECT_TRUE(table->insert(7, "seven"));
    EXPECT_TRUE(table->insert(9, "nine")); // Должен вызвать RR-поворот
    
    // Вставка с двойными поворотами
    EXPECT_TRUE(table->insert(6, "six")); // Может вызвать RL-поворот
    EXPECT_TRUE(table->insert(2, "two")); // Может вызвать LR-поворот
    
    EXPECT_EQ(table->get_el_count(), 7);
}

// Тест поиска элементов
TEST_F(AVLTreeTableTest, FindOperations) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    
    // Поиск существующих элементов
    EXPECT_TRUE(table->find(5));
    EXPECT_TRUE(table->find(1));
    EXPECT_TRUE(table->find(4));
    
    // Поиск несуществующих элементов
    EXPECT_FALSE(table->find(2));
    EXPECT_FALSE(table->find(6));
}

// Тест удаления элементов с балансировкой
TEST_F(AVLTreeTableTest, DeleteAndBalance) {
    // Создаем сбалансированное дерево
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");
    table->insert(9, "nine");
    
    // Удаление листа (без балансировки)
    table->del(1);
    EXPECT_EQ(table->get_el_count(), 6);
    EXPECT_FALSE(table->find(1));
    
    // Удаление узла с одним потомком
    table->del(3); // Имеет правого потомка 9
    EXPECT_EQ(table->get_el_count(), 5);
    EXPECT_FALSE(table->find(3));
    EXPECT_TRUE(table->find(4)); // Проверяем, что 9 остался
    
    // Удаление узла с двумя потомками
    table->del(5); // Корень с двумя потомками
    EXPECT_EQ(table->get_el_count(), 4);
    EXPECT_FALSE(table->find(5));
    
    // Попытка удалить несуществующий элемент
    EXPECT_NO_THROW(table->del(10));
}

// Тест итерационных методов
TEST_F(AVLTreeTableTest, IterationMethods) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");
    table->insert(9, "nine");
    
    // Проверка порядка обхода (должен быть отсортированным)
    std::vector<int> expected_order = {1, 3, 4, 5, 6, 7, 9};
    std::vector<int> actual_order;
    
    for (table->reset(); !table->is_end(); table->go_next()) {
        actual_order.push_back(table->get_curr_key());
    }
    
    EXPECT_EQ(actual_order, expected_order);
}

// Тест сериализации дерева
TEST_F(AVLTreeTableTest, SerializationTest) {
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
TEST_F(AVLTreeTableTest, EdgeCases) {
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

// Тест эффективности (счетчик eff)
TEST_F(AVLTreeTableTest, EfficiencyCounter) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    
    // Поиск должен увеличивать eff
    int initialEff = table->get_eff();
    table->find(3);
    EXPECT_GT(table->get_eff(), initialEff);
    
    // Удаление также увеличивает eff
    initialEff = table->get_eff();
    table->del(5);
    EXPECT_GT(table->get_eff(), initialEff);
}

// Тест с последовательным удалением всех элементов
TEST_F(AVLTreeTableTest, SequentialDeletion) {
    table->insert(5, "five");
    table->insert(3, "three");
    table->insert(7, "seven");
    table->insert(1, "one");
    table->insert(4, "four");
    table->insert(6, "six");
    table->insert(9, "nine");
    
    // Удаляем все элементы в произвольном порядке
    table->del(5);
    table->del(1);
    table->del(7);
    table->del(3);
    table->del(6);
    table->del(4);
    table->del(9);
    
    EXPECT_TRUE(table->is_empty());
    EXPECT_EQ(table->get_el_count(), 0);
}

// Тест сложных случаев балансировки
TEST_F(AVLTreeTableTest, ComplexBalanceCases) {
    // Создаем дерево, требующее сложных балансировок
    table->insert(30, "thirty");
    table->insert(20, "twenty");
    table->insert(40, "forty");
    table->insert(10, "ten");
    table->insert(25, "twenty-five");
    table->insert(35, "thirty-five");
    table->insert(50, "fifty");
    table->insert(5, "five");
    table->insert(15, "fifteen");
    table->insert(27, "twenty-seven");
    table->insert(45, "forty-five");
    table->insert(55, "fifty-five");
    
    // Проверяем, что дерево остается сбалансированным
    EXPECT_EQ(table->get_el_count(), 12);
    
    // Удаляем элементы, которые могут вызвать сложные балансировки
    table->del(20); // Узел с двумя потомками
    table->del(40); // Узел с двумя потомками
    table->del(10); // Может вызвать балансировку
    
    EXPECT_EQ(table->get_el_count(), 9);
    
    // Проверяем порядок элементов после удалений
    std::vector<int> expected_order = {5, 15, 25, 27, 30, 35, 45, 50, 55};
    std::vector<int> actual_order;
    
    for (table->reset(); !table->is_end(); table->go_next()) {
        actual_order.push_back(table->get_curr_key());
    }
    
    EXPECT_EQ(actual_order, expected_order);
}

TEST_F(AVLTreeTableTest, SequentialInsert) {

    for(int i = 0; i < 100; i ++)
    {
        table->insert(i, std::to_string(i));
    }
    std::cout << table->get_eff();
    EXPECT_TRUE(table->get_eff()/100.0 >= 5 && table->get_eff()/100.0 <= 8);
    EXPECT_EQ(table->get_el_count(), 100);
}