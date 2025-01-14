#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <algorithm>
#include <iterator>

// Функция для преобразования строки в IP-адрес (tuple)
std::tuple<int, int, int, int> parse_ip(const std::string& ip_str) {
    int n1, n2, n3, n4;
    char dot1, dot2, dot3;
    std::istringstream ss(ip_str);
    ss >> n1 >> dot1 >> n2 >> dot2 >> n3 >> dot3 >> n4;
    return {n1, n2, n3, n4};
}

// Лямбда-функция для сортировки IP-адресов в обратном лексикографическом порядке
auto reverse_lexicographical_compare = [](const auto& ip1, const auto& ip2) {
    return ip1 > ip2;
};

int main() {
    std::vector<std::tuple<int, int, int, int>> ip_list;
    std::ifstream file("ip_filter.tsv");

    // Проверка на успешное открытие файла
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string line;
    // Чтение строк из файла
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string text1, text2, text3;

        // Чтение полей из строки
        std::getline(ss, text1, '\t');
        std::getline(ss, text2, '\t');
        std::getline(ss, text3, '\n');

        // Парсим и сохраняем IP-адрес
        auto ip = parse_ip(text1);
        ip_list.push_back(ip);
    }

    // Закрытие файла
    file.close();

    // Сортировка списка IP-адресов
    std::sort(ip_list.begin(), ip_list.end(), reverse_lexicographical_compare);

    // Печать полного списка IP-адресов после сортировки
    for (const auto& ip : ip_list) {
        std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." 
                  << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
    }

    // Фильтрация и печать IP-адресов с первым байтом равным 1
    for (const auto& ip : ip_list) {
        if (std::get<0>(ip) == 1) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." 
                      << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }

    // Фильтрация и печать IP-адресов с первым байтом равным 46 и вторым байтом равным 70
    for (const auto& ip : ip_list) {
        if (std::get<0>(ip) == 46 && std::get<1>(ip) == 70) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." 
                      << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }

    // Фильтрация и печать IP-адресов с любым байтом равным 46
    for (const auto& ip : ip_list) {
        if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." 
                      << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }

    return 0;
}
