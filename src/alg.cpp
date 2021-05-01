// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch) {
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

std::string infx2pstfx(std::string inf) {
    TStack<char>stackCh;
    std::string str;
    for (int i = 0; i < inf.length(); i++) {
        if ((inf[i] >= '0') && (inf[i] <= '9')) {
            str += inf[i];
            str += ' ';
        }
        else 
            if ((inf[i] == '(') || (priority(inf[i]) > priority(stackCh.get())) || (stackCh.isEmpty())) {
                stackCh.push(inf[i]);
            }
        else if (inf[i] == ')') {
            while (!stackCh.isEmpty() && stackCh.get() != '(') {
                str += stackCh.get();
                str += ' ';
                stackCh.pop();
            }
            if (stackCh.get() == '(')
                stackCh.pop();
        }
        else {
            while ((!stackCh.isEmpty()) && (priority(stackCh.get()) >= priority(inf[i]))) {
                str = stackCh.get();
                str += ' ';
                stackCh.pop();
            }
            stackCh.push(inf[i]);
        }
    }
    while (!stackCh.isEmpty()) {
        str += stackCh.get();
        str += ' ';
        stackCh.pop();
    }
    return str;
}
}

int eval(std::string pst) {
    TStack<int>stackCh2;
    int result;
    for (int i = 0; i < pst.length(); i++) {
        if ((pst[i] >= '0') && (pst[i] <= '9')) {
            stackCh2.push(pst[i]- '0');
        }
        else 
            if (pst[i] != ' ') {
            int y = stackCh2.get();
            stackCh2.pop();
            int x = stackCh2.get();
            stackCh2.pop();
                if (pst[i] == '-') {
                    stackCh2.push(x - y);
                }
                else if (pst[i] == '+') {
                    stackCh2.push(x + y);
                }
                else if (pst[i] == '*') {
                    stackCh2.push(x * y);
                }
                else {
                    stackCh2.push(x / y);
                }
            }
    }
    result = stackCh2.get();
    return result;
}

