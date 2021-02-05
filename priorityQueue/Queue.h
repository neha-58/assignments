#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <iostream>
using namespace std;
#include "LList.h"
typedef int E;

class Queue : private LinkedList {
public:
  Queue(int size = 0);
  ~Queue(){};
  bool empty();
  E &front();
  E &back();
  int size();
  void insert(const E &thisElement);
  E remove();
  void display();
  void clearAll();
};

Queue::Queue(int size) : LinkedList(0) { cout << "Queue is created" << endl; }

bool Queue::empty() { return ((LinkedList::length() == 0) ? true : false); }

E &Queue::front() {
  LinkedList::moveToStart();
  return LinkedList::getValue();
}

E &Queue::back() {
  LinkedList::moveToEnd();
  return LinkedList::getValue();
}

int Queue::size() { return LinkedList::length(); }

void Queue::insert(const E &thisElement) { LinkedList::append(thisElement); }

E Queue::remove() {
  LinkedList::moveToStart();
  return LinkedList::remove();
}

void Queue::display() {

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

void Queue::clearAll() { LinkedList::clear(); }

#endif // QUEUE_H_INCLUDED
