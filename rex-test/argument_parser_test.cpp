// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"

#include <rex/argument_parser.h>

TEST(argument_parser, parse_command)
{
    const char* argv[] = { "test" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
}

TEST(argument_parser, parse_flags)
{
    const char* argv[] = { "test", "--foo", "--baz" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.define_flag("foo", "Foo flag");
    parser.define_flag("baz", "Baz flag");

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
    EXPECT_TRUE(parser.has_flag("foo"));
    EXPECT_TRUE(parser.has_flag("baz"));
}

TEST(argument_parser, parse_short_flags)
{
    const char* argv[] = { "test", "-f", "--baz" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.define_flag('f', "foo", "Foo flag");
    parser.define_flag('b', "baz", "Baz flag");

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
    EXPECT_TRUE(parser.has_flag("foo"));
    EXPECT_TRUE(parser.has_flag("baz"));
}

TEST(argument_parser, parse_options)
{
    const char* argv[] = { "test", "--foo=bar", "--baz=qux" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.define_option("foo", "Foo option", "default");
    parser.define_option("baz", "Baz option", "default");

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
    EXPECT_EQ(parser.get_option("foo"), "bar");
    EXPECT_EQ(parser.get_option("baz"), "qux");
}

TEST(argument_parser, parse_files)
{
    const char* argv[] = { "test", "foo.txt", "bar.txt" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
    ASSERT_EQ(parser.get_files().size(), 2u);
    EXPECT_EQ(parser.get_files()[0], "foo.txt");
    EXPECT_EQ(parser.get_files()[1], "bar.txt");
}

TEST(argument_parser, parse_all)
{
    const char* argv[] = { "test", "-f", "--baz=qux", "foo.txt", "bar.txt" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    parser.define_flag('f', "foo", "Foo flag");
    parser.define_option("baz", "Baz option", "default");

    parser.parse(argc, argv);

    EXPECT_EQ(parser.get_command(), "test");
    EXPECT_TRUE(parser.has_flag("foo"));
    EXPECT_EQ(parser.get_option("baz"), "qux");
    ASSERT_EQ(parser.get_files().size(), 2u);
    EXPECT_EQ(parser.get_files()[0], "foo.txt");
    EXPECT_EQ(parser.get_files()[1], "bar.txt");
}

TEST(argument_parser, parse_invalid_flag)
{
    const char* argv[] = { "test", "--foo" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    EXPECT_THROW(parser.parse(argc, argv), std::runtime_error);
}

TEST(argument_parser, parse_invalid_option)
{
    const char* argv[] = { "test", "--foo=bar" };
    int argc = sizeof(argv) / sizeof(char*);

    auto parser = rex::argument_parser{};

    EXPECT_THROW(parser.parse(argc, argv), std::runtime_error);
}

TEST(argument_parser, get_help)
{
    auto parser = rex::argument_parser{};

    parser.define_flag('f', "foo", "Foo flag");
    parser.define_option("baz", "Baz option", "default");

    const char* argv[] = { "test", "--foo" };
    int argc = sizeof(argv) / sizeof(char*);

    parser.parse(argc, argv);
    auto help = parser.get_help();

    EXPECT_EQ(help, "Usage:\n"
                    "  test [options] [files]\n"
                    "\n"
                    "Options:\n"
                    "  --baz     Baz option\n"
                    "  --foo, -f Foo flag\n");
}