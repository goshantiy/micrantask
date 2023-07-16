#ifndef APP_H
#define APP_H
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "database_manager.h"
#include "database_model.h"
#include "cache_model.h"

class DatabaseTreeApp
{
public:
    DatabaseTreeApp();

private:
    /**
     * @brief Загружает базу данных.
     * @return true, если загрузка базы данных прошла успешно, в противном случае - false.
     */
    bool loadDatabase();

    CacheModel _cacheModel;         /// Модель кэша.
    DatabaseModel _databaseModel;   /// Модель базы данных.
    DatabaseManager _databaseManager;   /// Менеджер базы данных.
    QQmlApplicationEngine _engine;   /// Графический движок приложения.

    QString _dbpath = "db.json";     /// Путь к базе данных.
};

#endif
