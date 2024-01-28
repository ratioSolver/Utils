#include "rational.hpp"
#include "inf_rational.hpp"
#include <cassert>

void test_rationals()
{
    utils::rational r1(1, 2);
    utils::rational r2(1, 3);

    assert(r1 + r2 == utils::rational(5, 6));
    assert(r1 - r2 == utils::rational(1, 6));
    assert(r1 * r2 == utils::rational(1, 6));
    assert(r1 / r2 == utils::rational(3, 2));

    assert(r1 + 1 == utils::rational(3, 2));
    assert(r1 - 1 == utils::rational(-1, 2));
    assert(r1 * 2 == utils::rational(1, 1));
    assert(r1 / 2 == utils::rational(1, 4));

    utils::rational a(1, 2);
    utils::rational b(1, 3);
    utils::rational c = a + b;
    assert(c == utils::rational(5, 6));

    utils::rational d(1, 2);
    utils::rational e(1, 2);
    utils::rational f = d + e;
    assert(f == utils::rational(1, 1));

    utils::rational g(1, 2);
    utils::rational h(1, 3);
    utils::rational i = g - h;
    assert(i == utils::rational(1, 6));

    utils::rational j(1, 2);
    utils::rational k(1, 2);
    utils::rational l = j - k;
    assert(l == utils::rational(0, 1));

    utils::rational m(1, 2);
    utils::rational n(1, 3);
    utils::rational o = m * n;
    assert(o == utils::rational(1, 6));

    utils::rational p(1, 2);
    utils::rational q(1, 2);
    utils::rational r = p * q;
    assert(r == utils::rational(1, 4));

    utils::rational s(1, 2);
    utils::rational t(1, 3);
    utils::rational u = s / t;
    assert(u == utils::rational(3, 2));

    utils::rational v(1, 2);
    utils::rational w(1, 2);
    utils::rational x = v / w;
    assert(x == utils::rational(1, 1));
}

void test_rationals_1()
{
    utils::rational r0;
    assert(r0.numerator() == 0);
    assert(r0.denominator() == 1);
    assert(r0 == utils::rational::zero);

    r0 += 1;
    assert(r0.numerator() == 1);
    assert(r0.denominator() == 1);
    assert(r0 == utils::rational::one);

    r0 += utils::rational(1, 2);
    assert(r0.numerator() == 3);
    assert(r0.denominator() == 2);

    r0 += utils::rational::negative_infinite;
    assert(r0.numerator() == -1);
    assert(r0.denominator() == 0);
    assert(r0 == utils::rational::negative_infinite);

    utils::rational r1(4, 2);
    assert(r1.numerator() == 2);
    assert(r1.denominator() == 1);

    utils::rational r2 = r1 / r0;
    assert(r2.numerator() == 0);
    assert(r2.denominator() == 1);
    assert(r2 == utils::rational::zero);

    r2 += 2;
    assert(r2.numerator() == 2);
    assert(r2.denominator() == 1);

    r2 -= -2;
    assert(r2.numerator() == 4);
    assert(r2.denominator() == 1);

    r2 *= 2;
    assert(r2.numerator() == 8);
    assert(r2.denominator() == 1);
}

void test_inf_rationals()
{
    assert(utils::rational::negative_infinite < utils::rational::positive_infinite);
    assert(utils::rational::negative_infinite <= utils::rational::positive_infinite);
    assert(utils::rational::positive_infinite >= utils::rational::negative_infinite);
    assert(utils::rational::positive_infinite > utils::rational::negative_infinite);

    utils::inf_rational eps(utils::rational::zero, utils::rational::one);
    assert(!(eps <= 0));
    assert(eps <= utils::inf_rational(utils::rational::zero, utils::rational::one));
    assert(eps > 0);
}

int main(int argc, char const *argv[])
{
    test_rationals();
    test_rationals_1();

    test_inf_rationals();

    return 0;
}
