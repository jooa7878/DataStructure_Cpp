// æ»ªÛ«ı, 2015405132
#include <stack>
#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <sstream>
#include <istream>
#include <strstream>

using namespace std;


int priority(char ch) {
	switch (ch) {
	case '(':
	case '{':
	case '[':
	case ')':
	case '}':
	case ']':
		return 0; break;

	case '+':
	case '-':
		return 1; break;
	case '*':
	case '/':
		return 2; break;

	default:
		return -1; break;
	}
}

bool check(istringstream& istr) {
	stack<char> symbols;
	char symbol;

	while (istr && istr.peek() != '\n') {
		if (istr.peek() == '(' || istr.peek() == '{' || istr.peek() == '[') {
			istr >> symbol;
			symbols.push(symbol);
		}

		else if (istr.peek() == ')') {
			if (symbols.top() == '(') {
				istr.ignore();
				symbols.pop();
			}
			else
				return false;
		}

		else if (istr.peek() == '}') {
			if (symbols.top() == '{') {
				istr.ignore();
				symbols.pop();
			}
			else
				return false;
		}

		else if (istr.peek() == ']') {
			if (symbols.top() == '[') {
				istr.ignore();
				symbols.pop();
			}
			else
				return false;
		}


		else
			istr.ignore();
	}

	if (!symbols.empty()) return false;
	else return true;
}

string infix_to_postfix(istringstream& istr) {
	string str;
	stack<char> s;

	const char DECIMAL = '.';
	double number;
	char operation;

	while (istr && istr.peek() != '\n') {
		if (istr.peek() == '(' || istr.peek() == '{' || istr.peek() == '[') {
			istr >> operation;
			s.push(operation);
		}


		else if (isdigit(istr.peek()) || istr.peek() == DECIMAL) {
			istr >> number;
			str += to_string(number);
			str += ' ';
		}


		else if (strchr("+-*/", istr.peek()) != NULL) {

			istr >> operation;
			while (!s.empty() && s.top() != '(' && s.top() != '{' && s.top() != '[' && priority(s.top()) >= priority(operation)) {
				str += s.top();
				s.pop();
			}
			s.push(operation);

		}


		else if (istr.peek() == ')') {
			istr.ignore();
			while (s.top() != '(') {
				str += s.top();
				str += ' ';
				s.pop();
			}
			s.pop();
		}

		else if (istr.peek() == '}') {
			istr.ignore();
			while (s.top() != '{') {
				str += s.top();
				str += ' ';
				s.pop();
			}
			s.pop();
		}

		else if (istr.peek() == ']') {
			istr.ignore();
			while (s.top() != '[') {
				str += s.top();
				str += ' ';
				s.pop();
			}
			s.pop();
		}

		else
			istr.ignore();

	}
	if (s.size() != 0) {
		str += s.top();
		s.pop();
	}
	return str;
}

int evaluate_stack(stack<double>& numbers, char operations) {

	double operand1, operand2;

	operand2 = numbers.top();
	numbers.pop();

	operand1 = numbers.top();
	numbers.pop();

	switch (operations) {
	case '+':
		numbers.push(operand1 + operand2); break;
	case '-':
		numbers.push(operand1 - operand2); break;
	case '*':
		numbers.push(operand1 * operand2); break;
	case '/':
		if (operand2 == 0.0) {
			return -1;
		}
		else
			numbers.push(operand1 / operand2); break;
	}
	return 1;
}



void read_and_write(istream& ins) {

	stack<double> numbers;
	string str;
	double number;
	char operation;
	const char DECIMAL = '.';
	int a;

	while (1) {

		ins >> str;
		if (str == "EOI") return;

		istringstream istr(str);



		if (!check(istr)) {
			std::cout << "Error : unbalacned parenthesis" << endl;
		}
		else {

			istr >> str;
			istringstream istr2(str);

			istringstream istr3(infix_to_postfix(istr2));

			while (istr3 && istr3.peek() != 'n') {
				if (isdigit(istr3.peek()) || istr3.peek() == DECIMAL) {
					istr3 >> number;
					numbers.push(number);
				}

				else if (strchr("+-*/", istr3.peek()) != NULL) {

					istr3 >> operation;
					a = evaluate_stack(numbers, operation);


				}

				else
					istr3.ignore();

			}
			cout << fixed;
			cout.precision(3);
			if (a == 1) {
				cout << numbers.top() << endl;
				numbers.pop();
			}

			else if (a == -1) {
				cout << "Error : divided by zero" << endl;
			}


		}


	}


}

int main() {
	read_and_write(cin);
}
	
	
	