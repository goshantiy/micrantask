#include <QGuiApplication>
#include <QStandardItemModel>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "app.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    DatabaseTreeApp test;
    return app.exec();
}
