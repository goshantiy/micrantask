#include "cache_model.h"

CacheModel::CacheModel() : BaseTreeModel()
{}
TreeBaseNode *CacheModel::copyNode(TreeBaseNode *sourceNode, TreeBaseNode *parentNode)
{
    if (!sourceNode)
        return nullptr;

    TreeBaseNode *copiedNode = new TreeBaseNode(parentNode);
    copiedNode->setId(sourceNode->getId());
    copiedNode->setKey(sourceNode->getKey());
    copiedNode->setValue(sourceNode->getValue());
    return copiedNode;
}
TreeBaseNode *CacheModel::copyNodeRecursive(TreeBaseNode *sourceNode, TreeBaseNode *parentNode)
{
    TreeBaseNode *copiedNode = copyNode(sourceNode, parentNode);
    QUuid mapIndex = copiedNode->getId();
    _idMap[mapIndex] = copiedNode;
    for (int i = 0; i < sourceNode->childCount(); ++i) {
        TreeBaseNode *sourceChildNode = sourceNode->getChild(i);
        TreeBaseNode *copiedChildNode = copyNodeRecursive(sourceChildNode, copiedNode);
        if (copiedChildNode)
            copiedNode->addChild(copiedChildNode);
    }

    return copiedNode;
}
bool CacheModel::setData(const QModelIndex &index, const QVariant &value)
{
    if (!index.isValid())
        return false;
    TreeBaseNode *node = static_cast<TreeBaseNode *>(index.internalPointer());
    if (!node)
        return false;

    node->setValue(value);

    return true;
}

void CacheModel::copySubtree(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;

    TreeBaseNode *sourceNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    if (!sourceNode || sourceNode->isDeleted())
        return;
    TreeBaseNode *copiedNode = copyNodeRecursive(sourceNode, _rootNode);
    if (copiedNode) {
        int copiedRow = _rootNode->getRow();
        beginInsertRows(QModelIndex(), copiedRow, copiedRow);
        _rootNode->addChild(copiedNode);
        endInsertRows();
    }
}
void CacheModel::resolveHierarchy(TreeBaseNode *copiedNode, const TreeBaseNode *sourceNode)
{
    TreeBaseNode *sourceParent = sourceNode->getParent();
    int copiedRow = _rootNode->getChildCount();
    QModelIndex modelinsertindex = QModelIndex();
    if (sourceParent == nullptr)
        return;
    auto parent = _idMap.find(sourceParent->getId());
    if (parent != _idMap.end()) {
        copiedRow = parent.value()->getChildCount();
        modelinsertindex = getIndex(parent.value());
    }

    beginInsertRows(modelinsertindex, copiedRow, copiedRow);

    if (parent != _idMap.end()) {
        copiedNode->setParent(parent.value());
        parent.value()->addChild(copiedNode);
    } else {
        _rootNode->addChild(copiedNode);
        copiedNode->setParent(_rootNode);
    }
    QUuid mapIndex = copiedNode->getId();
    _idMap[mapIndex] = copiedNode;

    endInsertRows();

    const QVector<TreeBaseNode *> sourceChildrens = sourceNode->getChildren();
    if (!sourceChildrens.isEmpty()) {
        for (const auto &it : sourceChildrens) {
            auto child = _idMap.find(it->getId());
            if (child != _idMap.end()) {
                TreeBaseNode *parent = child.value()->getParent();
                QModelIndex parentIndex = getIndex(copiedNode);
                beginMoveRows(QModelIndex(), child.value()->getRow(), child.value()->getRow(),
                              parentIndex, copiedNode->childCount() - 1);
                parent->removeChild(child.value());
                child.value()->setParent(copiedNode);
                copiedNode->addChild(child.value());
                endMoveRows();
            }
        }
        layoutChanged();
    }
}
void CacheModel::copyNode(const QModelIndex &sourceIndex)
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
}

void CacheModel::deleteData(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;
    TreeBaseNode *sourceNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    sourceNode->setDeleted(!sourceNode->isDeleted());
    layoutChanged();
}

void CacheModel::createNode(const QModelIndex &sourceIndex)
{
    if (!sourceIndex.isValid())
        return;
    TreeBaseNode *parentNode = static_cast<TreeBaseNode *>(sourceIndex.internalPointer());
    if (!parentNode)
        return;
    int newRow = parentNode->getChildCount();
    beginInsertRows(sourceIndex, newRow, newRow);
    TreeBaseNode *newNode = new TreeBaseNode(parentNode);

    QUuid newNodeId = QUuid::createUuid();
    newNode->setId(newNodeId);
    _idMap[newNodeId] = newNode;

    parentNode->addChild(newNode);
    endInsertRows();
}
