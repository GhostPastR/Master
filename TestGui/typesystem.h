#ifndef TYPESYSTEM_H
#define TYPESYSTEM_H

#include <memory>
#include <QList>
#include <QString>

class TypeSystem
{
public:
    TypeSystem( const QString &typeName = "" );
    TypeSystem( const TypeSystem &temp ) = default;
    TypeSystem( TypeSystem &&temp ) = default;
    TypeSystem &operator=( const TypeSystem &temp ) = default;
    TypeSystem &operator=( TypeSystem &&temp ) = default;
    ~TypeSystem();

    void setTypeName( const QString &typeName );
    const QString &typeName() const;
    const QList<TypeSystem> &items() const;

    void append( const QString &typeName );
    void append( const TypeSystem &sysType );

    TypeSystem &pfind( const QString &typeName, bool &isFind );
    const TypeSystem &find( const QString &typeName, bool &isFind ) const;

    QList<QStringList> variantNames() const;
private:
    QString typeName_;
    QList<TypeSystem> items_;
};

inline void TypeSystem::setTypeName( const QString &typeName )
{
    this->typeName_ = typeName;
}

inline const QString &TypeSystem::typeName() const
{
    return this->typeName_;
}

inline const QList<TypeSystem> &TypeSystem::items() const
{
    return this->items_;
}






class ListTypeSystem
{
public:
    ListTypeSystem();
    ListTypeSystem( const ListTypeSystem &temp ) = default;
    ListTypeSystem( ListTypeSystem &&temp ) = default;
    ListTypeSystem &operator=( const ListTypeSystem &temp ) = default;
    ListTypeSystem &operator=( ListTypeSystem &&temp ) = default;
    ~ListTypeSystem();

    const QList<TypeSystem> &items() const;

    bool checkItem( const QStringList &typeName ) const;
    QList<QStringList> allTypes() const;
    void append( const TypeSystem &typeSystem );

private:
    QList<TypeSystem> items_;

};

inline const QList<TypeSystem> &ListTypeSystem::items() const
{
    return this->items_;
}

#endif // TYPESYSTEM_H
