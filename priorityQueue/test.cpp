#include "IRQueue.h"

int main()
{
  IRQueue q;
  cout << "Input restricted Queue\n";

  cout << "Inserted: 100\n";
  q.insert(100);
  cout << "Inserted: 15\n";
  q.insert(15);
  cout << "Inserted: -27\n";
  q.insert(-27);
  cout << "Inserted: 445\n";
  q.insert(445);

  q.display();

  cout << "Removed " << q.removeFront() << " from front\n";
  cout << "Removed " << q.removeBack() << " from back\n";

/*   ORQueue q;
  cout << "Output restricted Queue\n";
  
  q.display();
 */
}

