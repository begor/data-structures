#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

// In id we will store identifier of of a table, or a symlink
struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
        size(size), parent(parent), rank(rank) {}
};

using set = DisjointSetsElement;

struct DisjointSets {
    int size;
    int max_table_size;
    vector<set> sets;
    
    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++) {
            sets[i].parent = i;
        }
    }

    int getParent(int table) {
        set& element = sets[table];

        if (element.parent != table) {
            int root = getParent(element.parent);
            element.parent = root;
        }

        return element.parent;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        
        if (realDestination != realSource) {
            set& dest_node = sets[realDestination];
            set& source_node = sets[realSource];

            if (dest_node.rank > source_node.rank) {
                source_node.parent = realDestination;
                dest_node.size += source_node.size;
                source_node.size = 0;

                max_table_size = max(max_table_size, dest_node.size);
            } else if (dest_node.rank == source_node.rank) {
                source_node.parent = realDestination;
                dest_node.size += source_node.size;
                source_node.size = 0;
                
                dest_node.rank++;

                max_table_size = max(max_table_size, dest_node.size);
            } else { 
                // Destination should be merged into Source
                dest_node.parent = realSource;
                source_node.size += dest_node.size;
                dest_node.size = 0;

                max_table_size = max(max_table_size, source_node.size);
            }
        }       
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
                --destination;
                --source;
        
        tables.merge(destination, source);
        cout << tables.max_table_size << endl;
    }

    return 0;
}
