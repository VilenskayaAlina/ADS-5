// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
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
};
#endif
// INCLUDE_TSTACK_H_

int calculation(char op, int x, int y) {
  switch (op) {
  case '+': return (x + y);
  case '-': return (y - x);
  case '*': return (x * y);
  case '/':
    if (x != 0)
      return y / x;
  default: return 0;
  }
}

int priority(char op) {
  switch (op) {
  case '(': return 0;
  case ')': return 1;
  case '-': return 2;
  case '+': return 2;
  case '*': return 3;
  case '/': return 3;
  default: return 4;
  }
}
std::string infx2pstfx(std::string inf) {
  char prob = ' ';
  std::string res;
  TStack <char, 50> stack;
  for (int i = 0; i < inf.size(); i++) {
    if (priority(inf[i]) == 4) {
      res.push_back(inf[i]);
      res.push_back(prob);
    }
    else {
      if (priority(inf[i]) == 0) {
        stack.push(inf[i]);
      }
      else if (priority(inf[i]) == 1) {
        while (priority(stack.get()) != 0) {
          res.push_back(stack.get());
          res.push_back(prob);
          stack.pop();
        }
        stack.pop();
      }
      else if (stack.isEmpty()) {
        stack.push(inf[i]);
      }
      else if ((priority(inf[i]) > priority(stack.get()))) {
        stack.push(inf[i]);
      }
      else {
        while ((priority(inf[i]) <= priority(stack.get())) && !stack.isEmpty()) {
          stack.pop();
        }
        stack.push(inf[i]);
      }
    }
  }
  while (!stack.isEmpty()) {
    res.push_back(stack.get());
    res.push_back(prob);
    stack.pop();
  }
  for (int i = 0; i < res.size(); i++) {
    if (res[res.size() - 1] == ' ')
      res.erase(res.size() - 1);
  }
  return res;
  return std::string("");
}

int eval(std::string pref) {
  TStack <int, 50> res_stack;
  int res = 0;
  int x, y;
  for (int i = 0; i < pref.size(); i++) {
    if (priority(pref[i]) == 4) {
      res_stack.push(pref[i] - '0');
    }
    else if (priority(pref[i]) < 4) {
      x = res_stack.get();
      res_stack.pop();
      y = res_stack.get();
      res_stack.pop();
      res_stack.push(calculation(pref[i], x, y));
    }
  }
  res = res_stack.get();
  return res;
  return 0;
}
