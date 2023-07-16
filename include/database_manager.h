#ifndef DATABASE_LOADER_H
#define DATABASE_LOADER_H
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QMap>
#include "database_node.h"
#include "database_id_generator.h"

class DatabaseManager
    : public QObject /// Менеджер базы данных, отвечающий за работу с файловой системой.
{
    Q_OBJECT
public:
    /*!
     * \brief Загружает JSON-файл и создает дерево узлов.
     * \brief filePath Путь к JSON-файлу.
     * \return Указатель на корневой узел дерева или nullptr.
     */
    TreeBaseNode *loadJson(const QString &filePath);
    /*!
     * \brief Рекурсивно разбирает JSON-значение и создает соответствующие узлы.
     * \brief jsonValue JSON-значение, которое разбирается.
     * \brief parentNode Родительский узел, к которому добавляются созданные узлы.
     * \return Указатель на корневой узел дерева.
     */
    TreeBaseNode *parseJson(const QJsonValue &, TreeBaseNode * = nullptr);
    /*!
     * \brief Возвращает ссылку на словарь узлов.
     * \return Ссылка на словарь узлов.
     */
    QMap<qulonglong, TreeBaseNode *> &getIdMap();
    /*!
     * \brief Инициализирует базу данных.
     * \brief dbPath Путь к базе данных.
     */
    void InitBaseDatabase(QString);
public slots:
    /*!
     * \brief Сохраняет изменения в указанном узле в базу данных.
     * \brief node Узел, содержащий изменения.
     */
    void saveChanges(TreeBaseNode *node);
    /*!
     * \brief Сбрасывает базу данных к базовым значениям.
     */
    void resetDatabase();
signals:
    /*!
     * \brief Сигнал, отправляющий новый корень дерева.
     */
    void sendChanges(TreeBaseNode *, QMap<qulonglong, TreeBaseNode *> _treeIdMap);

private:
    /*!
     * \brief Сохраняет дерево в формате JSON в указанный файл.
     * \brief filePath Путь к файлу, в который сохраняется JSON.
     * \brief _rootNode Корневой узел дерева.
     */
    void saveTreeToJson(const QString &filePath, TreeBaseNode *_rootNode);
    /*!
     * \brief Рекурсивно сериализует узел и его дочерние узлы в JSON-объект.
     * \brief jsonObject JSON-объект, в который сериализуется узел.
     * \brief node Узел, который сериализуется.
     */
    void serializeTreeToJson(QJsonObject &jsonObject, TreeBaseNode *node);

    QMap<qulonglong, TreeBaseNode *>
     _treeIdMap; /// Словарь, хранящий отображение идентификаторов на узлы.
    QString _dbpath; /// Путь к базе данных.

    DatabaseIdGenerator &_idGenerator = DatabaseIdGenerator::instance(); /// Синглтон генератор id.
};

#endif // DATABASE_LOADER_H
