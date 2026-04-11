/**
 * @file DataIO.cpp
 * @brief Реализация функций ввода/вывода данных и генерации.
 */

#include "DataIO.hpp"
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Создаёт папку (и все промежуточные), если её нет.
 * @param path Путь к папке.
 */
static void ensureDirectoryExists(const std::string& path) {
    fs::create_directories(fs::path(path));
}

/**
 * @brief Генерирует вектор случайных абитуриентов заданного размера.
 * @param size Количество элементов.
 * @return Вектор со случайными данными.
 */
static std::vector<Applicant> generateRandomApplicants(size_t size) {
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<unsigned>(seed));
    std::uniform_int_distribution<int> scoreDist(0, 300);
    std::uniform_int_distribution<int> nameIdxDist(0, 9);
    std::uniform_int_distribution<int> facultyIdxDist(0, 4);
    std::uniform_int_distribution<int> specIdxDist(0, 9);

    std::vector<std::string> firstNames = {"Ivan", "Petr", "Sergey", "Alexey", "Dmitry", "Andrey", "Mikhail", "Nikolay", "Vladimir", "Alexander"};
    std::vector<std::string> lastNames = {"Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov", "Popov", "Vasilyev", "Sokolov", "Mikhailov", "Novikov"};
    std::vector<std::string> faculties = {"FIT", "FEU", "FMF", "LF", "IF"};
    std::vector<std::string> specialties = {"Software Engineering", "Informatics", "Economics", "Management", "Mathematics", "Physics", "Law", "History", "Biology", "Chemistry"};

    std::vector<Applicant> result;
    result.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        int idxFirst = nameIdxDist(gen);
        int idxLast  = nameIdxDist(gen);
        std::string name = lastNames[idxLast] + " " + firstNames[idxFirst];
        std::string faculty = faculties[facultyIdxDist(gen)];
        std::string specialty = specialties[specIdxDist(gen)];
        int score = scoreDist(gen);
        result.emplace_back(name, faculty, specialty, score);
    }
    return result;
}

/**
 * @brief Сохраняет вектор в CSV-файл.
 * @param filename Полный путь к файлу.
 * @param data Вектор объектов.
 */
static void saveToFile(const std::string& filename, const std::vector<Applicant>& data) {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for writing: " + filename);
    for (const auto& a : data)
        file << a << "\n";
}

/**
 * @brief Загружает вектор из CSV-файла.
 * @param filename Полный путь к файлу.
 * @return Вектор объектов.
 */
static std::vector<Applicant> loadFromFile(const std::string& filename) {
    std::vector<Applicant> result;
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for reading: " + filename);
    Applicant a;
    while (file >> a)
        result.push_back(a);
    return result;
}

void generateAndSaveData(size_t size, const std::string& filename) {
    ensureDirectoryExists("raw");
    std::string fullPath = "raw/" + filename;
    std::vector<Applicant> data = generateRandomApplicants(size);
    saveToFile(fullPath, data);
}

std::vector<Applicant> loadData(const std::string& filename) {
    std::string fullPath = "raw/" + filename;
    return loadFromFile(fullPath);
}

void saveAllSortedToFile(const std::string& filename,
                         const std::vector<Applicant>& sorted_selection,
                         const std::vector<Applicant>& sorted_heap,
                         const std::vector<Applicant>& sorted_merge,
                         const std::vector<Applicant>& sorted_std) {
    ensureDirectoryExists("sorted");
    std::string fullPath = "sorted/" + filename;
    std::ofstream file(fullPath);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for writing: " + fullPath);

    auto writeArray = [&file](const std::string& label, const std::vector<Applicant>& data) {
        file << "# " << label << "\n";
        for (const auto& a : data)
            file << a << "\n";
        file << "\n";
    };

    writeArray("Selection sort", sorted_selection);
    writeArray("Heap sort", sorted_heap);
    writeArray("Merge sort", sorted_merge);
    writeArray("std::sort", sorted_std);
}