#include <iostream>
#include "MyCollection.h"
#include "SingleLinkedList.h"
#include "BinaryTree.h"
using namespace std;

int main()
{
    MyCollection<int>* col = /*new BinaryTree<int>*/ new SingleLinkedList<int>;
    col->Add(5);
    col->Add(2);
    col->Add(7);
    col->Add(1);
    col->Add(3);
    col->Add(6);
    col->Add(8);
    col->Print();
    col->Remove(2);
    col->Print();
    col->Sort();
    col->Print();
    delete col;
    return 0;
}