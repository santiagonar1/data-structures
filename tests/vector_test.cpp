#include <gtest/gtest.h>

#include <algorithm>

#include <vector.hpp>

TEST(VectorTest, Constructor) {
    constexpr int SIZE = 10;

    ds::Vector<int> vector;
    EXPECT_EQ(vector.size(), 0) << "Expected size 0";

    ds::Vector<int> vector_size_10(SIZE);
    EXPECT_EQ(vector_size_10.size(), SIZE) << "Expected size " << SIZE;

    ds::Vector<int> vector_size_0(0);
    EXPECT_EQ(vector_size_0.size(), 0) << "Expected size 0";

    EXPECT_THROW(ds::Vector<int> vector_size_negative(-1), std::length_error);

    constexpr int INIT_VALUE = 99;
    ds::Vector<int> vector_init_val(SIZE, INIT_VALUE);

    for (const auto &v: vector_init_val) {
        EXPECT_EQ(v, INIT_VALUE) << "All values should be " << INIT_VALUE;
    }

    ds::Vector<int> v_initialize_list = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < v_initialize_list.size(); i++) {
        EXPECT_EQ(v_initialize_list[i], i) << "Expected value " << i;
    }

    ds::Vector<int> v_from = {0, 1, 2, 3, 4, 5};

    ds::Vector<int> v_to_with_range(v_from.begin(), v_from.end());
    for (int i = 0; i < v_from.size(); i++) {
        EXPECT_EQ(v_from[i], v_to_with_range[i]) << "Expected value " << v_from[i];
    }
}

TEST(VectorTest, PushElements) {
    constexpr int NUM_PUSHS = 100;

    ds::Vector<int> v;

    for (int i = 0; i < NUM_PUSHS; i++) {
        v.push_back(i);
        EXPECT_EQ(v[i], i) << "Vector at [" << i << "] should be " << i;
    }

    EXPECT_EQ(v.size(), NUM_PUSHS) << "Expected size " << NUM_PUSHS;
}

TEST(VectorTest, Reserve) {
    constexpr int NUM_NEW_ELEMENTS = 200;
    constexpr int LESS_THAN_NUM_NEW_ELEMENTS = NUM_NEW_ELEMENTS - 20;
    constexpr int ONE_LESS_THAN_NUM_NEW_ELEMENTS = NUM_NEW_ELEMENTS - 1;
    constexpr int MORE_THAN_NUM_NEW_ELEMENTS = NUM_NEW_ELEMENTS + 20;
    constexpr int ONE_MORE_THAN_NUM_NEW_ELEMENTS = NUM_NEW_ELEMENTS + 20;
    constexpr int NEGATIVE_CAPACITY = -10;

    ds::Vector<int> vector_init_capacity_0;
    EXPECT_EQ(vector_init_capacity_0.size(), 0) << "Expected size 0";
    EXPECT_GE(vector_init_capacity_0.capacity(), 0) << "Expected size 0";
    vector_init_capacity_0.reserve(NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_0.size(), 0) << "Expected size 0";
    EXPECT_GE(vector_init_capacity_0.capacity(), NUM_NEW_ELEMENTS)
            << " Expected capacity greater or equal to " << NUM_NEW_ELEMENTS;

    ds::Vector<int> vector_init_capacity_less(LESS_THAN_NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_less.size(), LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << LESS_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_less.capacity(), LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << LESS_THAN_NUM_NEW_ELEMENTS;
    vector_init_capacity_less.reserve(NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_less.size(), LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << LESS_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_less.capacity(), NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << NUM_NEW_ELEMENTS;

    ds::Vector<int> vector_init_capacity_one_less(ONE_LESS_THAN_NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_one_less.size(), ONE_LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << ONE_LESS_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_one_less.capacity(), ONE_LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << ONE_LESS_THAN_NUM_NEW_ELEMENTS;
    vector_init_capacity_one_less.reserve(NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_one_less.size(), ONE_LESS_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << ONE_LESS_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_one_less.capacity(), NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << NUM_NEW_ELEMENTS;

    ds::Vector<int> vector_init_capacity_more(MORE_THAN_NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_more.size(), MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << MORE_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_more.capacity(), MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << MORE_THAN_NUM_NEW_ELEMENTS;
    const auto capacity_before_reserve = vector_init_capacity_more.capacity();
    vector_init_capacity_more.reserve(NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_more.size(), MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << MORE_THAN_NUM_NEW_ELEMENTS;
    EXPECT_EQ(vector_init_capacity_more.capacity(), capacity_before_reserve)
            << "Capacity should remain the same when current capacity greater than new one";

    ds::Vector<int> vector_init_capacity_one_more(ONE_MORE_THAN_NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_one_more.size(), ONE_MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << ONE_MORE_THAN_NUM_NEW_ELEMENTS;
    EXPECT_GE(vector_init_capacity_one_more.capacity(), ONE_MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected capacity greater or equal to " << ONE_MORE_THAN_NUM_NEW_ELEMENTS;
    const auto capacity_before_reserve_one_more = vector_init_capacity_one_more.capacity();
    vector_init_capacity_one_more.reserve(NUM_NEW_ELEMENTS);
    EXPECT_EQ(vector_init_capacity_one_more.size(), ONE_MORE_THAN_NUM_NEW_ELEMENTS)
            << "Expected size " << ONE_MORE_THAN_NUM_NEW_ELEMENTS;
    EXPECT_EQ(vector_init_capacity_one_more.capacity(), capacity_before_reserve_one_more)
            << "Capacity should remain the same when current capacity greater than new one";


    EXPECT_THROW(vector_init_capacity_more.reserve(NEGATIVE_CAPACITY), std::length_error);
}

TEST(VectorTest, CheckAt) {
    constexpr int VECTOR_SIZE = 100;
    constexpr int GREATER_THAN_VECTOR_SIZE = VECTOR_SIZE + 10;

    ds::Vector<int> v(VECTOR_SIZE);
    for (int i = 0; i < VECTOR_SIZE; i++) {
        v[i] = i;
        EXPECT_EQ(v.at(i), i) << "v.at(" << i << ") should be " << i;
    }

    EXPECT_THROW(v.at(GREATER_THAN_VECTOR_SIZE), std::out_of_range) << "v.at should throw std::out_of_range";
    EXPECT_THROW(v.at(VECTOR_SIZE), std::out_of_range) << "v.at should throw std::out_of_range";
    EXPECT_NO_THROW(v.at(VECTOR_SIZE - 1)) << "v.at should not throw std::out_of_range";
}

TEST(VectorTest, CheckFront) {
    constexpr int FIRST_VALUE = 100;
    constexpr int VECTOR_SIZE = 2;

    ds::Vector<int> v(VECTOR_SIZE);
    v[0] = FIRST_VALUE;
    EXPECT_EQ(v.front(), FIRST_VALUE) << "First value should be " << FIRST_VALUE;
}

TEST(VectorTest, CheckBack) {
    constexpr int LAST_VALUE = 100;
    constexpr int VECTOR_SIZE = 2;

    ds::Vector<int> v(VECTOR_SIZE);
    v[VECTOR_SIZE - 1] = LAST_VALUE;
    EXPECT_EQ(v.back(), LAST_VALUE) << "First value should be " << LAST_VALUE;
}

TEST(VectorTest, GetValues) {
    constexpr int NUM_VALUES = 100;

    ds::Vector<int> v;
    for (int i = 0; i < NUM_VALUES; i++) {
        v.push_back(i);
    }

    auto values = v.data();
    for (int i = 0; i < NUM_VALUES; i++) {
        EXPECT_EQ(v[i], values[i]) << "Values at " << i << " should be " << i;
    }

    ds::Vector<int> empty_v;
    EXPECT_EQ(empty_v.data(), nullptr) << "On empty vector data() should return nullptr";
}

TEST(VectorTest, Emtpy) {
    constexpr int NUM_VALUES = 100;

    ds::Vector<int> non_empty_v(NUM_VALUES);
    EXPECT_FALSE(non_empty_v.empty()) << "Vector should not be empty";

    ds::Vector<int> empty_v;
    EXPECT_TRUE(empty_v.empty()) << "Vector should be empty";
}

TEST(VectorTest, MaxSize) {
    // Values taken from playing with std::vector<>::max_size
    constexpr ds::Vector<char>::size_type MAX_SIZE_CHAR = 9223372036854775807;
    constexpr ds::Vector<int>::size_type MAX_SIZE_INT = 2305843009213693951;

    ds::Vector<char> v_char;
    EXPECT_EQ(v_char.max_size(), MAX_SIZE_CHAR);

    ds::Vector<int> v_int;
    EXPECT_EQ(v_int.max_size(), MAX_SIZE_INT);
}

TEST(VectorTest, ShrinkToFit) {
    constexpr int INITIAL_SIZE = 100;
    constexpr int LARGER_SIZE = INITIAL_SIZE + 20;

    ds::Vector<int> v(INITIAL_SIZE);
    v.reserve(LARGER_SIZE);
    EXPECT_GE(v.capacity(), LARGER_SIZE) << "Capacity should be at least " << LARGER_SIZE;
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), INITIAL_SIZE) << "After shrink capacity should be at least " << INITIAL_SIZE;
}

TEST(VectorTest, Clear) {
    constexpr int INITIAL_SIZE = 100;

    ds::Vector<int> v(INITIAL_SIZE);
    EXPECT_EQ(v.size(), INITIAL_SIZE) << "Initial size should be " << INITIAL_SIZE;
    const auto previous_capacity = v.capacity();
    v.clear();
    EXPECT_EQ(v.size(), 0) << "After clear size should be 0";
    EXPECT_EQ(v.capacity(), previous_capacity) << "After clear capacity should not change";
}

TEST(VectorTest, PopBack) {
    constexpr int INITIAL_SIZE = 100;

    ds::Vector<int> v(INITIAL_SIZE);
    EXPECT_EQ(v.size(), INITIAL_SIZE);

    for (int i = 0; i < INITIAL_SIZE; i++) {
        v.pop_back();
        EXPECT_EQ(v.size(), INITIAL_SIZE - (i + 1)) << "After pop_back size should decreased by 1";
    }
}

TEST(VectorTest, Iterator) {
    constexpr int SIZE = 100;
    constexpr int FILL_VALUE = 3;

    ds::Vector<int> v(SIZE);
    std::fill(v.begin(), v.end(), FILL_VALUE);

    int counter = 0;
    for (const auto &val: v) {
        EXPECT_EQ(val, FILL_VALUE) << "std::fill should have set this to " << FILL_VALUE;
        counter++;
    }
    EXPECT_EQ(counter, SIZE) << "It should have iterated over the whole size of vector";
}

TEST(VectorTest, ComparisonOperators) {
    constexpr int SIZE = 100;
    constexpr int DIFFERENT_SIZE = SIZE + 4;
    constexpr int INIT_VALUE = 42;
    constexpr int DIFFERENT_INIT_VALUE = INIT_VALUE + 4;

    ds::Vector<int> v(SIZE, INIT_VALUE);
    ds::Vector<int> v_same(SIZE, INIT_VALUE);
    ds::Vector<int> v_different_size(DIFFERENT_SIZE, INIT_VALUE);
    ds::Vector<int> v_different_init_value(SIZE, DIFFERENT_INIT_VALUE);
    ds::Vector<int> v_different_size_and_init_value(DIFFERENT_SIZE, DIFFERENT_INIT_VALUE);

    EXPECT_EQ(v, v_same);
    EXPECT_NE(v, v_different_size);
    EXPECT_NE(v, v_different_init_value);
    EXPECT_NE(v, v_different_size_and_init_value);
}

TEST(VectorTest, AssignmentOperator) {
    constexpr int SIZE = 100;
    constexpr int INIT_VALUE = 42;

    ds::Vector<int> v_from(SIZE, INIT_VALUE);
    ds::Vector<int> v_from_move(SIZE, INIT_VALUE);
    ds::Vector<int> v_to;
    ds::Vector<int> v_to_move;
    ds::Vector<int> v_to_list;
    const auto list = {4, 5, 6, 7};

    v_to = v_from;
    EXPECT_EQ(v_to, v_from);

    v_to_move = std::move(v_from_move);
    EXPECT_EQ(v_from_move.data(), nullptr) << "After move origin should have nullpt";
    for (int i = 0; i < SIZE; i++) {
        EXPECT_EQ(v_to_move[i], INIT_VALUE);
    }

    v_to_list = list;
    for (int i = 0; i < list.size(); i++) {
        EXPECT_EQ(data(list)[i], v_to_list[i]) << "Value should be " << data(list)[i];
    }
}

TEST(VectorTest, Assign) {
    constexpr int COUNT = 100;
    constexpr int VALUE = 42;
    constexpr int SIZE_GREATER_THAN_COUNT = COUNT + 10;
    constexpr int INIT_VALUE = VALUE + 10;

    {
        ds::Vector<int> init_empty_vector;
        init_empty_vector.assign(COUNT, VALUE);
        EXPECT_EQ(init_empty_vector.size(), COUNT) << "Vector size should be " << COUNT;
        for (const auto &val: init_empty_vector) {
            EXPECT_EQ(val, VALUE) << "After assign each value should be " << VALUE;
        }
    }

    {
        ds::Vector<int> non_empty_vector(SIZE_GREATER_THAN_COUNT, INIT_VALUE);
        non_empty_vector.assign(COUNT, VALUE);
        EXPECT_EQ(non_empty_vector.size(), COUNT) << "Vector size should be " << COUNT;
        for (const auto &val: non_empty_vector) {
            EXPECT_EQ(val, VALUE) << "After assign each value should be " << VALUE;
        }
    }

    {
        ds::Vector<int> init_empty_vector;
        ds::Vector<int> non_empty_vector(COUNT, VALUE);
        init_empty_vector.assign(non_empty_vector.begin(), non_empty_vector.end());
        EXPECT_EQ(init_empty_vector.size(), non_empty_vector.size()) << "Vector size should be " << non_empty_vector.size();
        EXPECT_EQ(init_empty_vector, non_empty_vector);
    }

    {
        ds::Vector<int> smaller_non_empty_vector(COUNT, VALUE);
        ds::Vector<int> larger_non_empty_vector(SIZE_GREATER_THAN_COUNT, INIT_VALUE);
        smaller_non_empty_vector.assign(larger_non_empty_vector.begin(), larger_non_empty_vector.end());
        EXPECT_EQ(smaller_non_empty_vector.size(), larger_non_empty_vector.size()) << "Vector size should be " << larger_non_empty_vector.size();
        EXPECT_EQ(smaller_non_empty_vector, larger_non_empty_vector);
    }

    {
        ds::Vector<int> smaller_non_empty_vector(COUNT, VALUE);
        ds::Vector<int> larger_non_empty_vector(SIZE_GREATER_THAN_COUNT, INIT_VALUE);
        larger_non_empty_vector.assign(smaller_non_empty_vector.begin(), smaller_non_empty_vector.end());
        EXPECT_EQ(larger_non_empty_vector.size(), smaller_non_empty_vector.size()) << "Vector size should be " << smaller_non_empty_vector.size();
        EXPECT_EQ(larger_non_empty_vector, smaller_non_empty_vector);
    }

    {
        const auto list = {1, 2, 3, 4};
        ds::Vector<int> init_empty_vector;
        init_empty_vector.assign(list);
        EXPECT_EQ(init_empty_vector.size(), list.size()) << "Vector size should be " << list.size();
        for (int i = 0; i < list.size(); i++) {
            EXPECT_EQ(init_empty_vector[i], data(list)[i]) << "Value should be " << data(list)[i];
        }
    }
}