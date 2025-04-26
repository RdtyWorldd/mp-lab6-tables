#include <iostream>
#include <ScanTable.h>
#include <SortTable.h>
#include <random>

int main()
{
    int size = 6;
    Table<int, int>* table = new ScanTable<int, int>(size);
    Table<int, int>* table1;

    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Определение диапазона (например, от 0 до 99)
    std::uniform_int_distribution<int> idit(0, 99);

    for(int i = 0; i < size; i++)
    {
        int key = idit(gen);
        std::cout << key << ' ';
        table->insert(key, i);
    }
    std::cout << std::endl;

    for(table->reset(); !table->is_end(); table->go_next())
    {
        std::cout << table->get_curr_key() << " " << table->get_curr_val() << std::endl;
    }
    std::cout << std::endl;

    table1 = new SortTable<int, int>(*((ScanTable<int, int> *)table));
    for(table1->reset(); !table1->is_end(); table1->go_next())
    {
        std::cout << table1->get_curr_key() << " " << table1->get_curr_val() << std::endl;
    }

    return 0;
} 