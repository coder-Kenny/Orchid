#pragma once

#include <string>
#include <string_view>

#include "file_encoding.hpp"

namespace file_manager {
    struct BomUtils {
        static FileEncoding detectEncoding(std::string_view content) {
            if (content.size() >= 3 &&
                (unsigned char)content[0] == 0xEF &&
                (unsigned char)content[1] == 0xBB &&
                (unsigned char)content[2] == 0xBF)
                return FileEncoding::UTF8_BOM;

            if (content.size() >= 2 &&
                (unsigned char)content[0] == 0xFF &&
                (unsigned char)content[1] == 0xFE)
                return FileEncoding::UTF16_LE;

            if (content.size() >= 2 &&
                (unsigned char)content[0] == 0xFE &&
                (unsigned char)content[1] == 0xFF)
                return FileEncoding::UTF16_BE;

            if (content.size() >= 4 &&
                (unsigned char)content[0] == 0xFF &&
                (unsigned char)content[1] == 0xFE &&
                (unsigned char)content[2] == 0x00 &&
                (unsigned char)content[3] == 0x00)
                return FileEncoding::UTF32_LE;

            if (content.size() >= 4 &&
                (unsigned char)content[0] == 0x00 &&
                (unsigned char)content[1] == 0x00 &&
                (unsigned char)content[2] == 0xFE &&
                (unsigned char)content[3] == 0xFF)
                return FileEncoding::UTF32_BE;

            return FileEncoding::UTF8;
        }

        static void removeUTF8BOM(std::string& content) {
            if (content.size() >= 3 &&
               (unsigned char)content[0] == 0xEF &&
               (unsigned char)content[1] == 0xBB &&
               (unsigned char)content[2] == 0xBF)
               content.erase(0, 3);
        }
    };
}