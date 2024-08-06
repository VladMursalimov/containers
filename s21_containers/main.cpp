#include "queue/queue.h"
#include "list/list.h"

int main() {
  s21::Queue<int> q = {1,3,4};
  while (!q.empty()) {
    std::cout << q.front() << " ";
    q.pop();
  }
  return 0;
}