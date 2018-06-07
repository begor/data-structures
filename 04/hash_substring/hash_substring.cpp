#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using ull = unsigned long long;

const int x = 263;
const ull prime = 100000000007;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

ull hash_func(const string& t, int s, int f) {
    ull hash = 0;

    std::cout << s << std::endl;

    for (int i = f; i >= s; --i) {
        std::cout << t[i];
        hash = (hash * x + t[i]) % prime;
    }

    std::cout << std::endl;
    
    return hash;
}


void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

vector<ull> compute_hashes(const string& t, const string& p) {
    int len = t.size() - p.size() + 1;
    vector<ull> hashes;
    hashes.resize(len);

    auto hi = t.size() - p.size();
    hashes[hi] = hash_func(t, hi, t.size() - 1);

    ull y = 1;

    for (int i = 1; i <= p.size(); ++i) {
        y = (y * x) % prime;
    }

    for (int i = hi - 1; i >= 0; --i) {
        std::cout << t[i] << "..." << t[i + p.size()] << std::endl;
        hashes[i] = (x * hashes[i + 1] + t[i] - y * t[i + p.size()]) % prime;
    }


    return hashes;
} 

std::vector<int> get_occurrences(const Data& input) {
    const string& p = input.pattern, t = input.text;
    vector<ull> hashes = compute_hashes(t, p);
    ull phash = hash_func(p, 0, p.size() - 1);

    std::cout << "Phash: " << phash << std::endl;

    std::vector<int> ans;
    for (size_t i = 0; i + p.size() <= t.size(); ++i) {
        ull hash = hashes[i];

        std::cout << i << " hash: " << hash << std::endl;

        if (hash == phash) {
            if (t.compare(i, p.size(), p) == 0) {
                ans.push_back(i);
            }
        }   
    }
    
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
