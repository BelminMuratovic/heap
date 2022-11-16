#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class Heap
{
private:
    size_t capacity_;
    size_t size_;
    T *ptr;

    bool full() const;
    bool empty() const;
    void print(size_t n) const;
    void reallocate();
    void balance_up(size_t index);
    void balance_down(size_t index);

public:
    Heap();
    Heap(const Heap &second);
    Heap(Heap &&second);
    Heap &operator=(const Heap &second);
    Heap &operator=(Heap &&second);
    ~Heap();
    template <typename U>
    void insert(U &&data);
    const T &min() const;
    const T &max() const;
    void removeMin();
    void removeMax();
    template <typename K>
    friend std::ostream &operator<<(std::ostream &out, const Heap<K> &heap);
};

template <typename T>
Heap<T>::Heap() : capacity_{10}, size_{0}, ptr{new T[capacity_]} {}

template <typename T>
Heap<T>::Heap(const Heap &second)
{
    capacity_ = second.capacity_;
    size_ = second.size_;
    ptr = new T[capacity_];
    std::copy(second.ptr, second.ptr + size_ + 1, ptr);
}

template <typename T>
Heap<T>::Heap(Heap &&second)
{
    capacity_ = second.capacity_;
    size_ = second.size_;
    ptr = second.ptr;
    second.capacity_ = 0;
    second.size_ = 0;
    second.ptr = nullptr;
}

template <typename T>
Heap<T> &Heap<T>::operator=(const Heap &second)
{
    if (&second == this)
        return *this;
    delete[] ptr;
    capacity_ = second.capacity_;
    size_ = second.size_;
    ptr = new T[capacity_];
    std::copy(second.ptr, second.ptr + size_ + 1, ptr);
    return *this;
}

template <typename T>
Heap<T> &Heap<T>::operator=(Heap &&second)
{
    if (&second == this)
        return *this;
    delete[] ptr;
    capacity_ = second.capacity_;
    size_ = second.size_;
    ptr = second.ptr;
    second.capacity_ = 0;
    second.size_ = 0;
    second.ptr = nullptr;
    return *this;
}

template <typename T>
Heap<T>::~Heap()
{
    delete[] ptr;
}

template <typename T>
template <typename U>
void Heap<T>::insert(U &&data)
{
    if (full())
        reallocate();
    ptr[++size_] = std::forward<U>(data);
    if (size_ > 1)
        balance_up(size_);
}

template <typename T>
const T &Heap<T>::min() const
{
    size_t min_ = 1;
    for (int i = 1; i <= size_; ++i) // metodi min i max su uradjeni samo kao konstantni metodi. Nekonstantni metodi
    {                                // nisu uradjeni iz razloga sto bi se tada potencijalno mogli promijeniti podaci,
        if (ptr[min_] > ptr[i])      // a zbog nemogucnosti ponovnog balansiranja, izgubila bi se osobina gomile
            min_ = i;
    }
    return ptr[min_];
}

template <typename T>
const T &Heap<T>::max() const
{
    return ptr[1];
}

template <typename T>
void Heap<T>::removeMin()
{
    if (empty())
        throw std::logic_error("Empty");

    size_t min = 1;
    for (int i = 1; i <= size_; ++i)
    {
        if (ptr[min] > ptr[i])
            min = i;
    }

    if (min == size_)
        --size_;
    else
    {
        std::swap(ptr[min], ptr[size_]);
        --size_;
        balance_up(min);
    }
}

template <typename T>
void Heap<T>::removeMax()
{
    if (empty())
        throw std::logic_error("Empty");

    std::swap(ptr[1], ptr[size_]);
    --size_;
    balance_down(1);
}

template <typename K>
std::ostream &operator<<(std::ostream &out, const Heap<K> &heap)
{
    heap.print(1);
    return out;
}

template <typename T>
bool Heap<T>::full() const
{
    return size_ + 1 == capacity_;
}

template <typename T>
bool Heap<T>::empty() const
{
    return size_ == 0;
}

template <typename T>
void Heap<T>::print(size_t n) const
{
    if (n > size_)
        return;
    print(n * 2);
    std::cout << ptr[n] << " ";
    print(n * 2 + 1);
}

template <typename T>
void Heap<T>::reallocate()
{
    capacity_ *= 2;
    T *temp = new T[capacity_];
    std::copy(ptr, ptr + size_ + 1, temp);
    delete[] ptr;
    ptr = temp;
    temp = nullptr;
}

template <typename T>
void Heap<T>::balance_up(size_t index)
{
    while (index > 1)
    {
        if (ptr[index] > ptr[index / 2])
        {
            std::swap(ptr[index], ptr[index / 2]);
            index = index / 2;
        }
        else
            break;
    }
}

template <typename T>
void Heap<T>::balance_down(size_t index)
{
    size_t left = index * 2;
    size_t right = index * 2 + 1;

    if ((ptr[index] < ptr[left] || ptr[index] < ptr[right]) && left < size_ && right <= size_)
    {
        size_t max = left;
        if (ptr[max] < ptr[right])
            max = right;
        std::swap(ptr[max], ptr[index]);
        balance_down(max);
    }
    else if (left <= size_ && right > size_)
    {
        if (ptr[left] > ptr[index])
            std::swap(ptr[left], ptr[index]);
    }
    else if (left > size_ && right <= size_)
    {
        if (ptr[right] > ptr[index])
            std::swap(ptr[right], ptr[index]);
    }
}
