#ifndef LLIST_H_INCLUDED
#define LLIST_H_INCLUDED

#include "ListADT.h"
#include "Node.h"

class LinkedList: public List {
    private:
      Node* head;                                         // Pointer to list header
      Node* tail;                                        // Pointer to last element
      Node* curr;                                        // Access to current element
      int cnt;    	                                        // Size of list

      void init() {                                         // Intialization helper method
        curr = tail = head = new Node();
        cnt = 0;
      }

      void removeall() {                                    // Return Node s to free store
        while(head != NULL) {
          curr = head;
          head = head->next;
          delete curr;
        }
      }

    public:
      LinkedList(int size=0) { init(); }               // Constructor
      ~LinkedList() { removeall(); }                             // Destructor
      void print() const;                                   // Print list contents
      void clear() { removeall(); init(); }                 // Clear list


      void insert(const E& it) {                             // Insert "it" at current position
        curr->next = new Node(it, curr->next);
        if (tail == curr) tail = curr->next;  // New tail
        cnt++;
      }

      void append(const E& it) {                                // Append "it" to list
        tail = tail->next = new Node(it, NULL);
        cnt++;
      }


      E remove() {                                              // Remove and return current element

        E it = curr->next->element;                             // Remember value
        Node* ltemp = curr->next;                            // Remember Node
        if (tail == curr->next) tail = curr;                    // Reset tail
        curr->next = curr->next->next;                          // Remove from list
        delete ltemp;                                           // Reclaim space
        cnt--;			                                         // Decrement the count
        return it;
      }

      void moveToStart()                                        // Place curr at list start
        { curr = head; }

      void moveToEnd()                                          // Place curr at list end
        { curr = tail; }


      void prev() {                                             // Move curr one step left; no change if already at front
        if (curr == head) return;                               // No previous element
        Node* temp = head;
                                                                // March down list until we find the previous element
        while (temp->next!=curr) temp=temp->next;
        curr = temp;
      }


      void next()                                               // Move curr one step right; no change if already at end
        { if (curr != tail) curr = curr->next; }

      int length() const  { return cnt; } // Return length


      int currPos() const {                                     // Return the position of the current element
        Node* temp = head;
        int i;
        for (i=0; curr != temp; i++)
          temp = temp->next;
        return i;
      }


      void moveToPos(int pos) {                                     // Move down list to "pos" position

        curr = head;
        for(int i=0; i<pos; i++) curr = curr->next;
      }

      E& getValue() const {                                   // Return current element

        return curr->next->element;
      }
    };


#endif // LLIST_H_INCLUDED
