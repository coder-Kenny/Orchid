#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

#include "file_error.hpp"
#include "file_kind.hpp"

namespace file_manager {
    class FileData {
    public:
        explicit FileData(std::filesystem::path path,
                          std::string content,
                          std::uintmax_t size,
                          FileError error,
                          FileKind kind);

        static FileData FileData::makeSuccess(std::filesystem::path path,
                                       std::string content,
                                       std::uintmax_t size,
                                       FileKind kind) {
            return FileData(path, content, size, FileError::None, kind);
        }

        static FileData FileData::makeError(std::filesystem::path path, FileError error) {
            return FileData(path, {}, 0, error, FileKind::Unknown);
        }

        [[nodiscard]] bool FileData::hasError() const noexcept {
            return error_ != FileError::None;
        }

        // Getters
        [[nodiscard]] std::filesystem::path getPath() const noexcept { return path_; }
        [[nodiscard]] const std::string& getContent() const noexcept { return content_; }
        [[nodiscard]] std::uintmax_t getSize() const noexcept { return size_; }
        [[nodiscard]] FileError getError() const noexcept { return error_; }
        [[nodiscard]] FileKind getKind() const noexcept { return kind_; }

    private:
        std::filesystem::path path_{};
        std::string content_{};
        std::uintmax_t size_{0};
        FileError error_{FileError::None};
        FileKind kind_{FileKind::Unknown};
    };
}
