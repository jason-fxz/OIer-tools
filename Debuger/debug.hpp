#ifndef DEBUG_HPP
#define DEBUG_HPP 1

#include <cstdio>
#include <string>
#include <set>

// color & typo 
namespace CM {
    typedef std::string color;
    // 0:black  1:red  2:green  3:yellow  4:blue  5:magenta  6:cyan  7:white
    const color t[8] = {"\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m"};
    const color b[8] = {"\033[40m", "\033[41m", "\033[42m", "\033[43m", "\033[44m", "\033[45m", "\033[46m", "\033[47m"};
    const color &t_black = t[0], &t_red = t[1], &t_green = t[2], &t_yellow = t[3],
                 &t_blue = t[4], &t_magenta = t[5], &t_cyan = t[6], &t_white = t[7];
    const color &b_black = b[0], &b_red = b[1], &b_green = b[2], &b_yellow = b[3],
                 &b_blue = b[4], &b_magenta = b[5], &b_cyan = b[6], &b_white = b[7];
    typedef std::string typo;
    const typo ty[10] = {"\033[0m", "\033[1m", "\033[2m", "\033[3m", "\033[4m", "\033[5m", "\033[6m", "\033[7m", "\033[8m", "\033[9m"};
    const typo &ty_clean = ty[0], &ty_bold = ty[1], &ty_light = ty[2], &ty_italic = ty[3],
                &ty_underline = ty[4], &ty_blink = ty[5], &ty_invert = ty[7], &ty_hide = ty[8],
                 &ty_delete = ty[9];
    std::string setcm(std::string str, std::string c) {
        return c + str + ty_clean;
    }
}

#define BUF_SIZE 1000000
// string format, like printf
template <typename ...Args>
std::string fmt(std::string format, Args ...args) {
    static char buf[BUF_SIZE];
    snprintf(buf, BUF_SIZE, format.c_str(), args...);
    return std::string(buf);
}

// turn number to string
template <typename Tp> std::string Str(Tp x) { return std::to_string(x); }

#define _Name(a) #a

#define See(...) _See(#__VA_ARGS__, __VA_ARGS__)

template <typename Tp>
inline std::string  _See(const char* format, Tp t) {
    return std::string(format) + " = " + Str(t);
}

template <typename Tp, typename... Args>
inline std::string _See(const char *format, Tp x, Args... args) {
    using namespace std;
    std::string buf;
    while (*format != ',') buf.push_back(*format++);
    buf += " = " + Str(x) + ",";
    return buf + _See(format + 1, args...);
}


// template<typename _Key, typename _Compare = std::less<_Key>, typename _Allocator = std::allocator<_Key> >
// std::string Str(set<_Key, _Compare, _Allocator> st) {
//     std::string buf = fmt("%s[%u ~ %u] = {", Name, l, r);
//     debug(a)
// }


#define Seearr(a, l, r) outarr(#a, a, l, r)
template <typename Tp>
std::string outarr(const char *Name, Tp a, size_t l, size_t r) {
    std::string buf = fmt("%s[%u ~ %u] = {", Name, l, r);
    for (size_t i = l; i <= r; ++i) {
        buf += Str(a[i]);
        if (i < r) buf += ", ";
        else buf += "} ";
    }
    return buf;
}

// logger
namespace logger {
    FILE *_flog = stderr;
    std::string LOG_H = CM::t_green + CM::ty_bold + "LOG: " + CM::ty_clean;
    std::string ERR_H = CM::t_red + CM::ty_bold + "ERR: " + CM::ty_clean;
    std::string WARN_H = CM::t_yellow + CM::ty_bold + "WARN: " + CM::ty_clean;

    void Log(std::string content) {
        content = LOG_H + content + '\n';
        fputs(content.c_str(), _flog);
        fflush(_flog);
    }
    void Err(std::string content) {
        content = ERR_H + content + '\n';
        fputs(content.c_str(), _flog);
        fflush(_flog);
    }
    void Warn(std::string content) {
        content = WARN_H + content + '\n';
        fputs(content.c_str(), _flog);
        fflush(_flog);
    }
    void SetFile(const char *file) {
        fputs((CM::ty_bold + "Log File: " + CM::t_magenta + std::string(file) + CM::ty_clean +
               "\n\n").c_str(), stderr);
        _flog = fopen(file, "w");
        LOG_H = "LOG: ";
        ERR_H = "ERR: ";
        WARN_H = "WARN: ";
    }
    struct _close_flog {
        ~_close_flog() { fflush(_flog); fclose(_flog);}
    };
}

#define Assert(expr) (static_cast<bool>(expr) ? void(0) : __Assert_failed(#expr, __FILE__, __LINE__, __func__))

void __Assert_failed(const char *expr, const char *file, const unsigned int &line, const char *func) {
    logger::Err(fmt("%s: %s: %s:  Assertion `%s` failed.",
                    CM::setcm(file, CM::t_green).c_str(),
                    CM::setcm(Str(line), CM::t_cyan).c_str(),
                    CM::setcm(func, CM::t_yellow).c_str(),
                    CM::setcm(expr, CM::t_blue).c_str()));
}

#endif
