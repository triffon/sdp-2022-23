#ifndef __LIST_HIGHORDER_HPP
#define __LIST_HIGHORDER_HPP

template <typename L, typename T>
class ListHighOrder {
public:
    using UnaryFunction = T (*)(T const&);

    static int plus1(int const& x) { return x + 1; }

    static L map(UnaryFunction f, L const& l) {
        L result;
        for(T const& x : l)
            result.insertLast(f(x));
        return result;
    }

    static void mapAssign(UnaryFunction f, L& l) {
        for(T& x : l)
            x = f(x);
    }


/*
    static ? filter(?, ?);
    static ? filterAssign(?, ?);
    static ? foldr(?, ?, ?);
    static ? foldl(?, ?, ?);
    */
};

#endif