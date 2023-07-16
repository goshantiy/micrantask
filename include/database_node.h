#ifndef DATABASE_NODE_H
#define DATABASE_NODE_H
#include <QString>
#include <QVariant>
#include <QList>
#include <QObject>
#include <QDebug>

class TreeBaseNode /// Базовый узел дерева.
{
public:
    /**
     * @brief Конструктор по умолчанию.
     * @param parent Родительский узел.
     */
    explicit TreeBaseNode(TreeBaseNode *parent = nullptr);
    /**
     * @brief Конструктор с указанием ключа.
     * @param key Ключ узла.
     * @param parent Родительский узел.
     */
    explicit TreeBaseNode(QString, TreeBaseNode *parent);
    /**
     * @brief Конструктор копирования.
     * @param other Другой узел, который копируется.
     */
    explicit TreeBaseNode(const TreeBaseNode &other);
    /**
     * @brief Оператор присваивания.
     * @param other Другой узел, который присваивается.
     * @return Ссылка на текущий узел после присваивания.
     */
    TreeBaseNode &operator=(const TreeBaseNode &);

    // Setters

    /**
     * @brief Устанавливает значение узла.
     * @param value Значение узла.
     */
    void setValue(QVariant);
    /**
     * @brief Устанавливает родительский узел.
     * @param parent Родительский узел.
     */
    void setParent(TreeBaseNode *parent);
    /**
     * @brief Устанавливает флаг удаления узла.
     * @param deleted Флаг удаления узла.
     */
    void setDeleted(bool);
    /**
     * @brief Устанавливает идентификатор узла.
     * @param id Идентификатор узла.
     */
    void setId(qulonglong);

    // Getters

    /**
     * @brief Возвращает значение узла.
     * @return Значение узла.
     */
    QVariant getValue() const;
    /**
     * @brief Возвращает родительский узел.
     * @return Родительский узел.
     */
    TreeBaseNode *getParent() const;
    /**
     * @brief Возвращает дочерний узел по индексу.
     * @param index Индекс дочернего узла.
     * @return Дочерний узел.
     */
    TreeBaseNode *getChild(qulonglong index);
    /**
     * @brief Возвращает список дочерних узлов.
     * @return Список дочерних узлов.
     */
    QList<TreeBaseNode *> getChildren() const;
    /**
     * @brief Возвращает индекс узла относительно родительского узла.
     * @return Индекс узла.
     */
    int getRow() const;
    /**
     * @brief Возвращает идентификатор узла.
     * @return Идентификатор узла.
     */
    qulonglong getId();

    // Child

    /**
     * @brief Добавляет дочерний узел.
     * @param child Дочерний узел.
     */
    void addChild(TreeBaseNode *);
    /**
     * @brief Удаляет дочерний узел.
     * @param child Дочерний узел.
     */
    void removeChild(TreeBaseNode *child);
    /**
     * @brief Возвращает количество дочерних узлов.
     * @return Количество дочерних узлов.
     */
    int childCount() const;
    /**
     * @brief Возвращает индекс указанного узла среди дочерних узлов.
     * @param node Узел, для которого ищется индекс.
     * @return Индекс узла.
     */
    int indexOfChild(TreeBaseNode *node);
    /**
     * @brief Проверяет, является ли узел удаленным.
     * @return true, если узел помочен как удаленный, в противном случае - false.
     */
    bool isDeleted();
    ~TreeBaseNode();

private:
    qulonglong _id; /// Идентификатор узла.
    bool _deleted = false; /// Флаг удаления узла.
    QVariant _value; /// Значение узла.
    QList<TreeBaseNode *> _children; /// Список дочерних узлов.
    TreeBaseNode *_parent = nullptr; /// Родительский узел.
};
#endif // DATABASE_NODE_H
