#include "mainwindow.h"

#include <QApplication>
#include "QFile"
#include "QDebug"

int main(int argc, char *argv[])
{
//    QFile file("data/actors/new_naive_actor.txt");
//    file.open(file.ReadOnly);
//    QTextStream in(&file);
//    QString s;
//    in >> s;
//    qDebug() << s;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
