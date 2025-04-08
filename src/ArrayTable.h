#pragma once
#include "Table.h"

//abstract class for tables based on array 
// ScanTable(unsotred keys), SortTable(sotred keys)

template<typename Key, typename Value>
class ArrayTable: public Table<Key, Value>
{
protected:
    int arr_size;
    int curr;
    
    Record *pRec;
public:
    ArrayTable(int _size = 10);
    ArrayTable(const ArrayTable& table);
    ArrayTable& operaor=(const ArrayTable& table); 
    ~ArrayTable();

    bool is_full();
    // bool os_empy() - locate in class Table

    // find insert del absarac methods

    void reset();
    void go_next();
    bool is_end();
};

template <typename Key, typename Value>
inline ArrayTable<Key, Value>::ArrayTable(int _size) : Table()
{
    //check some standarts to exceptions
    if(_size <= 0)
    {
        throw std::exception(); 
    }

    arr_size = _size;
    pRec = new Record[arr_size];
    curr = -1;
}

template <typename Key, typename Value>
inline ArrayTable<Key, Value>::ArrayTable(const ArrayTable &table)
{
    if(this->arr_size != table.arr_size)
    {   
        Record* tmp = this->pRec;
        try {
            this->pRec = new Record[table.arr_size];
        } catch(std::exception e) {
            this->pRec = tmp;
            return;
        }
        delete[] tmp;
    }
    this->arr_size = table.arr_size;
    this->el_count = table.el_count;
    this->curr = table.curr;
    for(int i = 0; i < this->el_count; i++)
    {
        this->pRec[i] = table.pRec[i];
    }
}

template <typename Key, typename Value>
inline ArrayTable<Key, Value>::~ArrayTable() { delete[] pRec; }

template <typename Key, typename Value>
inline bool ArrayTable<Key, Value>::is_full() { return el_count == arr_size; }

template <typename Key, typename Value>
inline void ArrayTable<Key, Value>::reset() { curr = 0; }

template <typename Key, typename Value>
inline void ArrayTable<Key, Value>::go_next() { curr++; }

template <typename Key, typename Value>
inline bool ArrayTable<Key, Value>::is_end() { return el_count == curr };
