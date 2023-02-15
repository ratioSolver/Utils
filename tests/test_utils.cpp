#include "combinations.h"
#include "cartesian_product.h"
#include "memory.h"
#include "logging_containers.h"
#include "rational.h"
#include <iostream>
#include <vector>

class b;

class a : public utils::countable
{
public:
    a(utils::c_ptr<b> &m_b) : m_b(m_b) { LOG("a"); }
    ~a() { LOG("~a"); }

private:
    utils::c_ptr<b> &m_b;
};

class b : public utils::self_countable<b>
{
public:
    b() { LOG("b"); }
    ~b() { LOG("~b"); }

    void add_a() { m_a.push_back(utils::c_ptr<a>(new a(self()))); }

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

int main(int, char **)
{
    test_combinations();
    test_cartesian_product();
    test_memory();

    test_rationals();

    return 0;
}