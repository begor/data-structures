#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using std::vector;
using std::pair;
using std::priority_queue; // TODO: maybe implement own priority_queue?
using std::cin;
using std::cout;


// Each Worker represented as a pair of {available_time, index}, where:
// available_time - a second when worker is done with its job (at start its 0)
// index - just a given number.
// That allows to store them effectively in priority_queue
// with std::greated applied to pairs of numbers.
using worker = pair<long long, int>;


class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // Using a min queue with custom comparator.
    priority_queue<worker, std::vector<worker>, std::greater<worker>> q;
 
    for(int i = 0; i < num_workers_; ++i) {
      worker w = {0, i};
      q.push(w);
    }

    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    for (int i = 0; i < jobs_.size(); ++i) {
      long long duration = jobs_[i];

      worker w = q.top();
      q.pop();

      start_times_[i] = w.first;
      assigned_workers_[i] = w.second;

      worker new_w = {w.first + duration, w.second};
      q.push(new_w);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
