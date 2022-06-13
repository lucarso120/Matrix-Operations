#include "matriz.hpp"


Matriz::Matriz(){
    cout << "The standard matrix is a 3x3 Identity Matrix";
    matrix = {{1,0,0}, {0,1,0}, {0,0,1}};
}

Matriz::Matriz(int nDim, vector<double> nVetor){
    dim = nDim;
    vector<double> vetorTemp;
    vector<vector<double>> nMatrix;

    if (nVetor.size() % nDim !=0){
        throw runtime_error("Vetor deve ter linhas com dim elementos\n");
    }

    int counter = 0;
    for (int x : nVetor){
        vetorTemp.push_back(x);
        counter++;
        if (counter % dim == 0){
            nMatrix.push_back(vetorTemp);
            vetorTemp.clear();
        }
    }
    matrix = nMatrix;
}


void  Matriz::InsertNewMatrix(int nDim){

    int value, count;
    dim = nDim;
    vector<vector<double>> nMatrix;
     while(count < nDim){
        vector<double> temp;
        for (int i=0; i <nDim; ++i){
            cout << "digite a entrada " << count+1 << i+1 <<" ";
            cin >> value;
            if (!value){
                throw runtime_error("Deve inserir um numero inteiro valido.\n");                    
            }
            temp.push_back(value);
            if(temp.size()==nDim){
                nMatrix.push_back(temp);
            }
        }
        count++;
    }
    matrix = nMatrix;
    
}

double Matriz::getTrace(){

    for (int i=0; i <dim; ++i){
        for (int j=0; j < dim; ++j){
            if (i == j){
                traco += matrix[i][j];
            }
        }

    }
    return traco;
}

string Matriz::printMatrix(){
    string str;
    ostringstream os;

    for(vector<double> v : matrix){
        os << "|";
        for (int n : v){
            os << n <<" ";
        }
        os << "|\n";
    }
    str = os.str();
    return str;
}

int main(){

    Matriz m1(3,{1, 0, 3, 1, 1, 1, 3, 0, 1});
    cout << m1.printMatrix();
    cout << m1.getTrace();
    cout << "nova matriz: \n";
    m1.InsertNewMatrix(5);
    cout << m1.printMatrix();
    cout << m1.getTrace();
}