#include "combinations.h"
#include "cartesian_product.h"
#include "memory.h"
#include "logging_containers.h"
#include "inf_rational.h"
#include <iostream>
#include <vector>

void test_logging()
{
    LOG("test_logging");
    LOG_DEBUG("test_logging");
    LOG_WARN("test_logging");
    LOG_ERR("test_logging");
}

void test_logging_containers()
{
    LOG("test_logging_containers");
    std::vector<int> v = {1, 2, 3, 4, 5};
    LOG(v);
    std::vector<std::vector<int>> vv = {{1, 2, 3}, {4, 5, 6}};
    LOG(vv);
    std::vector<std::vector<std::vector<int>>> vvv = {{{1, 2, 3}, {4, 5, 6}}, {{1, 2, 3}, {4, 5, 6}}};
    LOG(vvv);
}

class b;

class a : public utils::countable
{
public:
    a(utils::c_ptr<b> m_b) : m_b(m_b) { LOG("a"); }
    ~a() { LOG("~a"); }

private:
    utils::c_ptr<b> m_b;
};

class b : public utils::countable
{
public:
    b() : countable(true) { LOG("b"); }
    ~b() { LOG("~b"); }

    void add_a() { m_a.push_back(utils::c_ptr<a>(new a(this))); }

private:
    std::vector<utils::c_ptr<a>> m_a;
};

void test_combinations()
{
    LOG("test_combinations");
    std::vector<int> v = {1, 2, 3, 4, 5};
    const auto combinations = utils::combinations(v, 3);
    for ([[maybe_unused]] auto &combination : combinations)
        LOG(combination);
}

void test_cartesian_product()
{
    LOG("test_cartesian_product");
    std::vector<std::vector<int>> v = {{1, 2, 3}, {4, 5, 6}};
    const auto cartesian_product = utils::cartesian_product(v);
    for ([[maybe_unused]] auto &product : cartesian_product)
        LOG(product);
}

void test_memory()
{
    LOG("test_memory");
    b c_b;
    c_b.add_a();
    c_b.add_a();
    c_b.add_a();
}

void test_rationals()
{
    LOG("test_rationals");
    utils::rational a(1, 2);
    utils::rational b(1, 3);
    utils::rational c = a + b;
    LOG(to_string(c));
    assert(c == utils::rational(5, 6));

    utils::rational d(1, 2);
    utils::rational e(1, 2);
    utils::rational f = d + e;
    LOG(to_string(f));
    assert(f == utils::rational(1, 1));

    utils::rational g(1, 2);
    utils::rational h(1, 3);
    utils::rational i = g - h;
    LOG(to_string(i));
    assert(i == utils::rational(1, 6));

    utils::rational j(1, 2);
    utils::rational k(1, 2);
    utils::rational l = j - k;
    LOG(to_string(l));
    assert(l == utils::rational(0, 1));

    utils::rational m(1, 2);
    utils::rational n(1, 3);
    utils::rational o = m * n;
    LOG(to_string(o));
    assert(o == utils::rational(1, 6));

    utils::rational p(1, 2);
    utils::rational q(1, 2);
    utils::rational r = p * q;
    LOG(to_string(r));
    assert(r == utils::rational(1, 4));

    utils::rational s(1, 2);
    utils::rational t(1, 3);
    utils::rational u = s / t;
    LOG(to_string(u));
    assert(u == utils::rational(3, 2));

    utils::rational v(1, 2);
    utils::rational w(1, 2);
    utils::rational x = v / w;
    LOG(to_string(x));
    assert(x == utils::rational(1, 1));
}

void test_rationals_0()
{
    utils::rational r0;
    assert(r0.numerator() == 0);
    assert(r0.denominator() == 1);
    assert(r0 == utils::rational::ZERO);

    r0 += 1;
    assert(r0.numerator() == 1);
    assert(r0.denominator() == 1);
    assert(r0 == utils::rational::ONE);

    r0 += utils::rational(1, 2);
    assert(r0.numerator() == 3);
    assert(r0.denominator() == 2);

    r0 += utils::rational::NEGATIVE_INFINITY;
    assert(r0.numerator() == -1);
    assert(r0.denominator() == 0);
    assert(r0 == utils::rational::NEGATIVE_INFINITY);

    utils::rational r1(4, 2);
    assert(r1.numerator() == 2);
    assert(r1.denominator() == 1);

    utils::rational r2 = r1 / r0;
    assert(r2.numerator() == 0);
    assert(r2.denominator() == 1);
    assert(r2 == utils::rational::ZERO);

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

void test_rationals_1()
{
    assert(utils::rational::NEGATIVE_INFINITY < utils::rational::POSITIVE_INFINITY);
    assert(utils::rational::NEGATIVE_INFINITY <= utils::rational::POSITIVE_INFINITY);
    assert(utils::rational::POSITIVE_INFINITY >= utils::rational::NEGATIVE_INFINITY);
    assert(utils::rational::POSITIVE_INFINITY > utils::rational::NEGATIVE_INFINITY);

    utils::inf_rational eps(utils::rational::ZERO, utils::rational::ONE);
    assert(!(eps <= 0));
    assert(eps <= utils::inf_rational(utils::rational::ZERO, utils::rational::ONE));
    assert(eps > 0);
}

int main(int, char **)
{
    test_logging();
    test_logging_containers();

    test_combinations();
    test_cartesian_product();
    test_memory();

    test_rationals();
    test_rationals_0();
    test_rationals_1();

    test_logging_containers();

    return 0;
}