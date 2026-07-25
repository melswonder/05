#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint
{
private:
	std::string value; // 10進数の文字列（先頭ゼロなし）

public:
	bigint() : value("0") {}
	bigint(unsigned long long num) : value(std::to_string(num)) {}
	bigint(const bigint &other) : value(other.value) {}

	bigint &operator=(const bigint &other)
	{
		value = other.value;
		return *this;
	}

	// 加算（筆算と同じ：下の桁から1桁ずつ足して繰り上がりを持ち越す）
	bigint operator+(const bigint &other) const
	{
		std::string rev; // 結果を下の桁から溜める
		int i = value.size() - 1;
		int j = other.value.size() - 1;
		int carry = 0;

		while (i >= 0 || j >= 0 || carry)
		{
			int sum = carry;
			if (i >= 0)
				sum += value[i--] - '0';
			if (j >= 0)
				sum += other.value[j--] - '0';
			rev.push_back('0' + sum % 10);
			carry = sum / 10;
		}

		bigint result;
		result.value.assign(rev.rbegin(), rev.rend());
		return result;
	}
	bigint &operator+=(const bigint &other)
	{
		*this = *this + other;
		return *this;
	}

	// インクリメント
	bigint &operator++()
	{
		*this += 1;
		return *this;
	}
	bigint operator++(int)
	{
		bigint tmp(*this);
		*this += 1;
		return tmp;
	}

	// 10進シフト
	bigint &operator<<=(size_t n)
	{
		if (value != "0")
			value.append(n, '0');
		return *this;
	}
	bigint &operator>>=(size_t n)
	{
		if (n >= value.size())
			value = "0";
		else
			value.erase(value.size() - n);
		return *this;
	}
	bigint operator<<(size_t n) const
	{
		bigint tmp(*this);
		return tmp <<= n;
	}
	bigint operator>>(size_t n) const
	{
		bigint tmp(*this);
		return tmp >>= n;
	}

	// 比較（桁数が違えば桁数で、同じなら辞書順で比較できる）
	bool operator<(const bigint &other) const
	{
		if (value.size() != other.value.size())
			return value.size() < other.value.size();
		return value < other.value;
	}
	bool operator>(const bigint &other) const { return other < *this; }
	bool operator<=(const bigint &other) const { return !(other < *this); }
	bool operator>=(const bigint &other) const { return !(*this < other); }
	bool operator==(const bigint &other) const { return value == other.value; }
	bool operator!=(const bigint &other) const { return value != other.value; }

	friend std::ostream &operator<<(std::ostream &os, const bigint &num)
	{
		return os << num.value;
	}
};

#endif
