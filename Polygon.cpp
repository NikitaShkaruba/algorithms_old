#include <iostream>
#include <cassert> 
#include <algorithm>
#include <cmath>
using namespace std;

namespace Stepic {
	// arrays
	int ** Create2dArray(size_t x, size_t y) {
		// low heap fragmentation method
		int ** arr = new int *[x];
		arr[0] = new int[x*y];
		for (size_t i = 1; i < x; i++)
			arr[i] = arr[i - 1] + y;
		return arr;
	}
	void free2dArray(int ** arr) {
		delete[] arr[0];
		delete[] arr;
	}
	void swap_min(int **mt, int m, int n) {
		int min = mt[0][0], minI = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (mt[i][j] < min) {
					min = mt[i][j];
					minI = i;
				}
		if (minI != 0) {
			int * buf = mt[0];
			mt[0] = mt[minI];
			mt[minI] = buf;
		}
	}
	int ** transpose(const int * const * m, size_t x, size_t y) {
		int ** mt = new int *[y];
		mt[0] = new int[x*y];

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++)
				mt[i][j] = m[j][i];
			mt[i + 1] = mt[i] + x;
		}
		return mt;
	}
	void printArray(const int * const * m, size_t x, size_t y) {
		cout << "****array****" << endl;
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++)
				cout << m[i][j] << " ";
			cout << endl;
		}
	}
	// strings
	class String {
	private:
		char *str_;
	public:
		String(const String &str) {
			this->str_ = new char[str.size() + 1];
			strcpy(this->str_, str.c_str());
		}
		String(const char *str = "") {
			str_ = new char[strlen(str)];
			strcpy(this->str_, str);
		}
		String(size_t n, char c) {
			this->str_ = new char[n];
			for (int i = 0; i < n; i++)
				str_[i] = c;
		}
		~String() {
			delete[] this->str_;
		}

		String &operator=(const String &str) {
			if (this != &str) {
				String pattern(str);

				char *buf = this->str_;
				this->str_ = pattern.str_;
				pattern.str_ = buf;
			}
		}
		size_t size() const {
			return strlen(this->str_);
		}
		char &at(size_t idx) const {
			return str_[idx];
		}
		const char *c_str() const {
			return this->str_;
		}
		int compare(String &str) const {
			int thisSize = this->size();
			int thatSize = str.size();
			bool isThisFewer = this->size() < str.size() ? true : false;
			int minlen = isThisFewer ? thisSize : thatSize;

			for (int i = 0; minlen; i++) {
				if (this->at(i) == str.at(i))
					continue;

				if (this->at(i) > str.at(i))
					return 1;
				if (this->at(i) < str.at(i))
					return -1;
			}

			if (thisSize == thatSize)
				return 0;
			return isThisFewer ? -1 : 1;
		}
		void append(String &str) {
			char *buf = this->str_;
			this->str_ = new char[this->size() + str.size() + 1];

			// copy
			for (int i = 0; buf[i] != '\0'; i++)
				this->str_[i] = buf[i];
			// append
			for (int i = 0; str.at(i) != '\0'; i++)
				this->str_[strlen(buf) + i] = str.at(i);
			str_[strlen(buf) + str.size()] = '\0';
			
			delete[] buf;
		}
	};
	unsigned int strlen(const char *str) {
		int i = 0;
		for (; *(str + i) != '\0'; i++);
		return i;
	}
	int strstr(const char *str, const char *pattern) {
		int i = 0, j = 0; // i - str index, j - pattern index
		while (str[i] != '\0') {
			for (; str[i] == pattern[j]; i++, j++) {
				if (pattern[j] == '\0')
					return j;
			}
			i -= j + 1; //  +1 means i++
			j = 0;
		}
		return -1;
	}
	void strcat(char *to, const char *from) {
		// counting *to symbols
		int x = 0;
		while (to[x] != '\0')
			x++;
		// concat them
		for (int i = 0; from[i] != '\0'; i++)
			to[x++] = from[i];
		to[x] = '\0';
	}
	// I/O
	char *getline() {
		int count = 0, memory = 2;
		char next;
		char *result = new char[memory];
		while (cin.get(next)) {
			// end of line
			if (next == '\n')
				break;
			// if overflow        
			if (count + 1 > memory) {
				char *buf = result;
				result = new char[memory *= 2];
				for (int i = 0; i < count; i++)
					result[i] = buf[i];
				delete[] buf;
			}
			// add to a string
			result[count] = next;
			count++;
		}
		result[count] = '\0';
		return result;
	}
	void getclearline() {
		char last, next;

		// w8 until first symbols are blanks
		while (cin.get(next) && next == ' ');
		cout << next;
		last = next;

		// logic
		while (cin.get(next)) {
			if (last != ' ' || next != ' ')
				cout << next;
			last = next;
		}
	}
	// Object-oriented programming
	struct Scope {
		virtual ~Scope() { }
		virtual double variableValue(std::string const &name) const = 0;
	};
	struct Expression {
		virtual ~Expression() {}

		virtual double evaluate(Scope* s) const {}
	};
	struct Number : Expression {
		Number(double value) : value_(value) {}
	
		double value() const {
			return value_;
		}
		double evaluate(Scope* s) const {
			return value_;
		}
	
	private:
		double value_;
	};
	struct BinaryOperation : Expression {
		BinaryOperation(Expression const *left, int op, Expression const *right) : left_(left), op_(op), right_(right) {
			assert(left_ && right_);
		}
		~BinaryOperation() {
			delete left_;
			delete right_;
		}

		Expression const *left() const {
			return left_;
		}
		Expression const *right() const {
			return right_;
		}
		int operation() const {
			return op_;
		}
		double evaluate(Scope* s) const {
			double left = left_->evaluate(s);
			double right = right_->evaluate(s);
	
			switch (op_) {
				case PLUS: return left + right;
				case MINUS: return left - right;
				case DIV: return left / right;
				case MUL: return left * right;
			}
			assert(0);
			return 0.0;
		}
	
	private:
		enum {
			PLUS = '+',
			MINUS = '-',
			DIV = '/',
			MUL = '*'
		};
		Expression const *left_;
		Expression const *right_;
		int op_;
	};
	struct FunctionCall : Expression {
		FunctionCall(std::string const &name, Expression const *arg) : name_(name), arg_(arg) {
			assert(arg_);
			assert(name_ == "sqrt" || name_ == "abs");
		}
		~FunctionCall() {
			delete arg_;
		}

		std::string const & name() const {
			return name_;
		}
		Expression const *arg() const {
			return arg_;
		}
		double evaluate(Scope* s) const {
			double value = arg_->evaluate(s);
			if (name_ == "sqrt")
				return std::sqrt(value);
			if (name_ == "abs")
				return value < 0 ? -value : value;
		}

	private:
		std::string const name_;
		Expression const *arg_;
	};
	struct Variable : Expression {
		Variable(std::string const &name) : name_(name) { }
		
		std::string const &name() const { return name_; }
		double evaluate(Scope* s) const {
			return s->variableValue(name_);
		}
	
	private:
		std::string const name_;
	};
	struct Rational
	{
		Rational(int numerator = 0, int denominator = 1);
		double to_double() const {

		}

		Rational inverse() const {
			return Rational(_numerator > 0 ? _denominator : -(int)_denominator, (unsigned)_numerator);
		}
		Rational operator +() const {
			// It's not abs() guys, trust me
			return Rational(_numerator, _denominator);
		}
		Rational operator -() const {
			return Rational(-_numerator, _denominator);
		}
		Rational & operator +=(Rational const & rnl) {
			unsigned sharedD = _lcm(_denominator, rnl._denominator);
			_numerator = (this->_denominator == sharedD ? _denominator : _denominator * sharedD / rnl._denominator) +
				(rnl._denominator == sharedD ? rnl._denominator : rnl._denominator * sharedD / _denominator);
			this->_simplify();

			return *this;
		}
		Rational & operator -=(Rational const & rnl) {
			return *this += -rnl;;
		}
		Rational & operator *=(Rational const & rnl) {
			_numerator *= rnl._numerator;
			_denominator *= rnl._denominator;
			this->_simplify();

			return *this;
		}
		Rational & operator /=(Rational const & rnl) {
			*this *= rnl.inverse();
			return *this;
		}

	private:
		int _numerator;
		unsigned _denominator;

	protected:
		void _simplify() {
			while (int devisor = _gcd(_denominator, _numerator) != 1) {
				_numerator /= devisor;
				_denominator /= devisor;
			}
		}
		// Greater common divisor
		int _gcd(int a, int b) { 
			return b == 0 ? a : _gcd(b, a % b);
		}
		// Loweer common multiplier
		int _lcm(int a, int b) { 
			return a * b / _gcd(a, b);
		}
	};
	// Some hacky things
	bool isEqualType(Expression const *left, Expression const *right) {
		// check for type equal
		int vptrLeft = *(int*)left;
		int vptrRight = *(int*)right;

		if (vptrLeft == vptrRight)
			return true;
		else
			return false;
	}
}

void main() {
	using namespace Stepic;

	cout << "result is: ";
	cout << "Press any key to continue...";
}