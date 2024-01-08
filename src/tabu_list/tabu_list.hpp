#ifndef TABU_LIST_H
#define TABU_LIST_H

#include <vector>
#include "../solution/solution.hpp"

class TabuList {
    vector<Solution> tabu_list;
    int max_size;

    public:
        TabuList();
        TabuList(int max_size);
        ~TabuList();
        void add(Solution &s);
        bool contains(Solution &s);
        void print();
        int size();
};

#endif // TABU_LIST_H