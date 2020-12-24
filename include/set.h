#ifndef SET_H
#define SET_H

#include <memory>

template<class T>
class set {
public:
    set();

    void push_back(const T& data);

    void push_back(T&& data);

    void insert(const int& pos, const T& data);

    void insert(const int& pos, T&& data);

    void erase(const T& data);

    bool contains(const T& data);

    T& operator[](const int& pos);

    T* get_elements();

    int get_size();
private:
    std::unique_ptr<T[]> values;
    int size;
};

template<class T>
int set<T>::get_size()
{
    return size;
}

template<class T>
set<T>::set()
{
    this->size = 0;
    values = nullptr;
}

template<class T>
T& set<T>::operator[](const int& pos)
{
    return values[pos];
}

template<class T>
T* set<T>::get_elements()
{
    return values.get();
}

template<class T>
void set<T>::erase(const T& data)
{
    std::unique_ptr<T[]> new_values = std::unique_ptr<T[]>(new T[size-1]);

    int i = 0;
    while(values[i] != data)
    {
        new_values[i] = std::move(values[i]);
        i++;
    }
    while(i < get_size()-1)
    {
        new_values[i] = std::move(values[i+1]);
        i++;
    }
    values = std::move(new_values);
    size--;
}

template<class T>
void set<T>::insert(const int& pos, const T& data)
{
    if (!contains(data))
    {
        std::unique_ptr<T[]> new_values = std::unique_ptr<T[]>(new T[size+1]);

        int i = 0;
        while(i < pos)
        {
            new_values[i] = std::move(values[i]);
            i++;
        }
        new_values[pos] = data;
        while(i < get_size())
        {
            new_values[i+1] = std::move(values[i]);
            i++;
        }
        values = std::move(new_values);
        size++;
    }
}

template<class T>
void set<T>::insert(const int& pos, T&& data)
{
    if (!contains(data))
    {
        std::unique_ptr<T[]> new_values = std::unique_ptr<T[]>(new T[size+1]);

        int i = 0;
        while(i < pos)
        {
            new_values[i] = std::move(values[i]);
            i++;
        }
        new_values[pos] = std::move(data);
        while(i < get_size())
        {
            new_values[i+1] = std::move(values[i]);
            i++;
        }
        values = std::move(new_values);
        size++;
    }
}

template<class T>
bool set<T>::contains(const T& data)
{
    for(int el_index=0; el_index<size; el_index++)
    {
        if (values[el_index] == data)
            return true;
    }

    return false;
}

template<class T>
void set<T>::push_back(const T& data)
{
    if(!contains(data))
    {
        std::unique_ptr<T[]> new_values = std::unique_ptr<T[]>(new T[size+1]);
        for(int el_index=0; el_index<size; el_index++)
            new_values[el_index] = std::move(values[el_index]);

        new_values[size] = data;
        values = std::move(new_values);
        size++;
    }
}

template<class T>
void set<T>::push_back(T&& data)
{
    if(!contains(data)) {
        std::unique_ptr<T[]> new_values = std::unique_ptr<T[]>(new T[size+1]);
        for(int el_index=0; el_index<size; el_index++)
            new_values[el_index] = std::move(values[el_index]);
        new_values[size] = std::move(data);

        values = std::move(new_values);
        size++;
    }
}

#endif
