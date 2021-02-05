#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

class List { // List ADT

    public:
      List() {}                                     // Default constructor
      virtual ~List() {}                            // Base destructor
      virtual void clear() = 0;                     // Clear contents from the list, to make it empty.
      virtual void insert(const E& item) = 0;       // Insert an element at the current location.
      virtual void append(const E& item) = 0;       // Append an element at the end of the list.
      virtual E remove() = 0;                       // Remove and return the current element.
      virtual void moveToStart() = 0;               // Set the current position to the start of the list
      virtual void moveToEnd() = 0;                 // Set the current position to the end of the list
      virtual void prev() = 0;                      // Move the current position one step left. No change if already at beginning.
      virtual void next() = 0;                      // Move the current position one step right. No change if already at end.
      virtual int length() const = 0;               // Return: The number of elements in the list.
      virtual int currPos() const = 0;              // Return: The position of the current element.
      virtual void moveToPos(int pos) = 0;          // Set current position.
      virtual const E& getValue() const = 0;        // Return: The current element.
    };

#endif // LINKEDLIST_H_INCLUDED
