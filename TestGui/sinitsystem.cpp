#include "sinitsystem.h"
#include <QFile>
#include "configparsing.h"

QMap<QString, QString> SInitSystem::sysValue_;

QMap<QString, QString> SInitSystem::sysValue()
{
    if( SInitSystem::sysValue_.isEmpty() )
        throw InitSystemError( 1 );
    return SInitSystem::sysValue_;
}

void SInitSystem::load( const QString &path )
{
    QString _path = path;
    if( _path.isEmpty() )
//        _path = "./";
        _path.append( "config.txt" );
    QFile _file( _path );
    if( !_file.open( QIODevice::ReadOnly ) )
        throw InitSystemError( 2 );
    QString _config( _file.readAll() );
    _file.close();
    ConfigParsing _cp;
    bool _error;
    SInitSystem::sysValue_ = _cp.configParsing( _config, _error );
    if( _error )
        throw InitSystemError( 3 );
}

InitSystemError::InitSystemError( int codeError )
{
    this->codeError_ = codeError;
}

QString InitSystemError::textError() const
{
    switch (this->codeError_) {
        case 2:
            return QT_TR_NOOP( "Не удалось открыть файл конфигураций!" );
        case 3:
            return QT_TR_NOOP( "Не удалось разобрать файл конфигураций!" );
        default:
            return "";
    }
}
