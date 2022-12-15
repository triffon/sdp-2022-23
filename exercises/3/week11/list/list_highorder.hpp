#ifndef __LIST_HIGHORDER_HPP
#define __LIST_HIGHORDER_HPP

template <typename L, typename T>
class ListHighOrder {
public:
    using UnaryFunction  = T (*)(T const&);
    using UnaryPredicate = bool (*)(T const&);

    static bool odd(int const& x) { return x % 2 != 0; }
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

    static L filter(UnaryPredicate p, L const& l) {
        L result;
        for(T const& x : l)
            if (p(x))
                result.insertLast(x);
        return result;
    }

    static void filterAssign(UnaryPredicate p, L& l) {
        for(typename L::I it = l.begin(); it.valid();)
            if (!p(*it)) {
                typename L::I toDelete = it++;
                T deleted;
                l.deleteAt(deleted, toDelete);
            } else
                ++it;
    }

/*
    static ? filterAssign(?, ?);
    static ? foldr(?, ?, ?);
    static ? foldl(?, ?, ?);
    */
};

#endif