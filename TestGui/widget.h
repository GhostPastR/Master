#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget( QWidget *parent = nullptr );
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void slotReadOutput();
    void slotReadError();
    void slotError( QProcess::ProcessError error );

private:
    Ui::Widget *ui;
    QProcess *processTest_;

    void writeFile();
};

#endif // WIDGET_H
