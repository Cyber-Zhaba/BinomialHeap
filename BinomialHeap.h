#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

const int cIntMin = std::numeric_limits<int>::min();

class BinomialHeap {
  struct Tree {
    int data;
    int degree;
    size_t id;
    Tree* parent;
    Tree* child;
    Tree* sibling;

    explicit Tree(int data, size_t id)
        : data(data),
          degree(0),
          id(id),
          parent(nullptr),
          child(nullptr),
          sibling(nullptr) {}

    bool operator<(const Tree& other) const {
      if (data != other.data) {
        return data < other.data;
      }
      return id < other.id;
    }

    bool operator>(const Tree& other) const { return other < *this; }
  };

  std::vector<std::vector<Tree*>> roots_;
  std::vector<Tree*> elements_;

  Tree* Merge(Tree* tree1, Tree* tree2);
  std::vector<Tree*> Union(std::vector<Tree*>& heap1,
                           std::vector<Tree*>& heap2);
  void SiftUp(Tree* node);
  void SiftDown(Tree* node);

 public:
  explicit BinomialHeap(int n) : roots_(n + 1), elements_(1) {}

  ~BinomialHeap() {
    for (auto* node : elements_) {
      delete node;
    }
  }

  void Insert(int key, int x);
  void Move(int key1, int key2);
  void ExtractMin(size_t key);
  void DeleteElement(int id);
  void UpdateElement(int id, int new_value);
  int GetMin(int key);
};

BinomialHeap::Tree* BinomialHeap::Merge(Tree* tree1, Tree* tree2) {
  if (*tree1 > *tree2) {
    std::swap(tree1, tree2);
  }
  tree2->parent = tree1;
  tree2->sibling = tree1->child;
  tree1->child = tree2;
  tree1->degree++;
  elements_[tree2->id] = tree1->child;
  return tree1;
}

std::vector<BinomialHeap::Tree*> BinomialHeap::Union(
    std::vector<Tree*>& heap1, std::vector<Tree*>& heap2) {
  std::vector<Tree*> new_heap;
  Tree* carry = nullptr;
  size_t max_size = std::max(heap1.size(), heap2.size());

  for (size_t i = 0; i < max_size; i++) {
    auto* tree1 = i < heap1.size() ? heap1[i] : nullptr;
    auto* tree2 = i < heap2.size() ? heap2[i] : nullptr;

    if (tree2 == nullptr) {
      std::swap(tree2, carry);
    }
    if (tree1 == nullptr) {
      std::swap(tree1, tree2);
      std::swap(tree2, carry);
    }

    if (tree1 != nullptr && tree2 != nullptr) {
      if (*tree1 > *tree2) {
        std::swap(tree1, tree2);
      }
      new_heap.push_back(carry);
      if (carry != nullptr) {
        elements_[carry->id] = carry;
      }
      carry = Merge(tree1, tree2);
    } else {
      new_heap.push_back(tree1);
      if (tree1 != nullptr) {
        elements_[tree1->id] = tree1;
      }
    }
  }
  if (carry != nullptr) {
    new_heap.push_back(carry);
    elements_[carry->id] = carry;
  }
  heap2.clear();
  return new_heap;
}

void BinomialHeap::Insert(int key, int x) {
  auto* tree = new Tree(x, elements_.size());
  elements_.push_back(tree);
  if (roots_[key].empty()) {
    roots_[key] = {tree};
    return;
  }
  std::vector temp_heap{tree};
  roots_[key] = Union(roots_[key], temp_heap);
}

void BinomialHeap::Move(int key1, int key2) {
  roots_[key2] = Union(roots_[key2], roots_[key1]);
}

void BinomialHeap::ExtractMin(size_t key) {
  Tree* min_node = nullptr;
  size_t idx = 0;
  for (size_t i = 0; i < roots_[key].size(); i++) {
    if (roots_[key][i] != nullptr) {
      if (min_node == nullptr || *roots_[key][i] < *min_node) {
        min_node = roots_[key][i];
        idx = i;
      }
    }
  }

  if (min_node == nullptr) {
    return;
  }

  int max_degree = 0;
  for (Tree* child = min_node->child; child != nullptr;
       child = child->sibling) {
    max_degree = std::max(max_degree, child->degree);
  }

  std::vector<Tree*> child_heap(max_degree + 1, nullptr);
  for (Tree* child = min_node->child; child != nullptr;
       child = child->sibling) {
    child->parent = nullptr;
    child_heap[child->degree] = child;
  }

  roots_[key][idx] = nullptr;
  roots_[key] = Union(roots_[key], child_heap);
  elements_[min_node->id] = nullptr;
  delete min_node;
}

void BinomialHeap::SiftUp(BinomialHeap::Tree* node) {
  if (node == nullptr || node->parent == nullptr) {
    return;
  }
  if (*node < *node->parent) {
    std::swap(node->data, node->parent->data);
    std::swap(node->id, node->parent->id);
    std::swap(elements_[node->id], elements_[node->parent->id]);
    SiftUp(node->parent);
  }
}

void BinomialHeap::SiftDown(BinomialHeap::Tree* node) {
  if (node == nullptr || node->child == nullptr) {
    return;
  }
  Tree* min_child = node->child;
  for (Tree* child = node->child->sibling; child != nullptr;
       child = child->sibling) {
    if (*child < *min_child) {
      min_child = child;
    }
  }
  if (*min_child < *node) {
    std::swap(node->data, min_child->data);
    std::swap(node->id, min_child->id);
    std::swap(elements_[node->id], elements_[min_child->id]);
    SiftDown(min_child);
  }
}

void BinomialHeap::DeleteElement(int id) {
  Tree* node = elements_[id];
  if (node == nullptr) {
    return;
  }
  node->data = cIntMin;
  SiftUp(node);
  while (node->parent != nullptr) {
    node = node->parent;
  }
  for (size_t i = 0; i < roots_.size(); i++) {
    size_t degree = node->degree;
    if (roots_[i].size() > degree && roots_[i][node->degree] == node) {
      ExtractMin(i);
      break;
    }
  }
}

int BinomialHeap::GetMin(int key) {
  Tree* ans = nullptr;
  for (Tree* n : roots_[key]) {
    if (n != nullptr && (ans == nullptr || *n < *ans)) {
      ans = n;
    }
  }
  if (ans != nullptr) {
    return ans->data;
  }
  return -1;
}

void BinomialHeap::UpdateElement(int id, int new_value) {
  Tree* node = elements_[id];
  if (node == nullptr) {
    return;
  }
  node->data = new_value;
  SiftUp(node);
  SiftDown(node);
}
