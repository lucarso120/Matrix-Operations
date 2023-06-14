## Matrix Class
This is a C++ class for working with matrices. It provides basic operations such as matrix addition, subtraction, multiplication, and transposition, as well as more advanced features such as matrix inversion, determinant, rank, norm, power, and eigenvalues/eigenvectors.

## Getting Started
To use the Matriz class, simply include the matriz.h header file in your C++ code:
```

include "matriz.h"
```


Then, create a Matriz object and perform operations on it:
```

MyMatrix::Matriz m1(3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
MyMatrix::Matriz m2(3, {9, 8, 7, 6, 5, 4, 3, 2, 1});

MyMatrix::Matriz m3 = m1 + m2;
std::cout << m3.printMatrix() << std::endl;
```

## Features
*Basic Operations
*Matrix addition: m1 + m2
*Matrix subtraction: m1 - m2
*Matrix multiplication: m1 * m2
*Matrix transposition: m1.transpose()
*Advanced Operations
*Matrix inversion: m1.inverse()
*Matrix determinant: m1.determinant()
*Matrix rank: m1.rank()
*Matrix norm: m1.norm()
*Matrix power: m1.power(n)
*Matrix eigenvalues and eigenvectors: m1.eigen()
