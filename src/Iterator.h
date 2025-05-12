#pragma once
#include <iterator>

template<typename T> class List;
template<typename T> struct Node;

template<typename T>
class ListIterator : public std::iterator<std::input_iterator_tag, T>
{
    friend class List<T>;
    friend struct Node<T>;
 
    Node<T>* pCurr;
    ListIterator(Node<T>* p);
public:
    ListIterator(const ListIterator& iterator);
    bool operator!=(ListIterator const& other) const;
    bool operator==(ListIterator const& other) const; //need for BOOST_FOREACH
    typename ListIterator<T>::reference operator*() const;
    ListIterator<T>& operator++();
};

template<typename T>
inline ListIterator<T>::ListIterator(Node<T>* p) : pCurr(p) {};

template <typename T>
inline ListIterator<T>::ListIterator(const ListIterator &iterator) : pCurr(iterator.pCurr) {}

template <typename T>
inline bool ListIterator<T>::operator!=(ListIterator const &other) const
{
    return pCurr->pNext != other.pCurr->pNext;
}

template <typename T>
inline bool ListIterator<T>::operator==(ListIterator const &other) const
{
    return pCurr->pNext == other.pCurr->pNext;
}

template <typename T>
inline typename ListIterator<T>::reference ListIterator<T>::operator*() const
{
    return pCurr->val;
}

template <typename T>
inline ListIterator<T>& ListIterator<T>::operator++()
{
    pCurr = pCurr->pNext;
    return *this;
}
