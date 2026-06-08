

#include <iostream>
#include <vector>     
#include <stack>      
#include <queue>      
#include <string>    
#include <cstdlib> 

struct Token {
        char type;
        int value;
        char op;
    };
std::vector<Token> tokenize(std::string input) {
    std::vector<Token> tokens;
    bool preWasInt = false;
    int parenthesesOpened{};
    int currVal{};

    while (!input.empty()) {
        char c = input.front();

        switch (c) {
        case '*':
        case '/':
        case '+':
        case '-': {
            Token n;
            n.type = 'N';
            n.value = currVal;
            n.op = ' ';
            tokens.push_back(n);

            Token o;
            o.type = 'O';
            o.value = 0;
            o.op = c;
            tokens.push_back(o);

            preWasInt = false;
            currVal = 0;
            break;
        }

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            if (!preWasInt) {
                currVal = c - '0';
                preWasInt = true;
            }
            else {
                currVal = currVal * 10 + (c - '0');
            }
            break;
        }

        case ' ':
            break;

        case '(':
            parenthesesOpened++;
            tokens.push_back({ 'P', 0, '(' });
            break;

        case ')':
            if (parenthesesOpened > 0) {
                parenthesesOpened--;
                tokens.push_back({ 'C', 0, ')' }); 
                preWasInt = false;
                currVal = 0;
            }
            else {
                std::cout << "missing opening parenthesis\n";
                std::exit(0);
            }
            break;

        default:
            std::cout << "wrong input\n";
            std::exit(0);
        }

        input.erase(0, 1);
    }

    if (preWasInt) {
        tokens.push_back({ 'N', currVal, ' ' });
        preWasInt = false;
        currVal = 0;
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
    std::queue<Token> out;

    for (int i = 0; i < tokens.size(); ++i) {
        Token t = tokens[i];

        if (t.type == 'N') {
            out.push(t);
        }

        else if (t.type == 'O') {
            while (!operat.empty() &&
                operat.top().type == 'O' &&
                getPrecendence(operat.top()) >= getPrecendence(t)) {
                out.push(operat.top());
                operat.pop();
            }
            operat.push(t);
        }

        else if (t.type == 'P') {
            operat.push(t);
        }

        else if (t.type == 'C') {
            while (!operat.empty() && operat.top().op != '(') {
                out.push(operat.top());
                operat.pop();
            }
            if (!operat.empty()) operat.pop(); // remove '('
        }
    }

    while (!operat.empty()) {
        out.push(operat.top());
        operat.pop();
    }

    return out;
}
int evaluateRPN(std::queue<Token> rpn) {
    std::stack<int> res;

    while (!rpn.empty()) {
        Token t = rpn.front();

        if (t.type == 'N') {
            res.push(t.value);
        }

        else if (t.type == 'O') {
            

            int b = res.top(); res.pop();
            int a = res.top(); res.pop();

            switch (t.op) {
            case '*': res.push(a * b); break;
            case '/': res.push(a / b); break;
            case '+': res.push(a + b); break;
            case '-': res.push(a - b); break;
            }
        }

        rpn.pop();
    }

    return res.top();
}

int main(){
    std::cout << "please enter an expression with with the limitation of operators '*/+-': \n";
    std::string input{};
    std::getline(std::cin, input);
    std::vector<Token> tokens = tokenize(input);  
    std::queue<Token> rpnFunktion = rpn(tokens);
    int result = evaluateRPN(rpnFunktion);
    std::cout << "the entered expression equates to: " << result;
}


