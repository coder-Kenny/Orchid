#pragma once

namespace file_manager {
    enum class FileError {
        None = 0,

        //Path / existence issues
        NotFound,
        NotAFile,

        // Permission issues
        PermissionDenied,

        // Opening / Reading issues
        OpenFailed,
        EmptyFile,
        SizeFailed,
        ReadFailed,

        Unknown
    };
}