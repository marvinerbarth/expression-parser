

#include <iostream>
#include <vector>     
#include <stack>      
#include <queue>      
#include <string>    
struct Token {
        char type;
        int value;
        char op;
    };
std::vector<Token> tokenize(std::string input) {
    std::vector<Token> tokens;
    while (!input.empty()) {
        char c = input.front();
        switch (c) {
        case'*':
        case'/':
        case'+':
        case'-': {
            Token o;
            o.type = 'O';
            o.value = 0;
            o.op = c;
            tokens.push_back(o);
            break;
        }
        case'0':
        case'1':
        case'2':
        case'3':
        case'4':
        case'5':
        case'6':
        case'7':
        case'8':
        case'9': {
            Token n;
            n.type = 'N';
            n.value = c - '0';
            n.op = ' ';
            tokens.push_back(n);
            break;
        }
        default:
            /*work on stop
              so the programm wont work when a wrong input is inputed, maybe even considering rules (operator cant follow operator etc.)
            */
            std::cout << "wrong input \n";break;
        }
        input.erase(0, 1);
    }
    return tokens;
}

int getPrecendence (Token t) {
    switch (t.op) {
        case'+':
        case'-': {
            return 1;
        }
        case'*':
        case'/': {
            return 2;
        } // operator with higher precendence added  after here
        default: return 0;
    }
}

std::queue<Token> rpn(std::vector<Token> tokens) {
    std::stack<Token> operat;
    std::queue<Token> rpn;
    for (int i = 0; i < tokens.size(); ++i) {
        Token t = tokens[i];
        if (t.type == 'N') rpn.push(t);
        else if (t.type == 'O') {
            if (operat.empty()) operat.push(t);
            else {
                while (!operat.empty() && getPrecendence(operat.top()) <= getPrecendence(t)) {
                    rpn.push(operat.top());
                    operat.pop();
                }
                operat.push(t);
            }
            
        
        }
    }
    while (!operat.empty()) {
        rpn.push(operat.top());
        operat.pop();
    }  // new types added after here
    return rpn;
}

int main()
{
    std::string input{};
    std::cin >> input;
    std::vector<Token> tokens = tokenize(input); // only numbers from 1-9 and operators "*/+-" for version 1. 
    std::queue<Token> rpnfunktion = rpn(tokens);
      
    
}


