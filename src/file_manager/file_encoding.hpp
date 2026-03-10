#pragma once

#include <string_view>

namespace file_manager {
    enum class FileEncoding {
        UTF8 = 0,
        UTF8_BOM,
        UTF16_LE,
        UTF16_BE,
        UTF32_LE,
        UTF32_BE,
        Unknown
    };

    constexpr bool isBadEnc(FileEncoding enc) {
        return enc != FileEncoding::UTF8 && enc != FileEncoding::UTF8_BOM;
    }

    constexpr std::string_view to_string(FileEncoding enc) {
        switch (enc) {
            case FileEncoding::UTF8: return "UTF-8";
            case FileEncoding::UTF8_BOM: return "UTF-8-BOM";
            case FileEncoding::UTF16_LE: return "UTF-16-LE";
            case FileEncoding::UTF16_BE: return "UTF-16-BE";
            case FileEncoding::UTF32_LE: return "UTF-32-LE";
            case FileEncoding::UTF32_BE: return "UTF-32-BE";
            case FileEncoding::Unknown: return "Unknown";
        }

        return "(unhandled FileEncoding value)";
    }
}