#include <iostream>
#include <fstream>  // Для работы с файлами
#include <cmath>    // Для математических функций
#include <stdexcept> // Для обработки исключений

using namespace std;

// Функция для вычисления выражения
double calculateExpression(double x, int n) {
    // Проверка на некорректное значение n
    if (n <= 0) {
        throw std::invalid_argument("n must be greater than 0");
    }

    if (x < 0) {
        double sum = 0;
        for (int t = 1; t <= n - 1; ++t) {
            for (int j = 1; j <= n; ++j) {
                sum += static_cast<double>(j) / (j * j + j);
            }
        }
        return sum;
    }
    else {
        double sum = 0;
        for (int t = 1; t <= n - 1; ++t) {
            sum += t;
        }
        return x - sum;
    }
}

int main() {
    double a, b, h;
    int n;
    char saveToFile;

    // Ввод параметров от пользователя
    cout << "Enter the beginning of the interval (a): ";
    cin >> a;
    cout << "Enter the end of the interval (b): ";
    cin >> b;
    cout << "Enter step (h): ";
    cin >> h;
    cout << "Enter the value of n: ";
    cin >> n;

    // Проверка на корректность ввода
    if (h <= 0 || a > b) {
        cout << "Incorrect data. Check start, end or step." << endl;
        return 1;
    }

    // Запрос на сохранение в файл
    cout << "Do I need to write the results to a file? (y/n): ";
    cin >> saveToFile;

    ofstream outFile;
    if (saveToFile == 'y' || saveToFile == 'Y') {
        outFile.open("results.txt");
        if (!outFile.is_open()) {
            cout << "Could not open file for writing." << endl;
            return 1;
        }
    }

    // Вычисление и вывод значений
    cout << "x\ty" << endl;
    if (outFile.is_open()) {
        outFile << "x\ty" << endl;
    }

    for (double x = a; x <= b; x += h) {
        try {
            double y = calculateExpression(x, n);
            cout << x << "\t" << y << endl;
            if (outFile.is_open()) {
                outFile << x << "\t" << y << endl;
            }
        }
        catch (const std::invalid_argument& e) {
            cout << "Error for x = " << x << ": " << e.what() << endl;
            if (outFile.is_open()) {
                outFile << "Error for x = " << x << ": " << e.what() << endl;
            }
        }
    }

    if (outFile.is_open()) {
        outFile.close();
        cout << "The results are recorded in the results.txt file." << endl;
    }

    return 0;
}
