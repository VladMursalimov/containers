#include <list>

#include "list.h"

int main() {
  List<int> list1 = {2, 4, 6};
  List<int> list2 = {1, 3, 5};
  list1.merge(list2);
  list1.printList();
  std::list<int> oflist1 = {2, 4, 6};
  std::list<int> oflist2 = {1, 3, 5};
  oflist1.merge(oflist2);
  for (auto i : oflist1) {
    std::cout << i;
  }

  return 0;
}
