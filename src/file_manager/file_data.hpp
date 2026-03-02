#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

#include "file_error.hpp"
#include "file_kind.hpp"

namespace file_manager {
    class FileData {
    public:
        [[nodiscard]] static FileData success(std::filesystem::path path,
                                              std::string content,
                                              std::uintmax_t size,
                                              FileKind kind) {
            return FileData(std::move(path), std::move(content), size, FileError::None, kind);
        }

        [[nodiscard]] static FileData failure(std::filesystem::path path, FileError error) {
            return FileData(std::move(path), {}, 0, error, FileKind::Unknown);
        }

        [[nodiscard]] bool hasError() const noexcept {
            return error_ != FileError::None;
        }

        // Getters
        [[nodiscard]] std::filesystem::path getPath() const noexcept { return path_; }
        [[nodiscard]] const std::string& getContent() const noexcept { return content_; }
        [[nodiscard]] std::uintmax_t getSize() const noexcept { return size_; }
        [[nodiscard]] FileError getError() const noexcept { return error_; }
        [[nodiscard]] FileKind getKind() const noexcept { return kind_; }

    private:
        explicit FileData(std::filesystem::path path,
                          std::string content,
                          std::uintmax_t size,
                          FileError error,
                          FileKind kind)
            : path_{std::move(path)},
              content_{std::move(content)},
              size_{size},
              error_{error},
              kind_{kind} {}

        std::filesystem::path path_{};
        std::string content_{};
        std::uintmax_t size_{};
        FileError error_{FileError::None};
        FileKind kind_{FileKind::Unknown};
    };
}
