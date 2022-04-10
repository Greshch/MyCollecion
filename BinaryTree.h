//
// Created by dima on 10.04.2022.
//

#ifndef MYAPP_BINARYTREE_H
#define MYAPP_BINARYTREE_H

#include "MyCollection.h"
#include <iostream>
#include <vector>
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
    virtual void Add(T const& t);
    virtual void Remove(int pos);
    virtual void Print() const;
    virtual bool Search(T const& t) const;
    virtual void Sort();
    ///////////////////////////////////////////////
public:
    bool IsEmpty();

private:
    void Clear();
    void FillFromVector(vector<T> const& vecT);
    ~BinaryTree();
    vector<T> GetVector() const;
};

#endif //MYAPP_BINARYTREE_H
