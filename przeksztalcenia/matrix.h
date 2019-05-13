#ifndef MATRIX_H
#define MATRIX_H

#include <QPoint>

class Matrix
{
public:
    Matrix();
    Matrix operator=(Matrix m);
    Matrix operator=(double** m);
    Matrix operator*(Matrix &m);
    double* operator*(double *);
    QPoint operator*(QPoint &p);

private:
    double matrix[3][3];
};

#endif // MATRIX_H
