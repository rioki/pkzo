//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _PONG2D_SIMULATION_H_
#define _PONG2D_SIMULATION_H_

#include <memory>
#include <chrono>
#include <random>

namespace pong2d
{
    class Simulation;

    enum class Direction
    {
        LEFT,
        RIGHT
    };

    class Object
    {
    public:
        Object(Simulation& simulation, const glm::vec2& size, const glm::vec2& position) noexcept;
        virtual ~Object();

        const glm::vec2& get_size() const noexcept;
        const glm::vec2& get_position() const noexcept;

        virtual void tick(std::chrono::milliseconds dt) noexcept = 0;

    protected:
        Simulation& simulation;
        glm::vec2 size     = {0.0f, 0.0f};
        glm::vec2 position = {0.0f, 0.0f};
    };

    class Ball : public Object
    {
    public:
        Ball(Simulation& simulation, const glm::vec2& position);

        void serve(Direction dir);
        void tick(std::chrono::milliseconds dt) noexcept override;

    private:
        glm::vec2 velocity = {0.0f, 0.0f};
    };

    class Paddle : public Object
    {
    public:
        Paddle(Simulation& simulation, const glm::vec2& position);

        void start_up() noexcept;
        void stop_up() noexcept;
        void start_down() noexcept;
        void stop_down() noexcept;

        void tick(std::chrono::milliseconds dt) noexcept override;

    private:
        bool move_up   = false;
        bool move_down = false;
    };

    class Simulation
    {
    public:
        Simulation(unsigned int random_seed);

        glm::vec2 get_field_size() const noexcept;

        unsigned int get_left_score() const noexcept;
        unsigned int get_right_score() const noexcept;

        Paddle& get_left_paddle() const noexcept;
        Paddle& get_right_paddle() const noexcept;
        Ball& get_ball() const noexcept;

        void tick(std::chrono::milliseconds dt);

    private:
        std::chrono::milliseconds time_accumulator = std::chrono::milliseconds(0);

        glm::vec2    field_size    = {800, 600};
        unsigned int left_score    = 0;
        unsigned int right_score   = 0;

        std::mt19937 random_engine;

        std::unique_ptr<Paddle> left_paddle;
        std::unique_ptr<Paddle> right_paddle;
        std::unique_ptr<Ball>   ball;

        void check_score();

    friend class Paddle;
    friend class Ball;
    };
}

#endif
