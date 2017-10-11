#include <math.h>
#include <stdint.h>

template<typename Type = double>
Type task1(const Type& a, const Type& b, const Type& x) {
    Type a1 = 0, a2 = 0;
    if (x != 0) {
        a1 = pow(a + b / x, 3);
        a2 = pow(b + a / x, 5);
    }
    return a1 + a2;
}

template<typename Type = double>
Type task2(const int64_t& i, const Type& x, const Type* const c) {
    Type a1 = 0, a2 = 0;
    if (i % 2 == 1) {
        if (x != 0) {
            a1 = 2.0 / 34.0 / x / x * i;
            a2 = 1.0 / 45.0 / x / x * i;
        }
        return 25.0 * c[i] * c[i] - a1 + a2;
    } else {
        if (c[i] != 0) {
            a1 = 2.0 / 34.0 / c[i] / c[i] * i;
            a2 = 1.0 / 45.0 / c[i] / c[i] * i;
        }
        return 25.0 * x * x - a1 + a2;
    }
}

template<typename Type = double>
Type task3(const int64_t& n, const Type* const a, const Type* const b) {
    int64_t i = 0;
    Type s = 0, p = 1;
    Type a1, a2;
    loop_label:
    if (i < n) {
        a1 = pow(a[i], 3);
        a2 = pow(b[i], 5);

        p *= a1 - a2;
        s += a1 + a2;

        i++;
        goto loop_label;
    }
    return p + s;
}
