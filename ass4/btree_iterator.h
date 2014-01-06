#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)


using namespace std;

template <typename T> class btree;
//template <typename T> class const_btree_iterator;
template <typename T> class const_btree_iterator;

template <typename T> class btree_iterator {
  public:
    friend class const_btree_iterator<T>;  
  
    typedef ptrdiff_t difference_type;
    typedef forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    reference operator*() const;
    pointer operator->() const { return &(operator*()); }
    btree_iterator& operator++(); // prefix ++
    btree_iterator operator++(int);  // postfix ++
    btree_iterator& operator--(); // prefix --
    btree_iterator operator--(int); // postfix --
    bool operator==(const btree_iterator& other) const;
    bool operator!=(const btree_iterator& other) const { return !operator==(other); }
    bool operator==(const const_btree_iterator<T>& other) const;
    bool operator!=(const const_btree_iterator<T>& other) const { return !operator==(other); }

    btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t pos = 0) : pointee_(pointee), pos_(pos) {}

  private:
    typename btree<T>::Node *pointee_;
    size_t pos_;
    //size_t childNum_ = 0;
};

template <typename T> class const_btree_iterator {
  public:
    friend class btree_iterator<T>;

    typedef ptrdiff_t difference_type;
    typedef forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    reference operator*() const;
    pointer operator->() const { return &(operator*()); }
    const_btree_iterator& operator++();
    const_btree_iterator operator++(int);  // postfix ++
    const_btree_iterator& operator--();
    const_btree_iterator operator--(int);
    bool operator==(const const_btree_iterator& other) const;
    bool operator!=(const const_btree_iterator& other) const { return !operator==(other); }
    bool operator==(const btree_iterator<T>& other) const;
    bool operator!=(const btree_iterator<T>& other) const { return !operator==(other); }
    const_btree_iterator(typename btree<T>::Node *pointee = nullptr, size_t pos = 0) : pointee_(pointee), pos_(pos) {}

    const_btree_iterator(const btree_iterator<T>& other) : pointee_(other.pointee_), pos_(other.pos_) { }
    //const_btree_iterator(const const_btree_iterator<T>& other) : pointee_(other.pointee_), pos_(other.pos_) { std::cout << "CONVERT CIT TO CIT" << std::endl;}


  private:
    typename btree<T>::Node *pointee_;
    size_t pos_ = 0;
};

#include "btree_iterator.tem"

#endif
