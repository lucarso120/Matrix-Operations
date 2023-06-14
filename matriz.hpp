#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

namespace MyMatrix {

    class Matriz {

    protected:
        std::vector<double> vetor;
        std::vector<std::vector<double>> matrix;
        int dim;
        double traco;

    public:
        Matriz();
        Matriz(const int& nDim, const std::vector<double>& nVetor);
        ~Matriz();

        void InsertNewMatrix(const int& nDim);
        double getTrace() const;
        std::string printMatrix() const;
        Matriz operator+(const Matriz& other) const;
        Matriz operator-(const Matriz& other) const;
        Matriz operator*(const Matriz& other) const;
        Matriz transpose() const;
        Matriz inverse() const;
        double determinant() const;
        int rank() const;
        double norm() const;
        Matriz power(const int& n) const;
        std::pair<std::vector<double>, Matriz> eigen() const;

    private:
        void checkDimensions(const Matriz& other) const;
        double cofactor(const int& row, const int& col) const;
        double minor(const int& row, const int& col) const;
    };

}

#endif