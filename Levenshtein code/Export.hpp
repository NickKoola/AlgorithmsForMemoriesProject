#ifndef EXPORT_HPP
#define EXPORT_HPP

#include <string>
#include <vector>

// Function to export a table of vectors of strings to a CSV file
void exportToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data);

// Function to export a table of vectors of integers to a CSV file
void exportToCSV(const std::string& filename, const std::vector<std::vector<int>>& data);

// Function to export a table of vectors of doubles to a CSV file
void exportToCSV(const std::string& filename, const std::vector<std::vector<double>>& data, int precision = 6);

#endif // EXPORT_HPP
