#ifndef SINITSYSTEM_H
#define SINITSYSTEM_H

#include <QMap>
#include <QString>

class InitSystemError
{
public:
    InitSystemError( int codeError );

    QString textError() const;

private:
    int codeError_;
};

class SInitSystem
{
public:
    SInitSystem() = delete;

    static QMap<QString, QString> sysValue();
    static void load( const QString &path );

private:
    static QMap<QString, QString> sysValue_;
    static void parsingConfig( const QString &configText );
};

#endif // SINITSYSTEM_H
