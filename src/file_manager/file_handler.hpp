#pragma once

#include <filesystem>
#include <vector>

#include "file_data.hpp"
#include "file_load_result.hpp"

namespace file_manager {
    class FileHandler {
    public:
        void newFile(const std::filesystem::path& path, FileKind);

    private:
        std::vector<FileData> files_;

        [[nodiscard]] FileLoadResult loadFile(const std::filesystem::path& path) const;
    };
}