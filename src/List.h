#pragma once

#include <iostream>
#include <initializer_list>
#include "Iterator.h"

template <typename T>
struct Node
{
  T val;
  Node<T>* pNext;
};

template <typename T>
class List
{
protected:
  Node<T>* pFirst;
  Node<T>* pLast;

  Node<T>* pCurr, *pPrev;
  size_t size;
public:
  typedef ListIterator<T> iterator;
  typedef ListIterator<const T> const_iterator;

  List();
  List(const List<T>& list);
  List(std::initializer_list<T> l);
  List<T>& operator= (const List<T>& list);
  ~List();
  
  void pushBack(T val);
  void pushFront(T val);
  void removeFirst(); //нужен тест
  void removeLast(); // нужен тест

  void add(int id, T val);
  T& get(int id);
  void remove(int id);
  T& operator[](int id);
  void clear();

  bool isEmpty() const;
  size_t getSize() const;

  void Reset();
  void GoNext();
  bool IsEnd();

  //перед pCurr, двигает pPrev

  T getCurr();
  void insertCurr(T val); //нужен тест
  void removeCurr(); // нужен тест

  iterator begin() { return iterator(pFirst); }
  iterator end() { return iterator(nullptr); }

  const_iterator begin() const { return const_iterator(pFirst); }
  const_iterator end() const { return const_iterator(nullptr); }

  bool operator== (const List<T>& list) const;
  bool operator!= (const List<T>& list) const;

  friend std::ostream& operator<< (std::ostream& out, const List<T>& list)
  {
	  Node<T>* tmp = list.pFirst;
    while(tmp != nullptr)
    {
      out << tmp->val << " ";
    }
    out << std::endl;
    return out;
  }

  friend std::istream& operator>> (std::istream& in, const List<T>& list)
  {
	  return in;
  }
};

template<typename T>
inline List<T>::List()
{
  pFirst = pLast = nullptr;
  pCurr = nullptr;
  pPrev = nullptr;
  size = 0;
}

template<typename T>
inline List<T>::List(std::initializer_list<T> list)
{
  if (list.size() == 0)
  {
    pFirst = pLast = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    size = 0;
    return;
  }
  size = list.size();
  auto lp = list.begin();
  pFirst = new Node<T>{ *lp, nullptr };
  lp++;
  if (size == 1)
  {
    pLast = pFirst;
    return;
  }

  Node<T>* prev = pFirst;
  Node<T>* now;
  for (int i = 1; i < list.size(); i++, lp++)
  {
    now = new Node<T>{ *lp, nullptr };
    prev->pNext = now;
    prev = prev->pNext;
  }
  pLast = now;
}

template<typename T>
inline List<T>::List(const List<T>& list)
{
  pCurr = pPrev = nullptr;
  size = list.size;
  if (list.pFirst == nullptr) {
	pFirst = nullptr;
	pLast = nullptr;
	return;
  }

  Node<T>* tmp = list.pFirst;
  pFirst = new Node<T>{ tmp->val, nullptr };
  Node<T>* previous = pFirst;

  tmp = tmp->pNext;
  while (tmp != nullptr) {
	Node<T>* node = new Node<T>{ tmp->val, nullptr };
	previous->pNext = node;

	previous = node; //previous = previous -> pNext;
	tmp = tmp->pNext;
  }
  pLast = previous;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& list)
{
  if (this != &list)
  {
	clear();

	size = list.size;
	if (list.pFirst == nullptr) {
	  pFirst = nullptr;
	  pLast = nullptr;
	  return *this;
	}

	Node<T>* tmp = list.pFirst;
	pFirst = new Node<T>{ tmp->val, nullptr };
	Node<T>* previous = pFirst;

	tmp = tmp->pNext;
	while (tmp != nullptr) {
	  Node<T>* node = new Node<T>{ tmp->val, nullptr };
	  previous->pNext = node;

	  previous = node; //previous = previous -> pNext;
	  tmp = tmp->pNext;
	}
	pLast = previous;
  }
  return *this;
}

template<typename T>
inline List<T>::~List()
{
  clear();
  delete pFirst;
  delete pLast;
}

template<typename T>
inline void List<T>::pushBack(T val)
{
  Node<T>* tmp = new Node<T>{ val, nullptr };
  if (pFirst == nullptr)
  {
	pFirst = pLast = tmp;
  }
  else
  {
	pLast->pNext = tmp;
	pLast = pLast->pNext;
  }
  size++;
}

template<typename T>
inline void List<T>::pushFront(T val)
{
  Node<T>* tmp = new Node<T>{ val, pFirst };
  pFirst = tmp;
  if (pLast == nullptr)
	pLast = pFirst;

  size++;
}

template <typename T>
inline void List<T>::removeFirst()
{
  if(pFirst == nullptr)
  {
    throw -1; //std::exception("list is empty");
  }

  if(pFirst == pLast)
  {
    delete pFirst;
    pFirst = nullptr;
    pLast = nullptr;
  }
  else 
  {
    Node<T>* tmp = pFirst;
    pFirst = pFirst->pNext;
    delete tmp;
  }
  size--;
}

template <typename T>
inline void List<T>::removeLast()
{
  if(pLast == nullptr)
  {
    throw -1; //std::exception("list is empy");
  }
    
  if(pFirst == pLast)
  {
    delete pFirst;
    pFirst = nullptr;
    pLast = nullptr;
  }
  else
  {
    Node<T>* tmp = pFirst;
    while(tmp->pNext != pLast)
    {
      tmp = tmp->pNext;
    }
    tmp->pNext = nullptr;
    delete pLast;
    pLast = tmp;
  }
  size--;
}

template<typename T>
inline void List<T>::add(int id, T val)
{
  if (id < 0 || id > size)
	  throw -1; //std::exception("index is out of range");
  if (id == 0) {
	  pushFront(val);
	  return;
  }
  if (id == size) {
	  pushBack(val);
	  return;
  }

  Node<T>* p = pFirst;
  for (int i = 0; i < id - 1; i++)
	p = p->pNext;

  Node<T>* tmp = new Node<T>{ val, p->pNext };
  p->pNext = tmp;

  size++;
}

template<typename T>
inline T& List<T>::get(int id)
{
  if (id < 0 || id >= size)
	throw -1; //std::exception("index is out of range");

  Node<T>* p = pFirst;
  for (int i = 0; i < id; i++)
	  p = p->pNext;

  return p->val;
}

template<typename T>
inline void List<T>::remove(int id)
{
  if (id < 0 || id >= size)
	throw -1; //std::exception("index is out of range");

  Node<T>* tmp = pFirst;
  if (id == 0)
  {
	  pFirst = pFirst->pNext;
  }
  else
  {
    Node<T>* prev = tmp;
    for (int i = 0; i < id; i++)
    {
      prev = tmp;
      tmp = tmp->pNext;
    }
    prev->pNext = tmp->pNext;
    if (id == size - 1)	pLast = prev;
  }
  size--;
  delete tmp;
}

template<typename T>
inline T& List<T>::operator[](int id)
{
  return get(id);
}

template<typename T>
inline void List<T>::clear()
{
  while (pFirst != nullptr)
  {
	Node<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
  }
  pLast = nullptr;
  size = 0;
}

template<typename T>
inline bool List<T>::isEmpty() const
{
  return size == 0;
}

template<typename T>
inline size_t List<T>::getSize() const
{
  return size;
}

template <typename T>
inline T List<T>::getCurr()
{
  return pCurr->val;
}

template <typename T>
inline void List<T>::insertCurr(T val)
{
  if(pCurr == pFirst)
  {
    pushFront(val);
    pPrev = pFirst;
  }
  else if(pPrev == pLast)
  {
    pushBack(val);
    pPrev = pLast;
  }
  else 
  {
    Node<T>* tmp = new Node<T>{val, pCurr};
    pPrev->pNext = tmp;
    pPrev = tmp;
    size++;
  }
}

template <typename T>
inline void List<T>::removeCurr()
{
  if(pCurr == pFirst)
  {
    removeFirst();
    pCurr = pFirst;
    return;
  }

  if (pCurr != nullptr)
  {
    Node<T>* tmp = pCurr;
    pCurr = pCurr->pNext;
    delete tmp;
    pPrev->pNext = pCurr;
    if(pCurr == nullptr)
    {
      pLast = pPrev;
    }
    size --;
  }
}

template <typename T>
inline bool List<T>::operator==(const List<T> &list) const
{
  if (pFirst == list.pFirst)
	return true;

  if (size != list.size)
	return false;

  Node<T>* firstS = pFirst;
  Node<T>* secondS = list.pFirst;

  while (firstS != nullptr && secondS != nullptr)
  {
	if (firstS->val != secondS->val)
	  return false;
	firstS = firstS->pNext;
	secondS = secondS->pNext;
  }
  if (firstS == nullptr && secondS == nullptr)
    return true;

  return false;
}

template<typename T>
inline bool List<T>::operator!=(const List<T>& list) const
{
  return !((*this) == list);
}

template<typename T>
inline void List<T>::Reset()
{
  pCurr = pFirst;
  pPrev = nullptr;
}

template<typename T>
inline void List<T>::GoNext()
{
  pPrev = pCurr;
  pCurr = pCurr->pNext;
}

template<typename T>
inline bool List<T>::IsEnd()
{
  return pLast == pPrev;
}