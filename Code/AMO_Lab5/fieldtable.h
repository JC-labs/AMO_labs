#ifndef FIELDTABLE_H
#define FIELDTABLE_H
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

class FieldColumn : public QVBoxLayout {
    Q_OBJECT
private:
    QVector<QLineEdit*> m_table;
public:
    explicit FieldColumn(size_t size) {
        m_table.resize(size);

        for (int i = 0; i < size; i++) {
            m_table[i] = new QLineEdit;
            addWidget(m_table[i]);
        }
    }
    ~FieldColumn() {
        for (int i = 0; i < m_table.size(); i++)
            delete m_table[i];
    }

    boost::numeric::ublas::vector<float> get(){
        boost::numeric::ublas::vector<float> res(m_table.size());
        for (int i = 0; i < m_table.size(); i++)
                res(i) = m_table[i]->text().toFloat();
        return res;
    }
};

class FieldTable : public QGridLayout {
    Q_OBJECT
private:
    QVector<QVector<QLineEdit*>> m_table;
public:
    explicit FieldTable(size_t size){
        m_table.resize(size);
        for (QVector<QLineEdit*>& it : m_table)
            it.resize(size);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                m_table[i][j] = new QLineEdit;
                addWidget(m_table[i][j], i, j, 1, 1);
            }
    }
    ~FieldTable() {
        for (int i = 0; i < m_table.size(); i++)
            for (int j = 0; j < m_table.size(); j++)
                delete m_table[i][j];
    }

    boost::numeric::ublas::matrix<float> get(){
        boost::numeric::ublas::matrix<float> res(m_table.size(), m_table.size());
        for (int i = 0; i < m_table.size(); i++)
            for (int j = 0; j < m_table.size(); j++)
                res(i, j) = m_table[i][j]->text().toFloat();
        return res;
    }
};

#endif // FIELDTABLE_H
