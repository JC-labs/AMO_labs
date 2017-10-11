#ifndef MATRIX_H
#define MATRIX_H
#include <QVector>

template <typename Type = float>
class AbstractMatrix {
protected:
    QVector<QVector<Type>> m_data;
public:
    explicit AbstractMatrix(size_t size) {
        m_data.resize(size);
        for (QVector<Type>& it : m_data)
            it.resize(size);
    }

    QVector<Type>& operator[](size_t i) {
        return m_data[i];
    }
    size_t size() {
        return m_data.size();
    }

    QVector<QVector<Type>>& operator*() {
        return m_data;
    }
};

using Matrix = AbstractMatrix<>;

#endif // MATRIX_H
