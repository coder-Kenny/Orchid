#pragma once

namespace file_manager {
    enum class FileKind {
        Resource = 0,
        Asset,
        Unknown,
    };

    inline std::string to_string(FileKind kind) {
        switch (kind) {
            case FileKind::Unknown: return "Unknown";
            case FileKind::Resource: return "Resource";
            case FileKind::Asset: return "Asset";
        }

        return "(unhandled FileKind value)";
    }
}
