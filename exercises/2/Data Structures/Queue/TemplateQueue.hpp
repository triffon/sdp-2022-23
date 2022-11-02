#pragma once

#include "ForwardList.hpp"

namespace dsa
{

template <typename T, typename Container = ForwardList<T>>
class TemplateQueue
{
public:
    void        enqueue( const T& elem );
    T           dequeue();

    void        push( const T& elem )   { container.push_back( elem ); }
    void        pop()                   { container.pop_front();       }
    T&          front()                 { return container.front();    }
    const T&    front() const           { return container.front();    }
    bool        empty() const           { return container.empty();    }
    size_t      size()  const           { return container.size();     }

private:
    Container   container;
};

template<typename T, typename Container>
inline void TemplateQueue<T, Container>::enqueue( const T& elem )
{
    this->push( elem );
}

template<typename T, typename Container>
inline T TemplateQueue<T, Container>::dequeue()
{
    T   res = this->front();
    this->pop();
    return res;
}

} // end of namespace dsa
