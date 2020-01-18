#include "typesystemparsing.h"
#include <QDebug>
#include <QFile>
#include "sinitsystem.h"

TypeSystemError::TypeSystemError( int code )
{
    this->code_ = code;
}

QString TypeSystemError::textError()
{
    switch ( this->code_ ) {
        case 1:
            return QT_TR_NOOP( "Не удалось открыть файл системных типов!" );
        case 2:
            return QT_TR_NOOP( "Не удалось разобрать файл системных типов!" );
        default:
            return "";
    }
}

TypeSystemParsing::TypeSystemParsing()
{

}

void TypeSystemParsing::typeParsing()
{
    auto _text = this->openFile();
    _text.remove( QRegExp( "[\n\t\r\v\f ]" ) );
    auto _type = _text.split( ";", QString::SkipEmptyParts );
    for( auto i : _type ) {
        this->parsing( i );
    }
}

QString TypeSystemParsing::openFile() const
{
    auto _path = SInitSystem::sysValue().value( "TypeSystemPath" );
    QFile _file( _path );
    if( !_file.open( QIODevice::ReadOnly ) )
        throw TypeSystemError( 1 );
    QString _text( _file.readAll() );
    _file.close();
    return _text;
}

void TypeSystemParsing::parsing( const QString &text, const QString &str ) const
{
    QString _type;
    if( !this->checkCramp( text ) )
        throw TypeSystemError( 2 );
    int _startIndex = text.indexOf( "{" );
    int _endIndex = text.lastIndexOf( "}" );
    if( ( _startIndex == -1 ) && ( _endIndex == -1 ) ) {
        _type = text;
        if( this->checkType( _type ) ) {
            qWarning() << QT_TR_NOOP( "Некорректное название типа!" ) << " "
                       << _type;
            throw TypeSystemError( 2 );
        }

        qDebug() << str << _type;
    }
    else {
        auto _str = text.mid( _endIndex + 1 );
        if( _str != "" ) {
            qWarning() << QT_TR_NOOP( "Неверный формат, присутствует "
                                      "недопустимый символ!" ) << " " << _str;
            throw TypeSystemError( 2 );
        }
        _str = text.mid( 0, _startIndex );
        if( _str == "" ) {
            qWarning() << QT_TR_NOOP( "Название типа отсутствует!" ) << " "
                       << text;
            throw TypeSystemError( 2 );
        }
        _type = _str;
        if( this->checkType( _type ) ) {
            qWarning() << QT_TR_NOOP( "Некорректное названия типа!" ) << " "
                       << _type;
            throw TypeSystemError( 2 );
        }

        qDebug() << str << _str;

        int _si = _startIndex + 1;
        _str = text.mid( _si, _endIndex - _si );
        auto _strList = this->split( _str, ',' );
        for( const auto &i : _strList ) {
            this->parsing( i, str + "===" );
        }
    }
}

QStringList TypeSystemParsing::split( const QString &text,
                                      const QChar &symbol ) const
{
    QStringList _strList;
    QString _str;
    int _ignore = 0;
    for( int i = 0, c = text.count(); i < c; i++ ) {
        if( text[i] == "{" )
            _ignore++;
        else if( text[i] == "}" )
            _ignore--;
        else if( ( text[i] == symbol ) && ( _ignore == 0 ) ) {
            if( !_str.isEmpty() ) {
                _strList.append( _str );
                _str.clear();
            }
            continue;
        }
        _str.append( text[i] );
    }
    if( !_str.isEmpty() )
        _strList.append( _str );
    return _strList;
}

bool TypeSystemParsing::checkType( const QString &nameType ) const
{
    return nameType.contains( QRegExp( "[^a-zA-Z_]" ) );
}

bool TypeSystemParsing::checkCramp( const QString &text ) const
{
    int _start = text.count( "{" );
    int _end = text.count( "}" );
    if( _start > _end ) {
        qWarning() << QT_TR_NOOP( "Отсутствует закрывающаяся скобка!" );
        return false;
    }
    else if( _start < _end ) {
        qWarning() << QT_TR_NOOP( "Слишком много закрывающих скобок!" );
        return false;
    }
    return true;
}
