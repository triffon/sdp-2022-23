#ifndef __LIST_HIGHORDER_HPP
#define __LIST_HIGHORDER_HPP

// TODO: реализирайте по-общи варианти, в които имаме отделен
// тип на резултата  (напр. typename R)
template <typename L, typename T>
class ListHighOrder {
public:
    using UnaryFunction  = T (*)(T const&);
    using UnaryPredicate = bool (*)(T const&);
    using BinaryOperation = T (*)(T const&, T const&);

    static bool odd(int const& x) { return x % 2 != 0; }
    static int plus1(int const& x) { return x + 1; }
    static int square(int const& x) { return x * x; }
    static int plus(int const& x, int const& y) { return x + y; }

    /*
    (define (map1 f l)
    (if (null? l) '()
        (cons (f (car l)) (map1 f (cdr l)))))
    */
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
    (define (filter p? l)
        (cond ((null? l) l)
                ((p? (car l)) (cons (car l) (filter p? (cdr l))))
                (else (filter p? (cdr l)))))
    */
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
    (define (foldr op nv l)
        (if (null? l) nv
            (op (car l) (foldr op nv (cdr l)))))
    */
    // O(|l|) по време и O(|l|) по памет
    static T foldr(BinaryOperation op, T const& nv, typename L::I it) {
        if (!it.valid())
            return nv;
        return op(*it, foldr(op, nv, it.next()));
    }

    /*
    (define (foldl op nv l)
      (if (null? l) nv (foldl op (op nv (car l)) (cdr l))))
    */
    // O(|l|) по време и O(1) по памет 
    static T foldl(BinaryOperation op, T const& nv, L const& l) {
        T result = nv;
        for(T const& x : l)
            result = op(result, x);
        return result;
    }

};

#endif