#include <database_model.h>
DatabaseModel::DatabaseModel()
{}

void DatabaseModel::receiveChanges(const QMap<qulonglong, TreeBaseNode *> &changesMap)
{
    QList<TreeBaseNode *> orphanedNodes; // Список хранящий узлы без предков
    beginResetModel();
    // Проходим по словорю изменений и обновляем/создаем новые узлы
    for (const auto &it : changesMap) {
        qulonglong id = it->getId();
        if (_idMap.contains(id)) {
            TreeBaseNode *nodeToUpdate = _idMap.value(id);
            nodeToUpdate->setValue(it->getValue());
            nodeToUpdate->setDeleted(it->isDeleted());
        } else {
            TreeBaseNode *newNode = new TreeBaseNode(*it);
            _idMap[id] = newNode;

            qulonglong parentId = it->getParent()->getId();
            if (_idMap.contains(parentId)) {
                _idMap[parentId]->addChild(newNode);
                newNode->setParent(_idMap[parentId]);
            } else
                orphanedNodes.append(newNode); // Если предок узла ещё не добавлен в словарь,
                                               // откладываем установку связи
        }
    }

    // Проходимся по списку "сирот" и устанавливаем для них предков
    for (TreeBaseNode *node : orphanedNodes) {
        qulonglong parentId = node->getParent()->getId();
        if (_idMap.contains(parentId)) {
            TreeBaseNode *parentNode = _idMap[parentId];
            parentNode->addChild(node);
            node->setParent(parentNode);
        } else {
            _rootNode->addChild(node);
            node->setParent(_rootNode);
        }
    }
    endResetModel();

    emit saveChanges(_rootNode);
    emit clearCache();
} // receiveChanges

void DatabaseModel::receiveOnReset(TreeBaseNode *resetRoot, QMap<qulonglong, TreeBaseNode *> map)
{
    // Устанавливаем данные после сброса базы данных.
    beginResetModel();
    delete _rootNode;
    _idMap.clear();

    _rootNode = new TreeBaseNode();
    _rootNode = resetRoot;

    setIdMap(map);
    endResetModel();
}//receiveOnReset
