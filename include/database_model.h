#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H
#include <base_tree_model.h>
class DatabaseModel : public BaseTreeModel
{
    Q_OBJECT
public:
    explicit DatabaseModel(TreeBaseNode* root);
};

#endif // DATABASE_MODEL_H
