#ifndef TYPESYSTEMPARSING_H
#define TYPESYSTEMPARSING_H

#include <QStringList>

class TypeSystemError
{
public:
    TypeSystemError( int code );
    QString textError();

private:
    int code_;
};





class TypeSystemParsing
{
public:
    TypeSystemParsing();

    void typeParsing();

private:
    QString openFile() const;

    void parsing( const QString &text, const QString &str = "" ) const;

    QStringList split( const QString &text, const QChar &symbol ) const;

    bool checkType( const QString &nameType ) const;

    bool checkCramp( const QString &text ) const;
};

#endif // TYPESYSTEMPARSING_H
