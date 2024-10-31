#include <cassert>
#include "rational.hpp"
#include "inf_rational.hpp"
#include "lit.hpp"
#include "lin.hpp"
#include "tableau.hpp"
#include "loss.hpp"

void test_literals()
{
    utils::lit l0(2, false);
    utils::lit l1 = !utils::lit(3);
    utils::lit l2(4);

    assert(variable(l0) == 2);
    assert(sign(l0) == false);
    assert(variable(l1) == 3);
    assert(sign(l1) == false);
    assert(variable(l2) == 4);
    assert(sign(l2) == true);
}

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

void test_lin()
{
    utils::lin l1;
    assert(l1.vars.empty());
    assert(l1.known_term == utils::rational::zero);

    utils::lin l2(utils::rational(1, 2));
    assert(l2.vars.empty());
    assert(l2.known_term == utils::rational(1, 2));

    utils::lin l3(1, utils::rational(1, 2));
    assert(l3.vars.size() == 1);
    assert(l3.vars[1] == utils::rational(1, 2));
    assert(l3.known_term == utils::rational::zero);

    utils::lin l4(1, utils::rational(1, 2));
    utils::lin l5(2, utils::rational(1, 3));
    utils::lin l6 = l4 + l5;
    assert(l6.vars.size() == 2);
    assert(l6.vars[1] == utils::rational(1, 2));
    assert(l6.vars[2] == utils::rational(1, 3));
    assert(l6.known_term == utils::rational::zero);

    utils::lin l7(1, utils::rational(1, 2));
    utils::lin l8(2, utils::rational(1, 3));
    utils::lin l9 = l7 - l8;
    assert(l9.vars.size() == 2);
    assert(l9.vars[1] == utils::rational(1, 2));
    assert(l9.vars[2] == utils::rational(-1, 3));
    assert(l9.known_term == utils::rational::zero);

    utils::lin l10(1, utils::rational(1, 2));
    utils::lin l12 = l10 * utils::rational(1, 3);
    assert(l12.vars.size() == 1);
    assert(l12.vars[1] == utils::rational(1, 6));
    assert(l12.known_term == utils::rational::zero);

    utils::lin l13(1, utils::rational(1, 2));
    utils::lin l14 = utils::rational(1, 3) * l13;
    assert(l14.vars.size() == 1);
    assert(l14.vars[1] == utils::rational(1, 6));
    assert(l14.known_term == utils::rational::zero);

    utils::lin l15(1, utils::rational(1, 2));
    utils::lin l16 = l15 / utils::rational(1, 3);
    assert(l16.vars.size() == 1);
    assert(l16.vars[1] == utils::rational(3, 2));
    assert(l16.known_term == utils::rational::zero);

    utils::lin l17(1, utils::rational(1, 2));
    utils::lin l18 = l17 / utils::rational(1, 2);
    assert(l18.vars.size() == 1);
    assert(l18.vars[1] == utils::rational(1, 1));
    assert(l18.known_term == utils::rational::zero);

    utils::lin l19(1, utils::rational(1, 2));
    utils::lin l20(2, utils::rational(1, 3));
    l19 += l20;
    assert(l19.vars.size() == 2);
    assert(l19.vars[1] == utils::rational(1, 2));
    assert(l19.vars[2] == utils::rational(1, 3));
    assert(l19.known_term == utils::rational::zero);

    utils::lin l21(1, utils::rational(1, 2));
    utils::lin l22(2, utils::rational(1, 3));
    l21 -= l22;
    assert(l21.vars.size() == 2);
    assert(l21.vars[1] == utils::rational(1, 2));
    assert(l21.vars[2] == utils::rational(-1, 3));
    assert(l21.known_term == utils::rational::zero);

    utils::lin l23(1, utils::rational(1, 2));
    l23 *= utils::rational(1, 3);
    assert(l23.vars.size() == 1);
    assert(l23.vars[1] == utils::rational(1, 6));
    assert(l23.known_term == utils::rational::zero);

    utils::lin l24(1, utils::rational(1, 2));
    l24 /= utils::rational(1, 3);
    assert(l24.vars.size() == 1);
    assert(l24.vars[1] == utils::rational(3, 2));
    assert(l24.known_term == utils::rational::zero);

    utils::lin l25(1, utils::rational(1, 2));
    l25 = -l25;
    assert(l25.vars.size() == 1);
    assert(l25.vars[1] == utils::rational(-1, 2));
    assert(l25.known_term == utils::rational::zero);
}

void test_tableau()
{
    utils::tableau t;
    auto x0 = t.new_var();
    auto x1 = t.new_var();
    auto x2 = t.new_var();
    auto x3 = t.new_var();

    utils::lin l1(x1, utils::rational(1, 2));
    l1 += utils::rational(1, 3);
    l1 += utils::lin(x2, utils::rational(1, 3));
    t.add_row(x0, std::move(l1));

    utils::lin l2(x1, utils::rational(1, 2));
    l2 += utils::rational(1, 3);
    l2 += utils::lin(x2, utils::rational(1, 3));
    t.add_row(x3, std::move(l2));

    t.pivot(x0, x1);
}

void test_loss()
{
    std::vector<float> y_true{1, 2, 3};
    std::vector<float> y_pred{1, 2, 3};

    assert(utils::mse(y_true.data(), y_pred.data(), 3) == 0);
    assert(utils::mae(y_true.data(), y_pred.data(), 3) == 0);
}

int main(int argc, char const *argv[])
{
    test_literals();

    test_rationals();
    test_rationals_1();

    test_inf_rationals();

    test_lin();

    test_tableau();

    test_loss();

    return 0;
}
