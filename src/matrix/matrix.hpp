#if !defined MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


/**
 * @class Matrix
 * @brief Represents a matrix of subsets.
 */
class Matrix {
    private:
        int m; // number of elements (rows)
        int n; // number of subsets (columns)
        vector<vector<bool>> matrix; // matrix of subsets
        vector<vector<bool>> transpose; // transpose of the matrix

        /**
         * @brief Transposes the matrix.
         */
        void transpose_matrix();

    public:
        /**
         * @brief Constructs a new Matrix object.
         */
        Matrix();


        /**
         * @brief Constructs a new Matrix object.
         * 
         * @param m The number of elements (rows) in the matrix.
         * @param n The number of subsets (columns) in the matrix.
         */
        Matrix(int m, int n);

        /**
         * @brief Gets the number of elements (rows) in the matrix.
         * 
         * @return The number of elements.
         */
        int get_m() const { return this->m; }

        /**
         * @brief Gets the number of subsets (columns) in the matrix.
         * 
         * @return The number of subsets.
         */
        int get_n() const { return this->n; }

        /**
         * @brief Gets the value of an element in the matrix.
         * 
         * @param i The row index of the element.
         * @param j The column index of the element.
         * @return The value of the element.
         */
        bool get(int i, int j);

        /**
         * @brief Sets the value of an element in the matrix.
         * 
         * @param i The row index of the element.
         * @param j The column index of the element.
         * @param value The value to be set.
         */
        void set(int i, int j, bool value);

        /**
         * @brief Gets a row from the matrix.
         * 
         * @param i The index of the row.
         * @return The row as a vector of booleans.
         */
        vector<bool>& get_row(int i);

        /**
         * @brief Gets a column from the matrix.
         * 
         * @param j The index of the column.
         * @return The column as a vector of booleans.
         */
        vector<bool>& get_column(int j);

        /**
         * @brief Prints the matrix.
         */
        void print();

        /**
         * @brief Reads the contents of a file and populates the matrix with the data.
         *
         * @param filename The name of the file to read from.
         * @return The populated Matrix object.
         */
        static Matrix read_from_file(string filename);
};

#endif // MATRIX_HPP
