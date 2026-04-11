/**
 * @file SortingAlgorithms.cpp
 * @brief Реализация алгоритмов сортировки.
 */

#include "SortingAlgorithms.hpp"
#include <algorithm>

void selectionSort(std::vector<Applicant>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            std::swap(arr[i], arr[min_idx]);
    }
}

/**
 * @brief Восстановление свойства max-кучи для элемента с индексом i.
 * @param arr Вектор.
 * @param n Размер кучи.
 * @param i Индекс корня поддерева.
 */
static void heapify(std::vector<Applicant>& arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<Applicant>& arr) {
    size_t n = arr.size();
    if (n == 0) return;
    for (int i = n/2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 * @brief Слияние двух отсортированных подмассивов.
 * @param arr Вектор.
 * @param left Левая граница первого подмассива.
 * @param mid Правая граница первого подмассива (середина).
 * @param right Правая граница второго подмассива.
 */
static void merge(std::vector<Applicant>& arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    std::vector<Applicant> L(n1), R(n2);

    for (size_t i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (size_t j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

/**
 * @brief Рекурсивная реализация сортировки слиянием.
 * @param arr Вектор.
 * @param left Левая граница сортируемого диапазона (включительно).
 * @param right Правая граница сортируемого диапазона (включительно).
 */
static void mergeSortRecursive(std::vector<Applicant>& arr, size_t left, size_t right) {
    if (left >= right) return;
    size_t mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(std::vector<Applicant>& arr) {
    if (!arr.empty())
        mergeSortRecursive(arr, 0, arr.size() - 1);
}