#pragma once
#include "ArrayTable.h"

// unsored table based on array

template<typename Key, typename Value>
class ScanTable : public ArrayTable<Key, Value>
{
    typedef typename Table<Key, Value>::Record Record;
public:
    ScanTable(int _size = 10);
    ScanTable(const ScanTable& table);
    ScanTable<Key, Value>& operator= (const ScanTable& table);
    //~ScanTable();
    
//cuur ставится на то место где назодится элемент, если его не нашли , то ставит curr в то место куда ее можно было бы добавить
    virtual bool find(Key key); 
    virtual bool insert(Key key, Value value);
    virtual void del(Key key);
};

template <typename Key, typename Value>
inline ScanTable<Key, Value>::ScanTable(int _size): ArrayTable<Key, Value>(_size) {}

template <typename Key, typename Value>
inline ScanTable<Key, Value>::ScanTable(const ScanTable &table): ArrayTable<Key, Value>(table) {}

template <typename Key, typename Value>
inline ScanTable<Key, Value> &ScanTable<Key, Value>::operator=(const ScanTable &table)
{
    return ArrayTable<Key, Value>::operator= (table);    
}

// template <typename Key, typename Value>
// inline ScanTable<Key, Value>::~ScanTable()
// {
//     ArrayTable<Key, Value>::~ArrayTable();
// }

template <typename Key, typename Value>
inline bool ScanTable<Key, Value>::find(Key key)
{
    for(int i = 0; i < this->el_count; i++)
    {
        this->eff++;
        if(this->pRec[i].key == key)
        {
            this->curr = i;
            return true;
        }
    }

    this->curr = this->el_count;
    return false;
}

template <typename Key, typename Value>
inline bool ScanTable<Key, Value>::insert(Key key, Value value)
{
    if(find(key))
    {
        return false;
    }

    Record rec = {key, value};
    // rec.key = key;
    // rec.val = value; 
    this->pRec[ this->curr]  = rec;
    (this->el_count)++;
    return true;
}

template <typename Key, typename Value>
inline void ScanTable<Key, Value>::del(Key key)
{
    if(find(key))
    {
        this->pRec[ this->curr ] = this->pRec[ this->el_count - 1];
        (this->el_count)--;
    } 
}
