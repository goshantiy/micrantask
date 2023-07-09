#ifndef BASE_TREE_MODEL_H
#define BASE_TREE_MODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "database_node.h"
class BaseTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit BaseTreeModel();
    explicit BaseTreeModel(TreeBaseNode* root);
    ~BaseTreeModel() override;
    enum CustomRoles
    {
        IdRole = Qt::UserRole + 1,
        ValueRole,
        DeletedRole
    };
    QModelIndex
    index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setRootNode(TreeBaseNode *);
    void setIdMap(QMap<QUuid, TreeBaseNode *>);
    QModelIndex getIndex(TreeBaseNode *node) const;

protected:
    QMap<QUuid, TreeBaseNode *> _idMap;
    QHash<int, QByteArray> roleNames() const override;
    TreeBaseNode *_rootNode;
};
#endif // BASE_TREE_MODEL_H
