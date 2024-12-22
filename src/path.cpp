//
// Created by sphdx on 23.12.2024.
//

#include "include/path.h"

std::string getSomeFilePath(const std::string &relativePath) {
    const std::filesystem::path currentPath = std::filesystem::current_path();
    const std::filesystem::path configFilePath = currentPath / "../" / relativePath;

    return configFilePath.string();
}
