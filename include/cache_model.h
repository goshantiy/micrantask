#ifndef CACHE_MODEL_H
#define CACHE_MODEL_H
#include <QModelIndex>
#include <QHash>
#include <QVariant>
#include "database_model.h"

class CacheModel : public BaseTreeModel
{
    Q_OBJECT

public:
    explicit CacheModel();
    Q_INVOKABLE void copySubtree(const QModelIndex &);
    Q_INVOKABLE void copyNode(const QModelIndex &);
    Q_INVOKABLE bool setData(const QModelIndex &index, const QVariant &value);
    Q_INVOKABLE void deleteData(const QModelIndex &index);
    Q_INVOKABLE void createNode(const QModelIndex &);

private:
    void resolveHierarchy(TreeBaseNode *copied, const TreeBaseNode *sourceNode);
    TreeBaseNode *copyNodeRecursive(TreeBaseNode *sourceNode, TreeBaseNode *parentNode = nullptr);
    TreeBaseNode *copyNode(TreeBaseNode *sourceNode, TreeBaseNode *parentNode = nullptr);
};

#endif // CACHE_MODEL_H
