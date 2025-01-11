#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdlib>

namespace fs = std::filesystem;

void listDirectory(const fs::path& path) {
    try {
        std::cout << "Contents of: " << path.string() << "\n";
        for (const auto& entry : fs::directory_iterator(path)) {
            std::cout << (entry.is_directory() ? "[DIR]  " : "[FILE] ") 
                      << entry.path().filename().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void viewFile(const fs::path& filePath) {
    try {
        if (fs::is_regular_file(filePath)) {
            std::ifstream file(filePath);
            if (file.is_open()) {
                std::cout << "\nContents of " << filePath.string() << ":\n";
                std::string line;
                while (std::getline(file, line)) {
                    std::cout << line << "\n";
                }
                file.close();
            } else {
                std::cerr << "Error: Unable to open file.\n";
            }
        } else {
            std::cerr << "Error: Specified path is not a file.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void createDirectory(const fs::path& dirPath) {
    try {
        if (fs::create_directory(dirPath)) {
            std::cout << "Directory created: " << dirPath.string() << "\n";
        } else {
            std::cerr << "Error: Directory could not be created.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void copyFile(const fs::path& srcPath, const fs::path& destPath) {
    try {
        fs::copy(srcPath, destPath, fs::copy_options::overwrite_existing);
        std::cout << "File copied to: " << destPath.string() << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& srcPath, const fs::path& destPath) {
    try {
        fs::rename(srcPath, destPath);
        std::cout << "File moved to: " << destPath.string() << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void displayMenu() {
    std::cout << "\nFile Manager Commands:\n";
    std::cout << "1. List Directory\n";
    std::cout << "2. View File\n";
    std::cout << "3. Create Directory\n";
    std::cout << "4. Copy File\n";
    std::cout << "5. Move File\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    fs::path currentPath = fs::current_path();
    int choice;

    while (true) {
        std::cout << "\nCurrent Directory: " << currentPath.string() << "\n";
        displayMenu();
        std::cin >> choice;

        if (choice == 1) {
            listDirectory(currentPath);
        } else if (choice == 2) {
            std::cout << "Enter file name to view: ";
            std::string fileName;
            std::cin >> fileName;
            viewFile(currentPath / fileName);
        } else if (choice == 3) {
            std::cout << "Enter name for new directory: ";
            std::string dirName;
            std::cin >> dirName;
            createDirectory(currentPath / dirName);
        } else if (choice == 4) {
            std::cout << "Enter source file name: ";
            std::string srcFile;
            std::cin >> srcFile;
            std::cout << "Enter destination path: ";
            std::string destPath;
            std::cin >> destPath;
            copyFile(currentPath / srcFile, fs::path(destPath));
        } else if (choice == 5) {
            std::cout << "Enter source file name: ";
            std::string srcFile;
            std::cin >> srcFile;
            std::cout << "Enter destination path: ";
            std::string destPath;
            std::cin >> destPath;
            moveFile(currentPath / srcFile, fs::path(destPath));
        } else if (choice == 6) {
            std::cout << "Exiting File Manager. Goodbye!\n";
            break;
        } else {
            std::cerr << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
