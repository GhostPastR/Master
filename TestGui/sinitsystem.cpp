#include "sinitsystem.h"
#include <QFile>

QMap<QString, QString> SInitSystem::sysValue()
{
    if( SInitSystem::sysValue_.isEmpty() )
        throw InitSystemError( 2 );
    return SInitSystem::sysValue_;
}

void SInitSystem::load( const QString &path )
{
    QString _path = path;
    if( _path.isEmpty() )
        _path = "./";
    _path.append( "config.ini" );
    QFile _file( _path );
    if( !_file.open( QIODevice::ReadOnly ) )
        throw InitSystemError( 1 );
    QString _config( _file.readAll() );
    _file.close();
}

void SInitSystem::parsingConfig( const QString &configText )
{


}

InitSystemError::InitSystemError( int codeError )
{
    this->codeError_ = codeError;
}

QString InitSystemError::textError() const
{
    switch (this->codeError_) {
        case 1:
            return "";
        case 2:
            return "";
        default:
            return "";
    }
}
