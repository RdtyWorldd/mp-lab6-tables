#pragma once
#include "Table.h"

template<typename Key, typename Value>
class HashTable : public Table<Key, Value>
{
protected:
    int size;
    virtual int hash_fuction(Key key)
    {
      return key % size;
    }
public:
    HashTable(int size): size(_size){}

    void serialize(std::ostream& os) 
    {
      for (this->reset(); !this->is_end(); this->go_next())
      {
        os << this->get_curr_key() << " " << this->get_curr_val() << std::endl;
      }
    }
};

template <typename Key, typename Value>
inline int HashTable<Key, Value>::hash_fuction(Key key)
{
    int res = 0;
    // char* p = (char*) &key;
    // for(int i = 0 ; i < sizeof(Key); i++)
    // {
    //     res = res + (*p);
    //     ++p;
    // }
    res = key % size;
    //std::cout << res << std::endl;
    return res;
}

template <typename Key, typename Value>
inline HashTable<Key, Value>::HashTable(int _size): size(_size){}
