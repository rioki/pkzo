
#ifndef _PKZO_CONFIG_PARSER_H_
#define _PKZO_CONFIG_PARSER_H_

#include <string>
#include <functional>
#include <fstream>

namespace pkzo
{
    class ConfigParser
    {
    public:

        ConfigParser();

        ConfigParser(const ConfigParser&) = delete;

        ~ConfigParser();

        const ConfigParser& operator = (const ConfigParser&) = delete;

        void on_section_begin(std::function<void (const std::string&)> cb);
        
        void on_section_end(std::function<void ()> cb);
        
        void on_key_value_pair(std::function<void (const std::string&, const std::string&)> cb);

        void parse(const std::string file);
    
    private:
        enum TokenType
        {
            WHITESPACE,
            ENDLINE,
            COMMENT,
            LBRAKET,
            RBRAKET,
            EQUAL,
            IDENTIFIER,
            STRING,
            END
        };
        
        std::function<void (const std::string&)> section_begin_cb;
        std::function<void ()> section_end_cb;
        std::function<void (const std::string&, const std::string&)> key_value_pair_cb;

        std::ifstream in;
        std::string   file;
        unsigned int  line;
        
        TokenType   next_token;
        std::string next_value;       

        void parse_section();
        void parse_section_header();
        void parse_key_value_pair();

        TokenType get_token(std::string& value);

        TokenType lex_token(std::string& value);
        TokenType lex_whitespace(std::string& value);
        TokenType lex_endline(std::string& value);
        TokenType lex_comment(std::string& value);
        TokenType lex_string(std::string& value);
        TokenType lex_identifer(std::string& value);
    };
}

#endif
