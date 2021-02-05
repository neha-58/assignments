#include "IRQueue.h"
#include "ORQueue.h"

int main() {
  E r;
  {
    IRQueue q;

    cout << "\nInitially: ";
    q.display();

    cout << "\n\ninsert(100): ";
    q.insert(100);
    q.display();

    cout << "\n\ninsert(15): ";
    q.insert(15);
    q.display();

    cout << "\n\ninsert(-27): ";
    q.insert(-27);
    q.display();

    r = q.removeFront();
    cout << "\n\nremoveFront(" << r << "): ";
    q.display();
    cout << " -> " << r;

    r = q.removeBack();
    cout << "\n\nremoveBack(" << r << "): ";
    q.display();
    cout << " -> " << r;

    q.clearAll();
    cout << "\n\n";
  }

  {
    ORQueue q;

    cout << "\nInitially: ";
    q.display();

    cout << "\n\ninsertFront(100): ";
    q.insertFront(100);
    q.display();

    cout << "\n\ninsertBack(15): ";
    q.insertBack(15);
    q.display();

    cout << "\n\ninsertFront(-27): ";
    q.insertFront(-27);
    q.display();

    r = q.remove();
    cout << "\n\nremove(" << r << "): ";
    q.display();
    cout << " -> " << r;

    r = q.remove();
    cout << "\n\nremove(" << r << "): ";
    q.display();
    cout << " -> " << r;

    q.clearAll();
    cout << "\n\n";
  }
  /*   ORQueue q;
    cout << "Output restricted Queue\n";

    q.display();
   */
}
