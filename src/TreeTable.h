#include "Table.h"
#include <stack>

template <typename Key, typename Value>
class TreeTable : public Table<Key, Value>
{
    typedef typename Table<Key, Value>::Record Record;
    struct TreeNode
    {
        TreeNode* right;
        TreeNode* left;
        Record rec;
    };

    TreeNode* root;
    TreeNode* curr;
    TreeNode* prev;

    size_t level;
    size_t pos; //количество просмотренных элементов
    std::stack<TreeNode*> stack;

    void print(std::ostream& out, TreeNode* node);
    
public:
    virtual bool is_full();

    virtual bool find(Key key);
    virtual bool insert(Key key, Value val);

    //ситуации при удалении
    //узел без потомков нет все удаляется
    //ситуация когда есть потомок (правый больше, левый меньше)
    //ситация когда есть оба потомка
    virtual void del(Key key);

    virtual void reset(); //самый маленький элемент
    virtual void go_next(); //чтобы найти следующий наименьший
    virtual bool is_end();

    virtual Key get_curr_key();
    virtual Value get_curr_val();

    //сериализация дерева
    //рекурсивный метод, печатаем корень, затем его потомков
    void serialize(std::ostream& out);
};

template <typename Key, typename Value>
inline bool TreeTable<Key, Value>::is_full()
{
    return false;
}

template <typename Key, typename Value>
inline bool TreeTable<Key, Value>::find(Key key)
{
    prev = nullptr;
    curr = root;

    while(curr != nullptr)
    {
        (this->eff)++;
        if(curr->rec.key == key)
        {
            return true;
        }
        else if(curr->rec.key < key)
        {
            prev = curr;
            curr = curr->right;
        }
        else
        {
            prev = curr;
            curr = curr->left;
        }
    }
    curr = prev;
    return false;
}

template <typename Key, typename Value>
inline bool TreeTable<Key, Value>::insert(Key key, Value val)
{
    if(find(key))
    {
        return false;
    }
    (this->el_count)++;
    TreeNode* node = new TreeNode {nullptr, nullptr, {key, val} };
    if(curr == nullptr)
    {
        root = node;
    }
    else if(curr->rec.key > key)
    {
        curr->left = node;
    }
    else
    {
        curr->right = node;
    }
    return true;
}

// тесты должны рассмотреть все три случая
// один тест проверяющий последовательное удаление
template <typename Key, typename Value>
inline void TreeTable<Key, Value>::del(Key key)
{
    if(!find(key))
    {
        return;
    }
    
    TreeNode* del_node = curr;
    if(curr->right == nullptr) //один потомок слева у найденного элемента
    {
        if(curr == root)
        {
            root = curr->left;
        }
        else
        {
            if(prev->right == curr)
            {
                prev->right = curr->left;
            }
            else
            {
                prev->left = curr->left;
            }
        }
    }
    else if(curr->left == nullptr) //когда один правый потомок у удаляемого узла
    {
        if(curr == root)
        {
            root = curr->right;
        }
        else
        {
            if(prev->right == curr)
            {
                prev->right = curr->right;
            }
            else
            {
                prev->left = curr->right;
            }
        }
    }
    else //случай когда есть оба наследника
    {
        TreeNode* pN = curr->left;
        prev = curr;
        while(pN->right != nullptr) //поиск наибольшего из меньших(чем удаляемый) элементов
        {
            prev = pN;
            pN = pN->right;
            (this->eff)++;
        }
        curr->rec.key = pN->rec.key;
        curr->rec.val = pN->rec.val;
        if(prev == curr) // не сделано ни одного шага нужно поставить
        {
            curr->left = pN->left;
        }
        else
        {
            prev->right = pN->left; // подставновка на место pN наибольшего из меньших(чем pN)
        }
        del_node = pN;
    }
    delete del_node;
    (this->el_count)--;
}

template <typename Key, typename Value>
inline void TreeTable<Key, Value>::reset()
{
    pos = 0;
    if(root == nullptr) return;
    curr = root;
    while (!stack.empty()) stack.pop();
    //stack.clear();
    while(curr->left != nullptr)
    {
        stack.push(curr);
        curr = curr->left;
    }
    stack.push(curr);
}

template <typename Key, typename Value>
inline void TreeTable<Key, Value>::go_next()
{
    curr = curr->right;
    stack.pop();
    if(curr)
    {
        while(curr->left != nullptr)
        {
            stack.push(curr);
            curr = curr->left;
        }
        stack.push(curr);
    }
    else if(stack.empty() == false)
    {
        curr = stack.top();
    }
    pos++;
}

template <typename Key, typename Value>
inline bool TreeTable<Key, Value>::is_end()
{
    return pos == this->el_count;
}

template <typename Key, typename Value>
inline Key TreeTable<Key, Value>::get_curr_key()
{
    return curr->rec.key;   
}    


template <typename Key, typename Value>
inline Value TreeTable<Key, Value>::get_curr_val()
{
    return curr->rec.val;
}

template <typename Key, typename Value>
inline void TreeTable<Key, Value>::serialize(std::ostream &out)
{
    level = 0;
    print(out, root);
}

template <typename Key, typename Value>
inline void TreeTable<Key, Value>::print(std::ostream &out, TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }

    for(int i =0; i< level; i++)
    {
        out << " ";
    }
    out << node->rec.key << std::endl;
    level++;
    print(out, node->right);
    print(out, node->left);
    level--;
}