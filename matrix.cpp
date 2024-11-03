#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 4; 


class Matrix {
private:

    // Store elements of the matrix for calculations
    int elements[MAX_SIZE][MAX_SIZE];

    // current matrix size 
    int size;

public:

    // Constructor with size parameter
    // Parameter will set the size
    Matrix(int n) {
    size = n;
}

    // Function to copy input matrix to the 'elements' array
    void set_elements(const int matrix[][MAX_SIZE]) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                elements[i][j] = matrix[i][j];
            }
        }
    }

    // Function for overloading the '+' operator
    // Use & to reference Matrix object so we can add the first matrix with a second one without making actually creating a copy
    Matrix operator+(const Matrix &other) const {
        
        // Create result object to store the sum
        Matrix result(size);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {

                // Acess the elements array of 'results' and store the sums as its own elements
                result.elements[i][j] = elements[i][j] + other.elements[i][j];
            }
        
    }
    return result;

}
    // Function for overloading the '*' operator
    Matrix operator*(const Matrix &other) const {

        // Create result object to store the sum
        Matrix result(size);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.elements[i][j] = 0;  
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {

                // Perform the matrix multiplication by finding dot product
                result.elements[i][j] += elements[i][k] * other.elements[k][j];
            }
        }
    }

    return result;
}

    void diagonalSums(int &mainSum, int &secondarySum) const {
        mainSum = 0;
        secondarySum = 0;
        
        for (int i = 0; i < size; ++i) {
            mainSum += elements[i][i];                 
            secondarySum += elements[i][size - i - 1]; 
        }
    }

    void swapRows()  {
        for (int j = 0; j < size; ++j) {
            int temp = elements[1][j];
            elements[1][j] = elements[2][j];
            elements[2][j] = temp;
        }
    }


    void print() const {

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j){
                cout << elements[i][j] << " ";
            }

            cout << endl;
        }
        
        cout << endl;

    }
};


int main() {

    // Initialize input file stream for the provided txt file
    ifstream infile("matrix-data-file.txt");
    
    // Read the first number in the txt file to set the size variable
    int n;
    infile >> n;

    // Initialize the data for matrix 1 and 2
    int matrix1_data[MAX_SIZE][MAX_SIZE];
    int matrix2_data[MAX_SIZE][MAX_SIZE];

    // Extract nxn values from the txt file and store them as matrix1 data
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix1_data[i][j];
        }
    }

    // Extract the next nxn values from the txt file and store them as matrix2 data
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix2_data[i][j];
        }
    }


    // Call the constructor for both matrices from the file
    // 'n' is the single number in the first line of the file that specifies the size
    Matrix matrix1(n);
    Matrix matrix2(n);

    // Call set_elements method on matrix1 and matrix2 objects.
    matrix1.set_elements(matrix1_data);
    matrix2.set_elements(matrix2_data);

    cout << "Matrix 1:" << endl;
    matrix1.print();

    cout << "Matrix 2:" << endl;
    matrix2.print();

    Matrix sum = matrix1 + matrix2;
    cout << "Sum of Matrix 1 and Matrix 2:" << endl;
    sum.print();

    Matrix product = matrix1 * matrix2;
    cout << "Product of Matrix 1 and Matrix 2:" << endl;
    product.print();

    int mainSum, secondarySum;
    matrix1.diagonalSums(mainSum, secondarySum);
    cout << "Diagonal Sums of Matrix 1:" << endl;
    cout << "Main Diagonal Sum: " << mainSum << endl;
    cout << "Secondary Diagonal Sum: " << secondarySum << endl << endl;

    int mainSums, secondarySums;
    matrix2.diagonalSums(mainSums, secondarySums);
    cout << "Diagonal Sums of Matrix 2:" << endl;
    cout << "Main Diagonal Sum: " << mainSums << endl;
    cout << "Secondary Diagonal Sum: " << secondarySums << endl << endl;

    matrix1.swapRows();
    cout << "Matrix 1 row swap:" << endl;
    matrix1.print();

    matrix2.swapRows();
    cout << "Matrix 2 row swap:" << endl;
    matrix2.print();



    infile.close();
    return 0;
}