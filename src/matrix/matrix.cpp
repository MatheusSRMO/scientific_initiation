#include "matrix.hpp"

using namespace std;

Matrix::Matrix() {
    this->m = 0;
    this->n = 0;
    this->matrix = vector<vector<bool>>();
    this->transpose = vector<vector<bool>>();
}

Matrix::Matrix(int m, int n) {
    this->m = m;
    this->n = n;
    this->matrix = vector<vector<bool>>(m, vector<bool>(n, false));
    this->transpose = vector<vector<bool>>(n, vector<bool>(m, false));
}

bool Matrix::get(int i, int j) {
    return this->matrix[i][j];
}

void Matrix::set(int i, int j, bool value) {
    this->matrix[i][j] = value;
    this->transpose[j][i] = value;
}

vector<bool>& Matrix::get_row(int i) {
    return this->matrix[i];
}

vector<bool>& Matrix::get_column(int j) {
    return this->transpose[j];
}

void Matrix::print() {
    for (int i = 0; i < this->get_m(); i++) {
        for (int j = 0; j < this->get_n(); j++) {
            cout << this->get(i, j) << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::read_from_file(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Unable to open file " << filename << endl;
        exit(1);
    }

    int m, n;
    file >> m >> n;
    
    Matrix matrix = Matrix(m, n);

    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            bool value;
            file >> value;
            matrix.set(i, j, value);
        }
    }

    file.close();

    return matrix;
}
