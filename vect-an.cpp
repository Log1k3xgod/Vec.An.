//Язык c++ 

#include <iostream>
#include <vector>
#include <cmath> 

// Функция для вычисления определителя матрицы NxN
double determinant(const std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    double det = 1.0;
    std::vector<std::vector<double>> temp = matrix; // копия для преобразований

    for (int i = 0; i < n; ++i) {
        // Поиск максимального элемента в столбце для выбора главного элемента
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(temp[k][i]) > std::abs(temp[maxRow][i])) {
                maxRow = k;
            }
        }
        if (std::abs(temp[maxRow][i]) < 1e-12) {
            // Определитель равен нулю
            return 0;
        }
        if (maxRow != i) {
            std::swap(temp[i], temp[maxRow]);
            det = -det; // меняется знак при перестановке строк
        }

        det *= temp[i][i];

        // Приведение к треугольному виду
        for (int k = i + 1; k < n; ++k) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i; j < n; ++j) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }
    return det;
}

// Метод Крамера для решения системы
std::vector<double> solveCramer(const std::vector<std::vector<double>>& A, const std::vector<double>& B) {
    int n = A.size();
    double detA = determinant(A);
    if (std::abs(detA) < 1e-12) {
        throw std::runtime_error("Система не имеет уникального решения (детерминант равен нулю).");
    }

    std::vector<double> solution(n);
    for (int i = 0; i < n; ++i) {
        // Создаем копию матрицы A и заменяем i-й столбец на вектор B
        std::vector<std::vector<double>> Ai = A;
        for (int j = 0; j < n; ++j) {
            Ai[j][i] = B[j];
        }
        double detAi = determinant(Ai);
        solution[i] = detAi / detA;
    }
    return solution;
}

int main() {
    // Пример системы:
    std::vector<std::vector<double>> A = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };

    std::vector<double> B = {8, -11, -3};

    try {
        auto solution = solveCramer(A, B);
        std::cout << "Решение системы:\n";
        for (size_t i=0; i<solution.size(); ++i)
            std::cout << "x" << i+1 << " = " << solution[i] << "\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
