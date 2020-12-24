#ifndef NODE_H
#define NODE_H

#include "set.h"

template<class T>
struct node {
    T data;
    node* parent;

    set<std::unique_ptr<node>> leaves;

    explicit node(const T& data);
};

template<class T>
node<T>::node(const T& data)
{
    this->data = data;
    this->parent = nullptr;
}

#endif
