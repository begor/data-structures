#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

using bucket = vector<string>;
using hash_table = vector<bucket>;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;

    hash_table table;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {
        table.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            bucket& b = table.at(query.ind);
            
            if (b.empty()) {
                std::cout << " ";
            } else {
                for (int i = static_cast<int>(b.size()) - 1; i >= 0; --i) {
                    std::cout << b[i] << " ";
                }
            }
            
            std::cout << "\n";
        } else {
            auto hash = hash_func(query.s);
            bucket& b = table.at(hash);

            vector<string>::iterator it = std::find(b.begin(), b.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != b.end());
            else if (query.type == "add") {
                if (it == b.end())
                    b.push_back(query.s);
            } else if (query.type == "del") {
                if (it != b.end())
                    b.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
