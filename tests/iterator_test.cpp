#include <gtest/gtest.h>

#include <contiguous_iterator.hpp>

TEST(ContiguousIterator, IsContiguousIterator) {
    static_assert(std::contiguous_iterator<it::ContiguousIterator<int, int &>>);
}