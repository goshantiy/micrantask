#include "cache_model.h"

CacheModel::CacheModel() : BaseTreeModel()
{}

TreeBaseNode *CacheModel::copyNode(TreeBaseNode *sourceNode, TreeBaseNode *parentNode)
{
    if (!sourceNode || _idMap.contains(sourceNode->getId()))
        return nullptr;
    TreeBaseNode *copiedNode = new TreeBaseNode(parentNode);
    copiedNode->setId(sourceNode->getId());
    copiedNode->setValue(sourceNode->getValue());
    copiedNode->setDeleted(sourceNode->isDeleted());
    return copiedNode;
} // copyNode

TreeBaseNode *CacheModel::copyNodeRecursive(TreeBaseNode *sourceNode, TreeBaseNode *parentNode)
{
    qulonglong sourceId = sourceNode->getId();
    TreeBaseNode *existingNode = _idMap.value(sourceId);
    // Если узел уже создан в модели не копируем, а устанавливаем новые связи.
    if (existingNode && parentNode) {
        TreeBaseNode *parent = existingNode->getParent();

        if (!parentNode->getParent()) {
            _rootNode->removeChild(existingNode);
            existingNode->setParent(parentNode);
        } else {
            parent->removeChild(existingNode);
        }
        for (int i = 0; i < sourceNode->childCount(); ++i) {
            TreeBaseNode *sourceChildNode = sourceNode->getChild(i);
            TreeBaseNode *copiedChildNode = copyNodeRecursive(sourceChildNode, existingNode);
            if (copiedChildNode) {
                int row = existingNode->childCount();
                beginInsertRows(getIndex(existingNode), row, row);
                existingNode->addChild(copiedChildNode);
                endInsertRows();
            }
        }
        return existingNode;
    }
    // Копируем узел и устанавливаем связь.
    TreeBaseNode *copiedNode = copyNode(sourceNode, parentNode);
    if (copiedNode) {
        qulonglong mapIndex = copiedNode->getId();
        _idMap[mapIndex] = copiedNode;
        for (int i = 0; i < sourceNode->childCount(); ++i) {
            TreeBaseNode *sourceChildNode = sourceNode->getChild(i);
            TreeBaseNode *copiedChildNode = copyNodeRecursive(sourceChildNode, copiedNode);
            if (copiedChildNode)
                copiedNode->addChild(copiedChildNode);
        }
    }
    return copiedNode;
} // copyNodeRecursive

bool CacheModel::setData(const QModelIndex &index, const QVariant &value)
{
    if (!index.isValid())
        return false;
    TreeBaseNode *node = static_cast<TreeBaseNode *>(index.internalPointer());
    if (!node)
        return false;

    node->setValue(value);

    return true;
} // setData

void CacheModel::receiveSubtree(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;

    TreeBaseNode *sourceNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    if (!sourceNode || sourceNode->isDeleted())
        return;
    beginResetModel();
    TreeBaseNode *copiedRoot = copyNodeRecursive(sourceNode, nullptr);
    if (copiedRoot) {
        // Поиск предка и определение связи.
        TreeBaseNode *sourceParent = sourceNode->getParent();
        qulonglong sourceParentId = sourceParent->getId();
        TreeBaseNode *thisParent = _rootNode;
        QModelIndex modelInsertIndex = QModelIndex();
        if (_idMap.contains(sourceParentId)) {
            thisParent = _idMap[sourceParentId];
        }
        if (thisParent->indexOfChild(copiedRoot) < 0) {
            copiedRoot->setParent(thisParent);
            thisParent->addChild(copiedRoot);
        }
    }
    endResetModel();
} // receiveSubtree

void CacheModel::receiveNode(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;

    TreeBaseNode *sourceNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    if (!sourceNode || sourceNode->isDeleted())
        return;
    TreeBaseNode *copiedNode = copyNode(sourceNode, nullptr);
    if (copiedNode) {
        resolveHierarchy(copiedNode, sourceNode);
    }
} // receiveNode

void CacheModel::resolveHierarchy(TreeBaseNode *copiedNode, const TreeBaseNode *sourceNode)
{
    // Поиск предка и определение связи.
    TreeBaseNode *sourceParent = sourceNode->getParent();
    TreeBaseNode *thisParent = _rootNode;
    int copiedRow = _rootNode->childCount();
    QModelIndex modelInsertIndex = QModelIndex();
    if (sourceParent == nullptr)
        return;

    auto parent = _idMap.find(sourceParent->getId());
    if (parent != _idMap.end()) {
        thisParent = parent.value();
        copiedRow = thisParent->childCount();
        modelInsertIndex = getIndex(thisParent);
    }

    beginInsertRows(modelInsertIndex, copiedRow, copiedRow);

    thisParent->addChild(copiedNode);
    copiedNode->setParent(thisParent);

    qulonglong mapIndex = copiedNode->getId();
    _idMap[mapIndex] = copiedNode;

    endInsertRows();

    // Поиск потомков и определение связей.
    const QList<TreeBaseNode *> sourceChildrens = sourceNode->getChildren();
    if (!sourceChildrens.isEmpty()) {
        for (const auto &it : sourceChildrens) {
            auto child = _idMap.find(it->getId());
            if (child != _idMap.end()) {
                TreeBaseNode *parent = child.value()->getParent();
                QModelIndex parentIndex = getIndex(copiedNode);
                beginMoveRows(QModelIndex(), child.value()->getRow(), child.value()->getRow(),
                              parentIndex, copiedNode->childCount());
                parent->removeChild(child.value());
                child.value()->setParent(copiedNode);
                copiedNode->addChild(child.value());
                endMoveRows();
            }
        }
    }
}//resolveHierarchy

void CacheModel::markDeleted(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;
    TreeBaseNode *sourceNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    sourceNode->setDeleted(!sourceNode->isDeleted());
    layoutChanged();
}//markDeleted

void CacheModel::deleteFromCache(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;
    TreeBaseNode *node = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());

    if (!node)
        return;
    TreeBaseNode *parent = node->getParent();
    beginResetModel();
    if (parent) {
        parent->removeChild(node);
    }

    for (auto it : node->getChildren()) it->setParent(node->getParent());

    _idMap.remove(node->getId());
    clearChildrensFromMap(node);

    delete node;
    endResetModel();
}//deleteFromCache

void CacheModel::clearChildrensFromMap(TreeBaseNode *node)
{
    for (auto it : node->getChildren()) {
        clearChildrensFromMap(it);
        _idMap.remove(it->getId());
    }
}//clearChildrensFromMap

void CacheModel::createNode(const QModelIndex &sourceIndex)
{
    TreeBaseNode *parentNode;
    if (!sourceIndex.isValid())
        parentNode = _rootNode;
    else {
        parentNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    }
    if (!parentNode)
        return;
    if (parentNode->isDeleted())
        return;
    int row = parentNode->childCount();
    beginInsertRows(sourceIndex, row, row);
    TreeBaseNode *newNode = new TreeBaseNode(parentNode);
    qulonglong newNodeId = _idGenerator.generateId();
    newNode->setId(newNodeId);
    newNode->setValue("New Node");
    _idMap[newNodeId] = newNode;
    parentNode->addChild(newNode);
    endInsertRows();
}

void CacheModel::clear()
{
    beginResetModel();
    _idMap.clear();
    delete _rootNode;
    _rootNode = new TreeBaseNode();
    endResetModel();
}

void CacheModel::moveChangesToDatabase()
{
    emit changesMoved(_idMap);
    clear();
}
