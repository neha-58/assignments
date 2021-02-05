#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <cstddef>
using namespace std;

typedef int E;
class Node {
public:
  E element;  // Value for this
  Node *next; // Pointer to next  in list
  // Constructors
  Node(const E &elemval, Node *nextval = NULL) {
    element = elemval;
    next = nextval;
  }
  Node(Node *nextval = NULL) { next = nextval; }
};

#endif // NODE_H_INCLUDED
