// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int p(char count) {
    switch (count) {
      case '(':
          return 0;
      case ')':
          return 1;
      case '+':
      case '-':
          return 2;
      case '*':
      case '/':
          return 3;
      default:
          return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    TStack<char> stack;
    std::string r;

    for (int i = 0; i < inf.length(); i++) {
        if ((inf[i] >= '0') && (inf[i] <= '9')) {
            r += inf[i];
            r += ' ';
        } else if (inf[i] == '(') {
            stack.push(inf[i]);
        } else if (p(inf[i]) > p(stack.get()) || stack.isEmpty()) {
            stack.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!stack.isEmpty() && stack.get() != '(') {
                r += stack.get();
                r += ' ';
                stack.pop();
            }

            if (stack.get() == '(') {
               stack.pop();
            }
        } else {
            while (!stack.isEmpty() && p(stack.get()) >= p(inf[i])) {
                r += stack.get();
                r += ' ';
                stack.pop();
            }

            stack.push(inf[i]);
        }
    }

    while (!stack.isEmpty()) {
        r += stack.get();
        r += ' ';
        stack.pop();
    }

    while (r[r.length() - 1] == ' ') {
        r = r.substr(0, r.length()-1);
    }

    return r;
}
int eval(std::string pst) {
    TStack<int> stack;
    for (int i = 0; i < pst.length(); i++) {
        if ((pst[i] >= '0') && (pst[i] <= '9')) {
            stack.push(pst[i] - '0');
        } else if (pst[i] != ' ') {
            int second = stack.get();
            stack.pop();
            int first = stack.get();
            stack.pop();

            if (pst[i] == '-') {
                stack.push(first - second);
            } else if (pst[i] == '+') {
                stack.push(first + second);
            } else if (pst[i] == '*') {
                stack.push(first * second);
            } else {
                stack.push(first / second);
            }
        }
    }

    return stack.get();
}

