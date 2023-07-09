#include "database_model.h"
BaseTreeModel::BaseTreeModel() : _rootNode(new TreeBaseNode())
{} // DatabaseModel()
BaseTreeModel::BaseTreeModel(TreeBaseNode *root) : _rootNode(root)
{} // DatabaseModel()
BaseTreeModel::~BaseTreeModel()
{
    delete _rootNode;
} //~DatabaseModel()

QVariant BaseTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    TreeBaseNode *item = static_cast<TreeBaseNode *>(index.internalPointer());

    switch (role) {
    case (IdRole): {
        return QVariant(item->getId());
    }
    case (ValueRole): {
        return QVariant(item->getValue());
    }
    case (DeletedRole): {
        return QVariant(item->isDeleted());
    }
    default:
        return QVariant();
    }
} // data
QHash<int, QByteArray> BaseTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[ValueRole] = "value";
    roles[DeletedRole] = "deleted";
    return roles;
}

QModelIndex BaseTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    TreeBaseNode *parentItem;

    if (!parent.isValid())
        parentItem = _rootNode;
    else
        parentItem = static_cast<TreeBaseNode *>(parent.internalPointer());

    TreeBaseNode *childItem = parentItem->getChild(row);
    if (nullptr != childItem)
        return createIndex(row, column, childItem);
    return QModelIndex {};
}

QModelIndex BaseTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    TreeBaseNode *childItem = static_cast<TreeBaseNode *>(index.internalPointer());
    TreeBaseNode *parentItem = childItem->getParent();

    if (parentItem == _rootNode)
        return QModelIndex();
    return createIndex(parentItem->getRow(), 0, parentItem);
}

int BaseTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeBaseNode *parentItem;

    if (!parent.isValid())
        parentItem = _rootNode;
    else
        parentItem = static_cast<TreeBaseNode *>(parent.internalPointer());
    return parentItem->childCount();
}

int BaseTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

bool BaseTreeModel::hasChildren(const QModelIndex &index) const
{
    if (!index.isValid())
        return false;
    TreeBaseNode *parentItem = static_cast<TreeBaseNode *>(index.internalPointer());
    return parentItem->getChildCount();
}

QModelIndex BaseTreeModel::getIndex(TreeBaseNode *node) const
{
    int row = node->getRow();
    return createIndex(row, 0, node);
}

void BaseTreeModel::setRootNode(TreeBaseNode *root)
{
    _rootNode = root;
}

void BaseTreeModel::setIdMap(QMap<QUuid, TreeBaseNode *> map)
{
    _idMap = map;
}
