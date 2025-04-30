#pragma once
#include "Table.h"

template<typename Key, typename Value>
class HashTable : public Table<Key, Value>
{
protected:
    int size;
    virtual int hash_fuction(Key key);
public:
    HashTable(int size);
};

template <typename Key, typename Value>
inline int HashTable<Key, Value>::hash_fuction(Key key)
{
    int res = 0;
    char* p = &key;
    for(int i = 0 ; i < sizeof(Key); i++)
    {
        res = res +  (*p)
        ++p;
    }
    return res;
}

template <typename Key, typename Value>
inline HashTable<Key, Value>::HashTable(int _size): size(_size){}
