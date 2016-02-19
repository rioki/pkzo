/*
  pkzo

  Copyright (c) 2014-2016 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Canvas.h"

#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#else
// TODO ezrc
#endif

#include <GL/glew.h>

namespace pkzo
{
    #ifdef _MSC_VER
    std::string LoadTextResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType)
    {
        HRSRC   hPhongVertex  = FindResource(hModule, lpName, lpType);
        HGLOBAL hgPhongVertex = LoadResource(hModule, hPhongVertex);
        DWORD   nSize         = SizeofResource(hModule, hPhongVertex);
        const char* psCode = (const char*)LockResource(hgPhongVertex);        
        return std::string(psCode, nSize);
    }
    #endif

    Canvas::Canvas(ivec2 s)
    : size(s)
    {
        projection_matrix = rgm::ortho<float>(0.0f, size[0], size[1], 0.0f, -1.0f, 1.0f);

        rect.create_plane(1.0f, 1.0f);

        #ifdef _MSC_VER
        HMODULE hModule = GetModuleHandle(_T("pkzo2d.dll"));

        std::string vertex   = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_CANVAS_VERTEX), _T("GLSL"));
        std::string fragment = LoadTextResource(hModule, MAKEINTRESOURCE(IDR_GLSL_CANVAS_FRAGMENT), _T("GLSL"));
        #else
        // TODO
        #endif

        shader.set_vertex_code(vertex);
        shader.set_fragment_code(fragment);
    }

    Canvas::~Canvas() {}
        
    void Canvas::set_size(ivec2 value)
    {
        size = value;
        projection_matrix = rgm::ortho<float>(0.0f, size[0], size[1], 0.0f, -1.0f, 1.0f);
    }

    ivec2 Canvas::get_size() const
    {
        return size;
    }

    void Canvas::draw_rectangle(ivec2 pos, ivec2 size, vec4 color)
    {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        model_view_matrix = rgm::mat4(1);
        model_view_matrix = rgm::translate(model_view_matrix, vec3(pos[0], pos[1], 0.0f));
        model_view_matrix = rgm::scale(model_view_matrix, vec3(size[0], size[1], 1.0f));
        model_view_matrix = rgm::translate(model_view_matrix, vec3(0.5f, 0.5f, 0.0f));

        shader.bind();
        shader.set_uniform("uProjectionMatrix", projection_matrix);
        shader.set_uniform("uModelViewMatrix", model_view_matrix);

        shader.set_uniform("uvec4", color);
        
        shader.set_uniform("uHasTexture", 0);
        
        rect.draw();
    }

    void Canvas::draw_rectangle(ivec2 pos, ivec2 size, vec4 color, Texture& texture)
    {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        model_view_matrix = rgm::mat4(1);
        model_view_matrix = rgm::translate(model_view_matrix, vec3(pos[0], pos[1], 0.0f));
        model_view_matrix = rgm::scale(model_view_matrix, vec3(size[0], size[1], 1.0f));
        model_view_matrix = rgm::translate(model_view_matrix, vec3(0.5f, 0.5f, 0.0f));

        shader.bind();
        shader.set_uniform("uProjectionMatrix", projection_matrix);
        shader.set_uniform("uModelViewMatrix", model_view_matrix);

        shader.set_uniform("uvec4", color);
        
        texture.bind(0);
        shader.set_uniform("uTexture", 0);
        shader.set_uniform("uHasTexture", 1);
        
        rect.draw();
    }
}