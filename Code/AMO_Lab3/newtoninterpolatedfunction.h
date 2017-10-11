#ifndef NEWTONINTERPOLATEDFUNCTION_H
#define NEWTONINTERPOLATEDFUNCTION_H
#include "abstractinterpolatedfunction.h"
#include <vector>
#include <map>

class NewtonInterpolatedFunction : public AbstractInterpolatedFunction {
protected:
    std::vector<float> m_x, m_y;
    std::map<size_t, float> m_d;
public:
    NewtonInterpolatedFunction(const std::vector<float> &x,
                               const std::vector<float> &y) {
        size_t n = x.size();
        if (n != y.size())
            throw DifferentSizesException();

        m_x = x;
        m_y = y;

        generateDifferences(m_x.size());
    }

    float difference(size_t n) {
        float res = 0.f;
        for (size_t j = 0; j <= n; j++) {
            float pr = 1.f;
            for (size_t i = 0; i <= n; i++)
                if (i != j)
                    pr *= m_x[j] - m_x[i];
            res += m_y[j] / pr;
        }
        return res;
    }

    void generateDifferences(size_t n){
        for (size_t i = 0; i < n; i++)
            m_d.insert(std::pair<size_t, float>(i, difference(i)));
    }

    virtual float operator()(const float& arg) override {
        float res = 0.f;
        for (size_t i = 0; i < m_x.size(); i++){
            float pr = 1.f;
            for (size_t j = 0; j < i; j++)
                pr *= arg - m_x[j];
            res += pr * m_d[i];
        }
        return res;
    }
};

#endif // NEWTONINTERPOLATEDFUNCTION_H
