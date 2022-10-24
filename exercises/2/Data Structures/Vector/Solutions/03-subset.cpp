#include <iostream>
#include <vector>

template <class T>
typename std::vector<T>::const_iterator find( const std::vector<T>& vec, const T& elem )
{
    typename std::vector<T>::const_iterator   it = vec.begin();

    for ( ; it != vec.end(); it++ )
        if ( *it == elem )
            break;

    return it;
}

template <class T>
bool isSupersetOf( const std::vector<T>& superset, const std::vector<T>& subset )
{
    for ( const T& subElem : subset )
        if ( find( superset, subElem ) == superset.end() )
            return false;

    return true;
}

template <class T>
bool isSubsetOf( const std::vector<T>& subset, const std::vector<T>& superset )
{
    return isSubsetOf( superset, subset );
}

void print( const char* name, const std::vector<int>& vec );



int main()
{
    std::vector<int>    vec     = { 5, 10, 12, 43, -123, -4, 3, 1 };
    std::vector<int>    vec2    = { 10, 43, 3, 5, 1, 12 };
    std::vector<int>    vec3    = { 5, -4, 3, 1, 69, 12, 10 };

    print( "vec" , vec  );
    print( "vec2", vec2 );
    print( "vec3", vec3 );

    std::cout << "\n";
    
    std::cout << "vec2 is a subset of vec: " << ( isSubsetOf( vec2, vec ) ? "True" : "False" ) << "\n";
    std::cout << "vec3 is a subset of vec: " << ( isSubsetOf( vec3, vec ) ? "True" : "False" ) << "\n";

    return 0;
}



void print( const char* name, const std::vector<int>& vec )
{
    std::cout << name << ":\t";
    for ( int elem : vec )
    {
        std::cout << elem << "\t";
    }
    std::cout << "\n";
}
