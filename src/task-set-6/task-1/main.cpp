#include <iostream>
#include <algorithm>

void heapify(int array[], int size, int root) {
    int largest {root};
    int left {2 * root + 1};
    int right {2 * root + 2};

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, size, largest);
    }
}

void build_heap(int array[], int size) {
    for (int i {size / 2 - 1}; i >= 0; --i) {
        heapify(array, size, i);
    }
}

void heap_sort(int array[], int size) {
    build_heap(array, size);

    for (int end {size - 1}; end > 0; --end) {
        std::swap(array[0], array[end]);
        heapify(array, end, 0);
    }
}

int main () {
    int array[] {4, 1, 7, 3, 8, 5};
    int size = sizeof(array) / sizeof(array[0]);

    std::cout << "Given array:\n";
    for (int i {0}; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    heap_sort(array, size);

    std::cout << "Sorted array:\n";
    for (int i {0}; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}
