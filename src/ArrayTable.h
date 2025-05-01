#pragma once
#include "Table.h"

//abstract class for tables based on array 
// ScanTable(unsotred keys), SortTable(sotred keys)

template<typename Key, typename Value>
class ArrayTable: public Table<Key, Value>
{
protected:
    typedef typename Table<Key, Value>::Record Record;
    int arr_size;
    int curr;

    Record *pRec;
public:
    ArrayTable(int _size = 10);
    ArrayTable(const ArrayTable& table);
    ArrayTable& operator=(const ArrayTable& table); 
    ~ArrayTable();

    bool is_full();
    // bool os_empy() - locate in class Table

    // find insert del absaract methods

    void reset();
    void go_next();
    bool is_end();

    Key get_curr_key();
    Value get_curr_val();
};

template <typename Key, typename Value>
inline ArrayTable<Key, Value>::ArrayTable(int _size) : Table<Key, Value>()
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
    this->arr_size = table.arr_size;
    this->pRec = new Record[table.arr_size];
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
inline bool ArrayTable<Key, Value>::is_full() { return this->el_count == arr_size; }

template <typename Key, typename Value>
inline void ArrayTable<Key, Value>::reset() { this->curr = 0; }

template <typename Key, typename Value>
inline void ArrayTable<Key, Value>::go_next() { (this->curr)++; }

template <typename Key, typename Value>
inline bool ArrayTable<Key, Value>::is_end() { return (this->el_count) == (this->curr); };

template <typename Key, typename Value>
inline Key ArrayTable<Key, Value>::get_curr_key()
{
    return pRec[curr].key;
}

template <typename Key, typename Value>
inline Value ArrayTable<Key, Value>::get_curr_val()
{
    return pRec[curr].val;
}

template <typename Key, typename Value>
inline ArrayTable<Key, Value> &ArrayTable<Key, Value>::operator=(const ArrayTable &table)
{
    if(this == &table)
    {
        return *this;
    }

    if(arr_size != table.arr_size)
    {
        Record* tmp = new Record[table.arr_size];

        this->arr_size = table.arr_size;
        delete[] this->pRec;
        this->pRec = tmp;
    }
    for(int i = 0; i < table.el_count; i++)
    {
        this->pRec[i] = table.pRec[i];
    }
    this->el_count = table.el_count;
    return *this;
}
