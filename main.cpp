#include <iostream>
#include <string>
#include <cmath>

class Fraction
{
private:
	int numerator;
	int denominator;
	//плавающая точка
	int GetDigitAfterDot(double value)const
	{
		std::string temp = std::to_string(value);
		int pointPosition = temp.find(",");
		std::string digitsAfterDot = temp.substr(pointPosition + 1);
		
		return std::stoi(digitsAfterDot);
	}

	int gcd(int a, int b)const
	{
		if (a % b == 0) return b;
		if (b % a == 0) return a;
		if (a > b) return gcd(a % b, b);
		return gcd(a, b % a);
	}

	//для операторовматематики приведение дроби
	int BringFraction(Fraction x)
	{
		int xNum = x.numerator;
		if (denominator != x.denominator)
		{
			int cd = denominator * x.denominator;

			xNum *= cd / x.denominator;
			numerator *= cd / denominator;

			denominator = cd;
		}
		return xNum;
	}

public:
	//проверка правильности свойства
	bool isFractionRight()const
	{
		return numerator < denominator;
	}

	bool isfraction()const
	{
		return numerator % denominator == 0;
	}

	//данные из дроби
	int GetNumBefDot()const
	{
		return numerator / denominator;
	}
	int GetNumAfterDot()const
	{
		return numerator % denominator;
	}
	Fraction GetReversedFraction()const
	{
		return Fraction(denominator, numerator);
	}

	//операторы математики
	void Add(Fraction x)
	{
		numerator += BringFraction(x);
	}

	void Subtract(Fraction x)
	{
		numerator -= BringFraction(x);
	}

	void Multiply(Fraction x)
	{
		numerator *= x.numerator;
		denominator *= x.denominator;
	}
	void Divide(Fraction x)
	{
		Multiply(x.GetReversedFraction());
	}

	//изменение полей
	void SetNumerator(int value)
	{
		numerator = value;
	}
	void SetDenominator(int value)
	{
		denominator = value;
	}
	//
	int GetNumerator() const
	{
		return numerator;
	}
	int GetDenominator() const
	{
		return denominator;
	}
	//операторы
	Fraction operator + (Fraction x)
	{
		Add(x);
		return Fraction(numerator, denominator);
	}
	Fraction operator - (Fraction x)
	{
		Subtract(x);
		return Fraction(numerator, denominator);
	}
	Fraction operator * (Fraction x)
	{
		Multiply(x);
		return Fraction(numerator, denominator);
	}
	Fraction operator / (Fraction x)
	{
		Divide(x);
		return Fraction(numerator, denominator);
	}

	
	//инкримент и дискримент
	Fraction operator -()
	{
		return Fraction(-numerator, -denominator);
	}
	Fraction operator +()
	{
		return Fraction(fabs(numerator), fabs(denominator));
	}
	Fraction operator ++()
	{
		Add(Fraction(1, 1));
		return Fraction(numerator, denominator);
	}
	Fraction operator --()
	{
		Add(Fraction(1, 1));
		return Fraction(numerator, denominator);
	}

	explicit Fraction(int num, int den)
	{
		numerator = num;
		denominator = den;
	}
	//для возведения в степень
	Fraction(double value)
	{
		numerator = GetDigitAfterDot(value);
		int digitCount = std::to_string(numerator).size();

		denominator = pow(10, digitCount);
		
		int cd = gcd(numerator, denominator);
		if (cd != 1)
		{
			numerator /= cd;
			denominator /= cd;
		}
	}
};

	//перегрузка потоков
std::ostream& operator << (std::ostream& os, Fraction& x)
{
	return os << x.GetNumerator() << std::endl << x.GetDenominator();
}
std::istream& operator >> (std::istream& os, Fraction& x)
{
	std::string num, den;
	os >> num >> den;

	x.SetNumerator(std::stoi(num));
	x.SetDenominator(std::stoi(den));

	return os;
}


int main() {
	setlocale(LC_ALL, "Russian");
	int n;

	Fraction test = Fraction(0.1234);
	std::cout << test.GetNumerator() << std::endl << test.GetDenominator() << std::endl;

	//Fraction x = Fraction(1, 2);
	//Fraction y = Fraction(5, 4);
	//std::cin >> x;
	//x = x + y;

	// std::cout << x.GetNumerator() << std::endl << x.GetDenominator();
	//std::cout << x;


	Fraction f1(3, 4);
	Fraction f2(2, 5);

	Fraction f3 = f1 + f2;
	std::cout << "f1 + f2 = " << f3 << std::endl;

	Fraction f4 = f1 - f2;
	std::cout << "f1 - f2 = " << f4 << std::endl;

	Fraction f5 = f1 * f2;
	std::cout << "f1 * f2 = " << f5 << std::endl;

	Fraction f6 = f1 / f2;
	std::cout << "f1 / f2 = " << f6 << std::endl;

	Fraction f7 = -f1;
	std::cout << "-f1 = " << f7 << std::endl;

	Fraction f8 = +f1;
	std::cout << "+f1 = " << f8 << std::endl;

	++f1;
	std::cout << "++f1 = " << f1 << std::endl;

	--f2;
	std::cout << "--f2 = " << f2 << std::endl;

	Fraction f9(3.14159);
	std::cout << "3.14159 = " << f9 << std::endl;

	return 0;


	return 0;
}