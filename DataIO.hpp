/**
 * @file DataIO.hpp
 * @brief Заголовочный файл для ввода/вывода данных и генерации.
 */

#pragma once
#include <vector>
#include <string>
#include "Applicant.hpp"

/**
 * @brief Генерирует случайные данные указанного размера и сохраняет их в файл (в папку raw/).
 * @param size Количество элементов.
 * @param filename Базовое имя файла (без пути).
 */
void generateAndSaveData(size_t size, const std::string& filename);

/**
 * @brief Загружает данные из файла (из папки raw/).
 * @param filename Базовое имя файла (без пути).
 * @return Вектор загруженных объектов.
 */
std::vector<Applicant> loadData(const std::string& filename);

/**
 * @brief Сохраняет четыре отсортированных массива в один файл (в папку sorted/) с подписями.
 * @param filename Базовое имя файла (без пути).
 * @param sorted_selection Отсортированный массив методом selection.
 * @param sorted_heap Отсортированный массив методом heap.
 * @param sorted_merge Отсортированный массив методом merge.
 * @param sorted_std Отсортированный массив методом std::sort.
 */
void saveAllSortedToFile(const std::string& filename,
                         const std::vector<Applicant>& sorted_selection,
                         const std::vector<Applicant>& sorted_heap,
                         const std::vector<Applicant>& sorted_merge,
                         const std::vector<Applicant>& sorted_std);