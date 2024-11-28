#include <iostream> //Incluye la biblioteca estandar para operaciones de entrada y salida
#include <algorithm> //Incluye la biblioteca para algoritmos como 'max_element' y 'min_element'
#include <vector> //incluye el contenedor vector para usar algoritmos de ordenamiento como bicketSort
#include <cmath> //incluye la biblioteca matematica, utilizada en algunas funciones
#ifdef _WIN32 //verfica si el sistema operativo es windows
#include <windows.h> //incluye las funciones especificas de windows (como system cls, para limpiar pantalla)
#else //si no es windows entonces es linux macos
#include <unistd.h> //incluye funciones de unix, como system clear para limpiar pantalla
#endif

using namespace std; //para evitar escribir std::

// Nodo para los árboles
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    int height; // Usado para AVL
    bool color; // Usado para Rojos y Negros
    TreeNode(int val) : data(val), left(nullptr), right(nullptr), height(1), color(true) {}
};

// Clase para Árbol Binario de Búsqueda (ABB)
class BinarySearchTree {
public:
    TreeNode* root;
    BinarySearchTree() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* remove(TreeNode* node, int value) {
        if (!node) return node;
        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(TreeNode* node) {
        if (node) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(TreeNode* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    TreeNode* search(TreeNode* node, int value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }
};

// Clase para Árbol AVL
class AVLTree {
public:
    TreeNode* root;
    AVLTree() : root(nullptr) {}

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    TreeNode* insert(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && value < node->left->data) return rotateRight(node);
        if (balance < -1 && value > node->right->data) return rotateLeft(node);
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    TreeNode* remove(TreeNode* node, int value) {
        if (!node) return node;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    TreeNode* search(TreeNode* node, int value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }
};


// Clase para Árbol Rojo-Negro
class RedBlackTree {
private:
    struct RBNode {
        int data;
        RBNode* left;
        RBNode* right;
        RBNode* parent;
        bool color; // true = rojo, false = negro

        RBNode(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
    };

    RBNode* root;

    void rotateLeft(RBNode*& root, RBNode*& node) {
        RBNode* nodeRight = node->right;
        node->right = nodeRight->left;

        if (nodeRight->left != nullptr)
            nodeRight->left->parent = node;

        nodeRight->parent = node->parent;

        if (node->parent == nullptr)
            root = nodeRight;
        else if (node == node->parent->left)
            node->parent->left = nodeRight;
        else
            node->parent->right = nodeRight;

        nodeRight->left = node;
        node->parent = nodeRight;
    }

    void rotateRight(RBNode*& root, RBNode*& node) {
        RBNode* nodeLeft = node->left;
        node->left = nodeLeft->right;

        if (nodeLeft->right != nullptr)
            nodeLeft->right->parent = node;

        nodeLeft->parent = node->parent;

        if (node->parent == nullptr)
            root = nodeLeft;
        else if (node == node->parent->left)
            node->parent->left = nodeLeft;
        else
            node->parent->right = nodeLeft;

        nodeLeft->right = node;
        node->parent = nodeLeft;
    }

    void balanceInsert(RBNode*& root, RBNode*& node) {
        RBNode* parent = nullptr;
        RBNode* grandparent = nullptr;

        while (node != root && node->color && node->parent->color) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                RBNode* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color) { // Caso 1: El tío es rojo
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->right) { // Caso 2: El nodo es un hijo derecho
                        rotateLeft(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Caso 3: El nodo es un hijo izquierdo
                    rotateRight(root, grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                RBNode* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color) { // Caso 1: El tío es rojo
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->left) { // Caso 2: El nodo es un hijo izquierdo
                        rotateRight(root, parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Caso 3: El nodo es un hijo derecho
                    rotateLeft(root, grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = false; // La raíz siempre es negra
    }

    void inorder(RBNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    RBNode* search(RBNode* node, int value) {
        if (node == nullptr || node->data == value)
            return node;
        if (value < node->data)
            return search(node->left, value);
        return search(node->right, value);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int value) {
        RBNode* node = new RBNode(value);
        if (root == nullptr) {
            root = node;
            root->color = false; // La raíz es negra
            return;
        }

        RBNode* temp = root;
        RBNode* parent = nullptr;

        while (temp != nullptr) {
            parent = temp;
            if (value < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }

        node->parent = parent;

        if (value < parent->data)
            parent->left = node;
        else
            parent->right = node;

        balanceInsert(root, node);
    }

    void search(int value) {
        RBNode* result = search(root, value);
        if (result != nullptr)
            cout << "Elemento encontrado: " << result->data << endl;
        else
            cout << "Elemento no encontrado.\n";
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void remove(int value) {
        cout << "La eliminación para Árbol Rojo-Negro está pendiente de implementación.\n";
    }
};


// Estructura de nodo de la lista enlazada
struct Node {
    int data; //Dato entero que almacena el nodo
    Node* next; //puntero al siguiente nodo en la lista enlazada
};

// Clase que define el comportamiento de una Pila (LIFO)
class Stack {
private:
    Node* top; //puntero que aounta al ultimo nodo agregado en la pila
    int size; //almacena el numero de elementos en la pila

public:
    Stack() : top(nullptr), size(0) {} //constructor que inicializa la pila con tamaño 0 y sin elementos.

    void push(int value) { //funcion para agregar un elemento a la pila
        Node* newNode = new Node(); //crea un nuevo nodo
        newNode->data = value; //asigna el valor al nodo
        newNode->next = top; //el nodo apunta al nodo actual en el top
        top = newNode; //actualiza el top para apuntar al nuevo nodo
        size++; //incrementa el tamaño de la pila
        cout << "Elemento " << value << " agregado a la pila.\n"; //mensaje de confirmacion
    }

    void pop() { //funcion para eliminar el ultimo elemento de la pila
        if (top == nullptr) { //verifica si la pila esta vacia
            cout << "La pila está vacía.\n";
            return; //sale si no hay elementos para eliminar
        }
        Node* temp = top; //guarda el nodo actual del top
        top = top->next; //actualiza al top al siguiente nodo 
        cout << "Elemento " << temp->data << " eliminado de la pila.\n";
        delete temp; //libera la memoria del nodo eliminado
        size--; //decrementa el tamaño de la pila
    }

    int* toArray() { //convierte la pila a un arreglo
        int* elements = new int[size]; //reserva memoria para el arreglo
        Node* temp = top; //puntero auxiliar para recorrer la pila
        for (int i = 0; i < size; i++) { 
            elements[i] = temp->data; //copia el dato de cada nodo al arreglo
            temp = temp->next; //avanza al siguiente nodo
        }
        return elements; //retorna el arreglo
    }

    void fromArray(int* elements) { //convierte un arreglo en una pila
        while (top != nullptr) { //limpia la pila actual
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        for (int i = size - 1; i >= 0; i--) { // Agrega cada elemento al top
            push(elements[i]);
        }
    }

    void display() { // Muestra los elementos en la pila
        if (top == nullptr) {
            cout << "La pila está vacía.\n";
            return;
        }
        Node* temp = top; // Puntero auxiliar para recorrer la pila
        cout << "Elementos en la pila: ";
        while (temp != nullptr) {
            cout << temp->data << " "; // Imprime el valor de cada nodo
            temp = temp->next; // Avanza al siguiente nodo
        }
        cout << endl;
    }
    
    int getSize() const { // Retorna el tamaño actual de la pila
        return size;
    }
};

// Clase que define el comportamiento de una cola (FIFO)
class Queue {
private:
    Node* front; // Puntero al primer nodo de la cola
    Node* rear; // Puntero al último nodo de la cola
    int size; // Almacena el número de elementos en la cola

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {} // Constructor que inicializa la cola vacía

    void enqueue(int value) {  // Agrega un elemento al final de la cola
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) { // Si la cola está vacía, ambos punteros apuntan al nuevo nodo
            front = rear = newNode;
        } else {  // Si no está vacía, añade al final
            rear->next = newNode;
            rear = newNode;
        }
        size++;   // Incrementa el tamaño de la cola
        cout << "Elemento " << value << " agregado a la cola.\n";
    }

    void dequeue() { // Elimina el primer elemento de la cola
        if (front == nullptr) { // Verifica si la cola está vacía
            cout << "La cola está vacía.\n";
            return;
        }
        Node* temp = front;  // Guarda el nodo del frente
        front = front->next;  // Actualiza el frente al siguiente nodo

        if (front == nullptr) { // Si la cola queda vacía, rear también se actualiza
            rear = nullptr;
        }
        cout << "Elemento " << temp->data << " eliminado de la cola.\n";
        delete temp; // Libera la memoria del nodo eliminado
        size--; // Decrementa el tamaño de la cola
    }

    int* toArray() { // Convierte la cola a un arreglo
        int* elements = new int[size]; // Reserva memoria para el arreglo
        Node* temp = front;  // Puntero auxiliar para recorrer la cola
        for (int i = 0; i < size; i++) {
            elements[i] = temp->data; // Copia el dato de cada nodo al arreglo
            temp = temp->next;
        }
        return elements; // Retorna el arreglo
    }

    void fromArray(int* elements) { // Convierte un arreglo en una cola
        while (front != nullptr) { // Limpia la cola actual
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr; // Reinicia rear a nullptr
        for (int i = 0; i < size; i++) {
            enqueue(elements[i]); // Inserta cada elemento en la cola
        }
    }

    void display() { // Muestra los elementos en la cola
        if (front == nullptr) {
            cout << "La cola está vacía.\n";
            return;
        }
        Node* temp = front; // Puntero auxiliar para recorrer la cola
        cout << "Elementos en la cola: ";
        while (temp != nullptr) {
            cout << temp->data << " "; // Imprime el valor de cada nodo
            temp = temp->next;
        }
        cout << endl;
    }

    int getSize() const { // Retorna el tamaño actual de la cola
        return size;
    }
};

// Algoritmos de ordenamiento independientes
void bubbleSort(int* arr, int size) {  // Ordenamiento Burbuja
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
    system("cls"); // Limpia la pantalla en Windows
#else
    system("clear");  // Limpia la pantalla en sistemas Unix
#endif
}

// Menú principal
void menu() {
    Stack stack; // Crea una instancia de Stack
    Queue queue; // Crea una instancia de Queue
    BinarySearchTree bst; // Crea una instancia de Árbol Binario de Búsqueda
    AVLTree avl; // Crea una instancia de Árbol AVL
    RedBlackTree rbt; // Crea una instancia de Árbol Rojo-Negro
    int choice, subChoice, value; // Variables para manejar opciones del menú y entrada de usuario

    do {
        cout << "\n--- Menú Principal ---\n";
        cout << "1. Usar Pila (LIFO)\n";
        cout << "2. Usar Cola (FIFO)\n";
        cout << "3. Usar Árbol Binario de Búsqueda (ABS)\n";
        cout << "4. Usar Árbol AVL\n";
        cout << "5. Usar Árbol Rojo-Negro\n";
        cout << "6. Salir\n";
        cout << "Elige una opción: ";
        cin >> choice;

        switch (choice) {  // Evalúa la elección del usuario
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

            case 3: // Menú de Árbol Binario de Búsqueda (ABB)
                do {
                    clearScreen();
                    cout << "\n--- Menú Árbol Binario de Búsqueda (ABS) ---\n";
                    cout << "1. Insertar elemento\n";
                    cout << "2. Buscar elemento\n";
                    cout << "3. Eliminar elemento\n";
                    cout << "4. Mostrar en recorrido inorden\n";
                    cout << "5. Regresar al menú principal\n";
                    cout << "Elige una opción: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Introduce el valor a insertar: ";
                            cin >> value;
                            bst.root = bst.insert(bst.root, value);
                            break;
                        case 2:
                            cout << "Introduce el valor a buscar: ";
                            cin >> value;
                            cout << (bst.search(bst.root, value) ? "Elemento encontrado.\n" : "Elemento no encontrado.\n");
                            break;
                        case 3:
                            cout << "Introduce el valor a eliminar: ";
                            cin >> value;
                            bst.root = bst.remove(bst.root, value);
                            break;
                        case 4:
                            cout << "Recorrido inorden: ";
                            bst.inorder(bst.root);
                            cout << endl;
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

            case 4: // Menú de Árbol AVL
                do {
                    clearScreen();
                    cout << "\n--- Menú Árbol AVL ---\n";
                    cout << "1. Insertar elemento\n";
                    cout << "2. Buscar elemento\n";
                    cout << "3. Mostrar en recorrido inorden\n";
                    cout << "4. Regresar al menú principal\n";
                    cout << "Elige una opción: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Introduce el valor a insertar: ";
                            cin >> value;
                            avl.root = avl.insert(avl.root, value);
                            break;
                        case 2:
                            cout << "Introduce el valor a buscar: ";
                            cin >> value;
                            cout << (avl.search(avl.root, value) ? "Elemento encontrado.\n" : "Elemento no encontrado.\n");
                            break;
                        case 3:
                            cout << "Recorrido inorden: ";
                            bst.inorder(avl.root);
                            cout << endl;
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Opción no válida.\n";
                    }
                    if (subChoice != 4) {
                        cout << "Presiona Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                } while (subChoice != 4);
                break;

            case 5: // Menú de Árbol Rojo-Negro
                do {
                    clearScreen();
                    cout << "\n--- Menú Árbol Rojo-Negro ---\n";
                    cout << "1. Insertar elemento\n";
                    cout << "2. Buscar elemento\n";
                    cout << "3. Eliminar elemento\n";
                    cout << "4. Regresar al menú principal\n";
                    cout << "Elige una opción: ";
                    cin >> subChoice;

                    switch (subChoice) {
                        case 1:
                            cout << "Introduce el valor a insertar: ";
                            cin >> value;
                            rbt.insert(value);
                            break;
                        case 2:
                            cout << "Introduce el valor a buscar: ";
                            cin >> value;
                            rbt.search(value);
                            break;
                        case 3:
                            cout << "Introduce el valor a eliminar: ";
                            cin >> value;
                            rbt.remove(value);
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Opción no válida.\n";
                    }
                    if (subChoice != 4) {
                        cout << "Presiona Enter para continuar...";
                        cin.ignore();
                        cin.get();
                    }
                } while (subChoice != 4);
                break;

            case 6:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opción no válida.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();  // Llama a la función principal del menú
    return 0; // Termina el programa
}