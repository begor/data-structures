#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

const int MAX_NUMBER = 10000000;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    vector<string> phone_book(MAX_NUMBER);

    for (const auto& q : queries) {
        if (q.type == "add") {
            phone_book[q.number] = q.name;
        } else if (q.type == "del") {
            phone_book[q.number] = "";
        } else {
            string maybe_name = phone_book[q.number];
            if (maybe_name.empty()) {
                maybe_name = "not found";
            }
            result.push_back(maybe_name);
        }
    }
    
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
