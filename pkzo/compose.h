// Strig composition library.
// Copyright 2011-2019 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. 
// See http://www.wtfpl.net/ for more details. 

#ifndef _COMPOSE_H_
#define _COMPOSE_H_

#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

namespace impl
{
    template <typename T>
    std::string to_string(T value)
    {
        std::stringstream buff;
        buff << value;
        return buff.str();
    }

    template <>
    inline std::string to_string(bool value)
    {
        return value ? "true" : "false";
    }

    template <>
    inline std::string to_string(const std::string& value)
    {
        return value;
    }

    inline
    int char_to_int(char c)
    {
        switch (c)
        {
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            default:
                throw std::logic_error("not a number");
        }
    }

    template <typename Arg>
    void unpack(std::vector<std::string>& args, Arg value)
    {
        args.push_back(to_string(value));
    }

    template <typename Arg, typename ... Args>
    void unpack(std::vector<std::string>& args, Arg value, Args ... remainder)
    {
        args.push_back(to_string(value));
        unpack(args, remainder...);
    }

    template <typename ... Args>
    std::string compose(const std::string& format, Args ... args)
    {
        std::vector<std::string> sargs;
        unpack(sargs, args...);
        
        std::string result;

        for (unsigned int i = 0; i < format.size(); i++)
        {
            if (format[i] == '%')
            {
                if (i + 1 < format.size())
                {
                    int idx = char_to_int(format[i + 1]);
                    result += sargs.at(idx);
                    i++;
                }
                else
                {
                    throw std::logic_error("% at end of string.");
                }
            }
            else
            {
                result.push_back(format[i]);
            }
        }

        return result;
    }
}

using impl::compose;

#endif
