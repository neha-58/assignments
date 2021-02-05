#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <iostream>
using namespace std;
#include "LList.h"
typedef int E;

class Deque : private LinkedList {
public:
  Deque(int size = 0);
  ~Deque(){};
  bool empty();
  E &front();
  E &back();
  int size();
  void insertFront(const E &thisElement);
  void insertBack(const E &thisElement);
  E removeFront();
  E removeBack();
  void display();
  void clearAll();
};

Deque::Deque(int size) : LinkedList(0) { cout << "Queue is created" << endl; }

bool Deque::empty() { return ((LinkedList::length() == 0) ? true : false); }

E &Deque::front() {
  LinkedList::moveToStart();
  return LinkedList::getValue();
}

E &Deque::back() {
  LinkedList::moveToEnd();
  return LinkedList::getValue();
}

int Deque::size() { return LinkedList::length(); }

void Deque::insertFront(const E &thisElement) { // insertLeft ??
  LinkedList::moveToStart();
  LinkedList::insert(thisElement);
}

void Deque::insertBack(const E &thisElement) {
  LinkedList::append(thisElement);
}

E Deque::removeFront() {
  LinkedList::moveToStart();
  return LinkedList::remove();
}

E Deque::removeBack() {
  LinkedList::moveToEnd();
  return LinkedList::remove();
}

void Deque::display() {

  if (empty())
    cout << "The queue is empty" << endl;
  else {
    cout << "The elements in the queue are :";
    int length = size();
    LinkedList::moveToStart();
    for (int i = 1; i <= length; i++) {
      cout << LinkedList::getValue() << " ";
      LinkedList::next();
    }
    cout << endl;
  }
}

void Deque::clearAll() { LinkedList::clear(); }

#endif // DEQUE_H_INCLUDED
