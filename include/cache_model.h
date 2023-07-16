#ifndef CACHE_MODEL_H
#define CACHE_MODEL_H
#include <QModelIndex>
#include <QHash>
#include <QVariant>
#include "database_model.h"
#include "database_id_generator.h"

class CacheModel : public BaseTreeModel /// Модель представления кеша базы данных.
{
    Q_OBJECT

signals:
    /*!
     * \brief Сигнал, отправляемый базе данных при перемещении изменений
     * \param map Словарь узлов, содержащие изменения.
     */
    void changesMoved(const QMap<qulonglong, TreeBaseNode *> &map);
public slots:
    /*!
     * \brief Слот, принимающий поддерево для обновления модели.
     * \param index Индекс корня поддерева, которое нужно добавить.
     */
    void receiveSubtree(const QModelIndex &);
    /*!
     * \brief Слот, принимающий узел для обновления модели.
     * \param index Индекс элемента, который добавляется в модель.
     */
    void receiveNode(const QModelIndex &);
    /*!
     * \brief Слот, принимающий узел для обновления модели.
     * \param index Индекс элемента, который добавляется в модель.
     */
public:
    explicit CacheModel();
    /*!
     * \brief Устанавливает данные для указанного индекса.
     * \param index Индекс элемента, для которого устанавливаются данные.
     * \param value Значение данных.
     * \return true, если данные были успешно установлены, в противном случае - false.
     */
    Q_INVOKABLE bool setData(const QModelIndex &, const QVariant &);
    /*!
     * \brief Помечает указанный элемент как удаленный.
     * \param index Индекс элемента, который помечается как удаленный.
     */
    Q_INVOKABLE void markDeleted(const QModelIndex &);
    /*!
     * \brief Создает новый узел в кэше.
     * \param index Индекс родительского элемента, к которому добавляется новый узел.
     */
    Q_INVOKABLE void createNode(const QModelIndex &);
    /*!
     * \brief Удаляет элемент из кэша.
     * \param index Индекс элемента, который удаляется из кэша.
     */
    Q_INVOKABLE void deleteFromCache(const QModelIndex &);
    /*!
     * \brief Очищает кэш.
     */
    Q_INVOKABLE void clear();
    /*!
     * \brief Перемещает изменения из кэша в базу данных.
     */
    Q_INVOKABLE void moveChangesToDatabase();

private:
    /*!
     * \brief Разрешает иерархию между узлами.
     * \param copied Скопированный узел, для которого разрешается иерархия.
     * \param sourceNode Исходный узел, из которого копируется иерархия.
     */
    void resolveHierarchy(TreeBaseNode *copied, const TreeBaseNode *sourceNode);
    /*!
     * \brief Рекурсивно копирует узел и его дочерние узлы.
     * \param sourceNode Исходный узел, который копируется.
     * \param parentNode Родительский узел, к которому добавляется копия.
     * \return Указатель на скопированный узел.
     */
    TreeBaseNode *copyNodeRecursive(TreeBaseNode *sourceNode, TreeBaseNode *parentNode = nullptr);
    /*!
     * \brief Копирует узел и его дочерние узлы.
     * \param sourceNode Исходный узел, который копируется.
     * \param parentNode Родительский узел, к которому добавляется копия.
     * \return Указатель на скопированный узел.
     */
    TreeBaseNode *copyNode(TreeBaseNode *sourceNode, TreeBaseNode *parentNode = nullptr);
    /*! \brief Вспомогательный метод для удаления всех потомков из словаря узлов.
     *  \param node Целевой узел.
     */
    void clearChildrensFromMap(TreeBaseNode *node);
    DatabaseIdGenerator &_idGenerator = DatabaseIdGenerator::instance(); /// Синглтон генератор id.
};

#endif // CACHE_MODEL_H
