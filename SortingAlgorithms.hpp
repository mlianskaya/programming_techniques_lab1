/**
 * @file SortingAlgorithms.hpp
 * @brief Заголовочный файл с объявлениями алгоритмов сортировки.
 */

#pragma once
#include <vector>
#include "Applicant.hpp"

/**
 * @brief Сортировка выбором (selection sort).
 * @param arr Вектор объектов Applicant для сортировки.
 * @note Сложность O(n²), не требует дополнительной памяти, нестабильна.
 */
void selectionSort(std::vector<Applicant>& arr);

/**
 * @brief Пирамидальная сортировка (heap sort).
 * @param arr Вектор объектов Applicant для сортировки.
 * @note Сложность O(n log n), не требует дополнительной памяти, нестабильна.
 */
void heapSort(std::vector<Applicant>& arr);

/**
 * @brief Сортировка слиянием (merge sort).
 * @param arr Вектор объектов Applicant для сортировки.
 * @note Сложность O(n log n), требует O(n) дополнительной памяти, стабильна.
 */
void mergeSort(std::vector<Applicant>& arr);