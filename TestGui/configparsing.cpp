#include "configparsing.h"
#include <QDebug>

ConfigParsing::ConfigParsing()
{
    this->commandChar_ = "\n\t\r\v\f ";
    this->comment_.first = "//!";
    this->comment_.second = "!//";
}

QMap<QString, QString> ConfigParsing::configParsing( QString config,
                                                     bool &error ) const
{
    error = true;
    QMap<QString, QString> _parametr;
    if( !this->removeComment( config ) )
        return  _parametr;
    if( config.isEmpty() ) {
        qWarning() << QT_TR_NOOP( "Файл конфигурации пустой!" );
        return _parametr;
    }
    this->removeSymbolFirst( config );
    this->removeSymbolLast( config );
    if( config.at( config.count() - 1 ) != ";" ) {
        qWarning() << QT_TR_NOOP( "Отсутствует символ завершения ';'!" );
        return _parametr;
    }
    _parametr =this->keyValueParsing(
               config.split( ";", QString::SkipEmptyParts ), error );
    if( error )
        return _parametr;
    error = false;
    return _parametr;
}

void ConfigParsing::removeSymbolFirst( QString &text ) const
{
    for( int i = 0; this->commandChar_.indexOf( text[i] ) != -1; )
        text.remove( i, 1 );
}

void ConfigParsing::removeSymbolLast( QString &text ) const
{
    int _c = text.count() - 1;
    for( int i = _c; this->commandChar_.indexOf( text[i] ) != -1; i-- )
        text.remove( i, 1 );
}

bool ConfigParsing::checkKey( const QString &key ) const
{
    if( key.isEmpty() ) {
        qWarning() << QT_TR_NOOP( "Пустой ключ!" );
        return false;
    }
    QString _symbol;
    if( key.contains( QRegExp( "[^a-zA-Zа-яА-Я0-9_]" ) ) ) {
        qWarning() << QT_TR_NOOP( "В названия ключа содержится недопустимый "
                                  "символ!" ) << " " << key;
        return false;
    }
    return true;
}

bool ConfigParsing::checkValue( const QString &value ) const
{
    if( value.isEmpty() ) {
        qWarning() << QT_TR_NOOP( "Пустое значения ключа!" );
        return false;
    }
    if( !value.contains( QRegExp( "^\"" ) ) ||
            !value.contains( QRegExp( "\"$" ) ) ) {
        qWarning() << QT_TR_NOOP( "Неверно задано значения ключа!" ) << " "
                   << value;
        return false;
    }
    return true;
}

bool ConfigParsing::removeComment( QString &text ) const
{
    while ( true ) {
        int _start = text.indexOf( this->comment_.first );
        if( _start == -1 ) {
            if( text.indexOf( this->comment_.second ) != -1 ) {
                qWarning() << QT_TR_NOOP( "Присутствует символ закрывающий "
                                          "комментарий без открывающего!" );
                return false;
            }
            else break;
        }
        else {
            int _end = text.indexOf( this->comment_.second );
            if( _end == -1 )
                text.remove( _start, text.count() - _start );
            else
                text.remove( _start, _end - _start +
                             this->comment_.second.count() );
        }
    }
    return true;
}

QMap<QString, QString> ConfigParsing::keyValueParsing( QStringList keyValue,
                                                       bool &error ) const
{
    error = true;
    QMap<QString, QString> _parametr;
    if( keyValue.isEmpty() ) {
        qWarning() << QT_TR_NOOP( "Нет параметров конфигураций" );
        return _parametr;
    }
    QList<QStringList> _keyValue;
    for( auto &i : keyValue ) {
        this->removeSymbolFirst( i );
        this->removeSymbolLast( i );
        auto _type = i.split( "=" );
        if( _type.count() != 2 ) {
            qWarning() << QT_TR_NOOP( "Неверный формат ключ-значения!" )
                       << " : " << i;
            return _parametr;
        }
        this->removeSymbolLast( _type.first() );
        this->removeSymbolFirst( _type.last() );
        if( !this->checkKey( _type.first() ) )
            return _parametr;
        if( !this->checkValue( _type.last() ) )
            return _parametr;
        _type.last().remove( 0, 1 );
        _type.last().remove( _type.last().count() - 1, 1 );
        _keyValue.append( _type );
    }
    for( const auto &i : _keyValue )
        _parametr.insert( i.first(), i.last() );
    error = false;
    return _parametr;
}


