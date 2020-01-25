#ifndef TESTEDMETHOD_H
#define TESTEDMETHOD_H

#include <QString>
#include <QPair>
#include <QList>

class TestedMethodError
{
public:
    TestedMethodError( int codeError );

    QString textError() const;

private:
    int codeError_;
};





class TestedMethod
{
public:
    TestedMethod();
    ~TestedMethod();

    const QString &textMethod() const;
    void setTextMethod( const QString &textMethod );

    const QString &output() const;

    const QList<QPair<QString, QString>> &parametr() const;

    const QString &nameMethod() const;

private:
    QString textMethod_;
    QString nameMethod_;
    QString output_;
    QList<QPair<QString, QString>> parametr_;

    void parsingMethod( const QString &textMethod );
    void parsingOutput( QString textMethod );
    void parsingParametr( QString textMethod );

    void removeSymbolFirst( QString &text ) const;
    void removeSymbolLast( QString &text ) const;

    int indexLAstSymbolMethod(const QString &text ) const;
};

const QString &TestedMethod::textMethod() const
{
    return this->textMethod_;
}

inline const QString &TestedMethod::output() const
{
    return this->output_;
}

inline const QList<QPair<QString, QString> > &TestedMethod::parametr() const
{
    return this->parametr_;
}

inline const QString &TestedMethod::nameMethod() const
{
    return this->nameMethod_;
}

#endif // TESTEDMETHOD_H
