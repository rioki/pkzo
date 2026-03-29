// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Ghost.h"

#include <pkzo/debug.h>

#include "Scene.h"
#include "PhysicsSimulation.h"

namespace pkzo
{
    using pkzo::check;

    Ghost::Ghost(Init init)
    : Group({init.parent, init.transform})
    {
        auto scene = get_root();
        check(scene);

        auto physics_sim = scene->get_physics_simulation();
        check(physics_sim);
        physics_sim->add(this);
    }

    Ghost::~Ghost()
    {
        auto scene = get_root();
        check(scene);

        auto physics_sim = scene->get_physics_simulation();
        check(physics_sim);
        physics_sim->remove(this);
    }
}