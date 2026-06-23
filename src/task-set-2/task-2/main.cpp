#include "linked-list.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

bool is_sort_order_ascending() {
    int sort_choice {};
    std::cout << "\n1. Ascending order\n2. Descending order\n";
    std::cout << "\nEnter your choice: ";

    if (!(std::cin >> sort_choice) || std::cin.peek() != '\n' || sort_choice < 1 || sort_choice > 2) {
        std::cerr << "\nError! Invalid sort choice!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (sort_choice == 1) {
        return true;
    }

    return false;
}

int main() {
    std::ifstream file("grades.txt");

    if (!file) {
        std::cerr << "Error! Could not open grades.txt file!\n";
        return 1;
    }

    std::string name {}, surname {};
    int grade {};
    LinkedList group_list {};

    while (file >> name >> surname >> grade) {
        group_list.append(name, surname, grade);
    }

    file.close();

    int user_choice {};
    bool is_exit_requesred {false};

    do {
        std::cout << "1. Display the list\n"
                    "2. Insert element\n"
                    "3. Remove element\n"
                    "4. Sort list by name\n"
                    "5. Sort list by surname\n"
                    "6. Sort list by grade\n"
                    "7. Display average grade of the group\n"
                    "8. Exit\n"
                    "\nEnter your choice: ";
        std::cin >> user_choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (user_choice) {
        case 1:
            std::cout << '\n';
            group_list.display();
            break;
        case 2:
            std::cout << "\nName: ";
            std::cin >> name;
            std::cout << "Surname: ";
            std::cin >> surname;
            std::cout << "Grade: ";
            if (!(std::cin >> grade) || std::cin.peek() != '\n' || grade < 0 || grade > 10) {
                std::cerr << "\nError! Grade must be a value in the range of 0-10!\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                group_list.append(name, surname, grade);
                std::cout << "\nStudent " << name << ' ' << surname << " was successfully added!\n\n";
            }
            break;
        case 3:
            std::cout << "\nName: ";
            std::cin >> name;
            std::cout << "Surname: ";
            std::cin >> surname;
            if (group_list.is_empty()) {
                std::cerr << "\nError! Group is is already empty!\n\n";
            } else {
                group_list.remove(name, surname);
                std::cout << "\nStudent " << name << ' ' << surname << " was removed successfully!\n\n";
            }
            break;
        case 4:
            is_sort_order_ascending()
            ? group_list.sort(LinkedList::SortField::Name, LinkedList::SortOrder::ASC)
            : group_list.sort(LinkedList::SortField::Name, LinkedList::SortOrder::DESC);
            std::cout << "\nGroup list was successfully sorted!\n\n";
            break;
        case 5:
            is_sort_order_ascending()
            ? group_list.sort(LinkedList::SortField::Surname, LinkedList::SortOrder::ASC)
            : group_list.sort(LinkedList::SortField::Surname, LinkedList::SortOrder::DESC);
            std::cout << "\nGroup list was successfully sorted!\n\n";
            break;
        case 6:
            is_sort_order_ascending()
            ? group_list.sort(LinkedList::SortField::Value, LinkedList::SortOrder::ASC)
            : group_list.sort(LinkedList::SortField::Value, LinkedList::SortOrder::DESC);
            std::cout << "\nGroup list was successfully sorted!\n\n";
            break;
        case 7:
            if (group_list.is_empty()) {
                std::cerr << "\nError! Group list is empty, cannot compute average grade!\n\n";
            } else {
                std::cout << "\nGroup average: "
                    << std::fixed  << std::setprecision(1)<< group_list.average() << "\n\n";
            }
            break;
        case 8:
            is_exit_requesred = true;
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

    } while (!is_exit_requesred);

    return 0;
}
