#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>  // Підключення бібліотеки для роботи з файлами
#include <cmath>    // Для функції pow
#include <string>   // Для роботи з типом string

using namespace std;

class CDoubleVector {
private:
    int size;       // Кількість елементів у векторі
    double* vector; // Вказівник на динамічний масив

public:
    // Конструктор за замовчуванням
    CDoubleVector() {
        size = 0;
        vector = nullptr;
    }

    // Конструктор з параметром для визначення розміру вектора
    CDoubleVector(int s) {
        Init(s);
    }

    // Метод ініціалізації вектора
    void Init(int s) {
        size = s;
        vector = new double[size];
        for (int i = 0; i < size; ++i) {
            vector[i] = 0.0; // Ініціалізація всіх елементів нулями
        }
    }

    // Деструктор для звільнення пам'яті
    ~CDoubleVector() {
        delete[] vector;
    }

    // Метод для встановлення значення елемента вектора
    void setElement(int index, double value) {
        if (index >= 0 && index < size) {
            vector[index] = value;
        }
        else {
            cout << "Index outside the vector" << endl;
        }
    }

    // Метод для отримання значення елемента вектора
    double getElement(int index) const {
        if (index >= 0 && index < size) {
            return vector[index];
        }
        else {
            cout << "Index outside the vector" << endl;
            return 0.0;
        }
    }

    // Метод для отримання розміру вектора
    int getSize() const {
        return size;
    }

    // Метод для знаходження мінімального значення
    double getMin() const {
        if (size == 0) return 0.0;
        double min = vector[0];
        for (int i = 1; i < size; ++i) {
            if (vector[i] < min) {
                min = vector[i];
            }
        }
        return min;
    }

    // Метод для знаходження максимального значення
    double getMax() const {
        if (size == 0) return 0.0;
        double max = vector[0];
        for (int i = 1; i < size; ++i) {
            if (vector[i] > max) {
                max = vector[i];
            }
        }
        return max;
    }

    // Метод для обчислення виразу
    double calculate(double x, double y, double z) const {
        double result = 0.0;
        // Перша сума: Σ (x^i * y^(10-i)), i від 1 до 10
        for (int i = 1; i <= 10; ++i) {
            result += pow(x, i) * pow(y, 10 - i);
        }
        // Друга сума: Σ ((x - y)^i * z^(10-i)), i від 2 до 5
        for (int i = 2; i <= 5; ++i) {
            result += pow(x - y, i) * pow(z, 10 - i);
        }
        return result;
    }

    // Метод для збереження вектора у бінарний файл
    void saveData(const string& filename) {
        ofstream outFile(filename, ios::binary);
        if (outFile.is_open()) {
            outFile.write(reinterpret_cast<char*>(&size), sizeof(size)); // Запис розміру
            outFile.write(reinterpret_cast<char*>(vector), size * sizeof(double)); // Запис вектора
            outFile.close();
            cout << "The data is saved to a file: " << filename << endl;
        }
        else {
            cout << "Error opening file for writing" << endl;
        }
    }

    // Метод для завантаження вектора з бінарного файлу
    void loadData(const string& filename) {
        ifstream inFile(filename, ios::binary);
        if (inFile.is_open()) {
            inFile.read(reinterpret_cast<char*>(&size), sizeof(size)); // Читання розміру
            delete[] vector;
            vector = new double[size];
            inFile.read(reinterpret_cast<char*>(vector), size * sizeof(double)); // Читання вектора
            inFile.close();
            cout << "Data is loaded from a file: " << filename << endl;
        }
        else {
            cout << "Error opening file for reading" << endl;
        }
    }

    // Метод для збереження результату обчислення у текстовий файл
    void saveResult(double result, const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Calculation result: " << result << endl;
            outFile.close();
            cout << "The result is saved in a file: " << filename << endl;
        }
        else {
            cout << "Error opening file for writing" << endl;
        }
    }
};

// Основна функція програми для тестування методів класу
int main() {
    // Створення об'єкта класу CDoubleVector та його ініціалізація
    CDoubleVector vec(11); // Розмір вектора 11 елементів

    // Вектор значень
    std::vector<double> values = { 0.3, 0.7, 0.9, 1.3, 1.7, 1.9, 2.3, 2.7, 2.9, 3.3, 3.7 };

    // Встановлення значень елементів вектора
    for (int i = 0; i < vec.getSize(); ++i) {
        vec.setElement(i, values[i]);
    }

    // Тестування методів saveData() та loadData()
    vec.saveData("vector_data.bin");
    CDoubleVector vecLoaded;
    vecLoaded.loadData("vector_data.bin");

    // Перевірка завантажених даних
    std::cout << "Loaded vector elements:" << std::endl;
    for (int i = 0; i < vecLoaded.getSize(); ++i) {
        std::cout << "vecLoaded[" << i << "] = " << vecLoaded.getElement(i) << std::endl;
    }

    // Тестування методу saveResult()
    double x = 1.5, y = 2.0, z = 0.5;
    double result = vec.calculate(x, y, z);
    vec.saveResult(result, "result.txt");

    return 0;
}
