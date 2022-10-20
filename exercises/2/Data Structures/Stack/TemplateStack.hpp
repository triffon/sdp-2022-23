#pragma once
#include "dynamic_array.hpp"

namespace dsa
{

template < class T, class Container = dynamic_array<T> >
class TemplateStack
{
public:
    void        push( const T& elem )   { container.push_back( elem );  }
    void        pop()                   { container.pop_back();         }
    T&          top()                   { return container.back();      }
    const T&    top()   const           { return container.back();      }
    bool        empty() const           { return container.empty();     }
    size_t      size() const            { return container.size();      }

private:
    Container   container;
};

} // end namespace dsa
