export module BigInteger;
import <vector>;
import <iostream>;

using i64 = int64_t;

export class BigInteger {
private:
	std::vector<short> digits;
	bool negative;
	int __size();
	void __init(std::string num);
	void __init(i64 num);
	bool __empty();
	void __trim_left();
	BigInteger __add_two_positive(BigInteger &val);
	BigInteger __sub_two_positive(BigInteger val);
	BigInteger __mult_two_positive(BigInteger &val);
	BigInteger __add_two_negative(BigInteger &val);
	static BigInteger __sub(BigInteger val1,BigInteger val2);
	BigInteger __mult_two_negative(BigInteger &val);
	BigInteger __mult_with_one_negative(BigInteger &val);
public:
	// Constructors
	BigInteger(std::string num);
	BigInteger(i64 num);
	BigInteger();
	// Assignment
	BigInteger operator=(BigInteger val);
	BigInteger operator=(std::string num);
	BigInteger operator=(i64 num);
	// Updation
	BigInteger operator++();
	BigInteger operator++(int);
	// Arthematical
	BigInteger operator*(BigInteger val);
	BigInteger operator+(BigInteger val);
	BigInteger operator+(std::string val);
	BigInteger operator+(i64 val);
	BigInteger operator-(BigInteger val);
	// Relational
	bool operator==(BigInteger val);
	bool operator>(BigInteger val);
	bool operator<(BigInteger val);
	bool operator<=(BigInteger val);
	bool operator>=(BigInteger val);

	friend std::ostream& operator<<(std::ostream& out, BigInteger bigint);
};

int BigInteger::__size() {
	return digits.size();
}

bool BigInteger::__empty() {
	return (this->__size() == 0);
}

void BigInteger::__init(std::string num) {
	if (num[0] == '-')
		negative = true;
	num = (negative) ? std::string(num.begin() + 1, num.end()) : num;
	for (char dig : num ){
		digits.push_back(dig - '0');
	}
	__trim_left();
}

void BigInteger::__init(i64 num) {
	if (num < 0) {
		negative = true;
		num = num * (-1);
	}
	while (num > 0) {
		digits.insert(digits.begin(), (num % 10));
		num /= 10;
	}
	__trim_left();
}

void BigInteger::__trim_left() {
	int count{ 0 };
	for (short s : digits) {
		if (s == 0)
			++count;
		else
			break;
	}
	digits = std::vector<short>(digits.begin() + count, digits.end());
}

BigInteger BigInteger::__add_two_positive(BigInteger &val) {
	int carry = 0;
	BigInteger sum;
	sum.negative = false;
	int i = this->__size()-1, j = val.__size()-1;
	for (; i >= 0 && j >= 0; --i, --j) {
		int dig = this->digits[i] + val.digits[j] + carry;
		if (dig > 9) {
			carry = dig / 10;
		}
		else {
			carry = 0;
		}
		sum.digits.insert(sum.digits.begin(), (dig % 10));
	}
	for (; i >= 0; --i) {
		int dig = this->digits[i] + carry;
		if (dig > 9) {
			carry = dig / 10;
		}
		else {
			carry = 0;
		}
		sum.digits.insert(sum.digits.begin(), (dig % 10));
	}
	for (; j >= 0; --j) {
		int dig = val.digits[j] + carry;
		if (dig > 9) {
			carry = dig / 10;
		}
		else {
			carry = 0;
		}
		sum.digits.insert(sum.digits.begin(), (dig % 10));
	}
	if(carry > 0)
		sum.digits.insert(sum.digits.begin(), (carry));
	return sum;
}

BigInteger BigInteger::__mult_two_positive(BigInteger& val) {
	BigInteger product{};
	product.negative = false;
	int carry = 0;

	if (this->__empty() || val.__empty())
		return BigInteger(0);
	
	int t_size{ this->__size() - 1 }, v_size{ val.__size() - 1 };
	int i{ 0 }, j{ 0 };
	for (; i <= t_size; ++i) {
		BigInteger temp{};
		for (int k = 0; k < i; ++k) {
			temp.digits.push_back(0);
		}
		j = 0;
		carry = 0;
		for (; j <= v_size; ++j) {
			int prod = (this->digits[t_size - i] * val.digits[v_size - j]) + carry;
			if (prod > 9) {
				carry = prod / 10;
			}
			else {
				carry = 0;
			}
			temp.digits.insert(temp.digits.begin(), (prod % 10));
		}
		if(carry > 0) 
			temp.digits.insert(temp.digits.begin(), (carry));
		product = product + temp;
	}
	return product;
}

BigInteger BigInteger::__sub(BigInteger val1, BigInteger val2) {
	int carry = 0;
	int v1_size = val1.__size() - 1, v2_size = val2.__size() - 1;
	int i  = 0;
	BigInteger value;

	for (; i <= v2_size; ++i) {
		int diff = val1.digits[v1_size - i] - val2.digits[v2_size - i] - carry;
		if (diff < 0) {
			carry = 1;
			diff = diff + 10;
		}
		else {
			carry = 0;
		}
		value.digits.insert(value.digits.begin(), diff);
	}
	for (; i <= v1_size; ++i) {
		int diff = val1.digits[v1_size - i] -  carry;
		if (diff < 0) {
			carry = 1;
			diff = diff + 10;
		}
		else {
			carry = 0;
		}
		value.digits.insert(value.digits.begin(), diff);
	}
	return value;
}

BigInteger BigInteger::__sub_two_positive(BigInteger val) {
	if (*this > val) {
		return __sub(*this, val);
	}
	else if (*this < val) {
		BigInteger diff = __sub(val, *this);
		diff.negative = true;
		return diff;
	}
	else if (*this == val) {
		return BigInteger(0);
	}
}

BigInteger BigInteger::__add_two_negative(BigInteger &val) {
	BigInteger sum = __add_two_positive(val);
	sum.negative = true;
	return sum;
}
BigInteger BigInteger::__mult_two_negative(BigInteger &val) {
	BigInteger product = __mult_two_positive(val);
	product.negative = false;
	return product;
}

BigInteger BigInteger::__mult_with_one_negative(BigInteger &val) {
	BigInteger product = __mult_two_positive(val);
	product.negative = true;
	return product;
}

BigInteger::BigInteger() : digits{}, negative{false}{}
BigInteger::BigInteger(std::string num) : digits{}, negative{ false } {
	__init(num);
}

BigInteger::BigInteger(i64 num) : digits{}, negative{ false } {
	__init(num);
}

BigInteger BigInteger::operator=(BigInteger val) {
	*this = val;
	return *this;
}

BigInteger BigInteger::operator=(std::string num) {
	this->digits.clear();
	__init(num);
	return *this;
}
BigInteger BigInteger::operator=(i64 num) {
	this->digits.clear();
	__init(num);
	return *this;
}

bool BigInteger::operator==(BigInteger val) {
	if (this->negative != val.negative) return false;
	if (this->__size() != val.__size()) return false;
	int size = this->__size();
	for (int i = 0; i < size; ++i) {
		if (this->digits[i] != val.digits[i]) return false;
	}
	return true;
}

bool BigInteger::operator>(BigInteger val) {

	if (this->negative)
		if (!val.negative) return false;
	if (!this->negative)
		if (val.negative) return true;
	if (*this == val) return false;
	int t_size = this->__size() - 1, v_size = val.__size()-1;
	if (this->negative && val.negative) {
		if (t_size > v_size) return false;
		else if (t_size < v_size) return true;
		else {
			for (int i = 0; i <= t_size; ++i) {
				if (this->digits[i] == val, digits[i]) continue;
				else if (this->digits[i] > val.digits[i]) return false;
				else if (this->digits[i] < val.digits[i]) return true;
			}
		}
	}
	else {
		if (t_size < v_size) return false;
		else if (t_size > v_size) return true;
		else {
			for (int i = 0; i <= t_size; ++i) {
				if (this->digits[i] == val.digits[i]) continue;
				else if (this->digits[i] > val.digits[i]) return true;
				else if (this->digits[i] < val.digits[i]) return false;
			}
		}
	}
}

bool BigInteger::operator<(BigInteger val) {
	if (*this > val || *this == val) return false;
	return true;
}

bool BigInteger::operator<=(BigInteger val) {
	if (*this < val || *this == val) return true;
	return false;
}
bool BigInteger::operator>=(BigInteger val) {
	if (*this > val || *this == val) return true;
	return false;
}

BigInteger BigInteger::operator+(BigInteger val) {
	if (!this->negative) {
		if (!val.negative)
			return __add_two_positive(val);
		else {
			BigInteger b = val;
			b.negative = false;
			BigInteger temp = *this - b;
			return temp;
		}
	}
	else if (this->negative) {
		if (val.negative) {
			return __add_two_negative(val);
		}
		else {
			BigInteger a = *this;
			a.negative = false;
			return val - a;
		}
	}
}

BigInteger BigInteger::operator*(BigInteger val) {
	if (!(this->negative || val.negative))
		return __mult_two_positive(val);
	else if (this->negative && val.negative)
		return __mult_two_negative(val);
	else if (this->negative ^ val.negative)
		return __mult_with_one_negative(val);
	return BigInteger(0);
}

BigInteger BigInteger::operator++() {
	*this = *this + BigInteger(1);
	return *this;
}

BigInteger BigInteger::operator++(int) {
	BigInteger temp = *this;
	*this = *this + BigInteger(1);
	return temp;
}

BigInteger BigInteger::operator+(std::string val) {
	return *this + BigInteger(val);
}

BigInteger BigInteger::operator+(i64 val) {
	return *this + BigInteger(val);
}

BigInteger BigInteger::operator-(BigInteger val) {
	if (!this->negative) {
		if (val.negative) {
			BigInteger b = val;
			b.negative = false;
			return *this + b;
		}
		else
			return __sub_two_positive(val);
	}
	else if (this->negative) {
		if (val.negative)
			return val - *this;
		else {
			BigInteger a = *this;
			a.negative = false;
			BigInteger temp = a + val;
			temp.negative = true;
			return temp;
		}
	}
}

export std::ostream& operator<<(std::ostream& out, BigInteger bigint) {
	if (bigint.__empty()) {
		out << 0;
		return out;
	}
	if (bigint.negative) out << "-";
	for (short d : bigint.digits) {
		out << d;
	}
	return out;
}