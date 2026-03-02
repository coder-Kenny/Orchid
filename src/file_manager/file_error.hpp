#pragma once

#include <string>

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

    inline std::string to_string(FileError error) {
        switch (error) {
            case FileError::None: return "None";

            // Path / existence issues
            case FileError::NotFound: return "NotFound";
            case FileError::NotAFile: return "NotAFile";

            // Permission issues
            case FileError::PermissionDenied: return "PermissionDenied";

            // Opening / reading issues
            case FileError::OpenFailed: return "OpenFailed";
            case FileError::ReadFailed: return "ReadFailed";
            case FileError::SizeFailed: return "SizeFailed";
            case FileError::EmptyFile: return "EmptyFile";

            case FileError::Unknown: return "Unknown";
        }

        return "(unhandled FileError value)";
    }

}
