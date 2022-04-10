#include <iostream>
#include "MyCollection.h"
#include "SingleLinkedList.h"
using namespace std;

int main()
{
    MyCollection<int>* col = new SingleLinkedList<int>;
    /*for (int i = 0; i < 5; ++i)
    {
        col->Add(i + 1);
    }*/
    col->Add(1);
    col->Add(2);
    col->Add(3);
    col->Add(2);
    col->Add(4);
    col->Print();
    col->Remove(2);
    col->Print();
    delete col;
    return 0;
}