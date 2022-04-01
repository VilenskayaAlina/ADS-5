// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
private:
  T arr[50];
  int top;
public:
  TStack() : top(-1) {}
  bool isEmpty() {
    return top == -1;
  }
  bool isFull() {
    return top == size - 1;
  }
  void push(const T&value) {
    if (!isFull())
      arr[++top] = value;
    else
      throw "Full!";
  }
  T get() {
    if (!isEmpty())
      return arr[top];
    else
      throw "Empty!";
  }
  void pop() {
    if (!isEmpty())
      --top;
    else
      throw "Empty!";
  }
#endif  // INCLUDE_TSTACK_H_
