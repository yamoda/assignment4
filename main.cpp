#include <iostream>

#include "include/set.h"
#include "include/tree.h"
#include "include/node.h"

int main() {
    // пример использования
    tree<int> test_tree;

    // добавление элементов
    test_tree.insert_leaf(5, 6);
    test_tree.insert_leaf(5, 9);
    test_tree.insert_leaf(5, 8);
    test_tree.insert_leaf(5, 10);
    test_tree.insert_leaf(10, 11);
    test_tree.insert_leaf(10, 20);
    test_tree.insert_leaf(6, 15);
    test_tree.insert_leaf(6, 21);

    // распечатка элементов
    test_tree.print_elements();

    // поиск
    node<int>* node10 = test_tree.find(10);

    // удаление
    test_tree.erase(node10);
    std::cout << "После удаления элемента со значением 10" << std::endl;
    test_tree.print_elements();

    return 0;
}
