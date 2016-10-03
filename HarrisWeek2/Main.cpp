#include <iostream>

#include "MyDoubleLinkedList.h"

using namespace std;

int main()
{
	MyDoubleLinkedList<char, int> myList(false);

	myList.Insert('a', 10);
	myList.PrintCount();
	myList.Insert('b', 15);
	myList.PrintCount();
	myList.Insert('c', 20);
	myList.PrintCount();
	myList.Insert('d', 25);
	myList.PrintCount();

	myList.DebugPrintContents();

	MyNode<char, int>* myNode = myList.FindNode('a');
	if (myNode)
	{
		cout << "Found element! Value: " << myNode->GetData() << "\n";
	}
	myNode = myList.FindNode('e');
	if (!myNode)
	{
		cout << "Didn't find an element!\n\n";
	}

	myNode = myList.GetMaximum();
	if (myNode != NULL)
	{
		cout << "The maximum value is " << myNode->GetData() << " with the key of " << myNode->GetKey() << "\n\n";
	}

	myNode = myList.GetMinimum();
	if (myNode != NULL)
	{
		cout << "The minimum value is " << myNode->GetData() << " with the key of " << myNode->GetKey() << "\n\n";
	}

	myNode = myList.FindNode('c');
	myList.Delete(myNode);
	myList.PrintCount();
	
	myNode = myList.FindNode('b');
	myList.Delete(myNode);
	myList.PrintCount();

	cout << "\n\n";

	myList.DebugPrintContents();

	system("pause");
	return 0;
}