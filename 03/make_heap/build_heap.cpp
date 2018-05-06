#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector<pair<int, int>> swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int Parent(int child) {
    return (int)((child - 1) / 2);
  }

  int LeftChild(int parent) {
    return 2 * parent + 1;
  }

  int RightChild(int parent) {
    return 2 * parent + 2;
  }

  void SiftDown(int i) {
    int min_index = i;

    int lchild = LeftChild(i);
    bool in_bound = lchild >= 0 && lchild < data_.size();
    bool should_swap = data_[lchild] < data_[min_index];

    if (in_bound && should_swap) {
      min_index = lchild;
    }

    int rchild = RightChild(i);
    in_bound = rchild >= 0 && rchild < data_.size();
    should_swap = data_[rchild] < data_[min_index];

    if (in_bound && should_swap) {
      min_index = rchild;
    }

    if (i != min_index) {
      swap(data_[i], data_[min_index]);
      swaps_.push_back(make_pair(i, min_index));
      SiftDown(min_index);
    }

  }

  void BuildHeap() {
    // We should SiftDown every node from n/2 to zero
    // because last n/2 nodes are already in proper place
    // since there are no edges coming from them
    
    auto size = data_.size();

    for (auto i = (int)(size / 2); i >= 0; i--) {
      SiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    BuildHeap();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
