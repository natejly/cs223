#pragma once

#include <queue>
#include <utility>

/**
 * A priority queue that allows for the insertion of (key, value) pairs and
 *  the constant-time removal of the pair with the smallest key.
 *
 * @tparam Key the type of the keys in the queue
 * @tparam Value the type of the values in the queue
 */
template <typename Key, typename Value>
class MinQueue
{
public:
    /**
     * Inserts a key-value pair into the queue.
     *
     * @param key the key of the pair
     * @param value the value of the pair
     */
    void insert(const Key &key, const Value &value)
    {
        std::pair<Key, Value> pair(key, value);
        pq.push(pair);
    }

    /**
     * Removes the key-value pair with the smallest key from the queue.
     */
    Value remove_min()
    {
        Value value = pq.top().second;
        pq.pop();
        return value;
    }

    /**
     * Returns the key-value pair with the smallest key in the queue.
     */
    std::pair<Key, Value> &min() const
    {
        return pq.top();
    }

    /**
     * Reports whether the queue is empty.
     */
    bool empty() const
    {
        return pq.empty();
    }

private:
    /**
     * The priority queue that stores the key-value pairs. It is a min-heap
     *  because the third type parameter is std::greater.
     */
    std::priority_queue<std::pair<Key, Value>,
                        std::vector<std::pair<Key, Value>>,
                        std::greater<std::pair<Key, Value>>>
        pq;
};
