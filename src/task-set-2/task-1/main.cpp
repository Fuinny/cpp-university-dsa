#include "linked-list.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

int main() {
    std::ifstream file("grades.txt");

    if (!file) {
        std::cerr << "Could not open grades.txt file!\n";
        return 1;
    }

    int grade {};
    LinkedList group_grades {};

    while (file >> grade) {
        group_grades.append(grade);
    }

    file.close();

    std::cout << "Group Grades:\n";
    group_grades.display();
    std::cout << "\nGroup Average:\n";
    std::cout << std::fixed << std::setprecision(1) << group_grades.average() << '\n';

    return 0;
}
