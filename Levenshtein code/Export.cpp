#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Function to export a table of vectors of strings to a CSV file
void exportToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    // Get the current working directory
    fs::path current_path = fs::current_path();

    // Move two levels up to the project root directory
    fs::path project_root = current_path.parent_path().parent_path();

    // Combine with Tables directory
    std::string path = (project_root / "Tables" / filename).string() + ".csv";

    // Create "Tables" directory if it does not exist
    if (!fs::exists(project_root / "Tables")) {
        fs::create_directory(project_root / "Tables");
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    // Write data to the CSV file
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& row = data[i];

        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j != row.size() - 1) {
                file << ",";
            }
        }

        file << std::endl;
    }

    file.close();
}

// Function to export a table of vectors of integers to a CSV file
void exportToCSV(const std::string& filename, const std::vector<std::vector<int>>& data) {
    // Get the current working directory
    fs::path current_path = fs::current_path();

    // Move two levels up to the project root directory
    fs::path project_root = current_path.parent_path().parent_path();

    // Combine with Tables directory
    std::string path = (project_root / "Tables" / filename).string() + ".csv";

    // Create "Tables" directory if it does not exist
    if (!fs::exists(project_root / "Tables")) {
        fs::create_directory(project_root / "Tables");
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    // Write data to the CSV file
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& row = data[i];

        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j != row.size() - 1) {
                file << ",";
            }
        }

        file << std::endl;
    }

    file.close();
}

void exportToCSV(const std::string& filename, const std::vector<std::vector<double>>& data, int precision = 6) {
    // Get the current working directory
    fs::path current_path = fs::current_path();

    // Move two levels up to the project root directory
    fs::path project_root = current_path.parent_path().parent_path();

    // Combine with Tables directory and create file path
    std::string path = (project_root / "Tables" / filename).string() + ".csv";

    // Create "Tables" directory if it does not exist
    if (!fs::exists(project_root / "Tables")) {
        fs::create_directory(project_root / "Tables");
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return;
    }

    // Set precision for double values
    file << std::fixed << std::setprecision(precision);

    // Write data to the CSV file
    for (size_t i = 0; i < data.size(); ++i) {
        const auto& row = data[i];

        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j != row.size() - 1) {
                file << ",";
            }
        }

        file << std::endl;
    }

    file.close();
}
