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

#ifndef _PLY_PARSER_H_
#define _PLY_PARSER_H_

#include <string>
#include <fstream>
#include <vector>
#include <tuple>

#include <glm/glm.hpp>

enum TokenType
{
    WHITESPACE,
    NEWLINE,
    IDENTIFIER,
    NUMBER, 
    END_OF_FILE
};

class PlyParser
{
public:
    PlyParser();

    ~PlyParser();

    const std::vector<glm::vec3>& get_vertexes() const;
    const std::vector<glm::vec3>& get_normals() const; 
    const std::vector<glm::vec2>& get_texcoords() const; 
    const std::vector<glm::ivec3>& get_indexes() const;  

    void parse(const std::string& file);

private:
    std::vector<glm::vec3> vertexes;  // v4f
    std::vector<glm::vec3> normals;   // v3f
    std::vector<glm::vec2> texcoords; // v2f
    std::vector<glm::ivec3> indexes;  // trangles

    std::ifstream input;
    std::string file;
    unsigned int line;

    // - type: vertex or face
    // - number of entires
    // - properties
    typedef std::tuple<unsigned int, unsigned int, std::vector<std::string>> Element;  
    std::vector<Element> elements;

    TokenType get_next_token(std::string& value);
    TokenType lex_token(std::string& value);
    TokenType lex_whitespace(std::string& value);
    TokenType lex_newline(std::string& value);
    TokenType lex_identifier(std::string& value);
    TokenType lex_number(std::string& value);
    void lex_discard_line();

    void parse_keyword(const std::string& keyword);
    unsigned int parse_keyword(const std::vector<std::string>& keywords);
    std::string parse_identifier();
    double parse_float();
    unsigned long parse_integer();
        

    void parse_header();
    void parse_element();
    void parse_property();
    void parse_body();
    void parse_vertex(size_t i, const std::vector<std::string>& properties);
    void parse_face();
};

#endif
