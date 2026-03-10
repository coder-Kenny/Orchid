#pragma once

#include <cstdint>
#include <filesystem>
#include <unordered_map>

#include "file_data.hpp"
#include "file_kind.hpp"
#include "file_load_result.hpp"

namespace file_manager {
    class FileHandler {
    public:
        void newFile(const std::filesystem::path& raw_path, FileKind kind);

        [[nodiscard]] std::unordered_map<std::filesystem::path, FileData> getFiles() const { return files_; }

    private:
        std::unordered_map<std::filesystem::path, FileData> files_;

        FileLoadResult loadFile(const std::filesystem::path& path) const;

        std::optional<FileLoadResult> checkStatus(const std::filesystem::path& path) const;
        std::optional<FileLoadResult> determineSize(const std::filesystem::path& path, std::uintmax_t& out_size) const;
        std::optional<FileLoadResult> readFile(const std::filesystem::path& path, std::string& out_content, std::uintmax_t size) const;
        std::optional<FileLoadResult> checkEncoding(FileEncoding& out_enc, std::string& content, std::uintmax_t& out_size) const;

    };
}