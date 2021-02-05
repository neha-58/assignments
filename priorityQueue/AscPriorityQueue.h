#ifndef ASC_PRIORITY_QUEUE_H_INCLUDED
#define ASC_PRIORITY_QUEUE_H_INCLUDED

using namespace std;
#include "LList.h"
#include "Queue.h"
#include <iostream>

class AscPriorityQueue : public LinkedList {
public:
  AscPriorityQueue(int size = 0);
  ~AscPriorityQueue() {}
  int size();
  bool empty();
  void insert(const E &thisElement);
  E remove();
  void display();
  void clearAll();
};

AscPriorityQueue::AscPriorityQueue(int size) : LinkedList(0) {
  cout << "Ascending Priority Queue is created" << endl;
};

void AscPriorityQueue::insert(const E &thisElement) {
  LinkedList::append(thisElement);
}

E AscPriorityQueue::remove() {
  LinkedList::moveToStart();
  E smallest = LinkedList::getValue();
  int pos = LinkedList::currPos();
  for (int i = 0; i < LinkedList::length() - 1; ++i) {
    LinkedList::next();
    if (LinkedList::getValue() < smallest) {
      smallest = LinkedList::getValue();
      pos = currPos();
    }
  }
  LinkedList::moveToPos(pos);
  return LinkedList::remove();
}

int AscPriorityQueue::size() { return LinkedList::length(); }

bool AscPriorityQueue::empty() { return ((LinkedList::length() == 0) ? true : false); }

void AscPriorityQueue::display() {
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

void AscPriorityQueue::clearAll() { LinkedList::clear(); }

#endif