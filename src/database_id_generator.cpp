#include "database_id_generator.h"

DatabaseIdGenerator &DatabaseIdGenerator::instance()
{
    static DatabaseIdGenerator db;
    return db;
}//instance

qulonglong DatabaseIdGenerator::generateId()
{
    return ++id;
}//generateId

void DatabaseIdGenerator::resetId()
{
    id = 0;
}//resetId
