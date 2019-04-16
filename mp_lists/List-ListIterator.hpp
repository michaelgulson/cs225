
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
<<<<<<< HEAD
        return *this;
    }
    
=======
        position_ = position_->next;
        return *this;
    }

>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        position_ = position_->next;
<<<<<<< HEAD
        return ListIterator(NULL);
=======
        return ListIterator(temp);
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
<<<<<<< HEAD
        return ListIterator();
=======
        ListNode* temp = position_;
        position_ = position_->prev;
        return ListIterator(temp);
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
<<<<<<< HEAD
        return false;
=======
        return (position_!=rhs.position_);
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
