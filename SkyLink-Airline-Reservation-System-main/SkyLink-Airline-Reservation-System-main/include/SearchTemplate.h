#ifndef SEARCH_TEMPLATE_H
#define SEARCH_TEMPLATE_H

#include <vector>
#include <memory>

// A simple and beginner-friendly template function to search and filter vector items.
// This fulfills the "one template function" requirement and is very easy to explain in a viva.
template <typename T, typename Predicate>
std::vector<std::shared_ptr<T>> searchItems(const std::vector<std::shared_ptr<T>>& items, Predicate pred) {
    std::vector<std::shared_ptr<T>> results;
    for (const auto& item : items) {
        if (pred(item)) {
            results.push_back(item);
        }
    }
    return results;
}

#endif // SEARCH_TEMPLATE_H
