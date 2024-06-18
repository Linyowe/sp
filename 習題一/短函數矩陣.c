#include <stdio.h>
#include <stdlib.h>

// 结构体定义表示矩阵
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

// 创建一个新矩阵
Matrix *createMatrix(int rows, int cols) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double *)malloc(cols * sizeof(double));
    }
    return mat;
}

// 释放矩阵内存
void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

// 打印矩阵
void dumpMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%lf\t", mat->data[i][j]);
        }
        printf("\n");
    }
}

// 计算矩阵转置
Matrix *transpose(Matrix *mat) {
    Matrix *result = createMatrix(mat->cols, mat->rows);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            result->data[j][i] = mat->data[i][j];
        }
    }
    return result;
}

// 计算矩阵相加
Matrix *add(Matrix *mat1, Matrix *mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        printf("Error: Matrices dimensions do not match!\n");
        return NULL;
    }
    Matrix *result = createMatrix(mat1->rows, mat1->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }
    return result;
}

// 计算矩阵相乘
Matrix *multiply(Matrix *mat1, Matrix *mat2) {
    if (mat1->cols != mat2->rows) {
        printf("Error: Matrices dimensions do not match for multiplication!\n");
        return NULL;
    }
    Matrix *result = createMatrix(mat1->rows, mat2->cols);
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < mat1->cols; k++) {
                result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }
    return result;
}

int main() {
    Matrix *mat1 = createMatrix(2, 3);
    Matrix *mat2 = createMatrix(3, 2);

    // 填充矩阵
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat1->cols; j++) {
            mat1->data[i][j] = i + j;
        }
    }

    for (int i = 0; i < mat2->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            mat2->data[i][j] = i - j;
        }
    }

    printf("Matrix 1:\n");
    dumpMatrix(mat1);
    printf("\n");

    printf("Matrix 2:\n");
    dumpMatrix(mat2);
    printf("\n");

    // 计算并打印转置矩阵
    Matrix *transpose_result = transpose(mat1);
    printf("Transpose of Matrix 1:\n");
    dumpMatrix(transpose_result);
    printf("\n");

    // 计算并打印两个矩阵相加的结果
    Matrix *add_result = add(mat1, mat2);
    printf("Addition of Matrix 1 and Matrix 2:\n");
    dumpMatrix(add_result);
    printf("\n");

    // 计算并打印两个矩阵相乘的结果
    Matrix *multiply_result = multiply(mat1, mat2);
    printf("Multiplication of Matrix 1 and Matrix 2:\n");
    dumpMatrix(multiply_result);
    printf("\n");

    // 释放内存
    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(transpose_result);
    freeMatrix(add_result);
    freeMatrix(multiply_result);

    return 0;
}
