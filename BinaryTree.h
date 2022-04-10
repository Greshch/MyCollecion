//
// Created by dima on 10.04.2022.
//

#ifndef MYAPP_BINARYTREE_H
#define MYAPP_BINARYTREE_H

#include "MyCollection.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

template<typename T>
class BinaryTree : public MyCollection<T>
{
private:
    struct Node
    {
        T _val;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root = nullptr;


public:
    ///////////////////////////////////////////////
    virtual void Add(T const& t) override;
    virtual void Remove(T const& t) override;
    void Print() const override;
    virtual bool Search(T const& t) const override;
    virtual void Sort() override; // random shufle
    ///////////////////////////////////////////////
public:
    bool IsEmpty();

private:
    void PrintStack() const;
    void AddStack(T const& t);
    void Clear()
    {
        ClearStack();
    }
    void ClearStack();
    void FillFromVector(vector<T> const& vecT);
    bool IsList(Node* node) const;
    Node* SearchStack(T const& value) const
    {
        stack<Node*> repo;
        repo.push(root);
        while (!repo.empty())
        {
            Node* tmp = repo.top();
            if (tmp != nullptr)
            {
                repo.pop();
                int val = tmp->_val;
                if (val == value)
                {
                    return tmp;
                }
                if (value < val)
                {
                    repo.push(tmp->left);
                }
                else
                {
                    repo.push(tmp->right);
                }
            }
            else
            {
                return nullptr;
            }
        }
    }
    Node* RighterThenNode(Node* node) const
    {
        stack<Node*> repo;
        repo.push(node);
        while (!repo.empty())
        {
            Node* tmp = repo.top();
            if (tmp != nullptr)
            {
                repo.pop();
                if (tmp->right != nullptr)
                {
                    repo.push(tmp->right);
                }
                else
                {
                    return tmp;
                }
            }
            else
            {
                return tmp->parent;
            }
        }
        return nullptr;
    }
    Node* LefterThenNode(Node* node) const
    {
        stack<Node*> repo;
        repo.push(node);
        while (!repo.empty())
        {
            Node* tmp = repo.top();
            if (tmp != nullptr)
            {
                repo.pop();
                if (tmp->left != nullptr)
                {
                    repo.push(tmp->left);
                }
                else
                {
                    return tmp;
                }
            }
            else
            {
                return tmp->parent;
            }
        }
        return nullptr;
    }
    ~BinaryTree()
    {
        Clear();
    }
    vector<T> GetVector() const;
};

template<typename T>
void BinaryTree<T>::ClearStack()
{
    if (root == nullptr)
    {
        return;
    }
    stack<Node*> repo;
    repo.push(root);
    while (!repo.empty())
    {
        Node* tmp = repo.top();
        if (tmp != nullptr)
        {
            repo.pop();
            if (tmp->left != nullptr)
            {
                repo.push(tmp->left);
            }
            if (tmp->right != nullptr)
            {
                repo.push(tmp->right);
            }
            //cout << "#" << tmp->_val << endl;
            delete tmp;
            tmp = nullptr;
        }
    }
    root = nullptr;
}

template<typename T>
void BinaryTree<T>::Print() const
{
    PrintStack();
    cout << endl;
}

template<typename T>
void BinaryTree<T>::PrintStack() const
{
    if (root == nullptr)
    {
        return;
    }
    stack<Node*> repo;
    repo.push(root);
    while (!repo.empty())
    {
        Node* tmp = repo.top();
        if (tmp != nullptr)
        {
            repo.pop();
            int val = tmp->_val;
            cout << val << (IsList(tmp) ? "^ " : " ");
            if (tmp->left != nullptr)
            {
                repo.push(tmp->left);
            }
            if (tmp->right != nullptr)
            {
                repo.push(tmp->right);
            }
        }
    }
}

template<typename T>
void BinaryTree<T>::AddStack(T const& value)
{
    ++this->count;
    if (root == nullptr)
    {
        Node* neo_node = new Node{ value };
        root = neo_node;
        return;
    }
    stack<Node*> repo;
    repo.push(root);
    bool left = false;
    Node* prev = root;
    while (!repo.empty())
    {
        Node* tmp = repo.top();
        if (tmp != nullptr)
        {
            repo.pop();
            T val = tmp->_val;
            if (val == value)
            {
                return;
            }
            if (value < val)
            {
                left = true;
                repo.push(tmp->left);
            }
            else
            {
                left = false;
                repo.push(tmp->right);
            }
        }
        else
        {
            Node* neo_node = new Node{ value, prev };
            if (left)
            {
                prev->left = neo_node;
            }
            else
            {
                prev->right = neo_node;
            }
            return;
        }
        prev = tmp;
    }
}

template<typename T>
void BinaryTree<T>::Add(const T &t)
{
    AddStack(t);
}

template<typename T>
bool BinaryTree<T>::IsList(Node* node) const
{
    if (node == nullptr)
    {
        return false;
    }
    return node->left == nullptr && node->right == nullptr;
}

template<typename T>
void BinaryTree<T>::Remove(T const& val)
{
    Node* tmp = SearchStack(val);
    if (tmp == nullptr)
    {
        return;
    }

    if (tmp == root)
    {
        vector<T> vec = GetVector();
        //vec.Print();
        random_shuffle(vec.begin(), vec.end());
        int sz = vec.size();
        Clear();
        for (int i = 0; i < sz; i++)
        {
            this->Add(vec[i]);
        }
        return;
    }

    Node* prev = tmp->parent;
    if (IsList(tmp))
    {
        if (prev->left == tmp)
        {
            prev->left = nullptr;
        }
        else
        {
            prev->right = nullptr;
        }
        return;
    }

    if (tmp->left != nullptr)
    {
        Node* rb = RighterThenNode(tmp->left);
        tmp->_val = rb->_val;
        if (tmp->left == rb)
        {
            if (IsList(rb))
            {
                tmp->left = nullptr;
            }
            else
            {
                rb->left->parent = tmp;
                tmp->left = rb->left;
            }
        }
        else
        {
            rb->parent->right = rb->left;
            if (rb->left != nullptr)
            {
                rb->left->parent = rb->parent;
            }
        }
        delete rb;
    }
    else if (tmp->right != nullptr)
    {
        Node* lb = LefterThenNode(tmp->right);
        tmp->_val = lb->_val;
        if (tmp->right == lb)
        {
            if (IsList(lb))
            {
                tmp->right = nullptr;
            }
            else
            {
                lb->right->parent = tmp;
                tmp->right = lb->right;
            }
        }
        else
        {
            lb->parent->left = lb->right;
            if (lb->right != nullptr)
            {
                //rb->parent->right = rb->left;
                lb->right->parent = lb->parent;
            }
        }
        delete lb;
    }
}

template<typename T>
bool BinaryTree<T>::Search(T const& val) const
{
    return SearchStack(val);
}

template<typename T>
void BinaryTree<T>::Sort()
{
    srand(time(0));
    vector<T> vals = GetVector();
    Clear();
    random_shuffle(vals.begin(), vals.end());
    for (auto const& e : vals)
    {
        Add(e);
    }
}

template<typename T>
vector<T> BinaryTree<T>::GetVector() const
{
    vector<T> res;
    stack<Node*> repo;
    repo.push(root);
    while (!repo.empty())
    {
        Node* tmp = repo.top();
        if (tmp != nullptr)
        {
            repo.pop();
            int val = tmp->_val;
            res.push_back(val);
            if (tmp->left != nullptr)
            {
                repo.push(tmp->left);
            }
            if (tmp->right != nullptr)
            {
                repo.push(tmp->right);
            }
        }
    }
    return res;
}


#endif //MYAPP_BINARYTREE_H
