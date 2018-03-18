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

// from PhongFragment.glsl
#define AMBIENT_LIGHT 0
#define DIFFUSE_LIGHT 1
#define POINT_LIGHT   2
#define SPOT_LIGHT    3

#include <gl/glew.h>
#include <pkzo/pkzo.h>

int main(int argc, char* argv[])
{    
    bool  running = true;
    float xangle  = 0.0;
    float yangle  = 0.0;

    pkzo::Mesh mesh;
    mesh.load("../assets/meshes/Teapot.ply");

    pkzo::Shader shader;
    shader.load("../assets/shaders/PhongVertex.glsl", "../assets/shaders/PhongFragment.glsl");

    pkzo::Window window(rgm::ivec2(1280, 768));  
    window.on_draw([&] () {                     
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

       rgm::mat4 projection = rgm::perspective(45.0f, window.get_aspect(), 0.1f, 100.0f);

       rgm::mat4 view(1);
        view = rgm::translate(view, rgm::vec3(0, 0, -7));
        view = rgm::rotate(view, rgm::vec3(1, 0, 0), yangle);
        view = rgm::rotate(view, rgm::vec3(0, 0, 1), xangle);        

       rgm::mat4 model(1);

       rgm::mat4 normal(view);

        shader.bind();
        shader.set_uniform("uProjectionMatrix",   projection);
        shader.set_uniform("uViewMatrix",         view);
        shader.set_uniform("uModelMatrix",        model);
        shader.set_uniform("uNormalMatrix",       normal);

        shader.set_uniform("uLightType",          DIFFUSE_LIGHT);
        shader.set_uniform("uLightDirection",    rgm::vec3(0.5, 0.5, 1));
        shader.set_uniform("uLightColor",        rgm::vec3(1, 1, 1));

        shader.set_uniform("uMaterialColor",     rgm::vec3(1, 1, 1));
        shader.set_uniform("uMaterialRoughness",  0.25f);
        shader.set_uniform("uMaterialHasTexture", 0);

        mesh.draw();
    });
    window.on_close([&] () {                    
        running = false;
    });

    pkzo::Keyboard keyboard;                    
    keyboard.on_key_press([&] (pkzo::Key key) { 
        if (key == pkzo::KEY_ESCAPE)            
        {                                       
            running = false;                    
        }
    });    

    pkzo::Mouse mouse;
    mouse.on_move([&] (rgm::ivec2 mov, rgm::ivec2 pos) {
        if (mouse.is_pressed(1)) 
        {
            xangle += mov[0];
            yangle += mov[1];
        }
    });

    while (running)                             
    {
        pkzo::route_events();                   
        
        window.draw();                          
    }
}
