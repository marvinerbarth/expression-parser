

#include <iostream>
#include <vector>     
#include <stack>      
#include <queue>      
#include <string>    
#include <cstdlib> 
#include <variant>
#include <string_view>

enum class Tokentype
{
    NUMBER,
    OPERATOR,
    LEFTPARENTHESIS,
    RIGHTPARENTHESIS, 
    UNARYMINUS
};
struct Token {
        Tokentype type;
        std::variant<int, char> value;
    };
std::vector<Token> tokenize(std::string_view input) {
    std::vector<Token> tokens;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        
        if (std::isspace(static_cast<unsigned char>(c))) {
            continue;
        }

        
        if (std::isdigit(static_cast<unsigned char>(c))) {
            int val = 0;

            
            while (i < input.size() && std::isdigit(static_cast<unsigned char>(input[i]))) {
                val = (val * 10) + (input[i] - '0');
                i++;
            }
            i--; 

            tokens.emplace_back(Token{ Tokentype::NUMBER, val});
        }
        
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            tokens.emplace_back(Token{ Tokentype::OPERATOR, c});
        }
        else if (c == '(') {
            tokens.emplace_back(Token{ Tokentype::LEFTPARENTHESIS, c });
        }
        else if (c == ')') {
            tokens.emplace_back(Token{ Tokentype::RIGHTPARENTHESIS, c });
        }
    }

    return tokens;
}

int getPrecendence ( const Token t) {
    if (const char* c = std::get_if<char>(&t.value)) {
        switch (*c) {
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
}

std::queue<Token> rpn(const std::vector<Token>& tokens) {
    std::stack<Token> operat;
    std::queue<Token> out;
    int parenthesis{ 0 };
    int implicitMult{ 0 };

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
            if (i > 0 && tokens[i-1].type != Tokentype::OPERATOR) {
                implicitMult++;
            }
            operat.push(t);
            parenthesis++;
        }

        else if (t.type == Tokentype::RIGHTPARENTHESIS) {
            if (parenthesis <= 0) std::exit(0);
            while (operat.top().type != Tokentype::LEFTPARENTHESIS) {
                out.push(operat.top());
                operat.pop();
                
            }
            if (implicitMult > 0) {
                out.push(Token{ Tokentype::OPERATOR, '*' });
                implicitMult--;
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
            res.push(std::get<int>(t.value));
        }

        else if (t.type == Tokentype::OPERATOR) {
            

            int b = res.top(); res.pop();
            int a = res.top(); res.pop();
            if (const char* c = std::get_if<char>(&t.value)) {
                switch (*c) {
                case '*': res.push(a * b); break;
                case '/': res.push(a / b); break;
                case '+': res.push(a + b); break;
                case '-': res.push(a - b); break;
                }
            }
        }

        rpn.pop();
    }

    return res.top();
}
int main() {
    std::cout << "Enter expressions using '+-*/'. Press 0 to exit.\n\n";
    std::string input{};

    while (std::cout << "please enter an expression: " && std::getline(std::cin, input)) {
        if (input.empty()) {
            continue;
        }if (input == "0") {
            std::exit(0);
        }

        std::vector<Token> tokens = tokenize(input);
        std::queue<Token> rpnFunktion = rpn(tokens);
        int result = evaluateRPN(rpnFunktion);

        std::cout << "the entered expression equates to: " << result << "\n\n";
    }

    return 0;
}


