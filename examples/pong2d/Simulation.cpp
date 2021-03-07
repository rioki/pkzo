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

#include "pch.h"
#include "Simulation.h"

namespace pong2d
{
    using namespace std::literals::chrono_literals;
    using fsec = std::chrono::duration<float>;

    constexpr auto TICK_RATE       = 10ms;
    constexpr auto BALL_SIZE       = glm::vec2{15.0, 15.0};
    constexpr auto INIT_BALL_SPEED = 150.0f;
    constexpr auto BALL_SPEEDUP    = 1.1f;
    constexpr auto PADDLE_SIZE     = glm::vec2{15.0, 100.0};
    constexpr auto PADDLE_SPEED    = 150.0f;

    Object::Object(Simulation& sim, const glm::vec2& s, const glm::vec2& p) noexcept
    : simulation(sim), size(s), position(p) {}

    Object::~Object() = default;

    const glm::vec2& Object::get_size() const noexcept
    {
        return size;
    }

    const glm::vec2& Object::get_position() const noexcept
    {
        return position;
    }

    bool overlap(const Object& a, const Object& b)
    {
        auto a_min = a.get_position() - a.get_size() / 2.0f;
        auto a_max = a.get_position() + a.get_size() / 2.0f;

        auto b_min = b.get_position() - b.get_size() / 2.0f;
        auto b_max = b.get_position() + b.get_size() / 2.0f;

        auto outside = a_min.x > b_max.x || a_max.x < b_min.x ||
                       a_min.y > b_max.y || a_max.y < b_min.y;

        return !outside;
    }

    Ball::Ball(Simulation& sim, const glm::vec2& position)
    : Object(sim, BALL_SIZE, position)
    {
        std::uniform_int_distribution<> bool_dis(0, 1);
        serve(bool_dis(simulation.random_engine) ? Direction::LEFT : Direction::RIGHT);
    }

    void Ball::serve(Direction dir)
    {
        switch (dir)
        {
            case Direction::LEFT:
            {
                std::uniform_real_distribution<float> ydis(-1.0, 1.0);
                position = {-300.0f, 0.0f};
                velocity = glm::normalize(glm::vec2(1.0f, ydis(simulation.random_engine))) * INIT_BALL_SPEED;
                break;
            }
            case Direction::RIGHT:
            {
                std::uniform_real_distribution<float> ydis(-1.0, 1.0);
                position = {300.0f, 0.0f};
                velocity = glm::normalize(glm::vec2(-1.0f, ydis(simulation.random_engine))) * INIT_BALL_SPEED;
                break;
            }
        }
    }

    void Ball::tick(std::chrono::milliseconds dt) noexcept
    {
        const auto& field_size = simulation.get_field_size();

        // relfect wall
        position += velocity * std::chrono::duration_cast<fsec>(dt).count();
        if ((position.y >= (field_size.y / 2.0f - size.y / 2.0f)) ||
            (position.y <= (-field_size.y / 2.0f + size.y / 2.0f)))
        {
            velocity.y = -velocity.y;
        }

        // reflect paddle
        if ((overlap(*this, *simulation.left_paddle) && velocity.x < 0.0f) ||
            (overlap(*this, *simulation.right_paddle) && velocity.x > 0.0f))
        {
            std::uniform_real_distribution<float> ydis(-0.2, 0.2);
            velocity.x = -velocity.x;
            velocity = velocity * BALL_SPEEDUP;
            velocity.y += ydis(simulation.random_engine);
        }
    }

    Paddle::Paddle(Simulation& sim, const glm::vec2& position)
    : Object(sim, PADDLE_SIZE, position) {}

    void Paddle::start_up() noexcept
    {
        move_up = true;
    }

    void Paddle::stop_up() noexcept
    {
        move_up = false;
    }

    void Paddle::start_down() noexcept
    {
        move_down = true;
    }

    void Paddle::stop_down() noexcept
    {
        move_down = false;
    }

    void Paddle::tick(std::chrono::milliseconds dt) noexcept
    {
        const auto& field_size = simulation.get_field_size();

        if (move_up && position.y <= (field_size.y/2.0f - size.y / 2.0f))
        {
            position.y += PADDLE_SPEED * std::chrono::duration_cast<fsec>(dt).count();
        }
        if (move_down && position.y >= (-field_size.y/2.0f + size.y / 2.0f))
        {
            position.y -= PADDLE_SPEED * std::chrono::duration_cast<fsec>(dt).count();
        }
    }

    Simulation::Simulation(unsigned int random_seed)
    : random_engine(random_seed)
    {
        left_paddle  = std::make_unique<Paddle>(*this, glm::vec2(-380.0, 0.0));
        right_paddle = std::make_unique<Paddle>(*this, glm::vec2(380.0, 0.0));
        ball         = std::make_unique<Ball>(*this, glm::vec2(0.0, 0.0));
    }

    glm::vec2 Simulation::get_field_size() const noexcept
    {
        return field_size;
    }

    unsigned int Simulation::get_left_score() const noexcept
    {
        return left_score;
    }

    unsigned int Simulation::get_right_score() const noexcept
    {
        return right_score;
    }

    Paddle& Simulation::get_left_paddle() const noexcept
    {
        assert(left_paddle);
        return *left_paddle;
    }

    Paddle& Simulation::get_right_paddle() const noexcept
    {
        assert(right_paddle);
        return *right_paddle;
    }

    Ball& Simulation::get_ball() const noexcept
    {
        assert(ball);
        return *ball;
    }

    void Simulation::tick(std::chrono::milliseconds dt)
    {
        time_accumulator += dt;
        while (time_accumulator > TICK_RATE)
        {
            left_paddle->tick(TICK_RATE);
            right_paddle->tick(TICK_RATE);
            ball->tick(TICK_RATE);
            check_score();
            time_accumulator -= TICK_RATE;
        }
    }

    void Simulation::check_score()
    {
        if (ball->get_position().x >= (field_size.x / 2.0f))
        {
            ball->serve(Direction::LEFT);
            left_score++;
        }
        if (ball->get_position().x <= (-field_size.x / 2.0f))
        {
            ball->serve(Direction::RIGHT);
            right_score++;
        }
    }
}
