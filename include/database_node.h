#ifndef DATABASE_NODE_H
#define DATABASE_NODE_H
#include <QString>
#include <QVector>
#include <QPointer>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QUuid>
class TreeBaseNode
{
public:
    explicit TreeBaseNode(TreeBaseNode *parent = nullptr);
    explicit TreeBaseNode(QString, TreeBaseNode *parent);
    explicit TreeBaseNode(const TreeBaseNode &other);
    TreeBaseNode &operator=(const TreeBaseNode &);
    // set
    void setValue(QVariant);
    void setKey(QString key);
    void setParent(TreeBaseNode *parent);
    void setDeleted(bool);
    void setId(QUuid);
    // get
    QString getKey();
    QVariant getValue() const;
    TreeBaseNode *getParent() const;
    TreeBaseNode *getChild(size_t index);
    QVector<TreeBaseNode *> getChildren() const;
    int getRow() const;
    QUuid getId();
    int getChildCount();
    // child
    void addChild(TreeBaseNode *);
    void removeChild(TreeBaseNode *child);
    int childCount() const;
    int indexOfChild(TreeBaseNode *node);

    bool isDeleted();
    ~TreeBaseNode();

private:
    QUuid _id;
    bool _deleted = false;
    QVariant _value;
    QString _key;
    QVector<TreeBaseNode *> _children;
    TreeBaseNode *_parent = nullptr;
};
#endif // DATABASE_NODE_H
