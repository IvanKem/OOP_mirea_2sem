//
// Created by iv.kem on 7/1/23.
//

#include <iostream>
template <typename T>
class Array
{
public:
    T * data_;
    int size_;
    // Список операций:
    explicit Array(int size_ = 0, const T& value = T()): size_(size_),  data_(new T[size_]){for (int i=0; i<size_;i++){data_[i]=value;}}
    //   конструктор класса, который создает    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть     //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    Array(const Array & A){
        size_=A.size_;
        data_ = new T[size_];
        for (int i=0; i<size_;i++){data_[i]=A.data_[i];}
    }
    //   конструктор копирования, который создает    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    ~Array(){delete [] data_;}
    //   деструктор, если он вам необходим.
    //
    Array& operator=(const Array & A){
        if (this != &A){
            delete [] data_;
            size_=A.size_;
            data_ = new T[size_];
            for (int i=0; i<size_;i++){data_[i]=A.data_[i];}
        }
        return *this;
    }

    //
    int size() const{
        return size_;
    }
    //   возвращает размер массива (количество
    //                              элементов).
    //
    T& operator[](int  i ){return data_[i] ;}
    const T& operator[](int i) const {return data_[i] ;}
    //   две версии оператора доступа по индексу.

};
int main()
{
    typedef Array<float> ArrayF;
    typedef Array<ArrayF> AArrayF;

    ArrayF a0(1, 3);
    std::cout << "a0 created" << std::endl;
    std::cout << a0[0] << std::endl << std::endl;

    AArrayF a(5, a0); // default constructor
    std::cout << "a created" << std::endl;
    std::cout << a[0][0] << std::endl << std::endl;

    AArrayF b(a); // copy constructor
    std::cout << "b created" << std::endl;
    std::cout << b[0][0] << std::endl << std::endl;

    AArrayF c; // default constructor
    std::cout << "c created" << std::endl << std::endl;
    c = b; // assignment (calls copy constructor and swap)
    std::cout << "c изменился" << std::endl << std::endl;
    std::cout << c[0][0] << std::endl << std::endl;
    return 0;
}