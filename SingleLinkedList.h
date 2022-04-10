//
// Created by dima on 09.04.2022.
//

#ifndef MYAPP_SINGLELINKEDLIST_H
#define MYAPP_SINGLELINKEDLIST_H

#include "MyCollection.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class SingleLinkedList : public MyCollection<T>
{
private:
    struct Node
    {
        T value;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    ///////////////////////////////////////////////
    virtual void Add(T const& t);
    virtual void Remove(T const& t);
    virtual void Print() const;
    virtual bool Search(T const& t) const;
    virtual void Sort();
    ///////////////////////////////////////////////
public:
    bool IsEmpty();

private:
    void Clear();
    void FillFromVector(vector<T> const& vecT);
    ~SingleLinkedList();
    vector<T> GetVector() const;
};

template<typename T>
void SingleLinkedList<T>::Add(const T& t)
{
    Node* cur = new Node{ t, nullptr };
    if (IsEmpty())
    {
        head = tail = cur;
    }
    else
    {
        tail->next = cur;
        tail = cur;
    }
    ++this->count;
}

template<typename T>
bool SingleLinkedList<T>::IsEmpty()
{
    return this->count == 0;;
}

template<typename T>
void SingleLinkedList<T>::Print() const
{
    Node* cur = head;
    for (int i = 0; i < this->count; i++)
    {
        cout << cur->value << " " ;
        if (i && i % 10 == 0)	cout << endl;
        cur = cur->next;
    }
    cout << endl;
}

template<typename T>
bool SingleLinkedList<T>::Search(const T &t) const
{
    Node* cur = head;
    for (int i = 0; i < this->count; i++)
    {
        int val = cur->value;
        if (val == t)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

template<typename T>
void SingleLinkedList<T>::Remove(T const& t)
{
    if (IsEmpty() || !Search(t)) return;
    Node* l = nullptr;
    Node* cur = head;
    Node* r = head->next;
    while (!IsEmpty() && cur != nullptr)
    {
        if (cur->value == t)
        {
            --this->count;
            delete cur;
            cur = nullptr;
            if (l == nullptr) // first element
            {
                head = r;
            }
            else if (r == nullptr) // last element
            {

            }
            else
            {
                l->next = r;
            }
        }
        //cout << cur->value << endl;
        l = cur;
        cur = r;
        if (cur == nullptr) continue;
        r = r->next;
    }
    cout << "\n$$$\n";
}

template<typename T>
void SingleLinkedList<T>::Sort()
{
    vector<T> vecT = GetVector();
    sort(vecT.begin(), vecT.end());
    Clear();
    FillFromVector(vecT);
}

template<typename T>
void SingleLinkedList<T>::Clear()
{
    Node* cur = head;
    this->count = 0;
    for (int i = 0; i < this->count; i++)
    {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    head = tail = nullptr;
}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    Clear();
}

template<typename T>
vector<T> SingleLinkedList<T>::GetVector() const
{
    vector<T> res;
    Node* cur = head;
    int result = -1;
    for (int i = 0; i < this->count; i++)
    {
        int val = cur->value;
        res.push_back(val);
        cur = cur->next;
    }
    return res;
}

template<typename T>
void SingleLinkedList<T>::FillFromVector(const vector<T> &vecT)
{
    for (auto const& e : vecT)
    {
        this->Add(e);
    }
}


#endif //MYAPP_SINGLELINKEDLIST_H
