#include <iostream>

#include "BinomialHeap.h"

int main() {
  int n;
  int q;
  std::cin >> n >> q;

  auto heap = BinomialHeap(n);

  while (q-- > 0) {
    int command;
    std::cin >> command;
    if (command == 0) {
      int a;
      int x;
      std::cin >> a >> x;
      heap.Insert(a, x);
    } else if (command == 1) {
      int a;
      int b;
      std::cin >> a >> b;
      heap.Move(a, b);
    } else if (command == 2) {
      int i;
      std::cin >> i;
      heap.DeleteElement(i);
    } else if (command == 3) {
      int i;
      int x;
      std::cin >> i >> x;
      heap.UpdateElement(i, x);
    } else if (command == 4) {
      int a;
      std::cin >> a;
      std::cout << heap.GetMin(a) << "\n";
    } else if (command == 5) {
      int a;
      std::cin >> a;
      heap.ExtractMin(a);
    }
  }
}
