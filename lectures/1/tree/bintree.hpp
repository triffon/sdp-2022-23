#ifndef __BINTREE_HPP
#define __BINTREE_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode *left, *right;

    BinTreeNode(T const& _data = T(), BinTreeNode* _left = nullptr, BinTreeNode* _right = nullptr) : 
        data(_data), left(_left), right(_right) {}
};

template <typename T>
class BinTreePosition {
    BinTreeNode<T>* ptr;
    using P = BinTreePosition<T>;

public:
    BinTreePosition(BinTreeNode<T>* _ptr = nullptr) : ptr(_ptr) {}

    bool valid() const { return ptr != nullptr; }

    operator bool() const { return valid(); }

    P left() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->left;
    }

    P& operator--() {return *this = left(); }
    P operator-() const { return left(); }

    P right() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return ptr->right;
    }

    P& operator++() {return *this = right(); }
    P operator+() const { return right(); }

    T const& get() const {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }

    T const& operator*() const { return get(); }

    T& get() {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return ptr->data;
    }

    T& operator*() { return get(); }

    void erase() {
        if (ptr != nullptr) {
            left().erase();
            right().erase();
            delete ptr;
        }
    } 
};

template <typename T>
class BinTreeMutatingPosition {
    // указател към указателя, който сочи към възела, указващ позицията
    BinTreeNode<T>** ptr;
    using MP = BinTreeMutatingPosition<T>;
    using P = BinTreePosition<T>;
    using N = BinTreeNode<T>;

public:
    BinTreeMutatingPosition(BinTreeNode<T>*& _ptr = nullptr) : ptr(&_ptr) {}

    bool valid() const {
        assert(ptr != nullptr);
        return *ptr != nullptr; }

    operator bool() { return valid(); }

    MP left() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return (*ptr)->left;
    }

    MP operator-() const { return left(); }
    MP& operator--() {return *this = left(); }

    MP right() const {
        if (!valid())
            std::runtime_error("Опит за преместване от невалидна позиция!");
        return (*ptr)->right;
    }

    MP operator+() const { return right(); }
    MP& operator++() {return *this = right(); }

    T const& get() const {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return (*ptr)->data;
    }

    T const& operator*() const { return get(); }

    T& get() {
        if (!valid())
            std::runtime_error("Опит за достъп до данна на невалидна позиция!");
        return (*ptr)->data;
    }

    T& operator*() { return get(); }

    operator P() {
        return P(*ptr);
    } 

    void createLeaf(T const& x) {
        P(*this).erase();
        *ptr = new N(x);
    }

    void transfer(MP other) { 
        // първо, запомняме какво има на тази позиция
        BinTreeNode<T>* save = *ptr;
        // прехвърляме цялото дърво от другата позиция
        *ptr = *other.ptr;
        // нулираме другата позиция
        *other.ptr = nullptr;
        // вече можем да изтрием каквото имаше на тази позиция
        P(save).erase();
    }
};

template <typename T>
class BinTree {
    BinTreeNode<T>* rootNode;
    using N = BinTreeNode<T>;

public:
    using P = BinTreePosition<T>;
    using MP = BinTreeMutatingPosition<T>;

private:
    N* copy(P pos) {
        return pos ? new N(*pos, copy(-pos), copy(+pos)) : nullptr;
    }

public:
    BinTree() : rootNode(nullptr) {}

    BinTree(BinTree const& bt) : rootNode(nullptr) {
        rootNode = copy(bt.root());
    }

    BinTree& operator=(BinTree const& bt) {
        if (this != &bt) {
            root().erase();
            rootNode = copy(bt.root());
        }
        return *this;
    }

    bool operator==(BinTree const& other) const {
        return areEqual(root(), other.root());
    }

    static bool areEqual(P pos1, P pos2) {
        return !pos1 && !pos2 ||
               pos1 && pos2 && *pos1 == *pos2
                    && areEqual(-pos1, -pos2)
                    && areEqual(+pos1, +pos2);
    }

    ~BinTree() {
        root().erase();
    }

    BinTree(T const& root, BinTree&& left = BinTree(), BinTree&& right = BinTree()) {
        rootNode = new BinTreeNode<T>(root, left.rootNode, right.rootNode);
        left.rootNode = right.rootNode = nullptr;
    }

    void print(std::ostream& os = std::cout) const {
        print(os, root());
    }

    void print(std::ostream& os, P pos) const {
        if (!pos.valid())
            os << "()";
        else {
            os << '(' << pos.get() << ' ';
            print(os, pos.left());
            os << ' ';
            print(os, pos.right());
            os << ')';
        }
    }

    void DOTprint(std::ostream& os = std::cout) const {
        os << "digraph tree {" << std::endl;
        DOTprint(os, root());
        os << "}" << std::endl;
    }

    void DOTprint(std::ostream& os, P pos) const {
        for (P child : {-pos, +pos})
            if (child) {
                os << '"' << *pos << "\" -> \"" << *child << "\";" << std::endl;
                DOTprint(os, child);
            }
    }

    unsigned depth() const { return depth(root()); }

    unsigned depth(P pos) const {
        return pos ? 1 + std::max(depth(-pos), depth(+pos)) : 0;
    }

    P root() const { return P(rootNode); }
    MP mutatingRoot() { return MP(rootNode); }
};

#endif