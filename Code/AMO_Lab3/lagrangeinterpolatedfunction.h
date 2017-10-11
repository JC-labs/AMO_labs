#ifndef LAGRANGEINTERPOLATEDFUNCTION_H
#define LAGRANGEINTERPOLATEDFUNCTION_H
#include "abstractinterpolatedfunction.h"
#include <vector>
#include <list>

class LagrangeCoef {
protected:
    float x_i, x_j;
public:
    LagrangeCoef(float x_i, float x_j) : x_i(x_i), x_j(x_j) {}
    virtual float operator()(const float& x) {
        return (x - x_j) / (x_i - x_j);
    }
};

class LagrangeCoefSet {
protected:
    std::list<LagrangeCoef> cs;
    float y;
public:
    LagrangeCoefSet(const float& y) : y(y) {}
    virtual void operator()(const LagrangeCoef& c) {
        cs.push_back(c);
    }
    virtual float operator()(const float& x) {
        float r = 1.f;
        for (auto it : cs)
            r *= it(x);
        return r * y;
    }
};

class LagrangeInterpolatedFunction : public AbstractInterpolatedFunction
{
protected:
    std::list<LagrangeCoefSet*> m_coefs;
public:
    LagrangeInterpolatedFunction(const std::vector<float> &x,
                                 const std::vector<float> &y) {
        size_t n = x.size();
        if (n != y.size())
            throw DifferentSizesException();

        for (size_t i = 0; i < n; i++) {
            m_coefs.push_front(new LagrangeCoefSet(y[i]));
            for (size_t j = 0; j < n; j++) {
                if (i != j) {
                    (*(*m_coefs.begin()))(LagrangeCoef(x[i], x[j]));
                }
            }
        }
    }

    virtual float operator()(const float& arg) override {
        float r = 0;
        for (auto it : m_coefs)
            r += (*it)(arg);
        return r;
    }
};

#endif // LAGRANGEINTERPOLATEDFUNCTION_H
