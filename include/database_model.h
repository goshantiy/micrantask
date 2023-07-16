#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H
#include "base_tree_model.h"

class DatabaseModel : public BaseTreeModel /// Модель представления базы данных.
{
    Q_OBJECT
public:
    explicit DatabaseModel();
signals:
    /*!
     * \brief Сигнал, отправляемый при загрузке узла в кеш.
     * \param sourceIndex Индекс исходного узла.
     */
    void moveNode(const QModelIndex &sourceIndex);
    /*!
     * \brief Сигнал, отправляемый при загрузке поддерева в кеш.
     * \param sourceIndex Индекс исходного узла.
     */
    void moveSubtree(const QModelIndex &sourceIndex);
    /*!
     * \brief Сигнал, отправляемый при сохранении изменений.
     * \param node Узел, содержащий изменения.
     */
    void saveChanges(TreeBaseNode *);
    /*!
     * \brief Сигнал, отправляемый менеджеру о сбросе базы данных.
     */
    void resetDatabase();
    /*!
     * \brief Сигнал, отправляемый кешу о очистке.
     */
    void clearCache();
public slots:
    /*!
     * \brief Слот, принимающий изменения и обновляющий модель.
     * \param changesMap Словарь, содержащий изменения.
     */
    void receiveChanges(const QMap<qulonglong, TreeBaseNode *> &changesMap);
    /*!
     * \brief Слот, устанавливающий новый корень дерева после сброса базы данных.
     * \param resetRoot Корень дерева.
     * \param map Словарь хранящий отображение id->узел.
     */
    void receiveOnReset(TreeBaseNode *resetRoot, QMap<qulonglong, TreeBaseNode *> map);
};

#endif // DATABASE_MODEL_H
