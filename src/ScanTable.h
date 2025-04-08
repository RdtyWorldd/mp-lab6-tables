#pragma once
#include "ArrayTable.h"

// unsored table based on array

template<typename Key, typename Value>
class ScanTable : public ArrayTable<Key, Value>
{
public:
    ScanTable(int _size = 10);
    ScanTable(const ScanTable& table);
    ScanTable& operator= (const ScanTable& table);
    ~ScanTable();
    
//cuur ставится на то место где назодится элемент, если его не нашли , то ставит curr в то место куда ее можно было бы добавить
    virtual bool find(Key key); 
    virtual bool insert(Key key, Value value);
    virtual void del(Key key);
};

template <typename Key, typename Value>
inline ScanTable<Key, Value>::ScanTable(int _size): ArrayTable(_size) {}

template <typename Key, typename Value>
inline ScanTable<Key, Value>::ScanTable(const ScanTable &table): ArrayTable(_size) {}

template <typename Key, typename Value>
inline ScanTable &ScanTable<Key, Value>::operator=(const ScanTable &table)
{
    return ArrayTable::operator= (table);    
}

template <typename Key, typename Value>
inline bool ScanTable<Key, Value>::find(Key key)
{
    for(int i = 0; i < el_count; i++)
    {
        eff++;
        if(pRec[i].key == key)
        {
            curr = i;
            return true;
        }
    }

    curr = el_count;
    return false;
}

template <typename Key, typename Value>
inline bool ScanTable<Key, Value>::insert(Key key, Value value)
{
    if(find(key))
    {
        return false;
    }

    Record rec {key, value};
    // rec.key = key;
    // rec.val = value;
    pRec[curr] = rec;
    el_count++;
    return true;
}

template <typename Key, typename Value>
inline void ScanTable<Key, Value>::del(Key key)
{
    if(find(key))
    {
        pRec[curr] = pRec[el_count - 1];
        el_count--;
    } 
}
