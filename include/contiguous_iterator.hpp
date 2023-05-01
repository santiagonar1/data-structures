//
// Created by santiago on 03.06.23.
//

#ifndef DS_CONTIGUOUS_ITERATOR_HPP
#define DS_CONTIGUOUS_ITERATOR_HPP

#include <utility>


namespace it {

    template<typename ValueType, typename ReferenceType>
    struct ContiguousIterator {
        using iterator_concept [[maybe_unused]] = std::contiguous_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = ValueType;
        using pointer = value_type *;
        using reference = ReferenceType;

        ContiguousIterator() = default;

        explicit ContiguousIterator(pointer p) { _ptr = p; }

        reference operator*() const { return *_ptr; }

        pointer operator->() const { return _ptr; }

        ContiguousIterator &operator++() {
            _ptr++;
            return *this;
        }

        ContiguousIterator operator++(int) {
            ContiguousIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        ContiguousIterator &operator+=(int i) {
            _ptr += i;
            return *this;
        }

        ContiguousIterator operator+(const difference_type other) const { return _ptr + other; }

        friend ContiguousIterator operator+(const difference_type value,
                                            const ContiguousIterator &other) {
            return other + value;
        }

        ContiguousIterator &operator--() {
            _ptr--;
            return *this;
        }

        ContiguousIterator operator--(int) {
            ContiguousIterator tmp = *this;
            --(*this);
            return tmp;
        }

        ContiguousIterator &operator-=(int i) {
            _ptr -= i;
            return *this;
        }

        difference_type operator-(const ContiguousIterator &other) const {
            return _ptr - other._ptr;
        }

        ContiguousIterator operator-(const difference_type other) const { return _ptr - other; }

        friend ContiguousIterator operator-(const difference_type value,
                                            const ContiguousIterator &other) {
            return other - value;
        }

        reference operator[](difference_type idx) const { return _ptr[idx]; }

        auto operator<=>(const ContiguousIterator &) const = default;

    private:
        pointer _ptr;
    };
} // namespace it

#endif //DS_CONTIGUOUS_ITERATOR_HPP
