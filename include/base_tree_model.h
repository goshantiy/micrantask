#ifndef BASE_TREE_MODEL_H
#define BASE_TREE_MODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "database_node.h"

class BaseTreeModel
    : public QAbstractItemModel /// Модель дерева для TreeView, реализует базовый функционал.
{
    Q_OBJECT

public:
    explicit BaseTreeModel();
    /**
     * @brief Конструктор, принимающий корневой узел.
     * @param root Корневой узел модели.
     */
    explicit BaseTreeModel(TreeBaseNode *root);
    ~BaseTreeModel() override;
    /**
     * @brief Перечисление с пользовательскими ролями модели.
     */
    enum CustomRoles
    {
        IdRole = Qt::UserRole + 1,
        ValueRole,
        DeletedRole
    };

    /// Переопределение методов модели QAbstractItemModel

    QModelIndex
    index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Устанавливает корневой узел модели.
     * @param root Корневой узел модели.
     */
    void setRootNode(TreeBaseNode *);
    /**
     * @brief Устанавливает словарь хранящий отображение id к узлу.
     * @param idMap Словарь.
     */
    void setIdMap(QMap<qulonglong, TreeBaseNode *>);
    /**
     * @brief Возвращает индекс для указанного узла в модели.
     * @param node Узел.
     * @return Индекс узла.
     */
    QModelIndex getIndex(TreeBaseNode *node) const;

protected:
    QMap<qulonglong, TreeBaseNode *> _idMap; /// Словарь хранящий отображение id к узлу.
    /**
     * @brief Возвращает набор имен ролей модели.
     * @return Набор имен ролей.
     */
    QHash<int, QByteArray> roleNames() const override;
    TreeBaseNode *_rootNode; /// Корневой узел дерева.
};
#endif // BASE_TREE_MODEL_H
