#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->processTest_ = new QProcess( this );
    connect( this->processTest_, SIGNAL(readyReadStandardOutput()),
             this, SLOT(slotReadOutput()) );
    connect( this->processTest_, SIGNAL(readyReadStandardError()),
             this, SLOT(slotReadError()) );
    connect( this->processTest_, SIGNAL(errorOccurred(QProcess::ProcessError)),
             this, SLOT(slotError(QProcess::ProcessError)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    this->writeFile();
    QString _pathProgram( "C:/Qt/Qt5.11.3/Tools/mingw530_32/bin/g++" );
    QStringList _arg;
    _arg << "-o" << "C:/Test/test.exe" << "C:/Test/main.cpp";
    QProcess *_process = new QProcess( this );
    _process->start( _pathProgram, _arg );
    if( !_process->waitForStarted() )
        qDebug() << "Error process!";
    if( _process->waitForFinished() )
    {
        _pathProgram = "C:/Test/test.exe";
        this->processTest_->start( _pathProgram, QStringList() );
        if( !this->processTest_->waitForStarted() )
            qDebug() << "Error processTest!";
        this->processTest_->waitForFinished();
    }
}

void Widget::slotReadOutput()
{
    auto _result = this->processTest_->readAllStandardOutput();
    if( this->processTest_->waitForFinished() )
    {
        QFile _file( "C:/Test/log.txt" );
        if( !_file.open( QIODevice::WriteOnly ) )
            qDebug() << "Error open file!";
        _file.write( _result );
        _file.close();
    }
    else
        qDebug() << "11";
}

void Widget::slotReadError()
{
    if( this->processTest_->waitForFinished() )
    {
        auto _result = this->processTest_->readAllStandardError();
        qDebug() << _result;
    }
}

void Widget::slotError( QProcess::ProcessError error )
{
    qDebug() << error;
}

void Widget::writeFile()
{
    QFile _file( "C:/Test/main.cpp" );
    if( !_file.open( QIODevice::WriteOnly ) )
        qDebug() << "Error open file main.cpp";

    QString _text;
    _text += "#include <iostream>\n\n";
    _text += "int main()\n";
    _text += "{\n";
    _text += "\tint mas[10];\n";
    _text += "\tfor( int i = 0; i < 10; i++ )\n";
    _text += "\t{\n";
    _text += "\t\tmas[i] = i;\n";
    _text += "\t\tstd::cout << mas[i] << std::endl;\n";
    _text += "\t}\n";
    _text += "\treturn 0;\n";
    _text += "}\n";

    _file.write( _text.toLocal8Bit() );
    _file.close();
}












