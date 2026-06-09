

#include <iostream>
#include <vector>     
#include <stack>      
#include <queue>      
#include <string>    
#include <cstdlib> 

enum class Tokentype
{
    NUMBER,
    OPERATOR,
    LEFTPARENTHESIS,
    RIGHTPARENTHESIS
};
struct Token {
        Tokentype type;
        int value;
        char op;
    };
std::vector<Token> tokenize(std::string input) {
    std::vector<Token> tokens;
    bool preWasInt = false;
    bool preWasClosingParenthesis = false;
    int currVal{};

    for (char c : input) {
        
        if (c >= '0' && c <= '9') {
            if (!preWasInt) {
                currVal = c - '0';
                preWasInt = true;
            }
            else {
                currVal = currVal * 10 + (c - '0');
            }
            preWasClosingParenthesis = false;
        }
        else if(c == '+' || c == '-' || c == '*' || c == '/') {
            if (preWasInt) {
                tokens.push_back({ Tokentype::NUMBER , currVal, ' ' });
            }
            tokens.push_back({ Tokentype::OPERATOR , 0, c });
            preWasClosingParenthesis = false;
            preWasInt = false;
            currVal = 0;
        }
        else if (c == '(') {

            if (preWasInt || preWasClosingParenthesis) {
                if (preWasInt) tokens.push_back({ Tokentype::NUMBER , currVal, ' ' }); 
                
                tokens.push_back({ Tokentype::OPERATOR , 0 , '*' });
            }
            
            tokens.push_back({ Tokentype::LEFTPARENTHESIS , 0, c });
            preWasInt = false;
            preWasClosingParenthesis = false;
            currVal = 0;
        }
        else if (c == ')') {
            if (preWasInt) {
                tokens.push_back({ Tokentype::NUMBER , currVal, ' ' });
            }
            tokens.push_back({ Tokentype::RIGHTPARENTHESIS , 0, c });
            preWasClosingParenthesis = true;
            preWasInt = false;
            currVal = 0;
            
        }

        
    }

    if (preWasInt) {
        tokens.push_back({ Tokentype::NUMBER , currVal, ' ' });
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
    int parenthesis{ 0 };

    for (int i = 0; i < tokens.size(); ++i) {
        Token t = tokens[i];

        if (t.type == Tokentype::NUMBER) {
            out.push(t);
        }

        else if (t.type == Tokentype::OPERATOR) {
            while (!operat.empty()  && 
            operat.top().type == Tokentype::OPERATOR && 
            getPrecendence(operat.top()) >= getPrecendence(t)) {

                out.push(operat.top());
                operat.pop();
            }
            operat.push(t);
        }
        

        else if (t.type == Tokentype::LEFTPARENTHESIS) {
            
            operat.push(t);
            parenthesis++;
        }

        else if (t.type == Tokentype::RIGHTPARENTHESIS) {
            if (parenthesis <= 0) std::exit(0);
            while (operat.top().op != '(') {
                out.push(operat.top());
                operat.pop();
                
            }
            parenthesis--;
            if (!operat.empty()) operat.pop(); 
        }
    }
    if (parenthesis != 0) std::exit(0);

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

        if (t.type == Tokentype::NUMBER) {
            res.push(t.value);
        }

        else if (t.type == Tokentype::OPERATOR) {
            

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
    std::cout << "please enter an expression; operators availeable '+-*/' \n";
    std::string input{};
    std::getline(std::cin, input);
    std::vector<Token> tokens = tokenize(input);  
    std::queue<Token> rpnFunktion = rpn(tokens);
    int result = evaluateRPN(rpnFunktion);
    std::cout << "the entered expression equates to: " << result;
}


