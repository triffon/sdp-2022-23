#include<iostream>
#include<vector>
#include<string>


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
    void printHelper(const TreeNode*& currentRoot) {
        if(!currentRoot) {
            return;
        }
        printHelper(currentRoot->left);
        std::cout << currentRoot->data;
        printHelper(currentRoot->right);
    }
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
    void addElement(const T);
    bool isMirror() const; //after insert in binary ordered tree
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

int main() {
    BinTree<int> t;
    t.addElement(1, "");
    t.addElement(2,"L");
    t.addElement(3,"R");
    t.addElement(4, "RR");
}