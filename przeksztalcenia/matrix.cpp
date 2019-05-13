#include "matrix.h"

Matrix::Matrix()
{
    int i,j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            matrix[i][j] = 0;
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
}

Matrix Matrix::operator=(Matrix m){
    for(int i=0; i < 3; i++)
        for(int j=0; j < 3; j++)
            this->matrix[i][j] = m.matrix[i][j];
    return *this;
}

Matrix Matrix::operator=(double **m){
    Matrix result;
    for(int i=0; i < 3; i++)
        for(int j=0; j < 3; j++)
            this->matrix[i][j] = m[i][j];
    return result;
}

Matrix Matrix::operator*(Matrix &m){
    Matrix result;
    int i, j ,k;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            result.matrix[i][j] = 0;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
          for(k = 0; k < 3; k++)
            result.matrix[i][j] = result.matrix[i][j] + this->matrix[i][k] * m.matrix[k][j];
    return result;
}

double * Matrix::operator*(double *w){
    double * result = new double[3];
    int i, j ,k;
    for(i = 0; i < 3; i++)
        result[i] = 0;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
          for(k = 0; k < 3; k++)
            result[i] = result[i] + this->matrix[i][k] * w[k];
    return result;
}

QPoint Matrix::operator*(QPoint &p){
    double * result = new double[3];
    double * w = new double[3];
    int i,k;
    QPoint resultQPoint;

    w[0] = p.x();
    w[1] = p.y();
    w[2] = 1.0;

    for(i = 0; i < 3; i++)
        result[i] = 0;

    for(i = 0; i < 3; i++)
          for(k = 0; k < 3; k++)
            result[i] = result[i] + this->matrix[i][k] * w[k];

    resultQPoint.setX(int(result[0]));
    resultQPoint.setY(int(result[1]));
    delete [] result;
    delete [] w;

    return resultQPoint;
}
