#if !defined GREEDY_LOCAL_SEARCH_H
#define GREEDY_LOCAL_SEARCH_H

#include "../solution/solution.hpp"
#include "../matrix/matrix.hpp"

class GreedySetCover {
    public :
        static Solution run(Matrix &matrix);
};

#endif // GREEDY_LOCAL_SEARCH_H