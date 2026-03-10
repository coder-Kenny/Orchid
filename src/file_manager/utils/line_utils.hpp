#pragma once

#include <string_view>
#include <vector>

namespace file_manager {
    struct LineUtils {
        static std::vector<size_t> computeLineStarts(std::string_view content) {
            std::vector<std::size_t> lines;
            for (std::size_t i = 0; i < content.size(); ++i) {
                if (content[i] == '\n') {
                    lines.emplace_back(i);
                }
            }
            return lines;
        }
    };
}