// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>

using namespace std;

class MyArrayParent
{
protected:
    //сколько памяти выделено?
    int capacity;
    //количество элементов - сколько памяти используем
    int count;
    //массив
    double* ptr;
public:
    //конструкторы и деструктор
    MyArrayParent(int Dimension = 100)
    {
        //cout << "\nMyArrayParent constructor";
        //выделить память под массив ptr, заполнить поля
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    //конструктор принимает существующий массив
    MyArrayParent(double* arr, int len)
    {

        //cout << "\nMyArrayParent constructor";
        //заполнить массив ptr, заполнить поля
        ptr = new double[len];
        capacity = len;
        count =0;
        for (int i=0; i<len;i++) {
            ptr[i] = *(arr+i);
            count++;
        }

    }
    MyArrayParent(const MyArrayParent& P)
    {
        count=P.count;
        capacity=P.capacity;
        ptr=new double [capacity];
        for (int i=0; i<count;i++)
            ptr[i]=P.ptr[i];
    }

    MyArrayParent& operator=(const MyArrayParent& P)
    {
        if (capacity<P.capacity){delete[] ptr; capacity=P.capacity; ptr= new double[capacity];}
        count=P.count;
        for (int i=0; i<count;i++)
            ptr[i]=P.ptr[i];
        return *this;

    }

    //деструктор
    ~MyArrayParent()
    {
        //cout << "\nMyArrayParent destructor";
        //освободить память, выделенную под ptr
        delete[] ptr;
    }

    //обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }
    double GetComponent(int index)
    {
        if (index >= 0 && index < count)
            return ptr[index];
        //сгенерировать исключение, если индекс неправильный
        return -1;
    }
    void SetComponent(int index, double value)
    {
        if (index >= 0 && index < count)
            ptr[index] = value;
        //сгенерировать исключение, если индекс неправильный
    }

    //добавление в конец нового значения
    void push(double value)
    {
        if (count < capacity)
        {
            ptr[count] = value;
            count++;
        }
    }

    //удаление элемента с конца
    void RemoveLastValue()
    {
        if (count > 0)
        {
            ptr[count - 1] = 0;
            count--;
        }
        //что делаем, если пуст?

    }

    double& operator[](int index)
    {
        //перегрузка оператора []
        return ptr[index];
    }

    //поиск элемента
    int IndexOf(double value, bool bFindFromStart = true)
    {
        int i = 0;
        if (bFindFromStart == true)
        {
            for (i = 0; i < count; i++)
            {
                if (ptr[i] == value)
                    return i;
            }

        }
        else
        {
            for (i = count-1; i >= 0; i--)
            {
                if (ptr[i] == value)
                    return i;
            }
        }
        return -1;
    }

    //удаление элемента
    void RemoveAt(int index = -1)
    {
        if (count == 0) return;
        if (index == -1)
        {
            RemoveLastValue();
            return;
        }
        for (int i = index; i < count-1; i++)
        {
            ptr[i] = ptr[i + 1];
        }
    }

    void print()
    {
        cout << "\nMyArrParent, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++)
        {
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }

};

class MyArrayChild : public MyArrayParent
{
public:
    //используем конструктор родителя. Нужно ли что-то ещё?
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {/** cout << "\nMyArrayChild constructor";**/ }
    MyArrayChild(double* arr, int len ) : MyArrayParent(arr,len) {/** cout << "\nMyArrayChild constructor"; **/}

    ~MyArrayChild() {/** cout << "\nMyArrayChild destructor\n"; **/}

    //поиск элемента
    //void IndexOf(double value, bool bFindFromStart = true);
    //поиск элемента
    int IndexOf(double value, bool bFindFromStart = true)
    {
        int i = 0;
        if (bFindFromStart == true)
        {
            for (i = 0; i < count; i++)
            {
                if (ptr[i] == value)
                    return i;
            }

        }
        else
        {
            for (i = count-1; i >= 0; i--)
            {
                if (ptr[i] == value)
                    return i;
            }
        }
        return -1;
    }

    //удаление элемента
    //void RemoveAt(int index = -1);
    void RemoveAt(int index = -1)
    {
        if (count == 0) return;
        if (index == -1)
        {
            RemoveLastValue();
            return;
        }
        for (int i = index; i < count-1; i++)
        {
            ptr[i] = ptr[i + 1];
        }
        count--;
    }

    //вставка элемента
    //void InsertAt(double value, int index = -1);
    void InsertAt(double value, int index = -1) {
        if (index==-1 || index==count)
            push(value);
        if (index<0 || index>count) return;

        for (int i=count; i>index;i--){
            ptr[i]=ptr[i-1];
        }
        ptr[index]=value;
        count++;
    }

    //Вариант 7. Удаление всех нечетных чисел из массива
    virtual MyArrayChild RemoveOddNumbers(){
        MyArrayChild res(*this);
        for (int i=0;i<count;i++){
            if (fmod(res[i],2)!=0) {res.RemoveAt(i);};
        };
        return res;
    }


    //выделение подпоследовательности
    MyArrayChild SubSequence(int StartIndex = 0, int length = -1){
        MyArrayChild res;
        res.count=0;
        res.capacity=length;
        if (length==-1 or length==0){return res;};
        for (int i=StartIndex;i<=length;i++){res.push(ptr[i]);}
        return res;
    }


    //добавление элемента в конец
    MyArrayChild operator+(double z){
        MyArrayChild res(*this);
        res.push(z);
        return res;
    }


};


class MySortedArray : public MyArrayChild{
protected:
    int BinSearch(double value, int left, int right)
    {
        int midlle =(left+right)/2;
        if (ptr[midlle]==value) return midlle;
        if (count==1) return -1;
        // база рекурсии
        if (left+1==right){
            if(ptr[right]==value) return right;
            return -1;
        }

        if (ptr[midlle]>value) return BinSearch(value,left,midlle);
        if (ptr[midlle]<value) return BinSearch(value,midlle,right);

    }

    int BinSearch_Iterative(double value, int left, int right)
    {
        if (count==1) return -1;
        // цикл
        while (left<=right){
            int midlle =left +(right-left)/2;
            if(ptr[midlle]==value) return midlle;
            if (ptr[midlle] < value)
                left = midlle + 1;

            else
                right = midlle - 1;
        }

        return -1;
    }

    int BinSearch_insert(double value, int left, int right)
    {
        int midlle =(left+right)/2;
        if (ptr[midlle]==value) return midlle;
        if (count==1) {
            if (ptr[0]>value) return 0;
            return 1;
        }
        // база рекурсии
        if (left+1==right){
            if(ptr[right]>value) return left;
            if(ptr[right]<value) return right+1;
            return right;
        }

        if (ptr[midlle]>value) return BinSearch(value,left,midlle);
        if (ptr[midlle]<value) return BinSearch(value,midlle,right);

    }

public:
    //используем конструктор родителя. Нужно ли что-то ещё?
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { /** cout << "\nMyArrayChild constructor";* */ }
    MySortedArray(double* arr, int len ) : MyArrayChild(arr,len) {}


    ~MySortedArray() { /** cout << "\nMyArrayChild destructor\n"; **/}


    virtual int IndexOf(double value, bool bFindFromStart = true)
    {
        return BinSearch_Iterative(value,0,count-1);
    }


    virtual void push(double value)
    {
        if (count == 0){
            MyArrayChild::push(value);
            return;
        }
        int index = BinSearch_insert(value,0,count-1);
        InsertAt(value,index);
    }




};

void f(MySortedArray s)
{
    cout << "\n In f(): "; s.print();
}


int main()
{

    if (true)
    {

        MyArrayChild arr;
        //MyArrayChild arr;
        int i = 0;
        for (i = 0; i < 10; i++) { arr.push(i + 1);}
        arr.RemoveLastValue();
        //arr.RemoveAt(4);
        arr.InsertAt(5,3);
        arr.print();
        //double d = arr.GetComponent(5); //arr[5]
        cout << "\nFind 4: "<<arr.IndexOf(4)<<"\tFind -10: "<<arr.IndexOf(-10);
        //cout << "\n" << sp << "\n";
        double A[] = {1,2,3,4,5,6,7,8,9,10};
        MyArrayChild arr1(A,sizeof(A)/sizeof(*A));
        arr1.print();cout<<"   Объект созданный по конструкртору типа  MyArrayParent(double*, int); "
                           "Добавлен также в MyArrayChild";
        MyArrayChild h; h = arr1.RemoveOddNumbers();h.print();cout<<"  Вариант 7.  Удаление нечетных";
        h= h.SubSequence(1,3);h.print();cout<<" Выделение подпоследовательности длинной 3";
        (h+3).print();cout<<" Перегрузка +, добавление в конец элемента (3)";
        double B[] = {1,2,3,4,5,6,7,8,9,10};
        MySortedArray arr2(B,sizeof(B)/sizeof(*B));arr2.print();cout<<" Новый массив типа MySortedArray"<< endl;
        cout <<"Итеративный бинарный поиск индекса элемента (6) : " <<arr2.IndexOf(6);


    }
    char c; cin >> c;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

