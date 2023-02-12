#include "combinations.h"
#include "cartesian_product.h"
#include "memory.h"
#include "logging_containers.h"
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

int main(int, char **)
{
    test_combinations();
    test_cartesian_product();
    test_memory();

    return 0;
}