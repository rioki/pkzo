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

#pragma once

#include <filesystem>

namespace island
{
    //! Get the user folder.
    //!
    //! This function return the user folder, for example %LOCALAPPDATA%/rioki/garden
    //! or $HOME/.rioki/garden.
    //!
    //! @return the user folder
    [[nodiscard]]
    std::filesystem::path get_user_folder();

    //! Get the save folder.
    //!
    //! This function returns the save folder, generally get_user_folder()/saves.
    //!
    //! @return the save folder
    [[nodiscard]]
    std::filesystem::path get_save_folder();

    //! Get the asset folder.
    //!
    //! This function return the asset folder. If the game was launched inside
    //! a debugger the function tries to find the asset folder relative to CWD,
    //! else it tries to get it from the installation params.
    //!
    //! @return the asset folder
    [[nodiscard]]
    std::filesystem::path get_asset_folder();
}