#include "Table.h"
#include <stack>
template <typename Key, typename Value>
class AVLTreeTable : public Table<Key, Value>
{
protected:
    typedef typename Table<Key,Value>::Record Record;

    enum HEIGHT
    {
        H_OK = 0,
        H_INC = 1,
        H_DEC = -1
    };
    enum BALANCE
    {
        LEFT = -1,
        OK,
        RIGHT
    };

    struct Node
    {
        Record rec;
        Node* left;
        Node* right;
        BALANCE balance;
    };

    Node* root;
    Node* curr , *prev;
    //возвращают показатель изменения высоты
    int left_balance(Node*& node, bool insert = true);
    int right_balance(Node*& node, bool insert = true);

    //повороты
    int ll_shift(Node*& node, bool insert = true);
    int lr_shift(Node*& node, bool insert = true);
    int rr_shift(Node*& node, bool insert = true);
    int rl_shift(Node*& node, bool insert = true);

    int insert_rec(Node*& node, Key key, Value val);
    int del_rec(Node*& node, Key key); 
    Node* find_min(Node* node);

    int remove_min(Node*& node); //исключает узел из дерева (физически он остается)
    
    size_t level;
    size_t pos; //количество просмотренных элементов
    std::stack<Node*> stack;

    void print(std::ostream& out, Node* node);

    void remove_tree(Node* node);
public:
    AVLTreeTable();
    ~AVLTreeTable();
    virtual bool is_full() { return false; };

    //алгоритмы рекурсивные
    virtual bool find(Key key);
    virtual bool insert(Key key, Value val); //если глубина увеличилась нудно запускать балансировку по той же стороне
    virtual void del(Key key); // если слева глубина уменьшилоась нужно запускать противополжную балансировку

    //при удалении вершины с двумя потомками нужно найти минимальный элемент справа или максимальный слева
    //

    virtual void reset();
    virtual void go_next();
    virtual bool is_end();

    virtual Key get_curr_key();
    virtual Value get_curr_val();
    void serialize(std::ostream& out);
};

template<typename Key, typename Value>
inline AVLTreeTable<Key, Value>::AVLTreeTable(): stack()
{
    root = nullptr;
}

template<typename Key, typename Value>
inline AVLTreeTable<Key, Value>::~AVLTreeTable()
{
    remove_tree(root);
}

template<typename Key, typename Value>
inline bool AVLTreeTable<Key, Value>::find(Key key)
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

template<typename Key, typename Value>
inline bool AVLTreeTable<Key, Value>::insert(Key key, Value val)
{
    if(find(key))
    {
        return false;
    }
    insert_rec(root, key, val);
    this->el_count++;
    return true;
}

template<typename Key, typename Value>
inline void AVLTreeTable<Key, Value>::del(Key key)
{
    if(this->is_empty() || !find(key))
    {
        return;
    }
    del_rec(root, key);
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::left_balance(Node *&node, bool insert)
{
    int res = HEIGHT::H_OK;
    if(insert)
    {
        switch (node->balance)
        {
            case RIGHT:
                node->balance = BALANCE::OK;
                res = HEIGHT::H_OK;
                break;
            case OK:
                node->balance = BALANCE::LEFT;
                res = HEIGHT::H_INC;
                break;
            case LEFT: //ll балансировка
                if(node->left->balance == BALANCE::LEFT)
                    res = ll_shift(node, insert);
                else //lr балансировка
                    res = lr_shift(node, insert);
                break;
        }
    }
    else //случай удаления
    {   //все тоже самое только константа результата где было ок станет уменьшаться
        switch (node->balance)
        {
            case RIGHT:
                node->balance = BALANCE::OK;
                res = HEIGHT::H_DEC;
                break;
            case OK:
                node->balance = BALANCE::LEFT;
                res = HEIGHT::H_OK;
                break;
            case LEFT: //ll балансировка
                if(node->left->balance != BALANCE::RIGHT)
                    res = ll_shift(node, insert);
                else //lr балансировка
                    res = lr_shift(node, insert);
                break;
        }
    }
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::right_balance(Node *&node, bool insert)
{
    int res = HEIGHT::H_OK;
    if(insert)
    {
        switch (node->balance)
        {
            case OK:
                node->balance = BALANCE::RIGHT;
                res = HEIGHT::H_INC;
                break;
            case LEFT:
                node->balance = BALANCE::OK; 
                res = HEIGHT::H_OK;
                break;
            case RIGHT: //rr балансировка
                if(node->right->balance == BALANCE::RIGHT)
                    res = rr_shift(node, insert);
                else //rl балансировка
                    res = rl_shift(node, insert);
                break;
        }
    }
    else //случай удаления
    {
        switch (node->balance)
        {
            case OK:
                node->balance = BALANCE::RIGHT;
                res = HEIGHT::H_OK;
                break;
            case LEFT:
                node->balance = BALANCE::OK; 
                res = HEIGHT::H_DEC;
                break;
            case RIGHT: //rr балансировка
                if(node->right->balance != BALANCE::LEFT)
                    res = rr_shift(node, insert);
                else //rl балансировка
                    res = rl_shift(node, insert);
                break;
        }
    }
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::ll_shift(Node*& node, bool insert)
{
    int res = HEIGHT::H_OK;
    Node* l_chld = node->left;
    node->left = l_chld->right;
    l_chld->right = node;
    if(insert)
    {
        node->balance = BALANCE::OK;
        l_chld->balance = BALANCE::OK;
        res = HEIGHT::H_OK;
    }
    else
    {
        if(l_chld->balance == BALANCE::OK)
        {
            node->balance = BALANCE::LEFT;
            l_chld->balance = BALANCE::RIGHT;
            res = HEIGHT::H_OK;
        }
        else
        {
            node->balance = BALANCE::OK;
            l_chld->balance = BALANCE::OK;
            res = HEIGHT::H_DEC;
        }
    }
       
    node = l_chld;
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::lr_shift(Node*& node, bool insert)
{
    int res = insert ? HEIGHT::H_OK : HEIGHT::H_DEC;
    Node* l_chld = node->left;
    Node* lr_chld = l_chld->right;
    //перестановка поддеревьев
    node->left = lr_chld->right;
    l_chld->right = lr_chld->left;
    //перестановка нового корня
    lr_chld->right = node;
    lr_chld->left = l_chld;

    //корректировка баланса
    if(lr_chld->balance == BALANCE::LEFT)
    {
        node->balance = BALANCE::RIGHT;
        l_chld->balance = BALANCE::OK;
    }
    else if(lr_chld->balance == BALANCE::RIGHT)
    {
        node->balance = BALANCE::OK;
        l_chld->balance = BALANCE::LEFT;
    }
    else
    {
        node->balance = BALANCE::OK;
        l_chld->balance = BALANCE::OK;
    }
    lr_chld->balance = BALANCE::OK;
    node = lr_chld;
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::rr_shift(Node*& node, bool insert)
{
    int res =HEIGHT::H_OK;
    Node* r_chld = node->right;
    node->right = r_chld->left;
    r_chld->left = node;
    if(insert)
    {
        node->balance = BALANCE::OK;
        r_chld->balance = BALANCE::OK;
        res = HEIGHT::H_OK;
    }
    else 
    {
        if(r_chld->balance == BALANCE::OK)
        {
            node->balance = BALANCE::RIGHT;
            r_chld->balance = BALANCE::LEFT;
            res = HEIGHT::H_OK;
        }
        else
        {
            node->balance = BALANCE::OK;
            r_chld->balance = BALANCE::OK;
            res = HEIGHT::H_DEC;
        }
    }
    
    node = r_chld;
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::rl_shift(Node*& node, bool insert)
{
    int res = (insert) ? HEIGHT::H_OK : HEIGHT::H_DEC;
    Node* r_chld = node->right;
    Node* rl_chld = r_chld->left;
    /*
        корень получает левое поддерево
        правый потомок получает правое поддерево
        корень становится левым потомком
        правый потомок становится вершиной праваого поддерева
        корнем дерева становится правый-левый потомок
    */
    node->right = rl_chld->left;
    r_chld->left = rl_chld->right;
    rl_chld->right = r_chld;
    rl_chld->left = node;

    if(rl_chld->balance == BALANCE::LEFT)
    {
        node->balance = BALANCE::OK;
        r_chld->balance = BALANCE::RIGHT;
    }
    else if(rl_chld->balance == BALANCE::RIGHT)
    {
        node->balance = BALANCE::LEFT;
        r_chld->balance = BALANCE::OK;
    }
    else
    {
        node->balance = BALANCE::OK;
        r_chld->balance = BALANCE::OK;
    }

    rl_chld->balance = BALANCE::OK;
    node =rl_chld;
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::insert_rec(Node *&node, Key key, Value val)
{
    int res = HEIGHT::H_OK;

    if(node == nullptr)
    {
        node = new Node { {key, val}, nullptr, nullptr, BALANCE::OK };
        res = HEIGHT::H_INC;
    }
    else if(node->rec.key > key)
    {
        int tmp = insert_rec(node->left, key, val);
        if(tmp == HEIGHT::H_INC)
            res = left_balance(node);
    }
    else
    {
        int tmp = insert_rec(node->right, key, val);
        if(tmp == HEIGHT::H_INC)
        {
            res = right_balance(node);
        }
    }
    return res;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::del_rec(Node *&node, Key key)
{

    int res = HEIGHT::H_OK;
    (this->eff)++;
    if(node == nullptr)
    {
        return res;
    }

    if(node->rec.key < key)
    {
        int tmp = del_rec(node->right, key);
        if(tmp != HEIGHT::H_OK)
        {
            res = left_balance(node, false);
        }
    }
    else if(node->rec.key > key)
    {
        int tmp = del_rec(node->left, key); 
        if(tmp != HEIGHT::H_OK)
        {
            res = right_balance(node, false);
        }
    }
    else 
    {
        (this->el_count)--;
        //удаление листа без потомков
        if(node->left == nullptr && node->right == nullptr)
        {
            delete node;
            node = nullptr;
            res = HEIGHT::H_DEC;
        }
        else if(node->left == nullptr) //есть только правый потомок
        {
            node->rec = node->right->rec;
            delete node->right;
            node->right = nullptr;
            node->balance = BALANCE::OK;
            res = HEIGHT::H_DEC;
        }
        else if(node->right == nullptr) { // есть только левый потомок
            node->rec = node->left->rec;
            delete node->left;
            node->left = nullptr;
            node->balance = BALANCE::OK;
            res = HEIGHT::H_DEC;
        }
        else // есть 2 потомка
        { 
            /*
                находим самый маленький элемент правого поддерева
                сохраняем его значение
                удаляем этот элемент
                балансируем дерево
            */
            Node* left = node->left; //можно опустить 
            Node* right = node->right;
        
            Node* min = find_min(right);
            res = remove_min(right); //тут есть правая балнсировка

            node->rec = min->rec; 
            delete min;

            node->right = right;
            node->left = left; //можно опустить

            if(res != HEIGHT::H_OK) //значит элемент найден перым проходом и балансировки в методе удаление не происходило
            {
                res = left_balance(node, false);
            }
        }
    }
    return res;
}

template <typename Key, typename Value>
inline AVLTreeTable<Key, Value>::Node* 
    AVLTreeTable<Key, Value>::find_min(Node *node)
{
    while(node->left != nullptr)
    {
        (this->eff)++;
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
inline int AVLTreeTable<Key, Value>::remove_min(Node*& node)
{
    (this->eff)++;
    int res = HEIGHT::H_OK;
    if(node->left == nullptr)
    {
        node = node->right;
        res = HEIGHT::H_DEC;
    }
    else 
    {
        res = remove_min(node->left);
        if(res != HEIGHT::H_OK)
        {
            res = right_balance(node, false); //так как удалили левый элемент
        }
    }
    
    return res;
}

template <typename Key, typename Value>
inline void AVLTreeTable<Key, Value>::reset()
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
inline void AVLTreeTable<Key, Value>::go_next()
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
inline bool AVLTreeTable<Key, Value>::is_end()
{
    return pos == this->el_count;
}

template <typename Key, typename Value>
inline Key AVLTreeTable<Key, Value>::get_curr_key()
{
    return curr->rec.key;   
}    


template <typename Key, typename Value>
inline Value AVLTreeTable<Key, Value>::get_curr_val()
{
    return curr->rec.val;
}

template <typename Key, typename Value>
inline void AVLTreeTable<Key, Value>::serialize(std::ostream &out)
{
    level = 0;
    print(out, root);
}

template <typename Key, typename Value>
inline void AVLTreeTable<Key, Value>::print(std::ostream &out, Node *node)
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

template <typename Key, typename Value>
inline void AVLTreeTable<Key, Value>::remove_tree(Node *node)
{
    if(node)
    {
        remove_tree(node->right);
        remove_tree(node->left);
        delete node;
    }

}