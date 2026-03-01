#include <utility>

#include "file_data.hpp"

namespace file_manager {
    namespace fs = std::filesystem;

    FileData::FileData(std::filesystem::path path,
                       std::string content,
                       std::uintmax_t size,
                       FileError error,
                       FileKind kind) :
        path_{std::move(path)}, content_{std::move(content)}, size_{size}, error_{error}, kind_{kind} {}
}
