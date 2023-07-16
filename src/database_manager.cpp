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
    _dbpath = filePath;
    TreeBaseNode *root = parseJson(jsonObject, nullptr);
    return root;
}//loadJson

TreeBaseNode *DatabaseManager::parseJson(const QJsonValue &value, TreeBaseNode *parent)
{
    TreeBaseNode *rootItem = new TreeBaseNode(parent);
    const QJsonObject object = value.toObject();

    if (object.contains("value")) {
        QJsonValue valueJson = object.value("value");
        rootItem->setValue(valueJson.toVariant());
        qulonglong nodeId = _idGenerator.generateId();
        rootItem->setId(nodeId);
        _treeIdMap[nodeId] = rootItem;
    }
    if (object.contains("deleted")) {
        QJsonValue valueJson = object.value("deleted");
        rootItem->setDeleted(valueJson.toBool());
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
void DatabaseManager::saveTreeToJson(const QString &filePath, TreeBaseNode *_rootNode)
{
    QJsonObject rootObject;
    QJsonArray childrenArray;
    QList<TreeBaseNode *> children = _rootNode->getChildren();
    for (const auto &childNode : children) {
        QJsonObject childObject;
        serializeTreeToJson(childObject, childNode);
        childrenArray.append(childObject);
    }
    rootObject["children"] = childrenArray;

    QJsonDocument jsonDoc(rootObject);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    }
}//parseJson

void DatabaseManager::serializeTreeToJson(QJsonObject &jsonObject, TreeBaseNode *node)
{
    QJsonObject nodeObject;
    nodeObject["value"] = node->getValue().toString();
    nodeObject["deleted"] = node->isDeleted();

    if (!node->getChildren().isEmpty()) {
        QJsonArray childrenArray;
        QList<TreeBaseNode *> childrens = node->getChildren();
        for (const auto &childNode : childrens) {
            QJsonObject childObject;
            serializeTreeToJson(childObject, childNode);
            childrenArray.append(childObject);
        }
        nodeObject["children"] = childrenArray;
    }

    jsonObject = nodeObject;
}//serializeTreeToJson

void DatabaseManager::InitBaseDatabase(QString path)
{
    QString base_database = R"(
{
"children":[{
  "value": "Root",
  "children": [
    {
      "value": "Some example text 1 ",
      "children": [
        {
          "value": "Some example text 2",
          "children": [
                {
                "value": "Some example text 3",
                "children": [
                    {
                    "value": "Some example text 4",
                    "children": []
                    }
                ]
                }
                      ]
        },
        {
          "value": "Some example text 5",
          "children": []
        }
      ]
    },
    {
      "value": "Some example text 6",
      "children": []
    }
  ]}
  ]
}
)";

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(base_database.toUtf8());
        _dbpath = path;
    }
}//InitBaseDatabase

void DatabaseManager::saveChanges(TreeBaseNode *node)
{
    saveTreeToJson(_dbpath, node);
}//saveChanges

void DatabaseManager::resetDatabase()
{
    InitBaseDatabase(_dbpath);
    _idGenerator.resetId();
    _treeIdMap.clear();
    TreeBaseNode *root = loadJson(_dbpath);
    emit sendChanges(root, getIdMap());
}//resetDatabase

QMap<qulonglong, TreeBaseNode *> &DatabaseManager::getIdMap()
{
    return _treeIdMap;
}//getIdMap
