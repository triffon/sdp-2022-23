#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<stack>


// Binary unordered tree

template<class T>
struct TreeNode{
    T data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const T, TreeNode<T>*, TreeNode<T>*);
};

template<class T>
TreeNode<T>::TreeNode(const T _data, TreeNode<T>* _left, TreeNode<T>* _right): data{_data}, left{_left}, right{_right} {}

template<class T>
class BinTree {
    TreeNode<T>* root;
    // size_t size;
    void addHelper(TreeNode<T>*, const T, std::string);
    void printHelper(const TreeNode<T>* currentRoot) const {
        if(!currentRoot) {
            return;
        }

        printHelper(currentRoot->left);
        std::cout << currentRoot->data << " ";
        printHelper(currentRoot->right);
    }
    void bfsHelper(const TreeNode<T>*) const;
    void addElementHelper(TreeNode<T>*&, const T&);
    bool isMirrorHelper(const TreeNode<T>*, const TreeNode<T>*);
    void removeHelper(TreeNode<T>*&, const T&);
    public:
    // canonical methods
    BinTree();
    bool empty() const;
    void addElement(const T data, const std::string& path);
    void print() const {
        printHelper(root);
    }
    void bfs() const;
    void dfs() const;
    void addElement(const T&);
    bool isMirror() const; //after insert in binary ordered tree
    void removeElement(const T&); //removes the element and keeps the ordered structure
};

template<class T>
BinTree<T>::BinTree(): root{nullptr} {}

template<class T>
bool BinTree<T>::empty() const { return root == nullptr; }

template<class T>
void BinTree<T>::addElement(const T data, const std::string& path) {
    addHelper(root, data, path);
}

template<class T>
void BinTree<T>::addHelper(TreeNode<T>* current_root, const T data, std::string path){
    if(path.empty() && !current_root) {
        root = new TreeNode<T>{data, nullptr, nullptr};
        return;
    }
    size_t i=0;
    while(path[i+1] != '\0' && current_root){
        if(path[i] == 'L') {
            current_root = current_root->left;
        }
        if(path[i] == 'R') {
            current_root = current_root->right;
        }
        i++;
    }
    if(!current_root) {
        throw std::out_of_range("Invalid path");
    }
    if(path[i] == 'L') {
        current_root->left = new TreeNode<T>{data, current_root->left, nullptr};
    } else {
        current_root->right = new TreeNode<T>{data, nullptr, current_root->right};
    }
}

template<class T>
void BinTree<T>::dfs() const {
    printHelper(root);
}

template<class T>
void BinTree<T>::bfs() const {
    bfsHelper(root);
}

template<class T>
void BinTree<T>::bfsHelper(const TreeNode<T>* currentRoot) const {
    if(!currentRoot) {
        return;
    }

    std::queue<TreeNode<T>*> helperQueue;
    // std::cout << currentRoot ->data << " ";
    helperQueue.push(currentRoot);
    while(!helperQueue.empty()) {
        TreeNode<T>* currentElement = helperQueue.front();
        helperQueue.pop();
        std::cout << currentElement->data << " ";
        // std::cout << currentElement->left->data << " ";
        // std::cout << currentElement->right->data << " ";
        if(currentElement->left) {
            helperQueue.push(currentElement->left);
        }
        if(currentElement->right) {
            helperQueue.push(currentElement->right);
        }
    }
}

// for Binary ordered tree
template<class T>
void BinTree<T>::addElement(const T& data) {
    // if(!root) {
    //      root = new TreeNode<T>{data, nullptr, nullptr};
    // }
    addElementHelper(root, data);
}


template<class T>
void BinTree<T>::addElementHelper(TreeNode<T>*& currentRoot, const T& data) {
    if(!currentRoot) {
        currentRoot = new TreeNode<T>{data, nullptr, nullptr};
        return;
    }
    if(data < currentRoot->data) {
        addElementHelper(currentRoot->left, data);
        // if(currentRoot->left) {
        //     addElementHelper(currentRoot->left, data);
        // } else {
        //     currentRoot->left = new TreeNode<T>{data, nullptr, nullptr};
        // }
    } else {
        addElementHelper(currentRoot->right, data);
        // if(currentRoot->right) {
        //     addElementHelper(currentRoot->right, data);
        // } else {
        //     currentRoot->right = new TreeNode<T>{data, nullptr, nullptr};
        // }
    }
}

template<class T>
bool BinTree<T>::isMirror() const {
    if(!root) {
        return true;
    }

    return isMirrorHelper(root->left, root->right);
}

template <class T>
bool BinTree<T>::isMirrorHelper(const TreeNode<T>* left, const TreeNode<T>* right)
{
    if (left == nullptr && right == nullptr)
    {
        return true;
    }
    if (left == nullptr ^ right == nullptr)
    {
        return false;
    }
    return isMirrorHelper(left->left, right->right) && isMirrorHelper(left->right, right->left);
}

template<class T>
void removeHelper(TreeNode<T>*& currentRoot, const T& data) {

}

/*
 currentRoot -> left -----------> 0x02312321
 addElementHelper(currentRoot) -------> 0x02312321
*/
/*
          20
    15          43
2      19   35     55
*/

// queue: 19 35 55
// console out: 20 15 43 2 ...

int main() {
    BinTree<int> t;
    // t.addElement(1, "");
    // t.addElement(2,"L");
    // t.addElement(3,"R");
    // t.addElement(4, "RR");
    for(auto elem: {50,35,100,21,45,40,46,36,41,60,120,150}) {
        t.addElement(elem);
    }
    t.print();
}