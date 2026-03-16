#include <iostream>


struct Rational
{
    int numerator;
    int denominator;
    // член данни


};

Rational createRational(int numerator, int denominator)
{
    return Rational {numerator, denominator};
}

void print(const Rational& rational)
{
    std::cout << rational.numerator << "/" << rational.denominator<<std::endl;
}



int gcd(int a, int b) {  // Greatest common divider -> ползваме алгоритъм на Евклид
                        // Алгоритъмът на Евклид намира най-големия общ делител (НОД) на две числа, 
                       //като многократно заменя по-голямото число с остатъка от делението му на по-малкото. 
                      //Процесът продължава, докато остатъкът стане 0, а последната ненулева стойност е НОД. 
    a = abs(a);
    b = abs(b);

    if(a < b) {
        std::swap(a, b);
    }

    while(b != 0) {
        unsigned temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

void simplify(Rational& rational) // ще променяме инстанцията на обекта директно
{
    // опростяваме дробта, като делим числителя и знаменателя на НОД
    int gcdOfRational = gcd(rational.numerator, rational.denominator);

    rational.numerator /= gcdOfRational;
    rational.denominator /= gcdOfRational;
}

Rational sum(const Rational& lhs, const Rational& rhs)
{
    int resultNumerator = lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator;
    int resultDenumerator = lhs.denominator * rhs.denominator;

    Rational result = createRational(resultNumerator, resultDenumerator);
    simplify(result);

    return result;
}

Rational subs(const Rational& lhs, const Rational& rhs)
{
    Rational toSubtract = createRational(-rhs.numerator, rhs.denominator); // change the sign

    return sum(lhs, toSubtract); // reuse sum
}

Rational multiply(const Rational& lhs, const Rational& rhs)
{
    int resultNumerator = lhs.numerator * rhs.numerator;
    int resultDenumerator = lhs.denominator * rhs.denominator;

    Rational result = createRational(resultNumerator, resultDenumerator);
    simplify(result);

    return result;
}

Rational div(const Rational& lhs, const Rational& rhs)
{
    Rational divider = createRational(rhs.denominator, rhs.numerator); // reverse the fraction

    return multiply(lhs, divider);
}



int main()
{
    Rational r{3, 5};
    r.denominator = 4;

    Rational r2 = { 2, 3};

    Rational r3;
    r3.denominator = 5;
    r3.numerator = 6;

    Rational lhs = createRational( 5,25 );
    Rational rhs = createRational( 1,3 );

    print(sum(rhs, lhs));
    print(subs(rhs, lhs));
    print(multiply(rhs, lhs));
    print(div(lhs, rhs));


}


