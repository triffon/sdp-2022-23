#ifndef __NODE_H
#define __NODE_H
#pragma once

#include <string>
#include <sstream>

template <typename T>
struct Node
{
    T       fData   = T();
    Node*   fpLeft  = nullptr;
    Node*   fpRight = nullptr;
};

template <typename T>
std::string printTree(const Node<T>* pTree)
{
    std::stringstream sout;
    if ( pTree != nullptr )
    {
        sout << '(';
        sout << pTree->data;
        sout << printTree( pTree->left );
        sout << printTree( pTree->right );
        sout << ')';
    }
    else
    {
        sout << '.';
    }

    return sout.str();
}

template <typename T>
void eraseTree(Node<T>*& pTree)
{
    if ( pTree != nullptr )
    {
        eraseTree( pTree->left );
        eraseTree( pTree->right );
        delete pTree;
        pTree = nullptr;
    }
}

#endif
