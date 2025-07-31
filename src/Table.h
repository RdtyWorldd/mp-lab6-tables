#pragma once
#include <iostream>

//abstact class for tables

template<typename Key, typename Value>
class Table
{
protected:
    //структура записей 
    struct Record
    {
        Key key;
        Value val;
    };
    
    int el_count; //счетчик элементов внутри таблицы
    int eff; //счетчик эффективности (выполненных атомарных операций)
public:
    Table();
    virtual ~Table();

    //гетттеры 
    int get_el_count();
    int get_eff();
    
    //методы проверки состояния таблицы 
    bool is_empty();
    virtual bool is_full()=0; 

    //методы основного интерфейса таблицы
    virtual bool find(Key key) =0;
    virtual bool insert(Key key, Value val) =0;
    virtual void del(Key key) =0;

    //методы интерфейса итерирования 
    virtual void reset() =0;
    virtual void go_next() =0;
    virtual bool is_end() =0;
    virtual Key get_curr_key() = 0;
    virtual Value get_curr_val() = 0;

    //вывод таблиц
    virtual void serialize(std::ostream& os) =0;
    friend std::ostream& operator<<(std::ostream& os, Table& t)
    {
      t.serialize(os);
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

template <typename Key, typename Value>
inline Table<Key, Value>::~Table()
{
}
