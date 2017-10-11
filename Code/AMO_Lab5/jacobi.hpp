#ifndef JACOBI_HPP
#define JACOBI_HPP
#include <boost/numeric/ublas/matrix.hpp>

class SizesException{};

boost::numeric::ublas::vector<float> Jacobi(boost::numeric::ublas::matrix<float> a,
                                            boost::numeric::ublas::vector<float> b,
                                            float acc) {
    int size = a.size1();
    if (size != a.size2() || size != b.size())
        throw SizesException();

    boost::numeric::ublas::vector<float> x(size), dx(size);
    float default_x = 1.f;

    for (int i = 0; i < size; i++) {
        b[i] /= a(i, i);
        x[i] = default_x;
        for (int j = 0; j < size; j++)
            if (i != j)
                a(i, j) = - a(i, j) / a(i, i);
        a(i, i) = 0;
    }

    bool exit;
    do {
        exit = true;
        dx = x;
        x = b + prod(a, dx);
        for (int i = 0; i < size; i++)
            exit &= fabs(x[i]-dx[i]) <= acc;
    } while(!exit);

    return x;
}

#endif // JACOBI_HPP
