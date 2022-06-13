#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Matriz{

    protected:
        vector<double> vetor;
        vector<vector<double>> matrix;
        int dim;
        double traco;

    public:
        Matriz();
        Matriz(int nDim, vector<double> nVetor);

        void InsertNewMatrix(int nDim);
        double getTrace();
        string printMatrix();


};

#endif