//sacar los algoritmos de ordenamiento, de las clases queue y stack cuando ya lo haya hecho solo llamarlas

#include <iostream> // Biblioteca estándar de C++ para la entrada y salida (cout, cin)
#include <algorithm> // Biblioteca para usar funciones estándar como sort, max_element, min_element
#include <vector> // Biblioteca para utilizar el contenedor vector
#include <cmath> // Biblioteca para funciones matemáticas como sqrt
#ifdef _WIN32 // Directiva de preprocesador para verificar si se compila en un sistema Windows
#include <windows.h> // Incluye las funciones específicas de Windows
#else // Si no es Windows (es Linux o macOS)
#include <unistd.h> // Incluye funciones de Unix, como sleep()
#endif

using namespace std; // Evita la necesidad de escribir 'std::' antes de los objetos estándar como cout

// Estructura que define un nodo de una lista enlazada
struct Node {
    int data; // Almacena el dato entero del nodo
    Node* next; // Puntero al siguiente nodo de la lista enlazada
};

// Clase que define el comportamiento de una Pila (LIFO - Last In, First Out)
class Stack {
private:
    Node* top; // Puntero que apunta al nodo superior (último agregado) de la pila
    int size; // Variable que almacena el número de elementos en la pila

public:
    Stack() : top(nullptr), size(0) {} // Constructor de la clase Stack: inicializa la pila con top en nullptr y size en 0

    void push(int value) { // Función que agrega un valor a la pila (operación push)
        Node* newNode = new Node();  // Crea un nuevo nodo
        newNode->data = value; // Asigna el valor ingresado al nuevo nodo
        newNode->next = top; // El nuevo nodo ahora apunta al antiguo "top"
        top = newNode; // El puntero top se actualiza para apuntar al nuevo nodo
        size++; // Incrementa el tamaño de la pila
        cout << "Elemento " << value << " agregado a la pila.\n"; // Muestra mensaje de confirmación
    }

    void pop() { // Función que elimina el último elemento agregado de la pila (operación pop)
        if (top == nullptr) { // Verifica si la pila está vacía
            cout << "La pila está vacía.\n"; // Muestra mensaje de error si está vacía
            return; // Sale de la función
        }
        Node* temp = top; // Temporalmente guarda el nodo que será eliminado
        top = top->next; // Actualiza el puntero top al siguiente nodo en la pila
        cout << "Elemento " << temp->data << " eliminado de la pila.\n"; // Mensaje de confirmación
        delete temp;  // Libera la memoria del nodo eliminado
        size--; // Decrementa el tamaño de la pila
    }

    void display() { // Función que muestra los elementos en la pila
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

    void selectionSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        // Selection Sort
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (elements[j] < elements[minIndex]) {
                    minIndex = j;
                }
            }
            swap(elements[i], elements[minIndex]);
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Selection Sort.\n";
    }

    void insertionSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        // Insertion Sort
        for (int i = 1; i < size; i++) {
            int key = elements[i];
            int j = i - 1;
            while (j >= 0 && elements[j] > key) {
                elements[j + 1] = elements[j];
                j--;
            }
            elements[j + 1] = key;
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Insertion Sort.\n";
    }

    void mergeSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        mergeSort(elements, 0, size - 1);

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Merge Sort.\n";
    }

    void quickSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        quickSort(elements, 0, size - 1);

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Quick Sort.\n";
    }

    void shellSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila por lo tanto no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                int temp = elements[i];
                int j;
                for (j = i; j >= gap && elements[j - gap] > temp; j -= gap) {
                    elements[j] = elements[j - gap];
                }
                elements[j] = temp;
            }
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Shell Sort.\n";
    }

    void countingSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int maxVal = *max_element(elements, elements + size);
        int minVal = *min_element(elements, elements + size);

        int range = maxVal - minVal + 1;
        int* count = new int[range]{0};
        int* output = new int[size];

        for (int i = 0; i < size; i++) {
            count[elements[i] - minVal]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            output[count[elements[i] - minVal] - 1] = elements[i];
            count[elements[i] - minVal]--;
        }

        for (int i = 0; i < size; i++) {
            elements[i] = output[i];
        }

        reconstructStack(elements);
        delete[] elements;
        delete[] count;
        delete[] output;
        cout << "La pila ha sido ordenada usando Counting Sort.\n";
    }

    void radixSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int maxVal = *max_element(elements, elements + size);
        for (int exp = 1; maxVal / exp > 0; exp *= 10) {
            countingSortForRadix(elements, size, exp);
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Radix Sort.\n";
    }

    void bucketSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int bucketCount = 10;
        vector<int> buckets[bucketCount];

        int maxVal = *max_element(elements, elements + size);
        for (int i = 0; i < size; i++) {
            int bucketIndex = bucketCount * elements[i] / (maxVal + 1);
            buckets[bucketIndex].push_back(elements[i]);
        }

        for (int i = 0; i < bucketCount; i++) {
            sort(buckets[i].begin(), buckets[i].end());
        }

        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                elements[index++] = buckets[i][j];
            }
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Bucket Sort.\n";
    }

    void heapSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(elements, size, i);
        }

        for (int i = size - 1; i >= 0; i--) {
            swap(elements[0], elements[i]);
            heapify(elements, i, 0);
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando Heap Sort.\n";
    }

    void timSort() {
        if (size == 0) {
            cout << "No hay elementos en la pila, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = top;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        const int RUN = 32;
        for (int i = 0; i < size; i += RUN) {
            insertionSortTim(elements, i, min((i + 31), (size - 1)));
        }

        for (int runSize = RUN; runSize < size; runSize = 2 * runSize) {
            for (int left = 0; left < size; left += 2 * runSize) {
                int mid = left + runSize - 1;
                int right = min((left + 2 * runSize - 1), (size - 1));
                if (mid < right) {
                    merge(elements, left, mid, right);
                }
            }
        }

        reconstructStack(elements);
        delete[] elements;
        cout << "La pila ha sido ordenada usando TimSort.\n";
    }

private:
    void reconstructStack(int* elements) {
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }

        for (int i = size - 1; i >= 0; i--) {
            Node* newNode = new Node();
            newNode->data = elements[i];
            newNode->next = top;
            top = newNode;
        }
    }

    void mergeSort(int* arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
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
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void quickSort(int* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(int* arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void heapify(int* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void countingSortForRadix(int* arr, int n, int exp) {
        int* output = new int[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        delete[] output;
    }

    void insertionSortTim(int* arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

// Clase que define el comportamiento de una Cola (FIFO)
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
        size--;
        cout << "Elemento " << temp->data << " eliminado de la cola.\n";
        delete temp;
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
    }

    void bubbleSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        // Bubble Sort
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (elements[j] > elements[j + 1]) {
                    swap(elements[j], elements[j + 1]);
                }
            }
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Bubble Sort.\n";
    }

    void selectionSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        // Selection Sort
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < size; j++) {
                if (elements[j] < elements[minIndex]) {
                    minIndex = j;
                }
            }
            swap(elements[i], elements[minIndex]);
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Selection Sort.\n";
    }

    void insertionSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        // Insertion Sort
        for (int i = 1; i < size; i++) {
            int key = elements[i];
            int j = i - 1;
            while (j >= 0 && elements[j] > key) {
                elements[j + 1] = elements[j];
                j--;
            }
            elements[j + 1] = key;
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Insertion Sort.\n";
    }

    void mergeSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        mergeSort(elements, 0, size - 1);

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Merge Sort.\n";
    }

    void quickSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        quickSort(elements, 0, size - 1);

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Quick Sort.\n";
    }

    void shellSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                int temp = elements[i];
                int j;
                for (j = i; j >= gap && elements[j - gap] > temp; j -= gap) {
                    elements[j] = elements[j - gap];
                }
                elements[j] = temp;
            }
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Shell Sort.\n";
    }

    // Counting Sort
    void countingSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int maxVal = *max_element(elements, elements + size);
        int minVal = *min_element(elements, elements + size);
        int range = maxVal - minVal + 1;

        int* count = new int[range]{0};
        int* output = new int[size];

        for (int i = 0; i < size; i++) {
            count[elements[i] - minVal]++;
        }

        for (int i = 1; i < range; i++) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; i--) {
            output[count[elements[i] - minVal] - 1] = elements[i];
            count[elements[i] - minVal]--;
        }

        for (int i = 0; i < size; i++) {
            elements[i] = output[i];
        }

        reconstructQueue(elements);
        delete[] elements;
        delete[] count;
        delete[] output;
        cout << "La cola ha sido ordenada usando Counting Sort.\n";
    }

    // Radix Sort
    void radixSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int maxVal = *max_element(elements, elements + size);
        for (int exp = 1; maxVal / exp > 0; exp *= 10) {
            countingSortForRadix(elements, size, exp);
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Radix Sort.\n";
    }

    // Bucket Sort
    void bucketSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        int bucketCount = 10;
        vector<int> buckets[bucketCount];

        int maxVal = *max_element(elements, elements + size);
        for (int i = 0; i < size; i++) {
            int bucketIndex = bucketCount * elements[i] / (maxVal + 1);
            buckets[bucketIndex].push_back(elements[i]);
        }

        for (int i = 0; i < bucketCount; i++) {
            sort(buckets[i].begin(), buckets[i].end());
        }

        int index = 0;
        for (int i = 0; i < bucketCount; i++) {
            for (int j = 0; j < buckets[i].size(); j++) {
                elements[index++] = buckets[i][j];
            }
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Bucket Sort.\n";
    }

    // Heap Sort
    void heapSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(elements, size, i);
        }

        for (int i = size - 1; i >= 0; i--) {
            swap(elements[0], elements[i]);
            heapify(elements, i, 0);
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando Heap Sort.\n";
    }

    // TimSort
    void timSortQueue() {
        if (size == 0) {
            cout << "No hay elementos en la cola, no se puede ordenar\n";
            return;
        }

        int* elements = new int[size];
        Node* temp = front;
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data;
            temp = temp->next;
        }

        const int RUN = 32;
        for (int i = 0; i < size; i += RUN) {
            insertionSortTim(elements, i, min((i + 31), (size - 1)));
        }

        for (int runSize = RUN; runSize < size; runSize = 2 * runSize) {
            for (int left = 0; left < size; left += 2 * runSize) {
                int mid = left + runSize - 1;
                int right = min((left + 2 * runSize - 1), (size - 1));
                if (mid < right) {
                    merge(elements, left, mid, right);
                }
            }
        }

        reconstructQueue(elements);
        delete[] elements;
        cout << "La cola ha sido ordenada usando TimSort.\n";
    }

private:
    void reconstructQueue(int* elements) {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;

        for (int i = 0; i < size; i++) {
            Node* newNode = new Node();
            newNode->data = elements[i];
            newNode->next = nullptr;

            if (rear == nullptr) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }
    }

    void mergeSort(int* arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
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
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void quickSort(int* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    int partition(int* arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void countingSortForRadix(int* arr, int n, int exp) {
        int* output = new int[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        delete[] output;
    }

    void heapify(int* arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void insertionSortTim(int* arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

//Función para limpiar pantalla
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};

// Función para mostrar el menú principal al usuario
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
            case 1:  // Menú de Pila
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
                        case 4:
                            cout << "\n--- Algoritmos de ordenamiento de la Pila ---\n";
                            cout << "1. Bubble Sort\n";
                            cout << "2. Selection Sort\n";
                            cout << "3. Insertion Sort\n";
                            cout << "4. Merge Sort\n";
                            cout << "5. Quick Sort\n";
                            cout << "6. Shell Sort\n";
                            cout << "7. Counting Sort\n";
                            cout << "8. Radix Sort\n";
                            cout << "9. Bucket Sort\n";
                            cout << "10. Heap Sort\n";
                            cout << "11. Tim Sort\n";
                            cout << "Elige una opción: ";
                            cin >> subChoice;

                            switch (subChoice) {
                                case 1: stack.bubbleSort(); break;
                                case 2: stack.selectionSort(); break;
                                case 3: stack.insertionSort(); break;
                                case 4: stack.mergeSort(); break;
                                case 5: stack.quickSort(); break;
                                case 6: stack.shellSort(); break;
                                case 7: stack.countingSort(); break;
                                case 8: stack.radixSort(); break;
                                case 9: stack.bucketSort(); break;
                                case 10: stack.heapSort(); break;
                                case 11: stack.timSort(); break;
                                default: cout << "Opción no válida.\n"; break;
                            }
                            break;
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

            case 2:  // Menú de Cola
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
                        case 4:
                            cout << "\n--- Algoritmos de ordenamiento de la Cola ---\n";
                            cout << "1. Bubble Sort\n";
                            cout << "2. Selection Sort\n";
                            cout << "3. Insertion Sort\n";
                            cout << "4. Merge Sort\n";
                            cout << "5. Quick Sort\n";
                            cout << "6. Shell Sort\n";
                            cout << "7. Counting Sort\n";
                            cout << "8. Radix Sort\n";
                            cout << "9. Bucket Sort\n";
                            cout << "10. Heap Sort\n";
                            cout << "11. Tim Sort\n";
                            cout << "Elige una opción: ";
                            cin >> subChoice;

                            switch (subChoice) {
                                case 1: queue.bubbleSortQueue(); break;
                                case 2: queue.selectionSortQueue(); break;
                                case 3: queue.insertionSortQueue(); break;
                                case 4: queue.mergeSortQueue(); break;
                                case 5: queue.quickSortQueue(); break;
                                case 6: queue.shellSortQueue(); break;
                                case 7: queue.countingSortQueue(); break;
                                case 8: queue.radixSortQueue(); break;
                                case 9: queue.bucketSortQueue(); break;
                                case 10: queue.heapSortQueue(); break;
                                case 11: queue.timSortQueue(); break;
                                default: cout << "Opción no válida.\n"; break;
                            }
                            break;
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
