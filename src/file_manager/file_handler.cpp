#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

#include "file_handler.hpp"
#include "file_data.hpp"
#include "file_error.hpp"

namespace file_manager {
    namespace fs = std::filesystem;

    FileLoadResult FileHandler::loadFile(const fs::path& path) const {
        std::error_code ec;
        const fs::file_status status = fs::status(path, ec);

        if (ec) {
            if (ec == std::errc::permission_denied)
                return FileLoadResult::failure(FileError::PermissionDenied);

            return FileLoadResult::failure(FileError::Unknown);
        }

        if (status.type() == fs::file_type::not_found) {
            return FileLoadResult::failure(FileError::NotFound);
        }

        if (status.type() != fs::file_type::regular) {
            return FileLoadResult::failure(FileError::Unknown);
        }

        const auto size = fs::file_size(path, ec);

        if (ec) {
            return FileLoadResult::failure(FileError::SizeFailed);
        }

        if (size == 0) {
            return FileLoadResult::failure(FileError::EmptyFile);
        }

        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return FileLoadResult::failure(FileError::OpenFailed);
        }

        std::string content(size, '\0');
        if (!file.read(content.data(), static_cast<std::streamsize>(size))) {
            return FileLoadResult::failure(FileError::ReadFailed);
        }

        return FileLoadResult::success(content, size);
    }

    void FileHandler::newFile(const fs::path& path, FileKind kind) {
        FileLoadResult result = loadFile(path);
        if (result.hasError()) {
            files_.emplace_back(FileData::failure(path, result.error_));
        } else {
            files_.emplace_back(FileData::success(path, result.content_, result.size_, kind));
        }
    }
}
