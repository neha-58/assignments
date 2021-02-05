#ifndef OR_QUEUE_H_INCLUDED
#define OR_QUEUE_H_INCLUDED

#include <iostream>
using namespace std;
#include "LList.h"
typedef int E;

class ORQueue : private LinkedList {
public:
  ORQueue(int size = 0);
  ~ORQueue(){};
  bool empty();
  E &front();
  E &back();
  int size();
  void insertFront(const E &thisElement);
  void insertBack(const E &thisElement);
  E remove();
  void display();
  void clearAll();
};

ORQueue::ORQueue(int size) : LinkedList(0) { cout << "Queue is created" << endl; }

bool ORQueue::empty() { return ((LinkedList::length() == 0) ? true : false); }

E &ORQueue::front() {
  LinkedList::moveToStart();
  return LinkedList::getValue();
}

E &ORQueue::back() {
  LinkedList::moveToEnd();
  return LinkedList::getValue();
}

int ORQueue::size() { return LinkedList::length(); }

void ORQueue::insertFront(const E &thisElement) { // insertLeft ??
  LinkedList::moveToStart();
  LinkedList::insert(thisElement);
}

void ORQueue::insertBack(const E &thisElement) {
  LinkedList::append(thisElement);
}

E ORQueue::remove() {
  LinkedList::moveToStart();
  return LinkedList::remove();
}

void ORQueue::display() {

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

void ORQueue::clearAll() { LinkedList::clear(); }

#endif // IR_QUEUE_H_INCLUDED
