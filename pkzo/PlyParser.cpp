//
// PLY Parser
// 
// Copyright (c) 2014 Sean Farrell
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "PlyParser.h"

#include <iterator> 
#include <sstream>
#include <map>

namespace std
{
std::ostream& operator << (std::ostream& os, const std::vector<std::string>& values)
{
    for (unsigned int i = 0; i < values.size(); i++)
    {
        os << values[i];
        if (i == values.size() - 2)
        {
            os << " or ";
        }
        else if (i != values.size() - 1)
        {
            os << ", ";
        }
    }
    return os;
}
}

PlyParser::PlyParser()
: line(0) {}

PlyParser::~PlyParser() {}

const std::vector<glm::vec3>& PlyParser::get_vertices() const
{
    return vertices;
}

const std::vector<glm::vec3>& PlyParser::get_normals() const
{
    return normals;
}

const std::vector<glm::vec2>& PlyParser::get_texcoords() const
{
    return texcoords;
}

const std::vector<glm::ivec3>& PlyParser::get_indexes() const
{
    return indexes;
}

void PlyParser::parse(const std::string& f)
{
    file = f;
    input.open(file);
    if (! input.good())
    {
        std::stringstream buff;
        buff << "Failed to open " << file << " for reading.";
        throw std::runtime_error(buff.str());    
    }

    parse_header();
    parse_body();
}

TokenType PlyParser::get_next_token(std::string& value)
{
    // skip whitepsaces

    TokenType token = lex_token(value);
    while (token == WHITESPACE || token == NEWLINE)
    {
        if (token == NEWLINE)
        {
            line++;
        }
        value = "";
        token = lex_token(value);
    }
                
    return token;
}

TokenType PlyParser::lex_token(std::string& value)
{
    int c = input.get();
    switch (c)
    {
        case ' ': case '\t': case '\v':
            value.push_back(c);
            return lex_whitespace(value);
        case '\n': case '\r':
            value.push_back(c);
            return lex_newline(value);
        case '+': case '-': case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7': case '8': case '9':
            value.push_back(c);
            return lex_number(value);
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
            value.push_back(c);
            return lex_identifier(value);
        case EOF:
            return END_OF_FILE;
        default:
        {
            value.push_back(c);

            std::stringstream buff;
            buff << "Unexpected character " << value << ".";
            throw std::runtime_error(buff.str());  
        }
    }
}

TokenType PlyParser::lex_whitespace(std::string& value)
{
    int c = input.get();
    while (true)        
    {
        switch (c)
        {
            case ' ': case '\t': case '\v':
                value.push_back(c);
                break;
            default:
                input.unget();
                return WHITESPACE;
        }
        c = input.get();
    }
}

TokenType PlyParser::lex_newline(std::string& value)
{
    int c = input.get();
    switch (c)
    {
        case '\n': case '\r':
            if (c != value[0])
            {
                // \r\n or \n\r
                value.push_back(c);
            }
            else
            {
                // treat \n \n as two newline, obviously
                input.unget();                            
            }
            return NEWLINE;
        default:
            input.unget();
            return NEWLINE;
    }
}

TokenType PlyParser::lex_identifier(std::string& value)
{
    int c = input.get();
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
            case '_':
                value.push_back(c);
                break;
            default:
                input.unget();
                return IDENTIFIER;
        }
        c = input.get();
    }        
}

TokenType PlyParser::lex_number(std::string& value)
{
    // NOTE: we don't actually validate if it makes a valid number here
    // NOTE: the e-notation is not implemented, is that actually valid in PLY?
    int c = input.get();
    while (true)        
    {
        switch (c)
        {                            
            case '+': case '-': case '.': case 'e': case 'E':
            case '0': case '1': case '2': case '3': case '4': 
            case '5': case '6': case '7': case '8': case '9':
                value.push_back(c);
                break;
            default:
                input.unget();
                return NUMBER;
        }
        c = input.get();
    }
}

void PlyParser::lex_discard_line()
{
    int c = input.get();
    while (c != '\n' && c != '\r' && c != EOF) 
    {
        c = input.get();
    }
    input.unget();
}

void PlyParser::parse_keyword(const std::string& keyword)
{
    std::string value;
    TokenType token = get_next_token(value);
    if (token != IDENTIFIER || value != keyword)
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Expected " << keyword << " but got " << value << ".";
        throw std::runtime_error(buff.str());
    }
}

unsigned int PlyParser::parse_keyword(const std::vector<std::string>& keywords)
{
    std::string value;
    TokenType token = get_next_token(value);
    auto i =  std::find(keywords.begin(), keywords.end(), value);
    if (token != IDENTIFIER || i == keywords.end())
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Expected " << keywords << " but got " << value << ".";
        throw std::runtime_error(buff.str());
    }
    return static_cast<unsigned int>(std::distance(keywords.begin(), i));
}

std::string PlyParser::parse_identifier()
{
    std::string value;
    TokenType token = get_next_token(value);
    if (token != IDENTIFIER)
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Expected identifier but got " << value << ".";
        throw std::runtime_error(buff.str());
    }
    return value;
}

double PlyParser::parse_float()
{
    std::string value;
    TokenType token = get_next_token(value);
    if (token == NUMBER)
    {
        // TODO use endptr to check if the entiere string was read
        double dv = strtod(&value[0], NULL);
        return dv;
    }
    else
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Expected number but got " << value << ".";
        throw std::runtime_error(buff.str());
    }
}

unsigned long PlyParser::parse_integer()
{
    std::string value;
    TokenType token = get_next_token(value);
    if (token == NUMBER)
    {
        // TODO use endptr to check if the entiere string was read
        unsigned long ulv = strtoul(&value[0], NULL, 10);
        return ulv;
    }
    else
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Expected integer but got " << value << ".";
        throw std::runtime_error(buff.str());
    }
}

std::vector<std::string> format_keywords = [] () -> std::vector<std::string> {
    std::vector<std::string> result;

    result.push_back("ascii");
    result.push_back("binary");

    return result;
}();

enum HeaderKeyword
{
    COMMENT,
    ELEMENT,
    PROPERTY,
    END_HEADER
};

std::vector<std::string> header_keywords = [] () -> std::vector<std::string> {
    std::vector<std::string> result;

    result.push_back("comment");
    result.push_back("element");
    result.push_back("property");
    result.push_back("end_header");        

    return result;
}();

enum ElementKeyword
{
    VERTEX,
    FACE
};

std::vector<std::string> element_keywords = [] () -> std::vector<std::string> {
    std::vector<std::string> result;

    result.push_back("vertex");
    result.push_back("face");
        
    return result;
}();

void PlyParser::parse_header()
{
    parse_keyword("ply");

    parse_keyword("format");                
    unsigned int format = parse_keyword(format_keywords);
    if (format != 0)
    {
        throw std::runtime_error("Only ASCII PLY files are suported.");
    }

    double version = parse_float();
    if (version != 1.0)
    {
        throw std::runtime_error("Only version 1.0 of PLY format is supported.");
    }

    unsigned int keyword;
    do
    {
        keyword = parse_keyword(header_keywords);

        switch (keyword)
        {
            case COMMENT:
                lex_discard_line();
                break;
            case ELEMENT:
                parse_element();
                break;
            case PROPERTY:
                parse_property();
                break;
            case END_HEADER:
                // do nothing
                break;
            default:
                throw std::logic_error("Unknown header keyword!");
        }

    }
    while (keyword != END_HEADER);
}

void PlyParser::parse_element()
{
    unsigned int type = parse_keyword(element_keywords);
    unsigned long count = parse_integer();

    elements.push_back(std::make_tuple(type, count, std::vector<std::string>()));
}

void PlyParser::parse_property()
{
    // NOTE: we don't care about the type

    std::string type = parse_identifier();
        
    if (type == "list")
    {
        std::string index_type = parse_identifier();
        std::string value_type = parse_identifier();
    }

    std::string name = parse_identifier();

    if (elements.empty())
    {
        std::stringstream buff;
        buff << file << "(" << line << "): Property before element.";
        throw std::runtime_error(buff.str());
    }

    std::get<2>(elements.back()).push_back(name);
}

void PlyParser::parse_body()
{
    for (const Element& element : elements)
    {
        if (std::get<0>(element) == VERTEX)
        {
            for (unsigned int i = 0; i < std::get<1>(element); i++)
            {
                parse_vertex(i, std::get<2>(element));
            }
        }
        else 
        {
            for (unsigned int i = 0; i < std::get<1>(element); i++)
            {
                parse_face();
            }
        }
    }
}    

void PlyParser::parse_vertex(size_t elem, const std::vector<std::string>& properties)
{
    std::map<std::string, float> values;
    values["x"] = values["y"] = values["z"] = 0.0;
    values["nx"] = values["nx"] = values["nx"] = 0.0;
    values["s"] = values["t"] = 0.0;

    for (unsigned int i = 0; i < properties.size(); i++)
    {
        values[properties[i]] = (float)parse_float();
    }

    vertices.push_back(glm::vec3(values["x"], values["y"], values["z"]));
    normals.push_back(glm::vec3(values["nx"], values["ny"], values["nz"]));
    texcoords.push_back(glm::vec2(values["s"], 1.0f - values["t"]));
}

void PlyParser::parse_face()
{
    unsigned int count = parse_integer();;

    std::vector<unsigned int> indglows(count, 0);
    for (unsigned int i = 0; i < indglows.size(); i++)
    {
        indglows[i] = parse_integer();
    }

    // we build fans, when n != 3
    for (unsigned int i = 2; i < indglows.size(); i++)
    {
        indexes.push_back(glm::ivec3(indglows[0], indglows[i - 1], indglows[i]));
    }
}
