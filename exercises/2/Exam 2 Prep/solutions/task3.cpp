#include <iostream>

template <typename T>
struct Node
{
    T       fData   = T();
    Node*   fpLeft  = nullptr;
    Node*   fpRight = nullptr;
};

template <typename T>
void eraseTree(Node<T>*& pTree);

// a)
Node<char>* buildTree(const std::string& str)
{
    if ( str.empty() )
        return nullptr;

    size_t  mid  = str.length() / 2;

    Node<char>* pNode   = new Node<char>{ str[mid] };
    pNode->fpLeft       = buildTree( str.substr( 0, mid ) );
    pNode->fpRight      = buildTree( str.substr( mid + 1 ) );

    return pNode;
}


// b)
void getMaxStringRec(const Node<char>* pRoot, char c
                    , int currCnt, std::string& currStr
                    , int& maxCnt, std::string& outMaxStr);


std::string getMaxString(const Node<char>* pRoot, char c)
{
    std::string currStr;
    std::string resMaxStr;
    int maxCnt = 0;
    getMaxStringRec( pRoot, c, 0, currStr, maxCnt, resMaxStr );
    return resMaxStr;
}


void getMaxStringRec(const Node<char>* pRoot, char c
                    , int currCnt, std::string& currStr
                    , int& maxCnt, std::string& outMaxStr)
{
    if ( pRoot != nullptr )
    {
        // on first visit of a node - add it to the current string
        currStr.push_back( pRoot->fData );

        if ( pRoot->fData )
            currCnt++;  // local variable (only changes its value in this function)

        getMaxStringRec( pRoot->fpLeft, c, currCnt, currStr, maxCnt, outMaxStr );
        getMaxStringRec( pRoot->fpRight, c, currCnt, currStr, maxCnt, outMaxStr );

        // after we are done with that node, on return from the recursive calls
        // - remove it from the current string
        currStr.pop_back();
    }
    else
    {
        // reached end of tree (reached after each leaf)
        if ( currCnt > maxCnt )
        {
            maxCnt      = currCnt;
            outMaxStr   = currStr;
        }
    }
}


int main()
{
	// TODO: test

	return 0;
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
