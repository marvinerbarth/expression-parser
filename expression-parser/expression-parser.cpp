

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

int main()
{
    std::string input{};
    std::cin >> input;
    std::vector<Token> tokens = tokenize(input); // only numbers from 1-9 and operators "*/+-" for version 1. 
    
}


