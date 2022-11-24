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

Node* mergeLists( Node* head1, Node* head2 )
{
	Node* resultList = nullptr;
	if ( head1 && head2 )
	{
		if ( head1->fData < head2->fData )
		{
			resultList = new Node { head1->fData, nullptr };
			head1 = head1->fpNext;
		}
		else
		{
			resultList = new Node { head2->fData, nullptr };
			head2 = head2->fpNext;
		}
	}
	Node* aheadIt = resultList;
	Node* currentIt = resultList;
	while ( head1 != nullptr && head2 != nullptr )
	{
		if ( head1->fData < head2->fData )
		{
			aheadIt = new Node { head1->fData, nullptr };
			head1 = head1->fpNext;
		}
		else
		{
			aheadIt = new Node { head2->fData, nullptr };
			head2 = head2->fpNext;
		}
		currentIt->fpNext = aheadIt;
		currentIt = currentIt->fpNext;
	}
	
	while ( head1 )
	{
		aheadIt = new Node { head1->fData, nullptr };
		currentIt->fpNext = aheadIt;
		currentIt = currentIt->fpNext;
		head1 = head1->fpNext;
	}
	while ( head2 )
	{
		aheadIt = new Node { head2->fData, nullptr };
		currentIt->fpNext = aheadIt;
		currentIt = currentIt->fpNext;
		head2 = head2->fpNext;
	}

	return resultList;
}

Node* mergeLists1( Node* head1, Node* head2 )
{
	Node* resultList = nullptr;
	Node* forward = head2;
	Node* current = head2;
	while ( forward->fData < head1->fData )
	{
		current = forward;
		forward = forward->fpNext;
	}
	if ( forward != head2 )
	{
		resultList = head2;
		current->fpNext = head1;
		head2 = forward;
	}
	else
	{
		resultList = head1;
	}
	
	while ( head2 )
	{
		if ( head1 && head1->fData <= head2->fData && head1->fpNext && head2->fData <= head1->fpNext->fData )
		{
			Node* ahead = head1->fpNext;
			head1->fpNext = head2;
			head1 = head1->fpNext;
			Node* currentNode = head2->fpNext;
			head2->fpNext = ahead;
			head2 =  currentNode;
		}
		else if ( head1 && head1->fpNext )
		{
			head1 = head1->fpNext;
		}
		else if ( head1 && !head1->fpNext )
		{
			head1->fpNext = head2;
			break;
		}
	}

	return resultList;
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

int main()
{
	Node* head1 = new Node{ 2
				, new Node{ 2
				, new Node{ 4
				, new Node{ 7
				, new Node{ 11
				, new Node{ 12
				, new Node{ 17
				, new Node{ 21, nullptr } } } } } } } };

	Node* head2 = new Node{ -4
				, new Node{ -3
				, new Node{ -1
				, new Node{ 0
				, new Node{ 0
				, new Node{ 5
				, new Node{ 7
				, new Node{ 10
				, new Node{ 17
				, new Node{ 37, nullptr } } } } } } } } } };

	std::cout << "First list: ";
	printList( head1 );
	std::cout << "Second list: ";
	printList( head2 );

	std::cout << "Merging..." << std::endl;
	Node* newList = mergeLists1( head1, head2 );

	std::cout << "The result list is: " << std::endl;
	printList( newList );

	deleteList( head1 );

	return 0;
}