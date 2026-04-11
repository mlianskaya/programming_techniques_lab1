/**
 * @file main.cpp
 * @brief Основная программа: проведение экспериментов, замер времени, сохранение результатов.
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <algorithm>
#include "Applicant.hpp"
#include "SortingAlgorithms.hpp"
#include "DataIO.hpp"

/**
 * @brief Измеряет время выполнения переданной функции сортировки.
 * @tparam SortFunc Тип вызываемого объекта (функция или лямбда).
 * @param data Ссылка на вектор (будет изменён сортировкой).
 * @param sortFunc Функция сортировки (принимает vector<Applicant>&).
 * @return Время в секундах.
 */
template<typename SortFunc>
double measureTime(std::vector<Applicant>& data, SortFunc sortFunc) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

/**
 * @brief Проводит эксперименты для заданных размеров массивов.
 * @param sizes Вектор размеров (например, {100, 200, ...}).
 * @param resultsFilename Имя файла для сохранения результатов (CSV).
 */
void runExperiments(const std::vector<size_t>& sizes, const std::string& resultsFilename) {
    std::ofstream outFile(resultsFilename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to create results file: " << resultsFilename << std::endl;
        return;
    }
    outFile << "size,selection,heap,merge,std_sort\n";

    std::cout << "Running experiments...\n";
    for (size_t size : sizes) {
        std::cout << "Size: " << size << std::endl;
        std::cout.flush();

        std::string dataFilename = "data_" + std::to_string(size) + ".csv";
        generateAndSaveData(size, dataFilename);
        std::cout << "  Generated data to file: " << dataFilename << std::endl;
        std::cout.flush();

        std::vector<Applicant> original = loadData(dataFilename);

        std::vector<Applicant> sorted_sel = original;
        double selTime = measureTime(sorted_sel, selectionSort);

        std::vector<Applicant> sorted_heap = original;
        double heapTime = measureTime(sorted_heap, heapSort);

        std::vector<Applicant> sorted_merge = original;
        double mergeTime = measureTime(sorted_merge, mergeSort);

        std::vector<Applicant> sorted_std = original;
        double stdTime = measureTime(sorted_std, [](std::vector<Applicant>& vec) {
            std::sort(vec.begin(), vec.end());
        });

        std::string sortedFilename = "sorted_" + std::to_string(size) + ".csv";
        saveAllSortedToFile(sortedFilename, sorted_sel, sorted_heap, sorted_merge, sorted_std);
        std::cout << "  Sorted data saved to " << sortedFilename << std::endl;
        std::cout.flush();

        outFile << size << "," << selTime << "," << heapTime << "," << mergeTime << "," << stdTime << "\n";
        outFile.flush();
    }
    outFile.close();
    std::cout << "Timing results saved to file: " << resultsFilename << std::endl;
}

/**
 * @brief Точка входа в программу.
 * @return 0 при успешном выполнении, 1 при ошибке.
 */
int main() {
    try {
        std::vector<size_t> sizes = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000};
        runExperiments(sizes, "timing_results.csv");
        std::cout << "\nProgram finished.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}