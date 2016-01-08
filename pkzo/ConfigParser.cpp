
#include "ConfigParser.h"

#include "compose.h"

namespace pkzo
{
    ConfigParser::ConfigParser() 
    : line(0) {}

    ConfigParser::~ConfigParser() {}

    void ConfigParser::on_section_begin(std::function<void(const std::string&)> cb)
    {
        section_begin_cb = cb;
    }

    void ConfigParser::on_section_end(std::function<void()> cb)
    {
        section_end_cb = cb;
    }

    void ConfigParser::on_key_value_pair(std::function<void(const std::string&, const std::string&)> cb)
    {
        key_value_pair_cb = cb;
    }

    void ConfigParser::parse(const std::string f)    
    {
        file = f;
        line = 0;

        in.open(file);
        if (! in.is_open())
        {
            throw std::runtime_error(compose("Failed to open %0 for reading.", file));        
        }

        // prime the look ahead
        get_token(next_value);

        while (next_token != END)
        {
            parse_section();
        }

        in.close();
    }

    void ConfigParser::parse_section()
    {
        parse_section_header();

        while (next_token == IDENTIFIER)
        {
            parse_key_value_pair();
        }

        if (section_end_cb)
        {
            section_end_cb();
        }
    }

    void ConfigParser::parse_section_header()
    {
        std::string value;
        TokenType   token; 
        
        token = get_token(value);
        if (token != LBRAKET) 
        {
            throw std::runtime_error(compose("%0(%1): Exprected '[' but got %2", file, line, value));
        }

        token = get_token(value);
        if (token != IDENTIFIER)
        {
            throw std::runtime_error(compose("%0(%1): Exprected identifier but got %2", file, line, value));
        }
        std::string name = value;

        token = get_token(value);
        if (token != RBRAKET)
        {
            throw std::runtime_error(compose("%0(%1): Exprected ']' but got %2", file, line, value));
        }

        if (section_begin_cb)
        {
            section_begin_cb(name);
        }
    }    

    void ConfigParser::parse_key_value_pair()
    {
        std::string value;
        TokenType   token;
        
        token = get_token(value);
        if (token != IDENTIFIER)
        {
            throw std::runtime_error(compose("%0(%1): Exprected identifier but got %2", file, line, value));
        }
        std::string key = value;

        token = get_token(value);
        if (token != EQUAL)
        {
            throw std::runtime_error(compose("%0(%1): Exprected = but got %2", file, line, value));
        }

        token = get_token(value);
        if (token != STRING && token != IDENTIFIER)
        {
            throw std::runtime_error(compose("%0(%1): Exprected string but got %2", file, line, value));
        }
        
        if (key_value_pair_cb)
        {
            key_value_pair_cb(key, value);
        }
    }

    ConfigParser::TokenType ConfigParser::get_token(std::string& value)
    {
        TokenType   this_token = next_token;
        std::string this_value = next_value;

        do
        {
            next_token = lex_token(next_value);
        }
        while (next_token == WHITESPACE || next_token == COMMENT || next_token == ENDLINE);

        value = this_value;
        return this_token;
    }

    ConfigParser::TokenType ConfigParser::lex_token(std::string& value)
    {
        int c = in.peek();
        switch (c)
        {
            case ' ': case '\t':
                return lex_whitespace(value);
            case '\n': case '\r':
                return lex_endline(value);
            case '#':
                return lex_comment(value);
            case '[': 
                in.get();
                value = "[";
                return LBRAKET;
            case ']': 
                value = "]";
                in.get();
                return RBRAKET;
            case '=':
                value = "=";
                in.get();
                return EQUAL;
            case '"':
                return lex_string(value);
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
            case '_': case '.':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                return lex_identifer(value);
            case EOF:
                return END;
            default:
                throw std::runtime_error(compose("%0(%1): Unexpected character %2", file, line, c));
        }
    }

    ConfigParser::TokenType ConfigParser::lex_whitespace(std::string& value)
    {        
        while (in.peek() == ' ' || in.peek() == '\t')
        {
            in.get();
        }
        value = "white space";
        return WHITESPACE;
    }
    
    ConfigParser::TokenType ConfigParser::lex_endline(std::string& value)
    {
        int c = in.get();
        if (c == '\r') 
        {
            if (in.peek() == '\n')
            {
                in.get();                            
            }
        }

        line++;

        value = "end of line";
        return ENDLINE;
    }
    
    ConfigParser::TokenType ConfigParser::lex_comment(std::string& value)
    {
        while (in.peek() != '\r' && in.peek() != '\n' && in.peek() != -1)            
        {
            in.get();
        }

        value = "comment";
        return COMMENT;
    }
    
    ConfigParser::TokenType ConfigParser::lex_string(std::string& value)
    {
        value.clear();

        in.get(); // read the leading " off

        int c = in.get();
        while (c != '"')    
        {
            if (c == '\n' || c == '\r')
            {
                throw std::runtime_error(compose("%0(%1): Newline in string.", file, line));
            }

            if (c == '\\')            
            {
                c = in.get();
                switch (c)
                {
                    case 'a':
                        c = '\a';
                    case 'b':
                        c = '\b';
                    case 'f':
                        c = '\f';
                    case 'n':
                        c = '\n';
                    case 'r':
                        c = '\r';
                    case 't':
                        c = '\v';
                    case '\\':
                        c = '\\';
                    case '\'':
                        c = '\'';
                    case '\"':
                        c = '\"';
                    case '?':
                        c = '?';  
                    default:
                        throw std::runtime_error(compose("%0(%1): Unknown escape sequence %2", file, line, c));
                }
            }
            
            value.push_back(c);

            c = in.get();
        }

        return STRING;
    }
    
    ConfigParser::TokenType ConfigParser::lex_identifer(std::string& value)
    {
        value.clear();
        int c = in.get();
        while (true)
        {
            switch (c)
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
            case '_': case '.':
                value.push_back(c);
                break;
            default:
                in.unget();
                return IDENTIFIER;
            }
            c = in.get();
        }
    }
}
