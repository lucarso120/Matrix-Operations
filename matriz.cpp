#include "matriz.hpp"
#include <cmath>

namespace MyMatrix {

    Matriz::Matriz() {
        cout << "The standard matrix is a 3x3 Identity Matrix";
        matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    }

    Matriz::Matriz(const int& nDim, const std::vector<double>& nVetor) {
        dim = nDim;
        vector<double> vetorTemp;
        vector<vector<double>> nMatrix;

        if (nVetor.size() % nDim != 0) {
            throw runtime_error("Vetor deve ter linhas com dim elementos\n");
        }

        int counter = 0;
        for (int x : nVetor) {
            vetorTemp.push_back(x);
            counter++;
            if (counter % dim == 0) {
                nMatrix.push_back(vetorTemp);
                vetorTemp.clear();
            }
        }
        matrix = nMatrix;
    }

    Matriz::~Matriz() {}

    void Matriz::InsertNewMatrix(const int& nDim) {
        int value, count;
        dim = nDim;
        vector<vector<double>> nMatrix;
        while (count < nDim) {
            vector<double> temp;
            for (int i = 0; i < nDim; ++i) {
                cout << "digite a entrada " << count + 1 << i + 1 << " ";
                cin >> value;
                if (!value) {
                    throw runtime_error("Deve inserir um numero inteiro valido.\n");
                }
                temp.push_back(value);
                if (temp.size() == nDim) {
                    nMatrix.push_back(temp);
                }
            }
            count++;
        }
        matrix = nMatrix;
    }

    double Matriz::getTrace() const {
        double traco = 0;
        for (int i = 0; i < dim; ++i) {
            traco += matrix[i][i];
        }
        return traco;
    }

    std::string Matriz::printMatrix() const {
        std::string str;
        ostringstream os;

        for (vector<double> v : matrix) {
            os << "|";
            for (int n : v) {
                os << n << " ";
            }
            os << "|\n";
        }
        str = os.str();
        return str;
    }

    Matriz Matriz::operator+(const Matriz& other) const {
        checkDimensions(other);
        Matriz result(dim, vector<double>(dim, 0));
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    Matriz Matriz::operator-(const Matriz& other) const {
        checkDimensions(other);
        Matriz result(dim, vector<double>(dim, 0));
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    Matriz Matriz::operator*(const Matriz& other) const {
        checkDimensions(other);
        Matriz result(dim, vector<double>(dim, 0));
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                for (int k = 0; k < dim; ++k) {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    Matriz Matriz::transpose() const {
        Matriz result(dim, vector<double>(dim, 0));
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.matrix[i][j] = matrix[j][i];
            }
        }
        return result;
    }

    Matriz Matriz::inverse() const {
        if (dim != 2) {
            throw runtime_error("Matrix must be 2x2 to compute inverse.\n");
        }
        double det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        if (det == 0) {
            throw runtime_error("Matrix is not invertible.\n");
        }
        Matriz result(dim, vector<double>(dim, 0));
        result.matrix[0][0] = matrix[1][1] / det;
        result.matrix[0][1] = -matrix[0][1] / det;
        result.matrix[1][0] = -matrix[1][0] / det;
        result.matrix[1][1] = matrix[0][0] / det;
        return result;
    }

    double Matriz::determinant() const {
        if (dim != 2) {
            throw runtime_error("Matrix must be 2x2 to compute determinant.\n");
        }
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int Matriz::rank() const {
        int rank = dim;
        Matriz temp(*this);
        for (int i = 0; i < dim; ++i) {
            if (temp.matrix[i][i] == 0) {
                bool found = false;
                for (int j = i + 1; j < dim; ++j) {
                    if (temp.matrix[j][i] != 0) {
                        found = true;
                        swap(temp.matrix[i], temp.matrix[j]);
                        break;
                    }
                }
                if (!found) {
                    rank--;
                    continue;
                }
            }
            for (int j = i + 1; j < dim; ++j) {
                double factor = temp.matrix[j][i] / temp.matrix[i][i];
                for (int k = i; k < dim; ++k) {
                    temp.matrix[j][k] -= factor * temp.matrix[i][k];
                }
            }
        }
        return rank;
    }

    double Matriz::norm() const {
        double sum = 0;
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                sum += matrix[i][j] * matrix[i][j];
            }
        }
        return sqrt(sum);
    }

    Matriz Matriz::power(const int& n) const {
        if (n == 0) {
            return Matriz(dim, vector<double>(dim, 0));
        }
        if (n == 1) {
            return *this;
        }
        Matriz temp = power(n / 2);
        if (n % 2 == 0) {
            return temp * temp;
        } else {
            return *this * temp * temp;
        }
    }

    std::pair<std::vector<double>, Matriz> Matriz::eigen() const {
        if (dim != 2) {
            throw runtime_error("Matrix must be 2x2 to compute eigenvalues and eigenvectors.\n");
        }
        double a = matrix[0][0];
        double b = matrix[0][1];
        double c = matrix[1][0];
        double d = matrix[1][1];
        double lambda1 = (a + d + sqrt((a + d) * (a + d) - 4 * (a * d - b * c))) / 2;
        double lambda2 = (a + d - sqrt((a + d) * (a + d) - 4 * (a * d - b * c))) / 2;
        double x1 = 1;
        double y1 = (lambda1 - a) / b;
        double x2 = 1;
        double y2 = (lambda2 - a) / b;
        std::vector<double> eigenvalues = {lambda1, lambda2};
        Matriz eigenvectors(2, {x1, y1, x2, y2});
        return {eigenvalues, eigenvectors};
    }

    void Matriz::checkDimensions(const Matriz& other) const {
        if (dim != other.dim) {
            throw runtime_error("Matrices must have the same dimensions.\n");
        }
    }

    double Matriz::cofactor(const int& row, const int& col) const {
        return pow(-1, row + col) * minor(row, col);
    }

    double Matriz::minor(const int& row, const int& col) const {
        Matriz temp(dim - 1, vector<double>(dim - 1, 0));
        int r = 0;
        for (int i = 0; i < dim; ++i) {
            if (i == row) {
                continue;
            }
            int c = 0;
            for (int j = 0; j < dim; ++j) {
                if (j == col) {
                    continue;
                }
                temp.matrix[r][c] = matrix[i][j];
                c++;
            }
            r++;
        }
        return temp.determinant();
    }

}

int main() {
    MyMatrix::Matriz m1(3, {1, 0, 3, 1, 1, 1, 3, 0, 1});
    cout << m1.printMatrix();
    cout << m1.getTrace() << endl;
    cout << "nova matriz: \n";
    m1.InsertNewMatrix(5);
    cout << m1.printMatrix();
    cout << m1.getTrace() << endl;
    cout << "m1 + m1:\n";
    cout << (m1 + m1).printMatrix();
    cout << "m1 - m1:\n";
    cout << (m1 - m1).printMatrix();
    cout << "m1 * m1:\n";
    cout << (m1 * m1).printMatrix();
    cout << "m1 transposta:\n";
    cout << m1.transpose().printMatrix();
    cout << "m1 inversa:\n";
    cout << m1.inverse().printMatrix();
    cout << "m1 determinante:\n";
    cout << m1.determinant() << endl;
    cout << "m1 rank:\n";
    cout << m1.rank() << endl;
    cout << "m1 norma:\n";
    cout << m1.norm() << endl;
    cout << "m1 elevada a 3:\n";
    cout << m1.power(3).printMatrix();
    auto [eigenvalues, eigenvectors] = m1.eigen();
    cout << "m1 autovalores:\n";
    for (double lambda : eigenvalues) {
        cout << lambda << " ";
    }
    cout << endl;
    cout << "m1 autovetores:\n";
    cout << eigenvectors.printMatrix();
}