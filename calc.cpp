#include <iostream>
#include <string>
#include <exception>

class Token {
public:
	char kind;
	double value;
	Token (char ch)
		:kind(ch), value(0) {}
	Token (char ch, double val)
		:kind(ch), value(val) {}
};

class Token_stream {
public:
	Token_stream();		// make a token stream that reads from cin
	Token get();		// get (next) Token
	void putback(Token t); 		// put a Token back (to stream); doen't return a value
private:
	bool full;		// buffer occupancy
	Token buffer;		// destination for putback()
};

Token_stream::Token_stream() 
	:full(false), buffer('0') {}


void Token_stream::putback(Token t) {
	if (full) {
		throw std::runtime_error("putback() into full buffer");
	}
	full = true;		// occupado
	buffer = t;		// put t in buffer
};

Token Token_stream::get() {
	if (full) {
		full = false;		// if there's already a token in the buffer, collect it
		return buffer;
	}
	char ch;
	std::cin >> ch;
	
	switch(ch) {
	case ';':
		return Token(ch);
	case 'q':
		throw std::runtime_error("quit");
		break;
	case '(': case ')': case '+': case '-': case '*': case '/': case '%': case '{': case '}':
		return Token(ch);
		break;
	case '.':
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		std::cin.putback(ch);		//in these cases, a digit or decimal point is read to cin,
		double val;					//indicating a number is being read. Ooh number; put back the first char
		std::cin >> val;			//now that first char of number back to cin, then read the entire floating point literal
		return Token('8', val);
		break;
	default:
		throw std::runtime_error("Bad token");
	}
}

Token_stream ts;
double expression();

double primary() {
	Token t = ts.get();

	switch(t.kind) {
	case '(':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')'){
				throw std::runtime_error("expected closing ')'");
			}
			return d;
			break;
		}
	case '{':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != '}'){
				throw std::runtime_error("expected closing '}'");
			}
			return d;
			break;
		}
	case '8':
		return t.value;
		break;
	default:
		throw std::runtime_error("Primary expected");
	}
}

double term() {
	double left = primary();
	Token t = ts.get();
	
	while (true){
		switch (t.kind) {
		case '*': 
			left *= primary();
			t = ts.get();
			break;
		case '/':
			left /= primary();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression() {
	double left = term();
	Token t = ts.get();
	
	while(true){
		switch(t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		case ';':
			return left;
			break;
		case 'q':
			throw std::runtime_error("quit");
		default:
			ts.putback(t);
			return left;
		}
	}
}

int main() {

	try {
		while (true) {
			std::cout << "Enter expression (end line with ';' and enter 'q' to quit): ";
			double var_exp = expression();
			std::cout << " = " << var_exp << std::endl;
		}
	}
	
	catch(std::exception& e) {
		if (std::string(e.what()) == "quit"){
			std::cerr << "Program Quit." << std::endl;
			return 0;
		}
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Unidentified exception\n" << std::endl;
		return 2;
	}
}
