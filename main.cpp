#include "mainwindow.h"
#include "connection.h"
#include "dialog.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    //for commit
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    bool test=c.createconnect();
    if(test)
    {//w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    Dialog d;

    d.show();
    d.produitOOS();
    return a.exec();
}
