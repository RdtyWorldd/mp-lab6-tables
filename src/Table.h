#pragma once
#include <iostream>

//abstact class for tables

template<typename Key, typename Value>
class Table
{
protected:
    struct Record
    {
        Key key;
        Value val;
    };

    int el_count;
    int eff;
public:
    Table();
    virtual Table& operator= (const Table&) =0;
    virtual ~Table() =0;

    int get_el_count();
    int get_eff();
    bool is_empty();
    virtual bool is_full()=0;

    virtual bool find(Key key) =0;
    virtual bool insert(Key key, Value val) =0;
    virtual void del(Key key) =0;

    virtual void reset() =0;
    virtual void go_next() =0;
    virtual bool is_end() =0;

    virtual Key get_curr_key() = 0;
    virtual Value get_cuur_val() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Table& t)
    {
      for (t.reset(); !t.is_end(); t.go_next())
      {
        os << t.GetCurr() << std::endl;
      }
      return os;
    }
};

template <typename Key, typename Value>
inline Table<Key, Value>::Table()
{
    el_count = 0;
    eff = 0;
}

template <typename Key, typename Value>
inline int Table<Key, Value>::get_el_count()
{
    return el_count;
}

template <typename Key, typename Value>
inline int Table<Key, Value>::get_eff()
{
    return eff;
}

template <typename Key, typename Value>
inline bool Table<Key, Value>::is_empty()
{
    return el_count == 0;
}
