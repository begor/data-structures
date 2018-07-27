#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

using prev_valid = std::pair<const Node&, bool>;

bool is_bst(const Node& n, const vector<Node>& tree, long long low, long long hi) {
  if (n.left != -1) {
    if (!is_bst(tree.at(n.left), tree, low, n.key)) {
      return false;
    }
  }

  if (n.key <= low || n.key >= hi) {
    return false;
  }

  if (n.right != -1) {
    if (!is_bst(tree.at(n.right), tree, n.key, hi)) {
      return false;
    }
  }
  return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty()) {
    return true;
  }

  return is_bst(tree.at(0), tree, -1000000000000000, 1000000000000000);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
 