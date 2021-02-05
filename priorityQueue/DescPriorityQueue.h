#ifndef DESC_PRIORITY_QUEUE_H_INCLUDED
#define DESC_PRIORITY_QUEUE_H_INCLUDED

using namespace std;
#include "LList.h"
#include "Queue.h"
#include <iostream>

class DescPriorityQueue : public LinkedList {
public:
  DescPriorityQueue(int size = 0);
  ~DescPriorityQueue() {}
  int size();
  bool empty();
  void insert(const E &thisElement);
  E remove();
  void display();
  void clearAll();
};

DescPriorityQueue::DescPriorityQueue(int size) : LinkedList(0) {
  cout << "Descending Priority Queue is created" << endl;
};

void DescPriorityQueue::insert(const E &thisElement) {
  LinkedList::append(thisElement);
}

E DescPriorityQueue::remove() {
  LinkedList::moveToStart();
  E largest = LinkedList::getValue();
  int pos = LinkedList::currPos();
  for (int i = 0; i < LinkedList::length() - 1; ++i) {
    LinkedList::next();
    if (LinkedList::getValue() > largest) {
      largest = LinkedList::getValue();
      pos = currPos();
    }
  }
  LinkedList::moveToPos(pos);
  return LinkedList::remove();
}

int DescPriorityQueue::size() { return LinkedList::length(); }

bool DescPriorityQueue::empty() { return ((LinkedList::length() == 0) ? true : false); }

void DescPriorityQueue::display() {
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

void DescPriorityQueue::clearAll() { LinkedList::clear(); }

#endif