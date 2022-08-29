// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"

#include <ice/AssetLibrary.h>
#include <ice/Asset.h>

#include "test_utils.h"

class TestAsset : public ice::Asset
{
public:
    TestAsset(const std::filesystem::path& file, unsigned int _size = 12)
    : Asset(file), size(_size)
    {
        auto input = std::ifstream(file);
        if (! input.is_open())
        {
            throw std::format("Failed to open {} for reading.", file.string());
        }
        input >> value;
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
    unsigned int size  = 0;
    unsigned int value = 0;
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