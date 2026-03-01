#pragma once

namespace file_manager {
    enum class FileError {
        None = 0,
        NotFound,
        NotAFile,
        PermissionDenied,
        OpenFailed,
        EmptyFile,
        SizeFailed,
        ReadFailed,
        Unknown
    };
}