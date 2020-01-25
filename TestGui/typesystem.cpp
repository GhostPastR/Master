#include "typesystem.h"

TypeSystem::TypeSystem( const QString &typeName )
{
    this->typeName_ = typeName;
}

TypeSystem::~TypeSystem()
{

}

void TypeSystem::append( const QString &typeName )
{
    this->items_.append( TypeSystem( typeName ) );
}

void TypeSystem::append( const TypeSystem &sysType )
{
    this->items_.append( sysType );
}

TypeSystem &TypeSystem::pfind( const QString &typeName, bool &isFind )
{
    isFind = false;
    for( auto &i : this->items_ ) {
        if( i.typeName_ == typeName ) {
            isFind = true;
            return i;
        }
    }
    TypeSystem *_temp = nullptr;
    return *_temp;
}

const TypeSystem &TypeSystem::find(const QString &typeName, bool &isFind) const
{
    isFind = false;
    for( const auto &i : this->items_ ) {
        if( i.typeName_ == typeName ) {
            isFind = true;
            return i;
        }
    }
    TypeSystem *_temp = nullptr;
    return *_temp;
}

QList<QStringList> TypeSystem::variantNames() const
{
    QList<QStringList> _variant;
    _variant.append( QStringList() << this->typeName_ );
    for( const auto &i : this->items_ ) {
        auto _v = i.variantNames();
        for( auto i : _v ) {
            QStringList _sl;
            _sl.append( this->typeName_ );
            _sl.append( i );
            _variant.append( _sl );
        }
    }
    return _variant;
}





ListTypeSystem::ListTypeSystem()
{

}

ListTypeSystem::~ListTypeSystem()
{

}

bool ListTypeSystem::checkItem( const QStringList &typeName ) const
{
    if( typeName.isEmpty() )
        return false;
    auto _first = typeName.constBegin();
    TypeSystem *_item = nullptr;
    for( auto i : this->items_ ) {
        if( i.typeName() == *_first ) {
            _item = &i;
            break;
        }
    }
    if( _item == nullptr )
        return false;
    _first++;
    if( _first == typeName.constEnd() )
        return true;
    bool _find;
    TypeSystem _it = *_item;
    while( true ) {
        _it = _it.find( *_first, _find );
        if( !_find )
            return false;
        _first++;
        if( _first == typeName.constEnd() )
            return true;
    }
}

QList<QStringList> ListTypeSystem::allTypes() const
{
    QList<QStringList> _items;
    for( auto i : this->items_ )
        _items.append( i.variantNames() );
    return _items;

}

void ListTypeSystem::append( const TypeSystem &typeSystem )
{
    this->items_.append( typeSystem );
}
