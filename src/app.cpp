#include "app.h"
DatabaseTreeApp::DatabaseTreeApp()
{
    // move
    QObject::connect(&_databaseModel, &DatabaseModel::moveNode, &_cacheModel,
                     &CacheModel::receiveNode);
    QObject::connect(&_databaseModel, &DatabaseModel::moveSubtree, &_cacheModel,
                     &CacheModel::receiveSubtree);
    // reset
    QObject::connect(&_databaseModel, &DatabaseModel::resetDatabase, &_databaseManager,
                     &DatabaseManager::resetDatabase);
    QObject::connect(&_databaseModel, &DatabaseModel::resetDatabase, &_cacheModel,
                     &CacheModel::clear);
    QObject::connect(&_databaseModel, &DatabaseModel::clearCache, &_cacheModel, &CacheModel::clear);
    // changes
    QObject::connect(&_databaseModel, &DatabaseModel::saveChanges, &_databaseManager,
                     &DatabaseManager::saveChanges);
    QObject::connect(&_cacheModel, &CacheModel::changesMoved, &_databaseModel,
                     &DatabaseModel::receiveChanges);
    QObject::connect(&_databaseManager, &DatabaseManager::sendChanges, &_databaseModel,
                     &DatabaseModel::receiveOnReset);

    QFile file(_dbpath);
    if (!file.exists())
        _databaseManager.InitBaseDatabase(_dbpath);
    if (loadDatabase()) {
        _engine.rootContext()->setContextProperty("databaseModel", &_databaseModel);
        _engine.rootContext()->setContextProperty("cacheModel", &_cacheModel);
        const QUrl url(QStringLiteral("qrc:/qml/databaseviewpage.qml"));
        _engine.load(url);
    }
}

bool DatabaseTreeApp::loadDatabase()
{
    TreeBaseNode *root = _databaseManager.loadJson(_dbpath);
    if (root) {
        _databaseModel.setRootNode(root);
        _databaseModel.setIdMap(_databaseManager.getIdMap());
        return true;
    }
    return false;
}
