#ifndef TREE_H
#define TREE_H

#include <memory>
#include <iostream>

#include "set.h"
#include "node.h"

template<class T>
class tree {
public:
    tree();

    void insert_leaf(const T& parent_data, const T& leaf_data);

    void erase(node<T>* node_ptr);

    void erase_leaves(node<T>* node_ptr);

    set<node<T>*> get_leaves(node<T>* node_ptr);

    void print_elements();

    node<T>* find(const T& data);

private:
    std::unique_ptr<node<T>> root;

    node<T>* find_util(node<T>* cur, const T& data);

    node<T>* find_rep(node<T>* node_ptr);

    void print_util(node<T>* cur);
};

template<class T>
void tree<T>::print_elements()
{
    print_util(root.get());
    std::cout << std::endl;
}

template<class T>
void tree<T>::print_util(node<T> *cur)
{
    if (!cur) return;
    for(int i=0; i<cur->leaves.get_size(); i++)
        print_util(cur->leaves[i].get());
    std::cout << cur->data << ' ';
}

template<class T>
set<node<T>*> tree<T>::get_leaves(node<T>* node_ptr)
{
    set<node<T>*> leaves_set;
    for (int i=0; i<node_ptr->leaves.get_size(); i++)
        leaves_set.push_back(node_ptr->leaves[i].get());
    return leaves_set;
}

template<class T>
void tree<T>::erase_leaves(node<T>* node_ptr)
{
    for (int i=0; i < node_ptr->leaves.get_size(); i++)
        erase(node_ptr->leaves[i].get());
}

template<class T>
node<T>* tree<T>::find_util(node<T>* cur, const T& data)
{
    if (cur->data == data)
        return cur;
    if (cur->leaves.get_size() == 0)
        return nullptr;

    for(int i=0; i<cur->leaves.get_size(); i++)
    {
        node<T>* node_found = find_util(cur->leaves[i].get(), data);
        if(node_found) return node_found;
    }
}

template<class T>
node<T>* tree<T>::find_rep(node<T>* node_ptr)
{
    node<T>* cur = node_ptr->leaves[node_ptr->leaves.get_size() - 1].get();
    while(cur->leaves.get_size()!=0)
        cur = cur->leaves[0].get();
    return cur;
}

template<class T>
void tree<T>::erase(node<T>* node_ptr)
{
    if (node_ptr->leaves.get_size() == 0)
    {
        for(int i=0; i<node_ptr->parent->leaves.get_size(); i++)
        {
            if (node_ptr->parent->leaves[i].get() == node_ptr)
                node_ptr->parent->leaves.erase(node_ptr->parent->leaves[i]);
        }
    }
    else if (node_ptr->leaves.get_size() == 1)
    {
        for(int i=0; i<node_ptr->parent->leaves.get_size(); i++)
        {
            if (node_ptr->parent->leaves[i].get() == node_ptr)
            {
                node_ptr->parent->leaves.insert(i, std::move(node_ptr->leaves[0]));
                node_ptr->parent->leaves.erase(node_ptr->parent->leaves[i+1]);
            }
        }
    }
    else
    {
        node<T>* rep_node = find_rep(node_ptr);
        node_ptr->data = rep_node->data;
        erase(rep_node);
    }
}

template<class T>
node<T>* tree<T>::find(const T& data)
{
    return find_util(root.get(), data);
}

template<class T>
tree<T>::tree()
{
    root = nullptr;
}

template<class T>
void tree<T>::insert_leaf(const T &parent_data, const T &leaf_data)
{
    std::unique_ptr<node<T>> new_leaf(new node<T>(leaf_data));

    if (root == nullptr)
    {
        std::unique_ptr<node<T>> new_root(new node<T>(parent_data));
        root = std::move(new_root);
        root->leaves.push_back(std::move(new_leaf));
        root->leaves[root->leaves.get_size()-1]->parent = root.get();
    }
    node<T>* parent_node = find(parent_data);
    node<T>* leaf_node = find(leaf_data);
    if(parent_node && !leaf_node)
    {
        parent_node->leaves.push_back(std::move(new_leaf));
        parent_node->leaves[parent_node->leaves.get_size()-1]->parent = parent_node;
    }
}

#endif
