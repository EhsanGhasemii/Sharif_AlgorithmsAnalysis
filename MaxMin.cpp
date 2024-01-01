

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool CheckTree(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int level = log2(i + 1) + 1;
        if (level % 2 == 1) {
            if (arr[i] < arr[2 * i + 1] || (2 * i + 2 != n && arr[i] < arr[2 * i + 2]))
                return false;
        }
        else {
            if (arr[i] > arr[2 * i + 1] || (2 * i + 2 != n && arr[i] > arr[2 * i + 2]))
                return false;
        }
   }
    return true;
}

int Sum(std::vector<int>& arr, int type) {
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        int level = log2(i + 1) + 1;
        if ((level % 2 == 1 && type == 0) || (level % 2 == 0 && type == 1)) {
            sum += arr[i];
        }
    }
    return sum;
}






void MaxHeapify(vector<int>& heap, int i) {
    int size = heap.size();
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;

    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        MaxHeapify(heap, largest);
    }
}

void MinHeapify(vector<int>& heap, int i) {
    int size = heap.size();
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        MinHeapify(heap, smallest);
    }
}

int FindMin(vector<int>& heap, int i) {
    int size = heap.size();
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = FindMin(heap, left);

    if (right < size && heap[right] < heap[smallest])
        smallest = FindMin(heap, right);

    return smallest;
}

void DelMin(vector<int>& heap) {
    int size = heap.size();

    if (size == 0) {
        cout << "Heap is empty\n";
        return;
    }

    int minElementIndex = FindMin(heap, 0);
    cout << "The min element is " << heap[minElementIndex] << endl;

    swap(heap[minElementIndex], heap[size - 1]);
    heap.pop_back();

    if (minElementIndex % 2 == 0)
        MinHeapify(heap, minElementIndex);
    else
        MaxHeapify(heap, minElementIndex);
}














int main() {
    //std::vector<int> arr = {54, 30, 40, 49, 37, 45, 48, 41, 44, 35, 36, 42};
	

	// get input from user
	

	vector<int> arr;
    int n;
    cout << "Enter the number of elements in the heap: ";
    cin >> n;
    cout << "Enter the elements of the heap: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr.push_back(x);
    }



    if (CheckTree(arr)) {
        int sumMax = Sum(arr, 0);
        int sumMin = Sum(arr, 1);
        std::cout << "The sum of the roots of the max heap is " << sumMax << ".\n";
        std::cout << "The sum of the roots of the min heap is " << sumMin << ".\n";


		std::cout << "Before deletion:\n";
        for (int i : arr)
            std::cout << i << ' ';
        std::cout << '\n';

        DelMin(arr);

        std::cout << "After deletion:\n";
        for (int i : arr)
            std::cout << i << ' ';
        std::cout << '\n';
    }
    else {
        std::cout << "The sequence does not correspond to a MaxMin Heap tree.\n";
    }
    return 0;
}
