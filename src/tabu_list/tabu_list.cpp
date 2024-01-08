#include "tabu_list.hpp"

using namespace std;

TabuList::TabuList() {
    this->max_size = 0;
    this->tabu_list = vector<Solution>();
}

TabuList::TabuList(int max_size) {
    this->max_size = max_size;
    this->tabu_list = vector<Solution>(max_size);
}

TabuList::~TabuList() {
    // nothing to do, vector is automatically destroyed
}

// Complexity: O(1)
void TabuList::add(Solution &s) {
    this->tabu_list.push_back(s);
    if ((int)this->tabu_list.size() > this->max_size) {
        this->tabu_list.erase(this->tabu_list.begin()); // remove first element and shift the rest
    }
}

// Complexity: O(n), where n is the number of elements
bool TabuList::contains(Solution &s) {
    for (int i = 0; i < (int)this->tabu_list.size(); i++)
        if (this->tabu_list[i] == s)
            return true;
    return false;
}

// Complexity: O(n), where n is the number of elements
void TabuList::print() {
    cout << "Tabu list: ";
    for (int i = 0; i < (int)this->tabu_list.size(); i++) {
        this->tabu_list[i].print();
        cout << " ";
    }
    cout << endl;
}

// Complexity: O(1)
int TabuList::size() {
    return (int)this->tabu_list.size();
}
