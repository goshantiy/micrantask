#ifndef DATABASE_ID_GENERATOR_H
#define DATABASE_ID_GENERATOR_H
#include <QtGlobal>

class DatabaseIdGenerator /// Генератор идентификаторов для базы данных.
{
public:
    /*!
     * \brief Генерирует уникальный идентификатор.
     * \return Уникальный идентификатор.
     */
    qulonglong generateId();
    void resetId();
    static DatabaseIdGenerator &instance();

private:
    /// Счетчик.
    qulonglong id = 0;
    /// Класс синглтон.
    explicit DatabaseIdGenerator() = default;
    ~DatabaseIdGenerator() = default;
    DatabaseIdGenerator(const DatabaseIdGenerator &) = delete;
    DatabaseIdGenerator &operator=(DatabaseIdGenerator) = delete;
};

#endif // DATABASE_ID_GENERATOR_H
