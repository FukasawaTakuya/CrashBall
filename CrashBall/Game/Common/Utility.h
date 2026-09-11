#pragma once

#include <windows.h>
#include <string>
#include <vector>

namespace Utility
{
    // ワイド文字に変換
    inline std::wstring ConvertToWideChar(const std::string& str) {
        if (str.empty()) return L"";

        // 必要サイズ取得 
        int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);

        // ヌル文字分を引く
        std::wstring wstr(size - 1, 0); 
        // 変換
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);

        return wstr;
    }

    // マルチバイト文字に変換
    inline std::string ConvertToMultiByteChar(const std::wstring& wstr)
    {
        if (wstr.empty()) return "";

        // 必要なサイズを取得 
        int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
        std::string str(size, 0);

        // 変換
        WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);

        // ヌル文字を抜く
        str.resize(size - 1);
        return str;
    }

    // m_の削除
    inline std::string RemoveMemberPrefix(const std::string& member)
    {
        size_t pos = member.rfind("_");
        return member.substr(pos + 1);
    }

    // StringView配列=>const char*配列に変換
    template<size_t N>
    inline std::array<const char*, N> StringViewToCharArray(const std::array<std::string_view, N>& svArray)
    {
        std::array<const char*, N> cArray;

        for (int i = 0; i < N; i++)
        {
            cArray[i] = svArray[i].data();
        }

        return cArray;
    }

}
