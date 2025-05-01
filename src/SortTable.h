#pragma once
#include "ScanTable.h"
#include <exception>

template<typename Key, typename Value>
class SortTable : public ScanTable<Key, Value>
{
private:
    typedef typename Table<Key, Value>::Record Record;
//i forget for what we write this methods (may be to cast unsotred table to sort)
    void sort(int nlogn = 0);
    void select_sort(); 
    void quick_sort(int start, int finish); 
    void merge_sort(int start, int finish); 
    void merge(int, int, int, int); 
public:
    SortTable(int _size = 10);
    SortTable(const SortTable& table);
    SortTable(const ScanTable<Key, Value>& table);

    SortTable<Key, Value>& operator= (const SortTable<Key, Value>& table);

    virtual bool find(Key key);
    virtual bool insert(Key key, Value value);
    virtual void del(Key key);
};

template <typename Key, typename Value>
inline void SortTable<Key, Value>::sort(int k)
{
    std::cout<< "in sort\n";
    switch (k)
    {
    case 0:
        select_sort();
        break;
    case 1:
        quick_sort(0, this->el_count-1);
        break;
    case 2:
        merge_sort(0, this->el_count-1);
        break;
    default:
        throw std::invalid_argument("not a number of sort");
        break;
    }
}

template <typename Key, typename Value>
inline void SortTable<Key, Value>::select_sort()
{ 
    for(int i = 0; i < this->el_count-1; i++)
    {
        Record m = this->pRec[i];
        for(int j = i+1; j < this->el_count; j++)
        {
            if(m.key > this->pRec[j].key)
            {
                m = this->pRec[j];
                this->pRec[j] = this->pRec[i];   
            }
        }
        this->pRec[i] = m;
    }
}

template <typename Key, typename Value>
inline void SortTable<Key, Value>::quick_sort(int start, int finish)
{
    int k = (start + finish) / 2;
    int left = start; 
    int right = finish;
    Record partion = this->pRec[k];
    while(left < right)
    {
        while(this->pRec[left].key  < partion.key)
            left ++;
        while(this->pRec[right].key > partion.key)
            right--;
        if(left <= right)
        {
            Record tmp = this->pRec[left];
            this->pRec[left] = this->pRec[right];
            this->pRec[right] = tmp;
            left++; 
            right--;
        }
    }
    if(start < left)
    {
        if((start+finish) & 1) 
        {
            quick_sort(start, right);
            quick_sort(left, finish);
        }
        else
        {
            quick_sort(start, right+1);
            quick_sort(left, finish);
        }
        
    } 
}

template <typename Key, typename Value>
inline void SortTable<Key, Value>::merge_sort(int start, int finish)
{
    int size = finish - start;
    int k = size / 2;
    std::cout<< start << finish << size << k << std::endl;
    if(size < 1)
    {
        return;
    }

    merge_sort(start, start+k);
    merge_sort(start+k+1, finish);
    merge(start, start+ k, start + k + 1, finish);
}

template <typename Key, typename Value>
inline void SortTable<Key, Value>::merge(int s_a, int f_a, int s_b, int f_b)
{
    int i = s_a, j = s_b, k = 0;
    int size = (f_a - s_a) + (f_b - s_b) + 2;
    std::cout << size << std::endl;
    Record* tmp = new Record[size];
    while(i <= f_a && j <= f_b)
    {
        std::cout<< "merge :" << s_a << "i:" << i << "j:" << j << std::endl;
        if(this->pRec[i].key <= this->pRec[j].key)
        {
            tmp[k] = this->pRec[i];
            i++;
        }
        else
        {
            tmp[k] = this->pRec[j];
            j++;
        }
        k++;
    }

    for( ; i <= f_a; i++)
    {
        tmp[k] = this->pRec[i];
        k++;
    }

    for( ; j <= f_b; j++)
    {
        tmp[k] = this->pRec[j];
        k++;
    }

    for(k = 0; k < size; k++)
    {
        std::cout<< "merge :" << s_a << "iter:" << k << std::endl;
        this->pRec[s_a + k] = tmp[k];
    }
    for(int k =0; k < size; k++)
    {
        std::cout << this->pRec[s_a + k].key << ' ';
    }
    std::cout<< std::endl;
}

//********************************

template <typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(int _size) : ScanTable<Key, Value>(_size) {}

template <typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(const SortTable& table) : ScanTable<Key, Value>(table) {
}

template<typename Key, typename Value>
inline SortTable<Key, Value>::SortTable(const ScanTable<Key, Value>& table): ScanTable<Key, Value>(table) {
    sort(1);
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
    if(find(key))
    {
        for(int i = this->curr; i < this->el_count - 1; i++)
        {
            this->pRec[i] = this->pRec[i+1]; 
            this->eff++;
        }
        this->el_count--;
    }
}

template <typename Key, typename Value>
inline SortTable<Key, Value> &SortTable<Key, Value>::operator=(const SortTable<Key, Value> &table)
{
    ArrayTable<Key, Value>::operator=(table);
    return *this;
}
