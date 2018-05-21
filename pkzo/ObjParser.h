//
// OBJ Parser
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

#ifndef _OBJ_PARSER_H_
#define _OBJ_PARSER_H_

#include <string>
#include <fstream>
#include <vector>
#include <tuple>

#include <rgm/rgm.h>

class ObjParser
{
public:

    ObjParser();

    ~ObjParser();

    const std::vector<rgm::vec3>& get_vertices() const;

    const std::vector<rgm::vec3>& get_normals() const;

    const std::vector<rgm::vec2>& get_texcoords() const;

    const std::vector<std::vector<rgm::ivec3>>& get_faces() const;

    void parse(const std::string& file);

private:
    enum TokenType
    {
        NO_TOKEN,
        WHITESPACE,
        NEWLINE,
        COMMENT,
        IDENTIFIER,
        NUMBER, 
        SLASH,
        DOT,
        BSLASH,
        END_OF_FILE
    };

    std::ifstream input;
    std::string file;
    unsigned int line;
        
    TokenType   token;
    TokenType   next_token;
    std::string value;
    std::string next_value;

    std::vector<rgm::vec3> vertices;
    std::vector<rgm::vec3> normals;
    std::vector<rgm::vec2> texcoords;
    std::vector<std::vector<rgm::ivec3>> faces;

    void get_next_token();
    TokenType lex_token(std::string& value);
    TokenType lex_whitespace(std::string& value);
    TokenType lex_newline(std::string& value);
    TokenType lex_comment(std::string& value);
    TokenType lex_identifier(std::string& value);
    TokenType lex_number(std::string& value);

    void parse_keyword(const std::string& keyword);
    unsigned int parse_keyword(const std::vector<std::string>& keywords);
    std::string parse_identifier();
    std::string parse_identifier_or_number();
    float parse_float();
    unsigned long parse_integer();
    std::string parse_filename();

    void parse_line();
    void parse_vertex();
    void parse_texcoord();
    void parse_normal();
    void parse_parmeter();
    void parse_face();
    void parse_mtllib();
    void parse_usemtl();
    void parse_object();
    void parse_group();
    void parse_smothing();
    rgm::ivec3 parse_face_point();
};

#endif
