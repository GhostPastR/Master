#include "testedmethod.h"

TestedMethodError::TestedMethodError( int codeError )
{
    this->codeError_ = codeError;
}

QString TestedMethodError::textError() const
{
    switch ( this->codeError_ ) {
        case 1:
            return QT_TR_NOOP( "У функции отсутствует символ '{'!" );
        case 2:
            return QT_TR_NOOP( "У функции отсутствует символ '(' разделяющий"
                               "список входных данных!" );
        case 3:
            return QT_TR_NOOP( "У функции отсутствует символ ')'!разделяющий"
                               "список входных данных!" );
        case 4:
            return QT_TR_NOOP( "Отсутствует названия функции!" );
        default:
            return "";
    }
}





TestedMethod::TestedMethod()
{

}

TestedMethod::~TestedMethod()
{

}

void TestedMethod::setTextMethod( const QString &textMethod )
{
    this->textMethod_ = textMethod;
    this->parsingMethod( textMethod );
}

void TestedMethod::parsingMethod( const QString &textMethod )
{
    int _indexEnd = textMethod.indexOf( "{" );
    if( _indexEnd == -1 )
        throw TestedMethodError( 1 );
    auto _strMethod = textMethod.mid( 0, _indexEnd );
    int _indexStart = textMethod.indexOf( "(" );
    if( _indexStart == -1  )
        throw TestedMethodError( 2 );
    _indexEnd = textMethod.indexOf( ")" );
    if( _indexEnd == -1 )
        throw TestedMethodError( 3 );
    this->parsingOutput( _strMethod.mid( 0, _indexStart ) );
    int _st = _indexStart + 1;
    this->parsingParametr( _strMethod.mid( _st, _indexEnd - _st ) );
}

void TestedMethod::parsingOutput( QString textMethod )
{
    this->removeSymbolLast( textMethod );
    this->removeSymbolFirst( textMethod );
    int _index = this->indexLAstSymbolMethod( textMethod );
    this->output_ = textMethod.mid( 0, _index );
    this->nameMethod_ = textMethod.mid( _index );
    this->removeSymbolLast( this->output_ );
}

void TestedMethod::parsingParametr( QString textMethod )
{
    this->parametr_.clear();
    this->removeSymbolLast( textMethod );
    this->removeSymbolFirst( textMethod );
    QStringList _listParametr = textMethod.split( "," );
    for( auto &i : _listParametr ) {
        this->removeSymbolFirst( i );
        this->removeSymbolLast( i );
        int _index = this->indexLAstSymbolMethod( i );
        auto _type = i.mid( 0, _index );
        this->removeSymbolLast( _type );
        auto _name = i.mid( _index );
        this->parametr_.append( QPair<QString, QString>( _type, _name ) );
    }
}

void TestedMethod::removeSymbolFirst( QString &text ) const
{
    QString _symbols( "\n\t\r\v\f " );
    int _c = text.count() - 1;
    for( int i = _c; _symbols.indexOf( text[i] ) != -1; )
        text.remove( i, 1 );
}

void TestedMethod::removeSymbolLast( QString &text ) const
{
    QString _symbols( "\n\t\r\v\f " );
    int _c = text.count() - 1;
    for( int i = _c; _symbols.indexOf( text[i] ) != -1; i-- )
        text.remove( i, 1 );
}

int TestedMethod::indexLAstSymbolMethod( const QString &text ) const
{
    QString _symbols( "\n\t\r\v\f " );
    int j = text.count() - 1;
    int _index = -1;
    for( ; _symbols.indexOf( text[j] ) == -1; j-- )
        _index = j;
    if( _index == -1 )
        throw  TestedMethodError( 4 );
    return _index;
}
