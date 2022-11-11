#include<iostream>
#include<stdexcept>
#include<vector>

template<class T>
class LList{
    struct Node{
        T data;
        Node* next;
        Node(const T&, Node*);
    };
    Node* start;
    Node* last;
    size_t listSize;

    public:
    class ListIterator {
        Node* current;

        public:
        ListIterator(Node*);
        bool operator !=(const ListIterator&);
        T operator*();
        ListIterator& operator++();
    };

    LList();
    void addElement(const T&);
    void addAfter(const T&, const size_t&);
    size_t size() const;
    bool empty() const;
    void print() const;
    ListIterator begin() const;
    ListIterator end() const;
};

template<class T>
LList<T>::ListIterator::ListIterator(Node* _pos): current{_pos} {}

template<class T>
bool LList<T>::ListIterator::operator!=(const LList<T>::ListIterator& other) {
    return current != other.current;
}

template<class T>
T LList<T>::ListIterator::operator*(){
    return current->data;
}
template<class T>
typename LList<T>::ListIterator& LList<T>::ListIterator::operator++() {
    if(current) {
        current = current->next;
    }

    return *this;
}

template<class T>
LList<T>::Node::Node(const T& _data, Node* _next): data{_data}, next{_next} {}

template<class T>
LList<T>::LList(): start{nullptr}, last{nullptr}, listSize{0} {}

// Adds element at the end of the list
template<class T>
void LList<T>::addElement(const T& data) {
    if(!start) {
        start = new Node{data, nullptr};
        last = start;
    } else {
        last->next = new Node{data, nullptr};
        last = last->next;
    }

    listSize++;
}

template<class T>
size_t LList<T>::size() const {
    return listSize;
}

template<class T>
bool LList<T>::empty() const {
    return start == nullptr;
}

template<class T>
void LList<T>::addAfter(const T& data, const size_t& index) {
    if(listSize < index+1) {
        throw std::out_of_range("Invalid index");
    } else {
        Node* current = start;
        size_t currentIndex = index;
        // locate(index, current);
        while(current != nullptr && currentIndex != 0) {
            current = current->next;
            currentIndex--;
        }
        current->next = new Node{data, current->next};
        // not a good design
        if(current == last) {
            last = last->next;
        }
        listSize++;
    }
}

template<class T>
void LList<T>::print() const {
    Node* current = start;
    while(current) {
        std::cout << current->data << " ";
        current = current->next;
    }
}

template<class T>
typename LList<T>::ListIterator LList<T>::begin() const {
    return LList<T>::ListIterator{start};
}

template<class T>
typename LList<T>::ListIterator LList<T>::end() const {
    return LList<T>::ListIterator{nullptr};
}

int main() {
    LList<int> list;
    list.addElement(1);
    list.addElement(2);
    list.addElement(3);
    list.addElement(4);

    // std::cout << std::boolalpha << list.empty() << std::endl;
    // std::cout << list.size() << std::endl;
    // list.print();
    list.addAfter(10, 1);
    std::cout << std::endl;
    // list.print();
    std::cout << std::endl;
    std::vector<int> v{1,2,3,4,5};

    // for(int e : v) {
    //     std::cout << e << " ";
    // }
    for (auto e : list) {
        std::cout << e << " ";
    }
    // begin, end, ++, --, *, !=
    return 0;
}