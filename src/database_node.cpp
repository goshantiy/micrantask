#include "database_node.h"
TreeBaseNode::TreeBaseNode(TreeBaseNode *parent) : _parent(parent)
{}

TreeBaseNode::TreeBaseNode(QString value, TreeBaseNode *parent) : _value(value), _parent(parent)
{} // DatabaseNode()

TreeBaseNode::TreeBaseNode(const TreeBaseNode &other) :
    _deleted(other._deleted), _value(other._value), _key(other._key), _parent(other._parent)
{
    for (TreeBaseNode *child : other._children) {
        TreeBaseNode *clonedChild = new TreeBaseNode(*child);
        clonedChild->setParent(this);
        _children.append(clonedChild);
    }
} // DatabaseNode()

TreeBaseNode &TreeBaseNode::operator=(const TreeBaseNode &other)
{
    if (this != &other) {
        _deleted = other._deleted;
        _value = other._value;
        _key = other._key;
        _id = other._id;

        for (TreeBaseNode *child : qAsConst(_children)) {
            delete child;
        }
        _children.clear();
        for (TreeBaseNode *child : other._children) {
            TreeBaseNode *clonedChild = new TreeBaseNode(*child);
            clonedChild->setParent(this);
            _children.append(clonedChild);
        }
    }
    return *this;
} // operator =
int TreeBaseNode::childCount() const
{
    return _children.size();
} // childCount()

TreeBaseNode *TreeBaseNode::getChild(size_t index)
{
    if (index < _children.size())
        return _children[index];

    return nullptr;
} // getChild

QVector<TreeBaseNode *> TreeBaseNode::getChildren() const
{
    return _children;
} // child()

int TreeBaseNode::indexOfChild(TreeBaseNode *node)
{
    return _children.indexOf(node);
} // indexOfChild()

void TreeBaseNode::addChild(TreeBaseNode *child)
{
    _children.append(child);
} // addChild()

int TreeBaseNode::getRow() const
{
    if (nullptr != _parent)
        return _parent->_children.indexOf(const_cast<TreeBaseNode *>(this));

    return 0;
} // getRow

QUuid TreeBaseNode::getId()
{
    return _id;
} // getId

int TreeBaseNode::getChildCount()
{
    return _children.size();
} // getChildCount()

bool TreeBaseNode::isDeleted()
{
    return _deleted;
} // isDeleted()

void TreeBaseNode::removeChild(TreeBaseNode *child)
{
    auto ix = indexOfChild(child);
    if (ix >= 0) {
        // delete _children[ix];
        _children.remove(indexOfChild(child));
    }
} // removeChild

void TreeBaseNode::setDeleted(bool deleted)
{
    if (_deleted == deleted)
        return;
    _deleted = deleted;
    for (auto &it : _children) it->setDeleted(deleted);
} // setDeleted

void TreeBaseNode::setId(QUuid id)
{
    _id = id;
} // setId

QString TreeBaseNode::getKey()
{
    return _key;
} // removeChild()
void TreeBaseNode::setValue(QVariant value)
{
    _value = value;
} // setValue

void TreeBaseNode::setKey(QString key)
{
    _key = key;
} // setKey

void TreeBaseNode::setParent(TreeBaseNode *parent)
{
    _parent = parent;
} // setParent
QVariant TreeBaseNode::getValue() const
{
    return _value;
} // getValue()

TreeBaseNode *TreeBaseNode::getParent() const
{
    return _parent;
} // getParent()

TreeBaseNode::~TreeBaseNode()
{
    qDeleteAll(_children);
} //~DatabaseNode()
