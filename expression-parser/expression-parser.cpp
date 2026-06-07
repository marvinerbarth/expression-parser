

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
    bool preWasInt = false;
    int currVal{};
    while (!input.empty()) {
        char c = input.front();
        switch (c) {
        case'*':
        case'/':
        case'+':
        case'-': {
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
            if (!preWasInt) {
                currVal = c - '0';
                preWasInt = true;
            }
            else {
                currVal = currVal * 10 + (c - '0');
            }
            
            break;
        }
        case' ': 
            break;
        default:
            /*work on stop
              so the programm wont work when a wrong input is inputed, maybe even considering rules (operator cant follow operator etc.)
            */
            std::cout << "wrong input \n";break;
        }
        input.erase(0, 1);
    }
    if(preWasInt) {
        Token n;
        n.type = 'N';
        n.value = currVal;
        n.op = ' ';
        tokens.push_back(n);
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
                while (!operat.empty() && getPrecendence(operat.top()) >= getPrecendence(t)) {
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
int evaluateRPN(std::queue<Token> rpn) {
    std::stack<int> res;
    while (!rpn.empty()) {
        Token t = rpn.front();
        if (t.type == 'N') {
            res.push(t.value);
            rpn.pop();
        }
        else if (t.type == 'O') {
            int b = res.top();
            res.pop();
            int a = res.top();
            res.pop();
            switch (t.op) {
            case'*': res.push(a * b);break;
            case'/': res.push(a / b);break;
            case'+': res.push(a + b);break;
            case'-': res.push(a - b);break;
            }
            rpn.pop();
        }

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


