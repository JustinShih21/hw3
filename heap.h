#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap : private std::vector<T>
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  
  // Data member for m
  int m_;
  // Data member for which heap it is (max or min)
  PComparator comp_;

  // Helper functions for 
  void reorderUp(int index);
  void reorderDown(int index);
};

// Add implementation of member functions here

// Constructor, initializes m_ and comp_ to be the appropriate values
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : std::vector<T>(), m_(m), comp_(c) 
{

}

// Deconstructor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {
  
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return (*this)[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");

  }

  // Makes the front of the vector the old back of the vector
  std::swap((*this)[0], this->back());
  
  // Pops the back of the array 
  this->pop_back();
  
  // Reorder the new top of the array, moving the old back down to the back (O(logn) time), the array isnt empty
  if (!empty()) {
    reorderDown(0);
  }

}


template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{

  // Use the vector empty
  return std::vector<T>::empty();

}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{

  // Use the vector size
  return std::vector<T>::size();

}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
  // Use the vector implementation to add on the item
  std::vector<T>::push_back(item);
  
  // Reorder everything after the adding of the new variable
  reorderUp(this->size() - 1);

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::reorderUp(int index) {

  // Create a loop to reorder the new index until its in its right position
  while (index > 0) {
    
    // The parent formula for m_
    size_t parent = (index - 1) / m_;

    // The comp_ acts as either a > or a < depending on what the user passes (min or max heap)
    if (comp_((*this)[index], (*this)[parent])) {
      
      // Dereferencecs "this object" for parent and index to swap them 
      std::swap((*this)[index], (*this)[parent]);
      index = parent;
    }
    else {
      break;
    }
  }
}



template <typename T, typename PComparator>
void Heap<T,PComparator>::reorderDown(int index) {

  // Start a while loop that will go until all the children are in the right place
  while (true) {
    size_t firstChild = m_ * index + 1;
    
    // Break at the end of the heap, no more children
    if (firstChild >= this->size()){

      break;
    }

    size_t bestChild = firstChild;
 
    // Find the best child based on the min or max heap
    for (int i = 1; i < m_; ++i) {
      size_t child = firstChild + i;
      if (child < this->size() && comp_((*this)[child], (*this)[bestChild])) {
        bestChild = child;
      }
    }

    // Switch the child and the parent 
    if (comp_((*this)[bestChild], (*this)[index])) {
      std::swap((*this)[index], (*this)[bestChild]);    
      index = bestChild;
    }
    // If they are the same then cut the loop
    else {
      break;
    }

  }
}



#endif

