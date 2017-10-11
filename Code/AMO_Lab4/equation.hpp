#ifndef EQUATION_HPP
#define EQUATION_HPP
#include <QMap>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <iostream>

class Polynom {
private:
    QMap<float, float> m_x;
public:
    explicit Polynom(const QString& poly) {
        QRegularExpression m_rx;
        m_rx = QRegularExpression("(|([-+0-9])[0-9.]+)x\\^((|[-+0-9])[0-9.]+)");
        QStringList m_units;
        for (auto it = m_rx.globalMatch(poly); it.hasNext();)
            m_units.push_back(it.next().captured());

        for (auto it : m_units) {
            QStringList t = it.split("x^");
            float f0 = t.at(0).toFloat();
            float f1 = t.at(1).toFloat();
            if (m_x.contains(f1))
                *m_x.find(f1) += (f0 == 0.f) ? 1.f : f0;
            else
                m_x.insert(f1, (f0 == 0.f) ? 1.f : f0);
        }

        m_rx = QRegularExpression("(|([-+0-9])[0-9.]+)x[^\\^]");
        QString t = m_rx.match(poly + ' ').captured();
        t = t.split('x').at(0);
        float f0 = t.toFloat();
        if (m_x.contains(1))
            *m_x.find(1) += (f0 == 0.f) ? 1.f : f0;
        else
            m_x.insert(1, (f0 == 0.f) ? 1.f : f0);

        m_rx = QRegularExpression("[^0-9.\\^]([-+0-9])([0-9.])+[^x0-9.]");
        t = m_rx.match(poly + ' ').captured();
        t.remove(0,1);
        t.chop(1);
        f0 = t.toFloat();
        if (m_x.contains(0))
            *m_x.find(0) += (f0 == 0.f) ? 1.f : f0;
        else
            m_x.insert(0, (f0 == 0.f) ? 1.f : f0);
    }
    float operator()(const float& arg){
        float res = 0;
        for (auto it : m_x)
            res += it * powf(arg, m_x.key(it));
        return res;
    }
};

#endif // EQUATION_HPP
