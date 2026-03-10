#pragma once

#include <filesystem>
#include <system_error>

namespace file_manager {
    struct PathUtils {
        static std::filesystem::path normalizePath(const std::filesystem::path& path) {
            std::error_code ec;
            auto canonical_path = std::filesystem::canonical(path, ec);

            if (!ec) return canonical_path;

            return std::filesystem::weakly_canonical(path, ec);
        }
    };
}