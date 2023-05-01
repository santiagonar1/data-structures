//
// Created by santiago on 01.05.23.
//

#ifndef DS_VECTOR_HPP
#define DS_VECTOR_HPP

#include <utility>

#include "contiguous_iterator.hpp"
#include "type_definitions.hpp"

namespace ds {

    template<typename T>
    class Vector {
    public:
        using size_type = types::size_t;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using difference_type = types::ptrdiff_t;
        using pointer = T *;
        using iterator = it::ContiguousIterator<T, reference>;
        using const_iterator = it::ContiguousIterator<T, const_reference>;


        Vector() : _size(0), _capacity(0), _values(nullptr) {}

        explicit Vector(size_type size, const T &value = T()) : _size(size), _capacity(size), _values(nullptr) {
            // TODO: Look for a cleaner way of doing this; otherwise we cannot use all values.
            // Also, this requires knowledge of what size_t is, which creates coupling.
            if (static_cast<long long>(size) < 0)
                throw std::length_error("Creating vector with negative number");

            _values = new T[_size];
            std::fill(begin(), end(), value);
        }

        Vector(std::initializer_list<T> init) : Vector(init.size()) { // NOLINT(cppcoreguidelines-pro-type-member-init)
            std::copy(init.begin(), init.end(), begin());
        }

        template<std::input_iterator InputIt>
        Vector(InputIt first, InputIt last) : Vector(std::distance(first, last)) { // NOLINT(cppcoreguidelines-pro-type-member-init)
            std::copy(first, last, begin());
        }

        ~Vector() {
            delete[] _values;
        }

        void assign(size_type count, const T &value) {
            if (not can_store(count)) {
                resize(count);
            }

            _size = count;
            std::fill(begin(), end(), value);
        }

        template<std::input_iterator InputIt>
        void assign(InputIt first, InputIt last) {
            const size_type count = std::distance(first, last);
            if (not can_store(count)) {
                resize(count);
            }

            _size = count;
            std::copy(first, last, begin());
        }

        void assign(std::initializer_list<T> ilist) {
            if (not can_store(ilist.size())) {
                resize(ilist.size());
            }

            _size = ilist.size();
            std::copy(ilist.begin(), ilist.end(), begin());
        }

        reference at(size_type pos) {
            if (pos >= _size) {
                throw std::out_of_range("id is out of range");
            }

            return _values[pos];
        }

        reference back() {
            return _values[_size - 1];
        }

        iterator begin() {
            return iterator(&_values[0]);
        }

        [[nodiscard]] size_type capacity() const {
            return _capacity;
        }

        const_iterator cbegin() const {
            return const_iterator(&_values[0]);
        }

        const_iterator cend() const {
            return const_iterator(&_values[_size]);
        }

        void clear() {
            _size = 0;
        }

        T *data() {
            return _values;
        }

        bool empty() {
            return begin() == end();
        }

        iterator end() {
            return iterator(&_values[_size]);
        }

        reference front() {
            return _values[0];
        }

        [[nodiscard]] size_type max_size() const {
            return std::numeric_limits<difference_type>::max() / sizeof(T);
        }

        reference operator[](size_type pos) {
            return _values[pos];
        }

        const_reference operator[](size_type pos) const {
            return _values[pos];
        }

        Vector<T> &operator=(const Vector<T> &other) {
            if (not can_store(other.size()))
                resize(other.size());

            _size = other.size();
            // TODO: Once we have cbegin() and cend(), replace by std::copy
            std::copy(other.cbegin(), other.cend(), begin());

            return *this;
        }

        Vector<T> &operator=(Vector<T> &&other) {
            _size = std::move(other._size);
            _capacity = std::move(other._capacity);
            _values = other._values;
            other._values = nullptr;
        }

        Vector<T> &operator=(std::initializer_list<T> list) {
            if (_capacity < list.size())
                resize(list.size());

            _size = list.size();
            std::copy(list.begin(), list.end(), begin());

            return *this;
        }

        void pop_back() {
            if (_size == 0)
                return;

            _size--;
        }

        void push_back(const T &value) {
            if (not can_store_more_elements())
                expand();

            _values[_size] = value;
            _size++;
        }

        void reserve(size_type new_cap) {
            // TODO: Look for a cleaner way of doing this; otherwise we cannot use all values.
            // Also, this requires knowledge of what size_t is, which creates coupling.
            if (static_cast<long long>(new_cap) < 0)
                throw std::length_error("New capacity has to be positive");

            // TODO: Throw length_error if new_cap > max_capacity()

            if (new_cap <= _capacity)
                return;

            resize(new_cap);
        }

        void shrink_to_fit() {
            resize(_size);
        }

        [[nodiscard]] size_type size() const {
            return _size;
        }

    private:
        size_type _capacity;
        size_type _size;
        T *_values;

        inline bool can_store_more_elements() {
            return _capacity > _size;
        }

        inline bool can_store(size_type num_elements) {
            return _capacity >= num_elements;
        }

        void expand() {
            const size_type new_capacity = _capacity > 0 ? _capacity * 2 : 1;
            resize(new_capacity);
        }

        void resize(size_type new_capacity) {
            if (new_capacity < _size)
                throw std::length_error("New capacity must be larger than current _size");

            if (new_capacity == _capacity)
                return;

            T *new_storage = new T[new_capacity];

            for (size_type i = 0; i < _size; i++) {
                new_storage[i] = _values[i];
            }

            std::swap(_values, new_storage);
            _capacity = new_capacity;

            delete[] new_storage;
        }
    };

    template<typename T>
    bool operator==(const Vector<T> &lhs, const Vector<T> &rhs) {
        if (lhs.size() != rhs.size())
            return false;

        for (int i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i])
                return false;
        }

        return true;
    }
} // namespace ds

#endif //DS_VECTOR_HPP
