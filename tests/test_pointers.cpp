#include "memory.hpp"
#include "logging.hpp"
#include <vector>

class A
{
public:
    A() { LOG_DEBUG("A constructor"); }
    ~A() { LOG_DEBUG("A destructor"); }

    void method() { LOG_DEBUG("A method"); }
};

void u_ptr_method(utils::u_ptr<A> a)
{
    a->method();
    (*a).method();
}

void test_u_ptr()
{
    auto a = utils::make_u_ptr<A>();
    u_ptr_method(std::move(a));
}

void s_ptr_method(utils::s_ptr<A> a)
{
    a->method();
    (*a).method();
}

void test_s_ptr()
{
    auto a = utils::make_s_ptr<A>();
    s_ptr_method(a);
}

void test_ref_wrapper()
{
    A a;
    utils::ref_wrapper<A> ref_a(a);
    ref_a->method();
    (*ref_a).method();

    std::vector<utils::ref_wrapper<A>> vec;
    vec.push_back(ref_a);
    vec[0]->method();
    (*vec[0]).method();
}

int main()
{
    test_u_ptr();
    test_s_ptr();
    test_ref_wrapper();
    return 0;
}