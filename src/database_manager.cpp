#include "database_manager.h"
TreeBaseNode *DatabaseManager::loadJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: read file";
        return nullptr;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull()) {
        qDebug() << "Error: null document";
        return nullptr;
    }

    QJsonObject jsonObject = jsonDoc.object();
    if (jsonObject.isEmpty()) {
        qDebug() << "Error: empty document";
        return nullptr;
    }
    TreeBaseNode *document_root = new TreeBaseNode(nullptr);
    TreeBaseNode *root = new TreeBaseNode(document_root);

    root = parseJson(jsonObject, root);
    document_root->addChild(root);
    return document_root;
}
TreeBaseNode *DatabaseManager::parseJson(const QJsonValue &value, TreeBaseNode *parent)
{
    TreeBaseNode *rootItem = new TreeBaseNode(parent);
    const QJsonObject object = value.toObject();

    if (object.contains("value")) {
        QJsonValue valueJson = object.value("value");
        rootItem->setValue(valueJson.toVariant());
        QUuid nodeId = generateId();
        rootItem->setId(nodeId);
        _treeIdMap[nodeId] = rootItem;
    }

    if (object.contains("children")) {
        QJsonValue childrenJson = object.value("children");
        const QJsonArray childrenArray = childrenJson.toArray();
        for (const QJsonValue &childValue : childrenArray) {
            TreeBaseNode *childNode = parseJson(childValue, rootItem);
            rootItem->addChild(childNode);
            childNode->setParent(rootItem);
        }
    }
    return rootItem;
}
QUuid DatabaseManager::generateId()
{
    return QUuid::createUuid();
}
QMap<QUuid, TreeBaseNode *> &DatabaseManager::getIdMap()
{
    return _treeIdMap;
}
