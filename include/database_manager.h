#ifndef DATABASE_LOADER_H
#define DATABASE_LOADER_H
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QMap>
#include "database_node.h"
class DatabaseManager
{
public:
    TreeBaseNode *loadJson(const QString &filePath);
    TreeBaseNode *parseJson(const QJsonValue &, TreeBaseNode * = nullptr);
    QMap<QUuid, TreeBaseNode *> &getIdMap();

private:
    QUuid generateId();
    QMap<QUuid, TreeBaseNode *> _treeIdMap;
};

#endif // DATABASE_LOADER_H
