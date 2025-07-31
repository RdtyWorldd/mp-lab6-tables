#include <iostream>
#include <ScanTable.h>
#include <SortTable.h>
#include <ArrayHashTable.h>
#include <myListHashTable.h>
#include <TreeTable.h>
#include <AVLTree.h>
#include <random>
#include <string>

using namespace std;

Table<int, int>* table;

void menu();
void table_gen(int size);
void select_mode(char answer);
void table_menu();
void select_table_menu(char answer);

void test(int size, int step)
{
    Table<int, int>** tables = new Table<int, int>*[6];
    Table<int, int>* scan, *sort, *list_hash, *arr_hash;

    tables[0] = new ScanTable<int, int>(size);
    tables[1] = new SortTable<int, int>(size);
    tables[2] = new ListHashTable<int, int>(size/10);
    tables[3] = new ArrayHashTable<int, int>((int)size*1.1, step);
    tables[4] = new TreeTable<int, int>();
    tables[5] = new AVLTreeTable<int, int>();
    
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> idit (0, 100000);

    for(int i = 0 ; i < size ; i++)
    {
        int key = idit(gen);
        int val = idit(gen);

        tables[0]->insert(key, val);
        tables[1]->insert(key, val);
        tables[2]->insert(key, val);
        tables[3]->insert(key, val);
        tables[4]->insert(key, val);
        tables[5]->insert(key, val);

    }

    cout << "elements count: " << tables[0]->get_el_count() << endl;
    cout << "scan table: " << tables[0]->get_eff() << ' ' << tables[0]->get_eff() / (double)(size) << endl;
    cout << "sort table: " << tables[1]->get_eff() << ' ' << tables[1]->get_eff() / (log2(size) + size) << endl;
    cout << "array hash table: " << tables[3]->get_eff() << ' ' << tables[3]->get_eff() / size << endl;
    cout << "list hash table: " << tables[2]->get_eff() << ' ' << tables[2]->get_eff() / size << endl;
    cout << " ----------- " << endl;
    cout << "tree table: " << tables[4]->get_eff() << ' ' << tables[4]->get_eff() / size << endl;
    cout << "avl tree table: " << tables[5]->get_eff() << ' ' << tables[5]->get_eff() / size << endl;

    for(int i =0; i < 6; i++)
    {
        delete tables[i];
    }
    delete[] tables;
    cout << "-----------" << endl;
}

void menu()
{
    char answer;
    cout << "Select type of table:\n";
    cout << "[1] Unsorted table\n"; 
    cout << "[2] Sorted table\n";
    cout << "[3] Array Hash table\n";
    cout << "[4] List Hash table\n";
    cout << "[5] Tree table\n";
    cout << "[6] AVL Tree table\n";
    cout << "[7] Test all tables\n";
    cout << "[8] exit\n";
    cin >> answer;
    select_mode(answer);
}

void table_gen(int size)
{
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> idit (0, 100000);

    for(int i = 0 ; i < size ; i++)
    {
        int key = idit(gen);
        int val = idit(gen);

        table->insert(key, val);
    }
}

void select_mode(char answer)
{
    if (answer == '8')
    {
        exit(0);
    }
    else if (answer == '5')
    {
        table = new TreeTable<int,int>();
        table_menu();
    }
    else if (answer == '6')
    {
        table = new AVLTreeTable<int,int>();
        table_menu();
    }

    int n = 0;
    cout << "Please Enter size of table" << endl;
    cin >> n;
    
    if (answer == '1')
    {
        table = new ScanTable<int,int>(n);
        
        table_menu();
    }
    else if (answer == '2')
    {
        table = new SortTable<int,int>(n);
        
        table_menu();
    }
    else if (answer == '3')
    {
        int step = 13;
        cout << "Enter the step: ";
        cin >> step;
        table = new ArrayHashTable<int,int>(n, step);
        
        table_menu();
    }
    else if (answer == '4')
    {
        table = new ListHashTable<int,int>(n/2);
        table_gen(n);
        table_menu();
    }
    else if (answer == '7')
    {
        int step = 13;
        cout << "Enter step of array hash table: ";
        cin >> step;
        test(n, step);
        menu();
    }
    else
    {
        cout << "Please select numbers from menu";
        menu();
    }
}

void table_menu()
{
    char answer;
    cout << "Select operation:\n";
    cout << "[0] print\n";
    cout << "[1] insert\n"; 
    cout << "[2] delete\n";
    cout << "[3] find\n";
    cout << "[4] efficency\n";
    cout << "[5] generate table\n";
    cout << "[6] exit\n";

    cin >> answer;
    select_table_menu(answer);   
}

void select_table_menu(char answer)
{
    if(answer == '0')
    {
        cout << endl;
        table->serialize(cout);
    }
    else if (answer == '1')
    {
        int k = 0, v = 0;
        cout << "Plese enter key, value: "<<endl;
        cin >> k >> v;
        if(table->insert(k, v) == false)
        {
            cout << "Key allready exist!" << endl;
        }
    }
    else if (answer == '2')
    {
        int k;
        cout << "Plese enter key: "<<endl;
        cin >> k;
        table->del(k);
    }
    else if (answer == '3')
    {
        int k = 0;
        cout << "Plese enter key "<<endl;
        cin >> k;
        if(table->find(k) == false)
            cout << "Key didn't find!" << endl;
        else
            cout << "Key finded!" << endl;
    }
    else if (answer == '4')
    {
        cout<< "Efficency: " << table->get_eff() << endl;
    }
    else if(answer == '5')
    {
        int size = 0;
        cout << "Please Enter count of generate elements" << endl;
        cin >> size;
        table_gen(size);
    }
    else if (answer == '6')
    {
        delete table;
        menu();
    }
    table_menu();
}

int main()
{
    // int size = 10000;
    // test(size);
    // TreeTable<int, string> table;
    // table.insert(5, "five");
    // table.insert(3, "three");
    // table.insert(7, "seven");
    // table.insert(1, "one");
    // table.insert(4, "four");
    //table.serialize(cout);
    menu();
    return 0;
}