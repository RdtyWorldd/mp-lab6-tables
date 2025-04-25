#include <iostream>
#include <ScanTable.h>
#include <random>

int main()
{
    int size = 5;
    Table<int, int>* table = new ScanTable<int, int>();


    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Определение диапазона (например, от 0 до 99)
    std::uniform_int_distribution<int> idit(0, 99);

    for(int i = 0; i < size; i++)
    {
        table->insert(idit(gen), i);
    }


    for(table->reset(); !table->is_end(); table->go_next())
    {
        std::cout << table->get_curr_key() << " " << table->get_curr_val() << std::endl;
    }

    return 0;
} 