/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
//#include <set>
#include <vector>
#include <map>
#include<algorithm>

// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename> class btree;

// Need to add declaration for operator<<  here
template <typename T> std::ostream& operator<< (std::ostream& os, const btree<T> &tree);

template <typename T> 
class btree {
 public:
  /** Hmm, need some iterator typedefs here... friends? **/
  friend class btree_iterator<T>;
  typedef btree_iterator<T> iterator;

  friend class const_btree_iterator<T>;
  typedef const_btree_iterator<T> const_iterator;

  //typedef reverse_iterator<const_iterator> const_reverse_btree_iterator;
  //typedef reverse_iterator<iterator> reverse_btree_iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;

  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined zero-arg constructor,
   * copy constructor, operator=, and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
  btree(size_t maxNodeElems = 40);

  /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
  btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
  btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
  btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
  btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
  friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

  iterator begin() const;
  iterator end() const;

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  //iterator rbegin();
  //iterator rend();
  const_iterator cbegin() const { return const_iterator(begin()); }
  const_iterator cend() const;

  //const_reverse_btree_iterator rbegin() const;
  //{ return const_reverse_iterator(end()); }
  const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
  const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */
  
  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
  iterator find(const T& elem);
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
  const_iterator find(const T& elem) const;
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and 
    * operator= method, and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
  std::pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
  ~btree();
  
private:
  // The details of your implementation go here
  
  //typedef Node<T> node;

  size_t maxNodeElems_;
  
  class Node {
   
    private:
      //Node * children_;
      //const size_t maxChildren_;
      //const size_t nodeSize_;
      //std::set<T> values_;       
      std::vector<T> values_;     
      std::map<int,Node*> children_; 
      Node *parent_;
      int childNum_;

    public:

      //friend class btree<T>;
      // T values_[nodeSize_];
      //T * values_;
      size_t count_ = 0;

      //Node(const T& t, Node* n) : value(t), parent(n) { }
      //Node (size_t size = 40) : children_(new Node[size+1]), maxChildren_(size+1) {
        //maxElems_ = size;
      //Node (size_t size = 40) : maxChildren_(size+1), nodeSize_(size), values_(new T[size]) {
      //  std::cout << "Node made with size = " << size << endl;
      //}
      Node() { } //std::cout << "Node Constructor" << std::endl; }

      //Node (int i, Node *n = nullptr) : item_(i), next_(n) { }

/*
      // Copy Constructor
      Node(const Node &original) : 
        values_(original.values_), 
        children_(original.children_), 
        parent_(original.parent_), 
        childNum_(original.childNum_) 
      { std::cout << "Node Copy Constructor" << std::endl; }
*/

      // Copy Constructor
      Node(const Node &original) { 
        //std::cout << "Node Copy Constructor" << std::endl; 
        values_ = original.values_;
        parent_ = original.parent_;
        childNum_ = original.childNum_;
      }

      // Copy Assignment
      Node& operator=(const Node &rhs) {
        //std::cout << "Node Copy Assignment" << std::endl;
        if (this != &rhs) {
          values_ = rhs.values_;

          //map<int, Node *>::const_iterator it; 

          for ( auto it = rhs.children_.begin() ; it != rhs.children_.end(); ++it ) { 
            //std::cout << "insert map" << std::endl;
            Node * node = new Node (*((*it).second));
            //node->printNode();
            children_.insert(make_pair( (*it).first, node ) ); 
          } 

          //children_ = rhs.children_;


          parent_ = rhs.parent_;
          childNum_ = rhs.childNum_;
        }
        return *this;
      }

      ~Node() {
        /*
        if (hasParent ()) {
          std::cout << "Deleting Parent " << endl;
          delete parent_;
        }
        */
        // delete child nodes
        for ( auto it = children_.begin(); it != children_.end(); ++it ) {
          if (it->second != NULL ) {
            delete it->second;
////            std::cout << "Node in children_ Deleted " << endl;
          }
          
        }
        children_.clear();
        
////        std::cout << "Node Deleted " << endl;
        
        //delete [] children_;
        //delete [] values_;
      }
      
/*
      bool operator==(const Node& other) const {
        std::cout << "operator== " << endl;
        return (values_ == other.values_);
      }

      bool operator!=(const Node& other) const { return !operator==(other); }
 */

      //std::cout << "maxChildren_: " << maxChildren_ << endl;
      //Node *children_[maxElems_+1]; // e.g. Node with 4 elements has 5 sub-B-trees

      void printNode () {
/*
        // just so i get idea of its parent, when testing
        if (parent_ == NULL) {
          std::cout << "parent_ == NULL" << std::endl;
        }
        else {
          std::cout << "Parent: " << std::endl;
          parent_->printNode();
          //std::cout << "parent_ NOT NULL" << std::endl;
        }
*/
////        std::cout << "printNode(): " << std::endl;
        for(auto it = values_.begin(); it != values_.end(); ++it) {
          cout << (*it) << " ";
        }
        cout << endl;   
/*
        for (unsigned int i = 0; i < count_; ++i) {
          std::cout << values_[i] << ' ';
        }
        std::cout << endl;
*/
      }

      void printNode (std::ostream& os) {
        for(auto it = values_.begin(); it != values_.end(); ++it) {
          os << (*it) << " ";
        }
      }   
      
      bool nodeContains (const T& elem) {
////        std::cout << "nodeContains(): " << std::endl;
        if (std::binary_search (values_.begin(), values_.end(), elem)) {
          //std::cout << "found!\n"; else std::cout << "not found.\n";
          return true;
        }
        else {
          return false;
        }
        //return values_.count(elem);
/*
        for (unsigned int i = 0; i < count_; ++i) {
          if (values_[i] == elem) {
            return true;
          }
        }
        return false;
*/
      }

      void insert(const T& elem) {
////        std::cout << "Node.insert():" << std::endl;
        // if node full, insert elem into a new child
        typename std::vector<T>::iterator low,up;
        if (values_.empty()) {
          values_.push_back(elem);
        }
        else {
          low = std::lower_bound (values_.begin(), values_.end(), elem);
          //std::cout << "Low set" << std::endl;
          up = std::upper_bound (values_.begin(), values_.end(), elem);   
          //std::cout << "Up set" << std::endl;
          //std::cout << "low: " << *low << " up: " << *up << std::endl;
////          std::cout << "lower_bound at position " << (low - values_.begin()) << endl;
          //int pos = (low - values_.begin());
////          std::cout << "upper_bound at position " << (up - values_.begin()) << endl;
            values_.insert(low, elem);

        }
      }

      int childPosition (const T& elem) {
////        std::cout << "childPosition(): " << std::endl;
        typename std::vector<T>::iterator low;
        low = std::lower_bound (values_.begin(), values_.end(), elem);
////        std::cout << "lower_bound at position " << (low - values_.begin()) << " for elem: " << elem << endl;
        return (low - values_.begin());  
/*
        std::set<int>::iterator itlow,itup;
        itlow = values_.lower_bound(elem);
        itup= values_.upper_bound(elem);
        std::cout << "itlow: " << *itlow << " itup: " << *itup << std::endl;
*/
        ///return 0;

/*
        int pos = count_ + 1; // start pos outside possible range
        // search in between all elems
        for (unsigned int i = 0; i < count_-1; ++i) {
          if (values_[i] < elem && values_[i+1] > elem) {
            pos = i+1;
          }
        }
        if (pos == count_ + 1) {
          if (elem < values_[0]) {
            pos = 0;
          }
        }
        if (pos == count_ + 1) {
          if (elem > values_[count_] ) {
            pos = count_;
          }
        }

        return pos;
*/
      }
      bool childExists (int pos) {
        if (children_.count(pos) > 0) {
          return true;
        }
        else {
          return false;
        }
        //return (children_.at(pos) != NULL);
      }


      Node* getChild (int pos) {
        return children_.at(pos);
      }

      Node* getParent () {
        return parent_;
      }

      bool hasParent () {
        return (parent_ != NULL);
      }
        
      void setParent (Node *node) {
        parent_ = node;
      }

      int getChildNum () {
        return childNum_;
      }

      void setChildNum (int n) {
        childNum_ = n;
      }

      size_t size () {
        return values_.size();
      }


      bool isLeaf() const { return children_.empty(); }
      //bool isEmpty() const { return (count_ == 0); }

      void addChild(int pos, const T& elem) { 
        //children_ = new Node[maxChildren_];
////        std::cout << "addChild(): " << std::endl;
        Node * node = new Node();
        node->insert(elem);
        node->setParent(this);
        node->setChildNum(pos);
        children_[pos] = node;
      }

      T& valueAt (size_t pos) {
        return values_.at(pos);
      }

      

  /*
      T firstVal() const { 
        return *(elems_.cbegin());
      }
  */

      //T value_;


      // set maintains order and does not allow for duplicate keys
      //std::set<T> elems_;
    //Node* child;

  };


  Node * root_;
  //Node *head_, *tail_;

  Node* findCorrectNode(const T& elem) {
////    std::cout << "findCorrectNode():" << endl;
    // if root is leaf and size < max
    if (root_->isLeaf()) {
      return root_;
    }
    // else keep searching
    else {
      Node *currNode = root_;
      Node *nextNode = root_;
      int pos = root_->childPosition(elem); 
////      std::cout << "pos: " << pos << endl;
      // if currNode has a Child
     while (currNode->childExists(pos)) {
      //if (currNode->childExists(pos)) {
        nextNode = currNode->getChild(pos);
        pos = nextNode->childPosition(elem); 
////        std::cout << "nextNode size: " << nextNode->size() << endl;
        //if (nextNode->size() < maxNodeElems_) {
        if (nextNode->isLeaf()) {
          return nextNode;
        }
        else {
          currNode = nextNode;
        }
        //}
       // else {
          // keep doing while loop
       // }
      }

      // if no child, elem must not exist 
      //else {
////        std::cout << "NO CHILD" << endl;
        return currNode;
      //}
    }
    return root_;
  }
};




/**
 * The template implementation needs to be visible to whatever
 * translation unit makes use of templatized btree methods.
 * The unconventional practice is to #include the implementation
 * file just before the end of the interface (sort of like
 * sneaking it in and hoping it isn't noticed).  Because the
 * .tem file is included here, the .h file is NOT #included in 
 * the .tem file.  We'd otherwise have circular inclusions
 * and the compiler would be peeved.
 */

#include "btree.tem"

#endif
