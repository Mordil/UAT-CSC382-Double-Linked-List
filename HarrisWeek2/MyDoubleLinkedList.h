#pragma once

#include <vector>
#include <string>

#include "MyNode.h"

template<typename K, typename V>
class MyDoubleLinkedList
{
	typedef MyNode<K, V> Node;

public:
	/*
		Initializes an empty list.
		allowDuplicates = only add new nodes if the key is unique
	*/
	MyDoubleLinkedList(bool allowsDuplicates) : _rootNode(NULL), _allowDuplicates(allowsDuplicates) { }
	~MyDoubleLinkedList() { delete _rootNode; }

	/* Inserts a new node in the list with the provided key and value. */
	void Insert(const K& key, const V& value)
	{
		// if duplicates are allowed, just add the node
		if (_allowDuplicates)
		{
			_addNode(key, value);
		}
		else
		{
			// otherwise search for the node
			Node* nodeToUpdate = FindNode(key);

			// if the node doesn't exist, add it
			if (nodeToUpdate == NULL)
			{
				_addNode(key, value);
			}
			else
			{
				// otherwise, update it
				nodeToUpdate->SetData(value);
			}
		}
	}

	/*
		I wouldn't structure the methods the way that they are, but given that the assignment calls out this specific signature, I have implemented the Delete
		method by accepting a pointer address and comparing addresses.
		If I was writing this for production, I would accept a key, or a value, or both to compare to see if it's the node, as there's too many scenarios to handle from being passed a pointer.
	*/

	/* Deletes the node if it exists in the array. */
	void Delete(Node*& nodeToDelete)
	{
		// Find the node matching the passed node's key
		Node* node = FindNode(nodeToDelete->GetKey());
		
		// if the node exists in the list
		if (nodeToDelete == node)
		{
			// grab its previous & next nodes
			Node* nextNode = node->GetNext();
			Node* previousNode = node->GetPrevious();

			// link the two together
			nextNode->SetPrevious(previousNode);
			previousNode->SetNext(nextNode);

			// delete the data in this list and decrement the counter
			delete node;
			_nodeCount--;
		}
	}
	
	/* Prints the current size of the list to the console. */
	void PrintCount() { std::cout << "The current size: " << to_string(_nodeCount) << "\n"; }

	/* Iterates through the list and prints the address of each item in the list, as well as the addresses of their next/previous nodes. */
	void DebugPrintContents()
	{
		Node* node = _rootNode;
		while (node != NULL)
		{
			std::cout << "Node with address: " << node;
			Node* previousAddress = node->GetPrevious();
			Node* nextAddress = node->GetNext();

			if (previousAddress != NULL)
			{
				std::cout << " has the previous address of " << previousAddress;
			}

			if (nextAddress != NULL)
			{
				std::cout << " and the next address of " << nextAddress;
			}

			std::cout << "\n";

			if (node->GetNext() == _rootNode)
			{
				node = NULL;
			}
			else
			{
				node = node->GetNext();
			}
		}

		std::cout << "\n\n";
	}
	
	/* Returns a pointer to a Node if one exists with the provided key, or a pointer to NULL otherwise. */
	Node* FindNode(const K& key) { return _findNode(key, _rootNode); }

	/*
		I know the extra credit specified the max/min KEYS, but I thought it made more sense to compare VALUES.
	*/

	/* Returns a pointer to a Node with the maximum value in the list, or a pointer to NULL otherwise. */
	Node* GetMaximum() { return _compareNodeValues(true); }

	/* Returns a pointer to a Node with the minimum value in the list, or a pointer to NULL otherwise. */
	Node* GetMinimum() { return _compareNodeValues(false); }

private:
	bool _allowDuplicates = false;
	int _nodeCount = 0;

	Node* _rootNode;

	void _addNode(const K& key, const V& value)
	{
		if (_rootNode == NULL)
		{
			_rootNode = new Node(key, value);
			_nodeCount++;
			return;
		}

		Node* previousNode = _rootNode;
		Node* endNode = _rootNode->GetNext();

		if (endNode == NULL)
		{
			Node* newNode = new Node(key, value);
			newNode->SetPrevious(previousNode);
			newNode->SetNext(previousNode);

			previousNode->SetPrevious(newNode);
			previousNode->SetNext(newNode);
			_nodeCount++;
			return;
		}
		else
		{
			while (endNode->GetNext() != _rootNode)
			{
				previousNode = endNode;
				endNode = endNode->GetNext();
			}

			// create the node and attach it to the old end node
			endNode->SetNext(new Node(key, value));
			// grab a pointer address to the new node
			Node* newNode = endNode->GetNext();

			// set the new node's previous and next
			newNode->SetPrevious(endNode);
			newNode->SetNext(_rootNode);

			_rootNode->SetPrevious(newNode);

			_nodeCount++;
		}
	}

	Node* _findNode(const K& key, Node*& startingNode)
	{
		if (startingNode == NULL)
		{
			return startingNode;
		}
		else if (startingNode->GetKey() != key)
		{
			Node* nextNode = startingNode->GetNext();

			if (nextNode == _rootNode)
			{
				return NULL;
			}

			return _findNode(key, nextNode);
		}
		else
		{
			return startingNode;
		}
	}

	Node* _compareNodeValues(bool greaterThanComparison)
	{
		Node* node = _rootNode;
		Node* maxValueNode = (_rootNode == NULL) ? NULL : _rootNode;

		while (node != NULL)
		{
			if (greaterThanComparison)
			{
				if (node->GetData() > maxValueNode->GetData())
				{
					maxValueNode = node;
				}
			}
			else
			{
				if (node->GetData() < maxValueNode->GetData())
				{
					maxValueNode = node;
				}
			}

			Node* nextNode = node->GetNext();

			if (nextNode == _rootNode)
			{
				node = NULL;
			}
			else
			{
				node = nextNode;
			}
		}

		return maxValueNode;
	}
};
