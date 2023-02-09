// Задача 1. Напишете функция която приема един аргумент – корен на дърво, 
// чиито възли могат да имат произволен брой деца. Всеки възел пази стойност -- цяло число.
//
// Функцията трябва да намери онзи път от корена на дървото, до някое листо, който има най-малка 
// сума на елементите в него. Този път трябва да се върне, като вектор от възлите в него. 
// Ако има няколко такива пътя, може да се върне който и да е от тях. Напишете кратка програма, 
// която демонстрира работата на функцията върху примерно дърво. По-долу са дадени представянето 
// на дървото и прототипът на функцията, която трябва да реализирате. Те трябва да са точно такива, 
// както са показани тук.
//
// struct Node {
//    int value;
//    std::vector<Node> children;
// };
//
// std::vector<Node*> findCheapestPath( Node* root )

#include <iostream>
#include <vector>

struct Node {
    int value;
    std::vector<Node> children;
};

void findCheapestRec(
    Node* pNode,                    // current node
    int currSum,                    // current path sum
    std::vector<Node*>& currPath,   // the "global" path currently taken
    int& outMinSum,                 // the current minumum path sum
    std::vector<Node*>& outMinPath )// the current minumum path
{
    if ( !pNode )
        return;

    // First step: Calculate the current path and sum
    currSum += pNode->value;
    currPath.push_back( pNode );

    if ( pNode->children.empty() )
    {
        // Base: The node is a leaf
        if ( currSum < outMinSum )
        {
            outMinPath  = currPath;
            outMinSum   = currSum;
        }
    }
    else
    {
        // General case: Traverse the children
        for ( size_t i = 0; i < pNode->children.size(); i++ )
        {
            Node& child = pNode->children[ i ];

            findCheapestRec( &child, currSum, currPath, outMinSum, outMinPath );
        }
    }

    // Last step: Remove the currently visited node from our "global" path
    currPath.pop_back();

    // The above `for loop` can be written as a `range-based for loop` like so:
    // for ( Node& child : root->children )
    // {
    //    findCheapestRec( &child, currSum, currPath, outMinSum, outMinPath );
    // }
}

std::vector<Node*> findCheapestPath( Node* root )
{
    if ( !root )
        return {};

    std::vector<Node*>  currPath;
    std::vector<Node*>  minPath;
    int minSum = std::numeric_limits<int>::max();   // largest number an int can hold

    findCheapestRec( root, 0, currPath, minSum, minPath );

    return minPath;
}

int main()
{
    Node root = 
        Node { 5, {
                Node{ 8, {} },
                Node{ 0 , {} },
                Node{ 11, {} }
            } };

    // You can also add children like this:
    //root.children.push_back( Node { 8, {} } );
    //root.children[ 0 ].children.push_back( Node { 2, {} } );

    std::vector<Node*> vec = findCheapestPath( &root );

    for ( size_t i = 0; i < vec.size(); i++ )
        std::cout << vec[ i ]->value << ' ';

    // Note: All nodes are allocated on the stack, the heap was not used
    // for the represantation of the nodes -> no need to delete anything.

	return 0;
}
