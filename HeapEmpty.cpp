// Heap.cpp: определяет точку входа для консольного приложения.
//


#include <string.h>
#include <iostream>


using namespace std;


class Book {
protected:
    const char *aut_name;
    const char *aut_sername;
    const char *book_name;
    int year;
    const char *name_publishers;
    int number_of_pages;
    enum type_of_publication {electronic, paper , audio};
    int circulation;


public:
    Book() {}
    Book(const char* a_n,const char* a_sn, const char* b_n, int ye, const char* n_pub,int n_pag, /*type_of_publication type,*/ int cir) {
        aut_name=a_n;
        aut_sername=a_sn;
        book_name=b_n;
        year=ye;
        name_publishers=n_pub;
        number_of_pages=n_pag;
        /*type_of_publication = type;*/
        circulation=cir;
    }



    ~Book() { cout << "\nBook destructor"; }
    int getCirculation() const { return circulation; }
    int getYear() const { return year; }
    const char* getBook_name() const { return book_name; }

    friend ostream& operator<<(ostream& os, const Book& M) {
        os << "aut_name: " << M.aut_name << endl
           << "aut_sername : " << M.aut_sername << endl
           << "book_name: " << M.book_name << endl
           << "year: " << M. year << endl
           << "name_publishers: " << M.name_publishers << endl
           << "number_of_pages: " << M.number_of_pages << endl
           << "circulation: " << M.circulation << endl;
        return os;
    }
};

bool operator==(const Book& M1, const Book& M2) {
    if (M1.getCirculation() == M2.getCirculation())
    return false;
}

bool operator<(const Book& M1, const Book& M2) {
    if (M1.getCirculation() == M2.getCirculation()) {
        if (M1.getYear() == M2.getYear())  {
            if (strcmp(M1.getBook_name(), M2.getBook_name()) == 0) {return true;}

            else if (strcmp(M1.getBook_name(), M2.getBook_name()) > 0){ return true;}
            else {return false;}
        }
        else if (strcmp(M1.getBook_name(), M2.getBook_name()) > 0)
            return false;
        else
            return true;
    }
    else
        return (M1.getCirculation() == M2.getCirculation()) ? false : true;
}

bool operator>(const Book& M1, const Book& M2) {
    return M2 < M1;
}

template <class T>
class Node
{
private:
	T value;
public:
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//сравнение узлов
	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};

template <class T>
void print(Node<T>* N)
{
    cout << N->getValue() << "\n";
}
//куча (heap)
template <class T>
class Heap
{
private:
    //массив
    Node<T>* arr;
    //сколько элементов добавлено
    int len;
    //сколько памяти выделено
    int size;
public:
    //доступ к вспомогательным полям кучи и оператор индекса
    int getCapacity() { return size; }
    int getCount() { return len; }
    Node<T>& operator[](int index)
    {
        if (index < 0 || index >= len)
            ;//?
        return arr[index];
    }
    //конструктор
    Heap<T>(int MemorySize = 100)
    {
        arr = new Node<T>[MemorySize];
        len = 0;
        size = MemorySize;
    }

    ~Heap<T>() {
        delete arr;
    }

    //поменять местами элементы arr[index1], arr[index2]
    void Swap(int index1, int index2)
    {
        if (index1 <= 0 || index1 >= len)
            ;
        if (index2 <= 0 || index2 >= len)
            ;
        //здесь нужна защита от дурака
        Node<T> temp;
        temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
    }
    //скопировать данные между двумя узлами
    void Copy(Node<T>* dest, Node<T>* source)
    {
        dest->setValue(source->getValue());
    }
    //функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
    Node<T>* GetLeftChild(int index)
    {
        if (index < 0 || index * 2 >= len)
            ;
        //здесь нужна защита от дурака
        return &arr[index * 2 + 1];
    }
    Node<T>* GetRightChild(int index)
    {
        if (index < 0 || index * 2 >= len);
        //здесь нужна защита от дурака
        return &arr[index * 2 + 2];
    }
    Node<T>* GetParent(int index)
    {
        if (index <= 0 || index >= len)
            ;
        //здесь нужна защита от дурака
        if (index % 2 == 0)
            return &arr[index / 2 - 1];
        return &arr[index / 2];
    }
    int GetLeftChildIndex(int index)
    {
        if (index < 0 || index * 2 >= len)
            ;
        //здесь нужна защита от дурака
        return index * 2 + 1;
    }
    int GetRightChildIndex(int index)
    {
        if (index < 0 || index * 2 >= len)
            ;
        //здесь нужна защита от дурака
        return index * 2 + 2;
    }
    int GetParentIndex(int index)
    {
        if (index <= 0 || index >= len)
            ;
        //здесь нужна защита от дурака
        if (index % 2 == 0)
            return index / 2 - 1;
        return index / 2;
    }
    //просеять элемент вверх
    void SiftUp(int index = -1)
    {
        if (index == -1) index = len - 1;
        int parent = GetParentIndex(index);
        int index2 = GetLeftChildIndex(parent);
        if (index2 == index)
            index2 = GetRightChildIndex(parent);
        int max_index = index;
        if (index < len && index2 < len && parent >= 0)
        {
            if (arr[index] > arr[index2])
                max_index = index;
            if (arr[index] < arr[index2])
                max_index = index2;
        }
        if (parent < len && parent >= 0 &&
            arr[max_index]>arr[parent])
        {
            //нужно просеивание вверх
            Swap(parent, max_index);
            SiftUp(parent);
        }
    }

    void Heapify(int index = 0) {
        int leftChild;
        int rightChild;
        int largestChild;
        for (; ; )
        {
            leftChild = GetLeftChildIndex(index);
            rightChild = GetRightChildIndex(index);
            largestChild = index;

            if (leftChild < len && arr[leftChild] > arr[largestChild])
            {
                largestChild = leftChild;
            }

            if (rightChild < len && arr[rightChild] > arr[largestChild])
            {
                largestChild = rightChild;
            }

            if (largestChild == index)
            {
                break;
            }

            Node<T> temp = arr[index];
            arr[index] = arr[largestChild];
            arr[largestChild] = temp;
            index = largestChild;
        }
    }

    Node<T>* ExtractMax()
    {
        //исключить максимум и запустить просеивание кучи
        Node<T>* res = new Node<T>(arr[0]);
        Swap(0, len - 1);
        len--;
        Heapify();
        return res;
    }

    Node<T>* remove(int index) {
        Node<T>* res = new Node<T>(arr[index]);
        Swap(index, len - 1);
        len--;
        if (arr[index].getValue() > GetParent(index)->getValue())
            SiftUp(index);
        else
            Heapify(index);
        return res;
    }

    //добавление элемента - вставляем его в конец массива и просеиваем вверх
    template <class T1>
    void push(T1 v)
    {
        Node<T>* N = new Node<T1>;
        N->setValue(v);
        push(N);
    }
    template <class T1>
    void push(Node<T1>* N)
    {
        if (len < size)
        {
            Copy(&arr[len], N);
            len++;
            SiftUp();
        }
    }
    //перечислить элементы кучи и применить к ним функцию
    void Straight(void(*f)(Node<T>*))
    {
        int i;
        for (i = 0; i < len; i++)
        {
            f(&arr[i]);
        }
    }
    //перебор элементов, аналогичный проходам бинарного дерева
    void InOrder(void(*f)(Node<T>*), int index = 0)
    {
        if (GetLeftChildIndex(index) < len)
            PreOrder(f, GetLeftChildIndex(index));
        if (index >= 0 && index < len)
            f(&arr[index]);
        if (GetRightChildIndex(index) < len)
            PreOrder(f, GetRightChildIndex(index));
    }
};




// 2i+1 - левое поддерево, 2i+2 - правое поддерево
int main()
{  //измени name и enum
    Heap<Book> Tree;
    Book arr[5];
    arr[0] = Book("Pavel", "Byev", "Codabra", 1994, "Avito", 2139,313542341);
    arr[1] = Book("Parot", "Trushin", "Sholkovo", 2000, "OZON", 2139,313542341);
    arr[2] = Book("Mihail", "Abramovich", "postypashki", 2004, "Yandex", 333339,317368233);
    arr[3] = Book("Genadiy", "Roshrov", "cric", 1980, "Tinkoff", 3249,999932341);
    arr[4] = Book("Igor", "Dobronravov", "Idiot", 2012, "Sber", 1119,645382341);
    for (int i = 0; i < 5; i++) Tree.push(arr[i]);
    cout << "\n-----\nStraight:\n";
    void(*f_ptr)(Node<Book>*); f_ptr = print;
    Tree.Straight(f_ptr);
    Tree.remove(5);
    cout << "After remove:\n";
    Tree.Straight(f_ptr);
    cout << "Extract max: \n";
    int i = 0;
    while (i < Tree.getCount())
    {
        Node<Book>* N = Tree.ExtractMax();
        N->print();
        delete N;
        cout << "\n";
    }


	char c; cin >> c;
	return 0;
}

