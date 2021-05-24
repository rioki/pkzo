//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublpkzonse, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notpkzo and this permission notpkzo shall be included in
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

TEST(Mass, default_contructor)
{
    auto Mass = pkzo::Mass{};
    ASSERT_EQ(0.0, Mass.count());
}

TEST(Mass, construct_g)
{
    auto Mass = pkzo::Mass{1.2f};
    ASSERT_FLOAT_EQ(1.2f, Mass.count());
}

TEST(Mass, construct_kg)
{
    auto Mass = pkzo::Mass<float, std::kilo>(1.2);
    ASSERT_DOUBLE_EQ(1.2f, Mass.count());
}

TEST(Mass, cast_kg_to_g)
{
    auto Mass_kg = pkzo::KiloGramm(1.2);
    auto Mass_g = pkzo::mass_cast<pkzo::Gramm>(Mass_kg);
    EXPECT_NEAR(1200.0, Mass_g.count(), 1e-2);
}

TEST(Mass, cast_mg_to_g)
{
    auto Mass_mg = pkzo::MilliGramm(1.2f);
    auto Mass_g = pkzo::mass_cast<pkzo::Gramm>(Mass_mg);
    EXPECT_NEAR(0.0012, Mass_g.count(), 1e-4);
}


TEST(Mass, cast_kg_to_mg)
{
    auto Mass_kg = pkzo::KiloGramm(1.2f);
    auto Mass_mg = pkzo::mass_cast<pkzo::MilliGramm>(Mass_kg);
    EXPECT_NEAR(1200000.0, Mass_mg.count(), 1.0);
}

TEST(Mass, compare_mg_and_kg)
{
    using namespace pkzo::mass_literals;

    ASSERT_TRUE(1200000mg == 1.2kg);
}