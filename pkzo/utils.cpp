// pkzo
// Copyright 2022-2023 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"
#include "utils.h"

namespace pkzo
{
    void trace(const std::string_view msg) noexcept
    {
        OutputDebugStringA(msg.data());
    }

    #ifndef NDEBUG
    void handle_soft_assert(const char* file, unsigned int line, const char* scond) noexcept
    {
        trace(std::format("{}({}): Assert {} failed!", file, line, scond));
    }
    #endif

    std::string join(const std::vector<std::string>& strs, const std::string& delimiter) noexcept
    {
        std::stringstream buff;

        size_t s = 1;
        for (const std::string& str : strs)
        {
            buff << str;
            if (s != strs.size())
            {
                buff << delimiter;
            }
            s++;
        }

        return buff.str();
    }

    std::vector<std::string> explode(const std::string& str, const std::string& delimiter) noexcept
    {
        std::vector<std::string> gibs;
        size_t start = 0;
        size_t end = 0;

        while ((start != std::string::npos) && (start < str.size()))
        {
            end = str.find(delimiter, start);

            std::string gib;
            if (end == std::string::npos)
            {
                gib = str.substr(start);
                start = std::string::npos;
            }
            else
            {
                gib = str.substr(start, end - start);
                start = end + delimiter.size();
            }
            gibs.push_back(gib);
        }

        return gibs;
    }

    void lex_whitespace(const std::string& str, size_t& i) noexcept
    {
        while (i < str.size())
        {
            switch (str[i])
            {
                case ' ': case '\t': case '\v':
                case '\n': case '\r':
                    i++;
                    break;
                default:
                    return;
            }
        }
    }

    void lex_number(const std::string& str, size_t& i, std::vector<std::string>& tokens) noexcept
    {
        tokens.emplace_back(std::string());
        while (i < str.size())
        {
            // NOTE: not validating the actual format
            switch (str[i])
            {
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                case '.':
                    tokens.back().push_back(str[i]);
                    i++;
                    break;
                default:
                    return;
            }
        }
    }

    void lex_identifier(const std::string& str, size_t& i, std::vector<std::string>& tokens) noexcept
    {
        tokens.emplace_back(std::string());
        while (i < str.size())
        {
            // NOTE: not validating the actual format
            switch (str[i])
            {
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
                case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
                case 's': case 't': case 'u': case 'v': case 'w': case 'x':
                case 'y': case 'z':
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
                case 'Y': case 'Z':
                case '_':
                    tokens.back().push_back(str[i]);
                    i++;
                    break;
                default:
                    return;
            }
        }
    }

    void lex_string(const std::string& str, size_t& i, std::vector<std::string>& tokens) noexcept
    {
        tokens.emplace_back(std::string());
        i++; // overread first "
        while (i < str.size())
        {
            switch (str[i])
            {
                case '"':
                    i++; // overread last "
                    return;
                // we don't handle \n \r errors here
                case '\\':
                    i++;
                    switch (str[i])
                    {
                        case '\'':
                            tokens.back().push_back('\'');
                            break;
                        case '"':
                            tokens.back().push_back('"');
                            break;
                        case '\\':
                            tokens.back().push_back('\\');
                            break;
                        case 'a':
                            tokens.back().push_back('\a');
                            break;
                        case 'b':
                            tokens.back().push_back('\b');
                            break;
                        case 'f':
                            tokens.back().push_back('\f');
                            break;
                        case 'n':
                            tokens.back().push_back('\n');
                            break;
                        case 'r':
                            tokens.back().push_back('\r');
                            break;
                        case 't':
                            tokens.back().push_back('\t');
                            break;
                        case 'v':
                            tokens.back().push_back('\v');
                            break;
                        default:
                            // also not handling this error
                            tokens.back().push_back(str[i]);
                            break;
                    }
                    i++;
                    break;
                default:
                    tokens.back().push_back(str[i]);
                    i++;
                    break;
            }
        }
    }

    std::vector<std::string> tokenize(const std::string& str) noexcept
    {
        std::vector<std::string> tokens;

        size_t i = 0;
        while (i < str.size())
        {
            switch (str[i])
            {
                case ' ': case '\t': case '\v':
                case '\n': case '\r':
                    lex_whitespace(str, i);
                    break;
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    lex_number(str, i, tokens);
                    break;
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
                case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
                case 's': case 't': case 'u': case 'v': case 'w': case 'x':
                case 'y': case 'z':
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
                case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
                case 'Y': case 'Z':
                case '_':
                    lex_identifier(str, i, tokens);
                    break;
                case '"':
                    lex_string(str, i, tokens);
                    break;
                default:
                    tokens.emplace_back(std::string(1u, str[i]));
                    i++;
                    break;
            }
        }

        return tokens;
    }

    auto get_mb_flags(MessageBoxIcon icon)
    {
        switch (icon)
        {
            case MessageBoxIcon::INFORMATION:
                return MB_OK|MB_ICONINFORMATION;
            case MessageBoxIcon::WARNING:
                return MB_OK|MB_ICONWARNING;
            case MessageBoxIcon::ERROR:
            default:
                return MB_OK|MB_ICONERROR;
        }
    }

    void show_message_box(MessageBoxIcon icon, const std::string_view title, const std::string_view message)
    {
        MessageBoxA(NULL, message.data(), title.data(), get_mb_flags(icon));
    }
}
