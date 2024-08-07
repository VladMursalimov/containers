#include <stack>
#include <vector>

#include "list/list.h"
#include "queue/queue.h"
#include "stack/stack.h"
#include "vector/vector.h"

int main() {
  s21::Vector<int> v = {1,2,3};
  s21::VectorIterator<int> it = v.end();
  it = v.insert(it, 5);
  v.print_vector();

  v.erase(it);
  v.push_back(878);
  v.pop_back();
  v.print_vector();

  // std::vector<int> container{1, 2, 3};
  // auto iter = container.end();
  // container.insert(iter, 5);
  // for (const auto& value : container)
  //   std::cout << value << ' ';
  return 0;
}