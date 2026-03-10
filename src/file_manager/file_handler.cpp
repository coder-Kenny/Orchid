#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <system_error>

#include "file_handler.hpp"
#include "file_data.hpp"
#include "file_error.hpp"
#include "file_encoding.hpp"
#include "utils/bom_utils.hpp"
#include "utils/line_utils.hpp"
#include "utils/path_utils.hpp"

#define TRY(expr) if (auto err = (expr)) return *err;

namespace file_manager {
    namespace fs = std::filesystem;

    void FileHandler::newFile(const fs::path& raw_path, FileKind kind) {
        fs::path path = PathUtils::normalizePath(raw_path);

        if (files_.contains(path)) return;

        FileLoadResult result = loadFile(path);
        if (result.hasError()) {
            files_.insert_or_assign(path, FileData::failure(result.error));
        } else {
            files_.insert_or_assign(path, FileData::success(result.encoding,
                                                                result.content,
                                                                result.line_starts,
                                                                result.size,
                                                                kind));
        }
    }

    FileLoadResult FileHandler::loadFile(const fs::path& path) const {
        FileEncoding enc{FileEncoding::Unknown};
        std::string content{};
        std::uintmax_t size{};

        TRY(checkStatus(path));
        TRY(determineSize(path, size));
        TRY(readFile(path, content, size));
        auto line_starts = LineUtils::computeLineStarts(content);
        TRY(checkEncoding(enc, content, size));

        return FileLoadResult::success(enc, content, line_starts, size);
    }


    std::optional<FileLoadResult> FileHandler::checkStatus(const fs::path& path) const {
        std::error_code ec;
        fs::file_status st = std::filesystem::status(path, ec);

        if (ec) {
            if (ec == std::make_error_code(std::errc::permission_denied))
                return FileLoadResult::failure(FileError::PermissionDenied);

            return FileLoadResult::failure(FileError::Unknown);
        }

        if (!fs::exists(st)) {
            return FileLoadResult::failure(FileError::NotFound);
        }

        if (!fs::is_regular_file(st)) {
            return FileLoadResult::failure(FileError::NotAFile);
        }

        return std::nullopt;
    }

    std::optional<FileLoadResult> FileHandler::determineSize(const fs::path& path, std::uintmax_t& out_size) const {
        std::error_code ec;
        out_size = fs::file_size(path, ec);

        if (ec)
            return FileLoadResult::failure(FileError::SizeFailed);

        if (out_size == 0)
            return FileLoadResult::failure(FileError::EmptyFile);

        return std::nullopt;
    }

    std::optional<FileLoadResult> FileHandler::readFile(const fs::path& path, std::string& out_content, std::uintmax_t size) const {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
            return FileLoadResult::failure(FileError::OpenFailed);

        out_content.resize(size);
        file.read(out_content.data(), static_cast<std::streamsize>(size));
        if (static_cast<std::uintmax_t>(file.gcount()) != size) {
            return FileLoadResult::failure(FileError::ReadFailed);
        }

        return std::nullopt;
    }

    std::optional<FileLoadResult> FileHandler::checkEncoding(FileEncoding& out_enc, std::string& content, std::uintmax_t& out_size) const {
        out_enc = BomUtils::detectEncoding(content);

        if (isBadEnc(out_enc)) {
            return FileLoadResult::failure(FileError::InvalidEncoding);
        }

        if (out_enc == FileEncoding::UTF8_BOM) {
            BomUtils::removeUTF8BOM(content);
            out_size -= 3;
        }

        return std::nullopt;
    }
}
