#include <list>

#include "list.h"

int main() {
  List<int> list1 = {3,1,1,2, 2, 3};
  std::cout<<list1.front();

  return 0;
}
