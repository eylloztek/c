#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixLib.h"

float *returnVector(int size){
    //a function that creates a vector with calloc 
    float *vector =(float *) calloc(size , sizeof(float));
    return vector;    
}

float **returnMatrix(int row, int col){
    //creating the rows of matrix using calloc
    float **matrix = (float **) calloc(row , sizeof(float*));
    
    for (int i = 0; i < row; i++){
        matrix[i] =(float*) calloc(col , sizeof(float));
    }

    return matrix;
}

void freeMatrix(float **mat, int row){
    //function for return the space we took from the memory to the system
    for (int i = 0; i < row; i++){
        free(mat[i]);
    }
    free(mat);
}

float mean(float *vec, int size){

    float sum=0.0;

    for (int i = 0; i < size; i++){
        sum +=vec[i];     
    }
    return (sum / size);
}

float covariance(float *vec1, float *vec2, int size){
    //cov(x,y) = (1/n)(x[i]-mean(x) * y[i]-mean(y))
    float sum=0;
    float mean1 = mean(vec1,size);
    float mean2 = mean(vec2,size);

    for (int i = 0; i < size; i++){
        sum += (vec1[i] - mean1) * (vec2[i] - mean2);
    }
    return sum / size;
}

float correlation(float *vec, float *vec2, int size){
    //corr(x,y) = cov(x,y)/[(sqrt(cov(x,x))*sqrt (cov(y,y))]
    return covariance(vec,vec2,size) / (sqrt(covariance(vec,vec,size)) * sqrt(covariance(vec2,vec2,size)));
}

float **matrixTranspose(float **mat, int row, int col){

    float **matrix = returnMatrix(col,row);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrix[j][i]=mat[i][j];
        }
    }
    return matrix;
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2){

    if(row2 != col1){
        printf("The number of columns of the first must be equal to the number of rows of the second.");
        return NULL;
    }
    
    float **matrix = returnMatrix(row1,col2);
    
    for (int i = 0; i < row1; i++) {
      for (int j = 0; j < col2; j++) {
        for (int k = 0; k < row2; k++) {
            matrix[i][j] += mat1[i][k] * mat2[k][j];
        }
      }
    }
   return matrix;
}

float *rowMeans(float **mat, int row, int col){

    float *vector = returnVector(row); 
    for (int i = 0; i < row; i++){
        vector[i] = mean(mat[i],col);
    }
    
    return vector;
}

float *columnMeans(float **mat, int row, int col){

    float *vector = returnVector(col);
    float sum = 0;
    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            sum += mat[j][i];
        }
        vector[i] = sum / (float)row;
        sum=0;
    }
    return vector;
}
    
float **covarianceMatrix(float **mat, int row, int col){
    float *colMean = columnMeans(mat, row, col);  
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            mat[i][j] -= colMean[j];
        }
    }

    float **transpose = matrixTranspose(mat, row, col);
    float **matrixCov = matrixMultiplication(transpose, mat, row, col, row, col);
    //(matrix * transpose(matrix)) / row
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            matrixCov[i][j] /= row;
        }
    }
    free(colMean);
    freeMatrix(transpose, row);
    return matrixCov;
}

float determinant(float **mat, int row){
    for (int i = 0; i < row; i++){
        mat[i] =(float*) realloc(mat[i], 5*sizeof(float)); 
        for (int j = 3; j < 5; j++){
            mat[i][j] = mat[i][j-3];
        }    
    }
    float det = 0;
    for (int i = 0; i < 3; i++){
        det += mat[0][i] * mat[1][i+1] * mat[2][i+2];
        det -= mat[2][i] * mat[1][i+1] * mat[0][i+2];
    }
    return det;
}

void printVector(float *vec, int N){
    for (int i = 0; i < N; i++){
        printf("%f  ", vec[i]);
    }
}

void printMatrix(float **mat, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){    
            printf("%f  ", mat[i][j]);
        }
        printf("\n");
    }
}

void matrixRandom(float **mat, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            mat[i][j] = (rand()%10)+1;
        }    
    }   
}

void vectorRandom(float *vector, int size){
    for (int i = 0; i < size; i++){
        vector[i] = (rand()%10)+1;
    }   
}