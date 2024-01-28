#pragma once

#define LOG_OFF_LEVEL 0
#define LOG_FATAL_LEVEL 1
#define LOG_ERR_LEVEL 2
#define LOG_WARN_LEVEL 3
#define LOG_DEBUG_LEVEL 4
#define LOG_INFO_LEVEL 5
#define LOG_TRACE_LEVEL 6

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_OFF_LEVEL
#else
#include <iostream>

#ifdef WIN32
#define COLOR_NORMAL ""
#define COLOR_BOLD_RED ""
#define COLOR_RED ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_BLUE ""
#else
#define COLOR_NORMAL "\033[0m"
#define COLOR_BOLD_RED "\033[1;31m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#endif
#endif

#if LOG_LEVEL >= LOG_FATAL_LEVEL
#define LOG_FATAL(msg) std::cerr << COLOR_BOLD_RED << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_FATAL(msg) {}
#endif

#if LOG_LEVEL >= LOG_ERR_LEVEL
#define LOG_ERR(msg) std::cerr << COLOR_RED << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_ERR(msg) {}
#endif

#if LOG_LEVEL >= LOG_WARN_LEVEL
#define LOG_WARN(msg) std::cerr << COLOR_YELLOW << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_WARN(msg) {}
#endif

#if LOG_LEVEL >= LOG_DEBUG_LEVEL
#define LOG_DEBUG(msg) std::cerr << COLOR_GREEN << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_DEBUG(msg) {}
#endif

#if LOG_LEVEL >= LOG_INFO_LEVEL
#define LOG_INFO(msg) std::cerr << COLOR_NORMAL << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_INFO(msg) {}
#endif

#if LOG_LEVEL >= LOG_TRACE_LEVEL
#define LOG_TRACE(msg) std::cerr << COLOR_BLUE << __FILE__ << "(" << __LINE__ << "): " << msg << COLOR_NORMAL << std::endl
#else
#define LOG_TRACE(msg) {}
#endif