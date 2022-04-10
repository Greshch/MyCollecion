//
// Created by dima on 09.04.2022.
//

#ifndef MYAPP_MYCOLLECTION_H
#define MYAPP_MYCOLLECTION_H

template<typename T>
class MyCollection
{
protected:
    int count = 0;

public:
    int GetCount() const { return count; }

    virtual void Add(T const& t)  = 0;

    virtual void Remove(T const& t) = 0;

    virtual void Print() const = 0;

    virtual bool Search(T const& t) const = 0;

    virtual void Sort() = 0;

    ~MyCollection(){}
};

#endif //MYAPP_MYCOLLECTION_H
