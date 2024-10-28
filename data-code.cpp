#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Estructura de nodo de la lista enlazada
struct Node {
    int data;
    Node* next;
};

// Clase Pila (Stack)
class Stack {
private:
    Node* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        size++;
        cout << "Elemento " << value << " agregado a la pila.\n";
    }

    void pop() {
        if (top == nullptr) {
            cout << "La pila está vacía.\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << "Elemento " << temp->data << " eliminado de la pila.\n";
        delete temp;
        size--;
    }

    int* toArray() {
        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }
        return elements;
    }

    void fromArray(int* elements) {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        for (int i = size - 1; i >= 0; i--) {
            push(elements[i]);
        }
    }

    void display() {
        if (top == nullptr) {
            cout << "La pila está vacía.\n";
            return;
        }
        Node* temp = top;
        cout << "Elementos en la pila: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    
    int getSize() const {
        return size;
    }
};

// Clase Cola (Queue)
class Queue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        cout << "Elemento " << value << " agregado a la cola.\n";
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "La cola está vacía.\n";
            return;
        }
        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        cout << "Elemento " << temp->data << " eliminado de la cola.\n";
        delete temp;
        size--;
    }

    int* toArray() {
        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }
        return elements;
    }

    void fromArray(int* elements) {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        for (int i = 0; i < size; i++) {
            enqueue(elements[i]);
        }
    }

    void display() {
        if (front == nullptr) {
            cout << "La cola está vacía.\n";
            return;
        }
        Node* temp = front;
        cout << "Elementos en la cola: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int getSize() const {
        return size;
    }
};

// Algoritmos de ordenamiento independientes
void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int* arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void shellSort(int* arr, int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void countingSort(int* arr, int size) {
    int maxVal = *max_element(arr, arr + size);
    int minVal = *min_element(arr, arr + size);
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0), output(size);
    for (int i = 0; i < size; i++) count[arr[i] - minVal]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = size - 1; i >= 0; i--) output[--count[arr[i] - minVal]] = arr[i];
    for (int i = 0; i < size; i++) arr[i] = output[i];
}

void radixSort(int* arr, int size) {
    int maxVal = *max_element(arr, arr + size);
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, size); // Llamar a countingSortForRadix modificado para radix
    }
}

void bucketSort(int* arr, int size) {
    int maxVal = *max_element(arr, arr + size);
    vector<int> buckets[10];

    for (int i = 0; i < size; i++) {
        int bucketIndex = 10 * arr[i] / (maxVal + 1);
        buckets[bucketIndex].push_back(arr[i]);
    }
    int index = 0;
    for (int i = 0; i < 10; i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void heapify(int* arr, int size, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < size && arr[left] > arr[largest]) largest = left;
    if (right < size && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) heapify(arr, size, i);
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void timSort(int* arr, int size) {
    const int RUN = 32;
    for (int i = 0; i < size; i += RUN)
        insertionSort(arr, min(i + 31, size - 1));
    for (int runSize = RUN; runSize < size; runSize *= 2) {
        for (int left = 0; left < size; left += 2 * runSize) {
            int mid = min(left + runSize - 1, size - 1);
            int right = min(left + 2 * runSize - 1, size - 1);
            if (mid < right) merge(arr, left, mid, right);
        }
    }
}

// Función para limpiar pantalla
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Menú principal
void menu() {
    Stack stack;
    Queue queue;
    int choice, subChoice, value;

    do {
        clearScreen();
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Usar Pila (LIFO)\n";
        cout << "2. Usar Cola (FIFO)\n";
        cout << "3. Salir\n";
        cout << "Elige una opción: ";
        cin >> choice;

        switch (choice) {
            case 1: // Menú de Pila
                do {
                    clearScreen();
                    cout << "\n--- Menú de Pila ---\n";
                    cout << "1. Insertar elemento en la pila (push)\n";
                    cout << "2. Eliminar elemento de la pila (pop)\n";
                    cout << "3. Mostrar elementos de la pila (display)\n";
                    cout << "4. Ordenar elementos de la pila\n";
                    cout << "5. Regresar al menú principal\n";
                    cout << "Elige una opción: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Introduce el valor a insertar: ";
                            cin >> value;
                            stack.push(value);
                            break;
                        case 2:
                            stack.pop();
                            break;
                        case 3:
                            stack.display();
                            break;
                        case 4: {
                            cout << "\n--- Algoritmos de ordenamiento ---\n";
                            cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n6. Shell Sort\n7. Counting Sort\n8. Radix Sort\n9. Bucket Sort\n10. Heap Sort\n11. Tim Sort\n";
                            cout << "Elige una opción: ";
                            cin >> subChoice;

                            int* elements = stack.toArray();
                            int size = stack.getSize();
                            switch (subChoice) {
                                case 1: bubbleSort(elements, size); break;
                                case 2: selectionSort(elements, size); break;
                                case 3: insertionSort(elements, size); break;
                                case 4: mergeSort(elements, 0, size - 1); break;
                                case 5: quickSort(elements, 0, size - 1); break;
                                case 6: shellSort(elements, size); break;
                                case 7: countingSort(elements, size); break;
                                case 8: radixSort(elements, size); break;
                                case 9: bucketSort(elements, size); break;
                                case 10: heapSort(elements, size); break;
                                case 11: timSort(elements, size); break;
                                default: cout << "Opción no válida.\n"; break;
                            }
                            stack.fromArray(elements);
                            delete[] elements;
                            break;
                        }
                        case 5:
                            break;
                        default:
                            cout << "Opción no válida.\n";
                    }
                    if (subChoice != 5) {
                        cout << "Presiona Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                } while (subChoice != 5);
                break;

            case 2: // Menú de Cola
                do {
                    clearScreen();
                    cout << "\n--- Menú de Cola ---\n";
                    cout << "1. Insertar elemento en la cola (enqueue)\n";
                    cout << "2. Eliminar elemento de la cola (dequeue)\n";
                    cout << "3. Mostrar elementos de la cola (display)\n";
                    cout << "4. Ordenar elementos de la cola\n";
                    cout << "5. Regresar al menú principal\n";
                    cout << "Elige una opción: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Introduce el valor a insertar: ";
                            cin >> value;
                            queue.enqueue(value);
                            break;
                        case 2:
                            queue.dequeue();
                            break;
                        case 3:
                            queue.display();
                            break;
                        case 4: {
                            cout << "\n--- Algoritmos de ordenamiento ---\n";
                            cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n6. Shell Sort\n7. Counting Sort\n8. Radix Sort\n9. Bucket Sort\n10. Heap Sort\n11. Tim Sort\n";
                            cout << "Elige una opción: ";
                            cin >> subChoice;

                            int* elements = queue.toArray();
                            int size = queue.getSize();
                            switch (subChoice) {
                                case 1: bubbleSort(elements, size); break;
                                case 2: selectionSort(elements, size); break;
                                case 3: insertionSort(elements, size); break;
                                case 4: mergeSort(elements, 0, size - 1); break;
                                case 5: quickSort(elements, 0, size - 1); break;
                                case 6: shellSort(elements, size); break;
                                case 7: countingSort(elements, size); break;
                                case 8: radixSort(elements, size); break;
                                case 9: bucketSort(elements, size); break;
                                case 10: heapSort(elements, size); break;
                                case 11: timSort(elements, size); break;
                                default: cout << "Opción no válida.\n"; break;
                            }
                            queue.fromArray(elements);
                            delete[] elements;
                            break;
                        }
                        case 5:
                            break;
                        default:
                            cout << "Opción no válida.\n";
                    }
                    if (subChoice != 5) {
                        cout << "Presiona Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                } while (subChoice != 5);
                break;

            case 3:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida.\n";
        }
    } while (choice != 3);
}

int main() {
    menu();
    return 0;
}
