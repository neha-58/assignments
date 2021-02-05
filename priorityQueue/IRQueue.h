#ifndef IR_QUEUE_H_INCLUDED
#define IR_QUEUE_H_INCLUDED

#include <iostream>
using namespace std;
#include "LList.h"
typedef int E;

class IRQueue : private LinkedList {
public:
  IRQueue(int size = 0);
  ~IRQueue(){};
  bool empty();
  E &front();
  E &back();
  int size();
  void insert(const E &thisElement);
  E removeFront();
  E removeBack();
  void display();
  void clearAll();
};

IRQueue::IRQueue(int size) : LinkedList(0) { cout << "\nInput Restricted Queue is created.\n"; }

bool IRQueue::empty() { return ((LinkedList::length() == 0) ? true : false); }

E &IRQueue::front() {
  LinkedList::moveToStart();
  return LinkedList::getValue();
}

E &IRQueue::back() {
  LinkedList::moveToEnd();
  return LinkedList::getValue();
}

int IRQueue::size() { return LinkedList::length(); }

void IRQueue::insert(const E &thisElement) {
  LinkedList::append(thisElement);
}

E IRQueue::removeFront() {
  LinkedList::moveToStart();
  return LinkedList::remove();
}

E IRQueue::removeBack() {
  LinkedList::moveToPos(LinkedList::length() - 1);
  return LinkedList::remove();
}

void IRQueue::display() {

  if (empty())
    cout << "{empty}";
  else {
    cout << "{ ";
    int length = size();
    LinkedList::moveToStart();
    for (int i = 1; i <= length; i++) {
      cout << LinkedList::getValue() << " ";
      LinkedList::next();
    }
    cout << '}';
  }
}

void IRQueue::clearAll() { LinkedList::clear(); }

#endif // DEQUE_H_INCLUDED
