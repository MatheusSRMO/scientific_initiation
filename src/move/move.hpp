#ifndef MOVE_HPP
#define MOVE_HPP

#include <iostream>

class Move {
    private:
        int index;
        bool from;
        bool to;
    public:
        Move();
        Move(int index, bool from, bool to);
        void print();
        bool operator==(const Move &m) const;
        bool operator!=(const Move &m) const;
};

#endif