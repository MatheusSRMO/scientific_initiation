#include "move.hpp"



Move::Move(): index(-1), from(false), to(false) {

}

Move::Move(int index, bool from, bool to) : index(index), from(from), to(to) {
}

void Move::print() {
    std::cout << "Index: " << this->index << "\tFrom: " << this->from << "\tTo: " << this->to << std::endl;
}

bool Move::operator==(const Move &m) const {
    return this->index == m.index && this->from == m.from && this->to == m.to;
}

bool Move::operator!=(const Move &m) const {
    return !(*this == m);
}
