#pragma once

#include <string>
#include <vector>

#include "file_error.hpp"

namespace file_manager {
    struct FileLoadResult {
        FileEncoding encoding = FileEncoding::Unknown;
        std::string content;
        std::vector<size_t> line_starts;
        std::uintmax_t size = 0;
        FileError error = FileError::None;

        static FileLoadResult success(FileEncoding encoding,
                                      std::string content,
                                      std::vector<size_t> line_starts,
                                      std::uintmax_t size) {
            return FileLoadResult{
                encoding,
                std::move(content),
                line_starts,
                size,
                FileError::None
            };
        }

        static FileLoadResult failure(FileError error) {
            return FileLoadResult{
                FileEncoding::Unknown,
                "",
                {},
                {},
                error
            };
        }

        bool hasError() const noexcept {
            return error != FileError::None;
        }
    };
}
