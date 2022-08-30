// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "utils.h"

namespace ice
{
    std::u32string utf32(const std::u8string& buff)
    {
        std::u32string result;

        auto cd = iconv_open("UTF-32LE", "UTF-8");
        assert(cd);

        char* inbuf        = reinterpret_cast<char*>(const_cast<char8_t*>(buff.data()));
        size_t inbytesleft = buff.size();

        std::array<char, 512> temp;
        char*  outbuf       = temp.data();
        size_t outbytesleft = temp.size();

        while (inbytesleft > 0u)
        {
            iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
            result.append(reinterpret_cast<char32_t*>(temp.data()), reinterpret_cast<char32_t*>(outbuf));
            outbuf       = temp.data();
            outbytesleft = temp.size();
        }

        int r = iconv_close(cd);
        assert(r == 0);

        return result;
    }

    std::u32string utf32(const std::string& buff)
    {
        return utf32(std::u8string(reinterpret_cast<const char8_t*>(buff.data())));
    }

    void trace(const std::string_view msg)
    {
        OutputDebugStringA(msg.data());
    }
}
