// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
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
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"

#include <ice/ice.h>

class TestAsset : public ice::Asset
{
public:
    TestAsset(const std::filesystem::path& _file, unsigned int _size = 12)
    : file(_file), size(_size)
    {
        auto input = std::ifstream(file);
        if (! input.is_open())
        {
            throw std::format("Failed to open {} for reading.", file.string());
        }
        input >> value;
    }

    const std::filesystem::path& get_file() const
    {
        return file;
    }

    unsigned int get_size() const
    {
        return size;
    }

    unsigned int get_value() const
    {
        return value;
    }

private:
    std::filesystem::path file;
    unsigned int          size  = 0;
    unsigned int          value = 0;
};

TEST(AssetLibrary, load_asset)
{
    auto lib = ice::AssetLibrary{};

    auto a = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt");
    ASSERT_NE(nullptr, a);

    EXPECT_EQ("TestAsset.txt", a->get_file().filename());
    EXPECT_EQ(42, a->get_value());
}

TEST(AssetLibrary, deduplicate)
{
    auto lib = ice::AssetLibrary{};

    auto a = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt");
    EXPECT_NE(nullptr, a);

    auto b = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt");
    EXPECT_NE(nullptr, b);

    EXPECT_EQ(a, b);
}

TEST(AssetLibrary, second_argument)
{
    auto lib = ice::AssetLibrary{};

    auto a = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt", 24);
    ASSERT_NE(nullptr, a);

    EXPECT_EQ("TestAsset.txt", a->get_file().filename());
    EXPECT_EQ(24, a->get_size());
}

TEST(AssetLibrary, second_argument_not_deduplicated)
{
    auto lib = ice::AssetLibrary{};

    auto a = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt", 24);
    EXPECT_NE(nullptr, a);

    auto b = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt", 48);
    EXPECT_NE(nullptr, b);

    EXPECT_NE(a, b);
}

TEST(AssetLibrary, search_path)
{
    // sanity check
    EXPECT_TRUE(ice::test::get_test_input().is_absolute());

    auto lib = ice::AssetLibrary{};
    lib.add_directory(ice::test::get_test_input());
    lib.add_directory(ice::test::get_asset_folder());

    // still loads absolute paths
    auto a = lib.load<TestAsset>(ice::test::get_test_input() / "TestAsset.txt", 24);
    EXPECT_NE(nullptr, a);

    // loads relative paths
    auto b = lib.load<TestAsset>("TestAsset.txt", 48);
    EXPECT_NE(nullptr, b);

    // and they are deduplicated nonetheless
    EXPECT_NE(a, b);
}