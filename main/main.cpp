#include <iostream>
#include "TriangleMatrix.h"
#include <windows.h>

using std::cin;
using std::cout;

using M = Matrix<double>;

size_t read_size(const char* prompt) {
    size_t v;

    cout << prompt;
    if (!(cin >> v) || v <= 0) {
        throw std::invalid_argument("Нужно положительное целое число");
    }

    return v;
}

double read_number(const char* prompt) {
    double v;

    cout << prompt;
    if (!(cin >> v)) {
        throw std::invalid_argument("Нужно число");
    }

    return v;
}

M& select(M& a, M& b, const char* prompt) {
    cout << prompt << " (A/B): ";

    char c;

    cin >> c;

    if (c == 'A' || c == 'a') return a;
    if (c == 'B' || c == 'b') return b;

    throw std::invalid_argument("Нужно ввести A или B");
}

void input_full(M& target) {
    size_t r = read_size("Строк: ");
    size_t c = read_size("Столбцов: ");
    M m(r, c);

    cout << "Введите " << r * c << " элементов:\n";
    if (!(cin >> m)) {
        throw std::invalid_argument("Ошибка ввода элементов");
    }

    target = m;
}

void input_triangle(M& target) {
    size_t n = read_size("Размер n: ");
    TriangleMatrix<double> t(n);

    cout << "Введите полную матрицу " << n << "x" << n << " (под диагональю только нули, " << n * n << " элементов):\n";
    if (!(cin >> t)) {
        throw std::invalid_argument("Ошибка ввода элементов");
    }

    target = t;
}

void print_menu() {
    cout << "\n=== Матричный калькулятор ===\n"
        << "1. Ввести матрицу (обычную)\n"
        << "2. Ввести верхнетреугольную матрицу\n"
        << "3. Показать A и B\n"
        << "4. A + B\n"
        << "5. A - B\n"
        << "6. A * B\n"
        << "7. Умножить матрицу на число\n"
        << "8. Транспонировать матрицу\n"
        << "0. Выход\n"
        << "Выбор: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    M A, B;

    while (true) {
        print_menu();

        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cout << "Нужно ввести номер пункта.\n";
            continue;
        }
        if (choice == 0) break;

        try {
            switch (choice) {
            case 1:
                input_full(select(A, B, "Куда записать"));
                break;
            case 2:
                input_triangle(select(A, B, "Куда записать"));
                break;
            case 3:
                cout << "A =\n" << A << "\nB =\n" << B << '\n';
                break;
            case 4: {
                M r = A + B;
                cout << "A + B =\n" << r << '\n';
                break;
            }
            case 5: {
                M r = A - B;
                cout << "A - B =\n" << r << '\n';
                break;
            }
            case 6: {
                M r = A * B;
                cout << "A * B =\n" << r << '\n';
                break;
            }
            case 7: {
                M& m = select(A, B, "Какую матрицу");
                double k = read_number("Число: ");
                M r = m * k;
                cout << "Результат =\n" << r << '\n';
                break;
            }
            case 8: {
                M& m = select(A, B, "Какую матрицу");
                cout << "Результат =\n" << m.transpose() << '\n';
                break;
            }
            default:
                cout << "Нет такого пункта.\n";
            }
        }
        catch (const std::exception& e) {
            cout << "Ошибка: " << e.what() << '\n';
        }
    }

    return 0;
}