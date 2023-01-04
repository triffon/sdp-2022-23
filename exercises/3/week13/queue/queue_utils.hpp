#ifndef __QUEUE_UTILS_HPP
#define __QUEUE_UTILS_HPP

#include <utility>
#include <stdexcept>
#include "abstract_queue.hpp"

template <typename T>
class QueueUtils {
public:
    static T extractMin(AbstractQueue<T>& q) {
        if (q.empty())
            throw std::runtime_error("Опит за изваждане на минимален елемент от празна опашка");
        T min = q.dequeue();
        T sentinel = T();
        q.enqueue(sentinel);
        while (q.head() != sentinel) {
            T current = q.dequeue();
            if (current < min)
                std::swap(min, current);
            q.enqueue(current);
        }
        // q.head() == sentinel
        q.dequeue();
        return min;
    }

    static void sortQueue(AbstractQueue<T>& input, AbstractQueue<T>& result) {
        if (!result.empty())
            throw std::runtime_error("Параметърът за резултат е непразна опашка!");
        while (!input.empty())
            result.enqueue(extractMin(input));
    }
};

#endif