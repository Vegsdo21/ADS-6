// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Cell {
    T content;
    Cell* link;
    Cell(const T& c, Cell* lnk = nullptr) : content(c), link(lnk) {}
  };

  Cell* begin;
  Cell* end;
  int length;

 public:
  TPQueue() : begin(nullptr), end(nullptr), length(0) {}

  ~TPQueue() {
    clear();
  }

  void push(const T& elem) {
    Cell* fresh = new Cell(elem);

    if (!begin || elem.prior > begin->content.prior) {
      fresh->link = begin;
      begin = fresh;
      if (!end) end = begin;
      length++;
      return;
    }

    Cell* iter = begin;
    while (iter->link && iter->link->content.prior >= elem.prior) {
      iter = iter->link;
    }

    fresh->link = iter->link;
    iter->link = fresh;

    if (!fresh->link)
      end = fresh;

    length++;
  }

  T pop() {
    if (isEmpty())
      throw std::runtime_error("Queue is empty");

    Cell* temp = begin;
    T result = temp->content;
    begin = begin->link;

    if (!begin)
      end = nullptr;

    delete temp;
    length--;
    return result;
  }

  const T& front() const {
    if (isEmpty())
      throw std::runtime_error("Queue is empty");
    return begin->content;
  }

  const T& back() const {
    if (isEmpty())
      throw std::runtime_error("Queue is empty");
    return end->content;
  }

  bool isEmpty() const {
    return begin == nullptr;
  }

  int size() const {
    return length;
  }

  void clear() {
    while (begin) {
      Cell* tmp = begin;
      begin = begin->link;
      delete tmp;
    }
    end = nullptr;
    length = 0;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
