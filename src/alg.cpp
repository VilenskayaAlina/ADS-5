// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

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
  std::string res;
  char prob = ' ';
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
      else if (stack.isEmpty()) {
        stack.push(inf[i]);
      }
      else if ((priority(inf[i]) > priority(stack.get()))) {
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
}

int eval(std::string pref) {
  TStack <int, 50> res_stack;
  int res = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < pref.size(); i++) {
    if (priority(pref[i]) == 4) {
      res_stack.push(pref[i] - '0');
    } else if (priority(pref[i]) < 4) {
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
