#include "widget.h"
#include <QApplication>
#include <QDebug>
#include "sinitsystem.h"
#include "typesystemparsing.h"

int main(int argc, char *argv[])
{


    try {
        SInitSystem::load();
        TypeSystemParsing().typeParsing();
    }
    catch ( InitSystemError error ) {
        qWarning() << error.textError();
    }
    catch( TypeSystemError error ) {
        qWarning() << error.textError();
    }



    return 0;

//    QApplication a(argc, argv);
//    Widget w;
//    w.show();
//    return a.exec();
}
