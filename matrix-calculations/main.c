#include <stdio.h>
#include <stdlib.h>
#include "matrixLib.h" 
#include <time.h>
#include <math.h>

int main(int num, char* args[]){
    if(num<2){
        printf("Missing value.");
        return 0;
    }
    srand(atoi(args[1]));

    float *vector = returnVector(3);
    //creating a vector and filling inside with random numbers
    vectorRandom(vector,3);
    printf("1st vector: \n");
    //printing vector
    printVector(vector,3);
    //mean of vector
    printf("\nmean of vector: %f", mean(vector,3));
    printf("\n");

    float *vector1 = returnVector(3);
    float *vector2 = returnVector(3);
    //creating 2 vectors and filling inside with random numbers
    vectorRandom(vector1,3); 
    vectorRandom(vector2,3);
    printVector(vector1,3);
    printf("\n");
    printVector(vector2,3);
    //printing the vector's correlation
    printf("\nvector's correlation: %f",correlation(vector1,vector2,3));
    //printing the vectors covariance
    printf("\nvector's covariance: %f", covariance(vector1,vector2,3)); 
    printf("\n");

    float **matrix1 = returnMatrix(3,3);
    float **matrix2 = returnMatrix(3,3);
    //creating 2 random matrixes and filling inside with random numbers
    matrixRandom(matrix1,3,3);
    printf("\nMatrix 1:\n");
    printMatrix(matrix1,3,3);
    matrixRandom(matrix2,3,3);
    printf("\nMatrix 2:\n");
    printMatrix(matrix2,3,3);
    //printing the multiplation of matrix
    printf("\nMatrix multiplication:\n");
    float **matrixMultiply = returnMatrix(3,3);
    matrixMultiply = matrixMultiplication(matrix1,matrix2,3,3,3,3);
    printMatrix(matrixMultiply,3,3);
    

    //calculating the transpose of a matrix that we created above
    float **transpose = matrixTranspose(matrix1,3,3);
    printf("\nTranspose of 1st matrix:\n");
    printMatrix(transpose,3,3);
    printf("\nDeterminant of 2nd matrix: %f",determinant(matrix2,3));
    printf("\n");

    float **matrix = returnMatrix(4,5);
    matrixRandom(matrix,4,5);
    printf("\nMatrix:\n");
    printMatrix(matrix,4,5);
    //calculating row means and column means of the random matrix 
    float *rowmean = rowMeans(matrix,4,5);
    float *colmean = columnMeans(matrix,4,5);
    printf("\nmean of rows: ");
    printVector(rowmean,4);
    printf("\n");
    printf("\nmean of columns: ");
    printVector(colmean,5);
    printf("\n");

    float **matrixCovariance = returnMatrix(3,3);
    printf("\nCovariance of matrix:\n");
    matrixCovariance = covarianceMatrix(matrix1,3,3);
    printMatrix(matrixCovariance,3,3);
    printf("\n");
    
    freeMatrix(matrix,3);
    freeMatrix(matrix1,3);
    freeMatrix(matrix2,3);
    freeMatrix(matrixCovariance,3);
    freeMatrix(matrixMultiply,3);


}
