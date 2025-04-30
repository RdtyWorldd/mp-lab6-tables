#pragma once
#include"HashTable.h"

template <typename Key, typename Value>
class ArrayHashTable : public HashTable<Key, Value>
{
protected:
    typedef typename Table<Key, Value>::Record Record;
    Record *pRec;
    int step;
    Record free_rec, del_rec;
    int curr;
    int i_count;
public:
    ArrayHashTable(int _size, int _step = 13);
    ~ArrayHashTable();
    bool is_full();

    bool find(Key key);
    bool insert(Key key, Value val);
    void del(Key key);

    void reset();
    void go_next();
    bool is_end();

    Key get_curr_key();
    Value get_curr_val();
};

template <typename Key, typename Value>
inline ArrayHashTable<Key, Value>::ArrayHashTable(int _size, int _step) : HashTable<Key, Value>(_size)
{
    step = _step;
    free_rec = {-1, 0};
    del_rec = {-2, 0};
    pRec = new Record[this->size];
    for(int i = 0; i < this->size;i++)
        pRec[i] = free_rec;
    //
}

template <typename Key, typename Value>
inline bool ArrayHashTable<Key, Value>::is_full()
{
    return this->el_count == this->size;
}

template <typename Key, typename Value>
inline bool ArrayHashTable<Key, Value>::find(Key key)
{
    curr = this->hash_fuction(key);
    int tmp = -1;
    
    for(int i = 0; i < this->size; i++)
    {
        if(pRec[curr].key == free_rec.key)
            break;
        else if(pRec[curr].key == del_rec.key && tmp == -1)
        {
            tmp = curr;
        }
        else if(pRec[curr].key == key)
        {
            return true;
        }
        curr = (curr + step) % this->size;
    }

    //set curr on first found deleted record
    if(tmp != -1)
        curr = tmp;
    return false;
}

template <typename Key, typename Value>
inline bool ArrayHashTable<Key, Value>::insert(Key key, Value val)
{
    if(!find(key))
    {
        this->el_count++;
        pRec[curr] = {key, val};
        return true;
    }
    return false;
}

template <typename Key, typename Value>
inline void ArrayHashTable<Key, Value>::del(Key key)
{
    if(find(key))
    {
        pRec[curr] = del_rec;
        this->el_count--;
    }
}

template <typename Key, typename Value>
inline void ArrayHashTable<Key, Value>::reset()
{
    curr = 0;
    i_count = 0;
    for(int i = 0 ; i < this->size; i++)
    {
        if(pRec[i].key != free_rec.key && pRec[i].key != del_rec.key)
        {
            curr = i;
            return;
        }
    }
}

template <typename Key, typename Value>
inline void ArrayHashTable<Key, Value>::go_next()
{
    for(int i = curr + 1; i < this->size; i++)
    {
        if(pRec[i].key != free_rec.key && pRec[i].key != del_rec.key)
        {
            curr = i;
            break;
        }
    }
    i_count++;
}

template <typename Key, typename Value>
inline bool ArrayHashTable<Key, Value>::is_end()
{
    return i_count == this->el_count;
}

template <typename Key, typename Value>
inline Key ArrayHashTable<Key, Value>::get_curr_key()
{
    return pRec[curr].key;
}

template <typename Key, typename Value>
inline Value ArrayHashTable<Key, Value>::get_curr_val()
{
    return pRec[curr].val;
}

template <typename Key, typename Value>
inline ArrayHashTable<Key, Value>::~ArrayHashTable()
{
    delete[] pRec;
}
