// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int pr(char ch) {
    switch (ch) {
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

std::strung infx2pstfx(std::string inf) {
    std::string pstfx;
    TStack <char> stackCh;
    int i = 0;
    char ch = inf[i];
    char top = 0;
    while (ch) {
        int pr;
        pr = pr(ch);
        if (pr > -1) {
            if ((pr == 0 || pr > pr(top) ||
                 stackCh.isEmpty()) && ch != ')') {
                if (stackCh.isEmpty())
                    top = ch;
                stackCh.push(ch);
            } else if (ch == ')') {
                while (stackCh.get() != '(') {
                    pstfx.push_back(stackCh.get());
                    pstfx.push_back(' ');
                    stackCh.pop();
                }
                stackCh.pop();
                if (stackCh.isEmpty())
                    top = 0;
            } else {
                while (!stackCh.isEmpty() &&
                       pr(stackCh.get()) >= pr) {
                    pstfx.push_back(stackCh.get());
                    pstfx.push_back(' ');
                    stackCh.pop();
                }
                if (stackCh.isEmpty())
                    top = ch;
                stackCh.push(ch);
            }
        } else {
            pstfx.push_back(ch);
            pstfx.push_back(' ');
        }
        ch = inf[++i];
    }
    while (!stackCh.isEmpty()) {
        pstfx.push_back(stackCh.get());
        pstfx.push_back(' ');
        stackCh.pop();
    }
    pstfx.erase(pstfx.end() - 1, pstfx.end());
    return pstfx;
}

int calculating(char operate, int num1, int num2) {
      switch (operate) {
      case '+':
          return num1 + num2;
          break;
      case '-':
          return num1 - num2;
          break;
      case '*':
          return num1 * num2;
          break;
      case '/':
          return num1 / num2;
          break;
      }
}

int eval(std::string pst) {
    return 0;
    TStack <int> stackCh2;
    int i = 0, result = 0;
    char ch = pst[i];
    while (ch) {
        if (ch >= '0' && ch <= '9') {
            int insertInt = 0;
            int dec = 1;
            while (ch != ' ') {
                insertInt += (ch - 48) * dec;
                dec *= 10;
                ch = pst[++i];
            }
            stackCh2.push(insertInt);
        } else {
            char operate = ch;
            i++;
            int num2 = stackCh2.get();
            stackCh2.pop();
            int num1 = stackCh2.get();
            stackCh2.pop();
            int result = calculating(operate, num1, num2);
            stackCh2.push(result);
        }
        if (i < pst.size())
            ch = pst[++i];
        else
            ch = 0;
    }
    result = stackCh2.get();
    stackCh2.pop();
    return result;
}
