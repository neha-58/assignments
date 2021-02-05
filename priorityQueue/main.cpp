#include "AscPriorityQueue.h"
#include <iostream>

using namespace std;

int main() {
  AscPriorityQueue q;
  q.insert(2);
  q.insert(3);
  q.insert(4);
  q.insert(21);
  q.insert(34);
  q.insert(9);
  q.display();

  cout << " Element " << q.remove() << " is removed" << endl;
  cout << " Element " << q.remove() << " is removed" << endl;
  q.display();

  q.clearAll();

  q.display();
  q.insert(6);
  q.insert(211);
  q.insert(334);
  q.insert(90);
  q.display();

  return 0;
}
