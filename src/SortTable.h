#pragma once
#include "ScanTable.h"
#include <exception>

template<typename Key, typename Value>
class SortTable : public ScanTable<Key, Value>
{
private:
    typedef typename Table<Key, Value>::Record Record;
//i forget for what we write this methods (may be to cast unsotred table to sort)
    // void select_sort();
    // void quick_sort(int start, int finish);
    // void merge_sort();
    // void merge();
public:
    SortTable(int _size);
    SortTable(const SortTable& table);
    SortTable(const ScanTable<Key, Value>& table);

    SortTable& operator= (const SortTable& table);

    virtual bool find(Key key);
    virtual bool insert(Key key, Value value);
    virtual void del(Key key);
};

// template <typename Key, typename Value>
// inline void SortTable<Key, Value>::select_sort()
// {
//     for(int i = 0; i < arr_size-1; i++)
//     {
//         Record m = pRec[i];
//         for(int j = i+1; i < arr_size; j++)
//         {
//             if(m > pRec[j])
//             {
//                 m = pRec[j];
//                 pRec[j] = pRec[i];   
//             }
//         }
//         arr[i] = m;
//     }
// }

// template <typename Key, typename Value>
// inline void SortTable<Key, Value>::quick_sort(int start, int finish)
// {
//     int k = (start + finish) / 2;
//     int left = start; 
//     int right = finish;
//     Record partion = pRec[k];
//     while(left < right)
//     {
//         while(pRec[left]  < partion)
//             left ++;
//         while(pRec[right] > partion)
//             right--;
//         if(left <= right)
//         {
//             //swap
//             left++; 
//             right--;
//         }
//     }
//     if(start < left)
//     {
//         quick_sort(start, left);
//         quick_sort(right, finish);
//     } 
// }

template <typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(int _size) : ScanTable<Key, Value>(_size) {}

template <typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(const SortTable& table) : ScanTable<Key, Value>(table) {}

template<typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(const ScanTable<Key, Value>& table): ScanTable<Key, Value>(table) {
    //some sort method
}

template <typename Key, typename Value>
inline bool SortTable<Key, Value>::find(Key key)
{
    //binary search
    int start = 0;
    int finish = this->el_count - 1;
    while(start <= finish)
    {
        this->eff++;
        int ind = (start + finish) / 2;
        if(this->pRec[ind].key > key)
        {
            finish = ind - 1;
        }
        else if(this->pRec[ind].key < key)
        {
            start = ind + 1;
        }
        else
        {
            this->curr = ind;
            return true;
        }
    }
    this->curr = start;
    return false;
}

template <typename Key, typename Value>
inline bool SortTable<Key, Value>::insert(Key key, Value value)
{
    if(find(key))
    {
        return false;
    }
    else if(this->el_count == this->arr_size)
    {
        //check may be it can be return false
        throw std::length_error("table is full");
    }
    else 
    {        
        for(int i = this->el_count; i > this->curr; i--)
        {
            this->pRec[i] = this->pRec[i-1]; 
            this->eff++;
        }
        Record rec = {key, value};
        this->pRec[ this-> curr ] = rec;
        this->el_count++;
    }
    
    
    return true;
}

template <typename Key, typename Value>
inline void SortTable<Key, Value>::del(Key key)
{
    if(!find(key))
    {
        for(int i = this->curr; i < this->el_count - 1; i++)
        {
            this->pRec[i] = this->pRec[i+1]; 
            this->eff++;
        }
        this->el_count--;
    }
}
