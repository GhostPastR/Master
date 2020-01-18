#ifndef CONFIGPARSING_H
#define CONFIGPARSING_H

#include <QMap>

class ConfigParsing
{
public:
    ConfigParsing();

    QMap<QString,QString> configParsing( QString config, bool &error ) const;

private:
    QString commandChar_;
    QPair<QString, QString> comment_;

    void removeSymbolFirst( QString &text ) const;
    void removeSymbolLast( QString &text ) const;
    bool checkKey( const QString &key ) const;
    bool checkValue( const QString &value ) const;

    bool removeComment( QString &text ) const;
    QMap<QString,QString> keyValueParsing( QStringList keyValue,
                                           bool &error ) const;
};

#endif // CONFIGPARSING_H
