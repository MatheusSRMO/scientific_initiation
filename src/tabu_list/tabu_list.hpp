#ifndef TABU_LIST_H
#define TABU_LIST_H

#include <vector>
#include "../solution/solution.hpp"
#include "../move/move.hpp"

class TabuList {
    vector<Move> tabu_list;
    int max_size;

    public:
        TabuList();
        TabuList(int max_size);
        ~TabuList();
        void add(Move &s);
        bool contains(Move &s);
        void print();
        int size();
};

#endif // TABU_LIST_H