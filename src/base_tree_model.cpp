#include "database_model.h"
BaseTreeModel::BaseTreeModel() : _rootNode(new TreeBaseNode())
{} // DatabaseModel()

BaseTreeModel::BaseTreeModel(TreeBaseNode *root)
{
    _rootNode = root;
} // DatabaseModel()

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
        return QVariant(static_cast<qulonglong>(item->getId()));
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
} // data()

QHash<int, QByteArray> BaseTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[ValueRole] = "value";
    roles[DeletedRole] = "deleted";
    return roles;
} // roleNames()

QModelIndex BaseTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeBaseNode *parentItem;

    if (!parent.isValid())
        parentItem = _rootNode;
    else
        parentItem = static_cast<TreeBaseNode *>(parent.internalPointer());

    TreeBaseNode *childItem = parentItem->getChild(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
} // index

QModelIndex BaseTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    TreeBaseNode *childItem = static_cast<TreeBaseNode *>(index.internalPointer());
    TreeBaseNode *parentItem = childItem->getParent();

    if (!parentItem || parentItem == _rootNode)
        return QModelIndex();
    return createIndex(parentItem->getRow(), 0, parentItem);
} // parent

int BaseTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeBaseNode *parentItem;

    if (!parent.isValid())
        parentItem = _rootNode;
    else
        parentItem = static_cast<TreeBaseNode *>(parent.internalPointer());
    return parentItem->childCount();
} // rowCount

int BaseTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
} // columnCount

bool BaseTreeModel::hasChildren(const QModelIndex &index) const
{
    if (!index.isValid())
        return false;
    TreeBaseNode *parentItem = static_cast<TreeBaseNode *>(index.internalPointer());
    return parentItem->childCount();
} // hasChildren

QModelIndex BaseTreeModel::getIndex(TreeBaseNode *node) const
{
    if (!node)
        return QModelIndex();
    return createIndex(node->getRow(), 0, node);
} // getIndex

void BaseTreeModel::setRootNode(TreeBaseNode *root)
{
    delete _rootNode;
    _rootNode = root;
} // setRootNode

void BaseTreeModel::setIdMap(QMap<qulonglong, TreeBaseNode *> map)
{
    _idMap = map;
} // setIdMap
