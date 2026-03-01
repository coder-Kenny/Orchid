#pragma once

#include <string>

#include "file_error.hpp"

namespace file_manager {
    struct FileLoadResult {
        std::string content_{};
        FileError error_{FileError::None};
        std::uintmax_t size_{};

        static FileLoadResult makeError(FileError error) {
            return {"", error, 0};
        }

        static FileLoadResult makeSuccess(std::string content, std::uintmax_t size) {
            return {std::move(content), FileError::None, size};
        }

        [[nodiscard]] bool hasError() const {
            return error_ != FileError::None;
        }
    };
}