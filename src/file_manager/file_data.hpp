#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "file_error.hpp"
#include "file_kind.hpp"
#include "file_encoding.hpp"

namespace file_manager {
    struct FileData {
        FileEncoding encoding = FileEncoding::Unknown;
        std::string content;
        std::vector<size_t> line_starts;
        std::uintmax_t size = 0;
        FileError error = FileError::None;
        FileKind kind = FileKind::Unknown;

        static FileData success(FileEncoding encoding,
                                std::string content,
                                std::vector<std::size_t> line_starts,
                                std::uintmax_t size,
                                FileKind kind) {
            return FileData{
                encoding,
                std::move(content),
                std::move(line_starts),
                size,
                FileError::None,
                kind
            };
        }

        static FileData failure(FileError error) {
            return FileData{
                FileEncoding::Unknown,
                {},
                {},
                0,
                error,
                FileKind::Unknown
            };
        }

        constexpr bool hasError() const noexcept {
            return error != FileError::None;
        }
    };
}
