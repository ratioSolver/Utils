#pragma once

#include "logging.h"
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "[";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        os << *it;
        if (std::next(it) != v.end())
            os << ", ";
    }
    os << "]";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m)
{
    os << "{";
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        os << it->first << ": " << it->second;
        if (std::next(it) != m.end())
            os << ", ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &m)
{
    os << "{";
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        os << it->first << ": " << it->second;
        if (std::next(it) != m.end())
            os << ", ";
    }
    os << "}";
    return os;
}