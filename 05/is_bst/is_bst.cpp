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

void in_order_recursive(const Node& n, const vector<Node>& tree, vector<int>& result) {
  int left_child = n.left;
  if (left_child != -1) {
    in_order_recursive(tree.at(left_child), tree, result);
  }

  result.push_back(n.key);

  int right_child = n.right;
  if (right_child != -1) {
    in_order_recursive(tree.at(right_child), tree, result);
  }
}

vector<int> in_order(const Node& root, const vector<Node>& tree) {
  vector<int> result;
  in_order_recursive(root, tree, result);
  return result;
}


bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.empty()) {
    return true;
  }
  
  const Node& root = tree.at(0);

  auto in_order_keys = in_order(root, tree);

  return std::is_sorted(in_order_keys.begin(), in_order_keys.end());
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
