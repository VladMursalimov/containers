#include <list>

#include "list.h"

int main() {
  List<int> list1 = {3,1,1,2, 2, 3};
  list1.sort();
  list1.reverse();
  list1.printList();

  return 0;
}
