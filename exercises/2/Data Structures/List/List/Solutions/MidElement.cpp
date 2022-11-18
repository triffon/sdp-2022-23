#include <iostream>


struct Node
{
	int fData;
	Node* fpNext;

};

void deleteList( Node* head )
{
	while ( head )
	{
		Node* temp = head->fpNext;
		delete head;
		head = temp;
	}
}


void printList( Node* head )
{
	while ( head )
	{
		Node* temp = head->fpNext;
		std::cout << head->fData << " ";
		head = temp;
	}
	std::cout << std::endl;
}

Node* middleElement( Node* head )
{
	Node* slowPtr = head;
	Node* fastPtr = head;

	while ( fastPtr && fastPtr->fpNext )
	{
		slowPtr = slowPtr->fpNext;
		fastPtr = fastPtr->fpNext->fpNext;
	}

	return slowPtr;
}

int main()
{
	Node* head  = new Node{ -4
				, new Node{ -3
				, new Node{ -1
				, new Node{ 0
				, new Node{ 1
				, new Node{ 2
				, new Node{ 5
				, new Node{ 7
				, new Node{ 10
				, new Node{ 17
				, new Node{ 37, nullptr } } } } } } } } } } };

	printList( head );

	Node* mid = middleElement( head );
	std::cout << "middle element is: " << mid->fData << std::endl;
	
	
	deleteList( head );
	return 0;
}