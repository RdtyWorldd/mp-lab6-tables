#pragma once
#include "HashTable.h"
#include "List.h"

template<typename Key, typename Value>
class ListHashTable: public HashTable<Key, Value>
{
protected:
typedef typename Table<Key, Value>::Record Record;
typedef typename List<Record>::iterator iterator;

    List<Record> *pRec;
    int curr_list;
    //iterator curr_iter;
public:
    ListHashTable(int _size = 10);
    ListHashTable(const ListHashTable& table);
    ListHashTable<Key, Value>& operator= (const ListHashTable& table);
    ~ListHashTable();

    bool is_full();

    bool find(Key key);
    bool insert(Key key, Value value);
    void del(Key key);

    //iteration methods
    void reset();
    bool is_end();
    void go_next();

    Key get_curr_key();
    Value get_curr_val();
};

template <typename Key, typename Value>
inline ListHashTable<Key, Value>::ListHashTable(int _size): HashTable<Key, Value>(_size)
{
    pRec = new List<Record> [this->size];
}

template <typename Key, typename Value>
inline ListHashTable<Key, Value>::ListHashTable(const ListHashTable &table): HashTable<Key, Value>(table.size)
{
    this->pRec = new List<Record> [this->size];
    this->el_count = table.el_count;
    for(int i =0; i < this->size; i++)
    {
        //copy  i list object from table to this
        this->pRec[i] = table.pRec[i];
    }
}

template <typename Key, typename Value>
inline ListHashTable<Key, Value> &ListHashTable<Key, Value>::operator=(const ListHashTable &table)
{
    if(this != &table)
    { 
        if(this->size != table.size)
        {
            delete[] this->pRec;
            this->pRec = new List<Record> [table.size];
        }

        this->size = table.size;
        this->el_count = table.el_count;
        for(int i = 0; i < this->size; i++)
        {
            this->pRec[i] = table.pRec[i];
        }
    }
    return *this;
}

template <typename Key, typename Value>
inline ListHashTable<Key, Value>::~ListHashTable()
{
    delete[] pRec;
}

template <typename Key, typename Value>
inline bool ListHashTable<Key, Value>::is_full()
{
    return false;
}

template <typename Key, typename Value>
inline bool ListHashTable<Key, Value>::find(Key key)
{
    curr_list = this->hash_fuction(key);
    List<Record>& iter_list = pRec[curr_list];

    for(iter_list.Reset(); !iter_list.IsEnd(); iter_list.GoNext())
    {
        (this->eff)++;
        if(iter_list.getCurr().key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
inline bool ListHashTable<Key, Value>::insert(Key key, Value value)
{
    if(!find(key))
    {
        pRec[curr_list].insertCurr( {key, value} );
        this->el_count++;
        return true;
    }
    return false;
}

template <typename Key, typename Value>
inline void ListHashTable<Key, Value>::del(Key key)
{
    if(find(key))
    {
        pRec[curr_list].removeCurr();
        this->el_count--;
    }
}

template <typename Key, typename Value>
inline void ListHashTable<Key, Value>::reset()
{
    curr_list = 0;
    List<Record>* iter_list = pRec + curr_list;
    //curr_iter = pRec[curr_list].begin();
    //iterator end = pRec[curr_list].end();
    iter_list->Reset();
    while(iter_list->IsEnd() && curr_list < this->size)
    {
        curr_list++;
        iter_list = pRec + curr_list;
        iter_list->Reset();
    }
}

template <typename Key, typename Value>
inline bool ListHashTable<Key, Value>::is_end()
{
    return curr_list == this->size;
}

template <typename Key, typename Value>
inline void ListHashTable<Key, Value>::go_next()
{
    List<Record>* iter_list = pRec + curr_list;
    iter_list->GoNext();
    //iterator end = pRec[curr_list].end();
        
    while(iter_list->IsEnd() && curr_list < this->size)
    {
        curr_list++;
        iter_list = pRec + curr_list;
        iter_list->Reset();
    }

}

template <typename Key, typename Value>
inline Key ListHashTable<Key, Value>::get_curr_key()
{
    return pRec[curr_list].getCurr().key;
}

template <typename Key, typename Value>
inline Value ListHashTable<Key, Value>::get_curr_val()
{
    return pRec[curr_list].getCurr().val;
}
// промежуточная реализация рабочих таблиц


