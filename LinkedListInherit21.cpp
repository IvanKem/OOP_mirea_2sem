// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <exception>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;



class Stadium {
protected:
    const char *name;
    const char *sports_name;
    int build_year;
    int capacity;
    int numbers_of_arenas;
public:
    Stadium() {
        cout << "\nStadium constructor 0";
        name = "Мордовия Арена";
        sports_name = "Футблол, Алтимат, Волейбол";

        build_year = 2012;
        capacity = 30000;
        numbers_of_arenas = 5;
    }

    Stadium(char *Name) {
        cout << "\nStadium constructor 0";
        name = Name;
        sports_name = "Футблол, Алтимат, Волейбол";

        build_year = 2012;
        capacity = 30000;
        numbers_of_arenas = 5;
    }

    ~Stadium() { cout << "\nStadium destructor"; }

    Stadium(const Stadium &m) {
        cout << "\nStadium copy constructor";
        name = m.name;
        sports_name = m.sports_name;
        build_year = m.build_year;
        capacity = m.build_year;
        numbers_of_arenas = m.numbers_of_arenas;
    }

    Stadium operator=(const Stadium &m) {
        name = m.name;
        sports_name = m.sports_name;
        build_year = m.build_year;
        capacity = m.build_year;
        numbers_of_arenas = m.numbers_of_arenas;
        return *this;
    }

    bool operator==(const Stadium &m) { return name == m.name and sports_name == m.sports_name and build_year == m.build_year
    and capacity == m.build_year and numbers_of_arenas == m.numbers_of_arenas;}
    bool operator==(string &m) { return name ==m;}



    void randomFilling(int n) {
        name = "Мордовия Арена";
        sports_name = "Футблол, Алтимат, Волейбол";
        build_year = rand() % n * 1000 + 1;
        capacity = rand() % n * 10000 + 1;
        numbers_of_arenas = rand() % n + 1;
    }

    const char *getName() { return name; }

    int getYear_of_Bulding() { return build_year; }

    const void print() {

        cout << name << "\n";
        cout << sports_name << "\n";
        cout << build_year << "\n";
        cout << capacity << "\n";
        cout << numbers_of_arenas << "\n";

    }

    friend ostream &operator<<(ostream &s, const Stadium &M) {
        if (typeid(s) == typeid(ofstream)) {
            s << M.name << "\n";
            s << M.sports_name << "\n";
            s << M.build_year << "\n";
            s << M.capacity << "\n";
            s << M.numbers_of_arenas << "\n";
        } else {
            s << M.name << "\n";
            s << M.sports_name << "\n";
            s << M.build_year << "\n";
            s << M.capacity << "\n";
            s << M.numbers_of_arenas << "\n";
        }
        return s;
    }

    friend istream &operator>>(istream &s, Stadium &M) {
        if (typeid(s) == typeid(ifstream)) {
            char *Name;
            char dummy;

            s >> Name >> dummy;
            M = Stadium(Name);

            return s;
        }
    }
};

template<class T>
class Element
{
    //protected:
public:
    //переместить в protected
    Element* next;
    Element* prev;
    T info;

public:

    Element(T data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element* Next, Element* Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }

    Element(const Element& el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    void setPrev(Element* e) {
        prev = e;
    }

    void setNext(Element* e) {
        next = e;
    }

    Element<T>* getPrev() {
        return prev;
    }

    Element<T>* getNext() {
        return next;
    }

    T getInfo() { return info; }
    void setInfo(T value) { info = value; }

    template<class T1>
    friend ostream& operator<<(ostream& s, Element<T1>& el);

};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
    {
        s << el.info;
        return s;
    }


template<class T>
class LinkedList
{
protected:
    Element<T>* head;
    Element<T>* tail;
    int count;
public:

    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }

    //удалить первый/последний элемент и вернуть удаленное значение
    virtual Element<T>* pop() = 0;
    //добавить элемент в список
    virtual Element<T>* push(T value) = 0;

    //доступ по индексу
    virtual Element<T>& operator[](int index)
    {
        //if(index<0 || index>=count) throw ...;
        Element<T>* current = head;
        for (int i=0; current != NULL && i<index; current = current->next, i++);
        return *current;
    }

    template<class T1>
    friend ostream& operator<<(ostream& s, LinkedList<T1>& el);

    //доработать деструктор
    virtual ~LinkedList()
    {
        cout << "\nLinkedList destructor";

        Element<T>* previous = NULL;
        for (Element<T>* current = head; current != NULL; )
        {
            previous = current;
            current = current->next;
            delete previous;
        }
    }
};

template<class T1>
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
    Element<T1>* current = el.head;
    for (; current != NULL; current = current->next)
        s << *current << " ";
    return s;
}

template<class T>
class Stack : public LinkedList<T> {
protected:
    virtual Element<T> *findRecursive(T value, Element<T> *elem) {
        if (value.getName() == elem->getInfo().getName()) {
            return elem;
        }
        if (elem == NULL) {
            return NULL;
        }
        return findRecursive(value, elem->getNext());
    }

public:
    Stack<T>() : LinkedList<T>() {}

    virtual ~Stack() { cout << "\nStack destructor"; }

    virtual Element<T> *pop_end() {
        if (LinkedList<T>::tail == NULL) return NULL;
        Element<T> *res = LinkedList<T>::tail;
        if (LinkedList<T>::head == LinkedList<T>::tail) {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            LinkedList<T>::count = 0;
            return res;
        }
        Element<T> *current = LinkedList<T>::head;
        for (; current->next != LinkedList<T>::tail; current = current->next);
        current->next = NULL;
        LinkedList<T>::tail = current;
        LinkedList<T>::count--;
        return res;
    }

    virtual Element<T> *push_end(T value) {
        Element<T> *newElem = new Element<T>(value);
        if (this->tail != NULL) {
            this->tail->next = newElem;
            this->tail = this->tail->next;
        } else
            this->head = this->tail = newElem;
        this->count++;
        return this->tail;
    }
    //удалить из начала
    virtual Element<T>* pop() {
        if (LinkedList<T>::head == NULL) return NULL;
        Element<T>* res = LinkedList<T>::head;
        if (LinkedList<T>::tail == LinkedList<T>::head) {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            LinkedList<T>::count = 0;
            return res;
        }
        Element<T>* current = LinkedList<T>::head->getNext();
        //current->setPrev(NULL);
        res->setNext(NULL);
        LinkedList<T>::head = current;
        LinkedList<T>::count--;
        return res;
    }

    // добавить элемент в начало
    virtual Element<T>* push(T value) {
        Element<T>* newElement = new Element<T>(value);
        if (LinkedList<T>::head != NULL) {
            newElement->setNext(LinkedList<T>::head);
            //BaseLinkedList<T>::head->setPrev(newElement);
            LinkedList<T>::head = newElement;
        }
        else
            LinkedList<T>::head = LinkedList<T>::tail = newElement;
        LinkedList<T>::count++;
        return LinkedList<T>::head;
    }

    virtual Element<T> *insert(T value, Element<T> *previous = NULL) {
        if (previous == NULL)
            return push(value);

        Element<T> *inserted = new Element<T>(value);
        Element<T> *next = previous->next;
        previous->next = inserted;
        inserted->next = next;
        LinkedList<T>::count++;
        return inserted;
    }

    virtual Element<T> *remove(Element<T> *elem = NULL) {
        if (elem == NULL || (LinkedList<T>::head == LinkedList<T>::tail))
            return pop();
        Element<T> *removable = elem->getNext();
        Element<T> *next = removable->getNext();
        elem->setNext(next);
        removable->setNext(NULL);
        LinkedList<T>::count--;
        return removable;
    }

    virtual Element<T> *findRecursive(T value) {
        return findRecursive(value, LinkedList<T>::head);
    }

    virtual Element<T> *find(T value) {
        Element<T> *current = LinkedList<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (value.getName() == current->getInfo().getName()) {
                return current;
            }
        }
        return NULL;
    }

protected:
    Stack<T> filterYearMore(int year) {
        Stack<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (current->getInfo().getYear_of_Bulding() > year)
                res.push(current->getInfo());
        }
        return res;
    }

    Stack<T> filterYearLess(int year) {
        Stack<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (current->getInfo().getYear_of_Bulding() < year)
                res.push(current->getInfo());
        }
        return res;
    }

public:
    Stack<T> filterYear(int year, bool more = 1) {
        if (more) {
            return filterYearMore(year);
        }
        return filterYearLess(year);
    }

    Stack<T> filter(bool (*func)(T)) {
        Stack<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (func(current->getInfo()))
                res.push(current->getInfo());
        }
        return res;
    }

    template<typename T1>
    friend istream &operator>>(istream &s, Stack<T1> &el) {
        if (typeid(s) == typeid(ifstream)) {
            int len;
            s >> len;
            for (int i = 0; i < len; i++) {
                T value;
                s >> value;
                el.push(value);
            }
            return s;
        }
        T value;
        s >> value;
        el.push(value);
        return s;
    }

    virtual ostream &save(ostream &s) {
        return operator<<(s, *this);
    }

    virtual istream &load(istream &s) {
        return operator>>(s, *this);
    }
};

/*class my_class
{
public:
    int x;
    my_class() { x = 0; cout << "\nmy_class constructor 0"; }
    ~my_class() {cout << "\nmy_class destructor"; }
    my_class(int a) { x = a; cout << "\nmy_class constructor 1"; }
    my_class(const my_class& m) { x = m.x; cout << "\nmy_class copy constructor"; }
};*/

template<class T>
class DoubleSidedLinkedList : public Stack<T> {
public:
    DoubleSidedLinkedList<T>() : Stack<T>() {}

    DoubleSidedLinkedList(T *arr, int len) {
        for (int i = 0; i < len; i++) {
            push(arr[i]);
        }
    }

    DoubleSidedLinkedList(const DoubleSidedLinkedList &L) {
        Stack<T>::count = L.Stack<T>::count;
        for (Element<T> *current = L.Stack<T>::head; current != NULL;) {
            Element<T> *next = current->getNext();
            push(current->getInfo());
            current = next;
        }
    }

    DoubleSidedLinkedList operator=(const DoubleSidedLinkedList &L) {
        Stack<T>::count = L.Stack<T>::count;
        Element<T> *previous = NULL;
        for (Element<T> *current = Stack<T>::head; current != NULL;) {
            previous = current;
            current = current->getNext();
            delete previous;
        }
        for (Element<T> *current = L.Stack<T>::head; current != NULL;) {
            Element<T> *next = current->getNext();
            push(current->getInfo());
            current = next;
        }
        return *this;
    }

    virtual ~DoubleSidedLinkedList() { cout << "\nDoubleSidedLinkedList destructor.\n"; }

    virtual Element<T> *push(T value) {
        Element<T> *head_before = Stack<T>::head;
        Stack<T>::push(value);
        if (head_before != NULL)
            head_before->setPrev(Stack<T>::head);
        Stack<T>::head->setPrev(NULL);
        return Stack<T>::head;
    }

    virtual Element<T> *pop() {
        if (Stack<T>::head == Stack<T>::tail)
            return Stack<T>::pop();
        Element<T> *newHead = Stack<T>::head->getNext();
        Element<T> *res = Stack<T>::head;
        newHead->setPrev(NULL);
        Stack<T>::head->setNext(NULL);
        Stack<T>::head = newHead;
        Stack<T>::count--;
        return res;
    }

    virtual Element<T> *insert(T value, Element<T> *previous = NULL) {
        if (previous == NULL) {
            return push(value);
        }
        Element<T> *inserted = Stack<T>::insert(value, previous);
        inserted->setPrev(previous);
        inserted->getNext()->setPrev(inserted);
        return inserted;
    }

    virtual Element<T> *remove(Element<T> *elem = NULL) {
        if (elem == NULL || (Stack<T>::head == Stack<T>::tail))
            return pop();
        Element<T> *removable = elem->getNext();
        Element<T> *next = removable->getNext();
        elem->setNext(next);
        next->setPrev(elem);
        Stack<T>::count--;
        removable->setPrev(NULL);
        removable->setNext(NULL);
        return removable;
    }

protected:
    DoubleSidedLinkedList<T> filterYearMore(int year) {
        DoubleSidedLinkedList<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (current->getInfo().getYear_of_Bulding() > year) {
                res.push(current->getInfo());
            }
        }
        return res;
    }

    DoubleSidedLinkedList<T> filterYearLess(int year) {
        DoubleSidedLinkedList<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (current->getInfo().getYear_of_Bulding() < year)
                res.push(current->getInfo());
        }
        return res;
    }

public:

    DoubleSidedLinkedList<T> filterYear(int year, bool more = 1) {
        Element<T> *current = Stack<T>::head;
        if (more) {
            return filterYearMore(year);
        }
        return filterYearLess(year);
    }

    DoubleSidedLinkedList<T> filter(bool (*func)(T)) {
        DoubleSidedLinkedList<T> res;
        Element<T> *current = Stack<T>::head;
        for (; current != NULL; current = current->getNext()) {
            if (func(current->getInfo()))
                res.push(current->getInfo());
        }
        return res;
    }

    friend ostream &operator<<(ostream &s, const DoubleSidedLinkedList<T> &el) {
        if (typeid(s) == typeid(ofstream)) {
            s << el.count << " ";
        }
        Element<T> *current = el.tail;
        for (; current != NULL; current = current->getPrev())
            s << *current << " ";
        return s;
    }

    friend istream &operator>>(istream &s, DoubleSidedLinkedList<T> &el) {
        if (typeid(s) == typeid(ifstream)) {
            int len;
            s >> len;
            for (int i = 0; i < len; i++) {
                T value;
                s >> value;
                el.push(value);
            }
            return s;
        }
        T value;
        s >> value;
        el.push(value);
        return s;
    }

    virtual ostream &save(ostream &s) {
        return operator<<(s, *this);
    }

    virtual istream &load(istream &s) {
        return operator>>(s, *this);
    }


};
string t="Мордовия Арена";
bool isMordovia(Stadium m) { return m.getName() == t;}
ostream& myManip(ostream& out) {
    out << hex << setw(60) << right<<endl;
    return out;
}

int main()
{

    /*Stack<int> S;
    for (int i = 0; i < 100; i += 10)
        S.push(i);
    cout << S<<"\n";*/
    /*Element<int>* current = S.pop();
    while (current != NULL)
    {
        cout << *current << " ";
        delete current;
        current = S.pop();
    }*/

    //LinkedList<int>* ptr = new DoubleSidedStack<int>;
    /*DoubleSidedLinkedList<int> ds;
    for (int i = 0; i < 100; i += 10)
        ds.push(i);
    Element<int>* ptr = &ds[3];
    ds.insert(-100, ptr);
    //cout<<"\nPop(): "<<*(ds.pop())<<"\n";
    cout << ds << "\n";*/
    //delete ptr;


    int n =5;
    Stadium *arr = new Stadium[n];
    for (int i=0;i<n;i++){
        Stadium s;
        s.randomFilling(10);
        arr[i]=s;
    }
    DoubleSidedLinkedList<Stadium> s(arr,10);
    Stadium m;
    m.randomFilling(56);

    //filter

    cout << s << endl;

    DoubleSidedLinkedList<Stadium> s1 = s.filterYear(5,1);
    cout << s1;
    bool(*fptr)(Stadium) = isMordovia;
    DoubleSidedLinkedList<Stadium> s2 = s.filter(fptr);
    cout << s2;
    // remove
    Element<Stadium>* ptr = &s[5];
    s.remove(ptr);
    cout << s << endl;

    // find
    cout << (ptr->getInfo()) << endl;
    cout << *(s.find(ptr->getInfo()));
    // push, pop
    Stadium m1;
    m1.randomFilling(50);
    s.push(m1);
    cout << s << endl;

    s.pop();
    cout << s << endl;


    // dynamic_cast
    LinkedList<Stadium>* arr1 = new DoubleSidedLinkedList<Stadium>;
    delete arr1;
    arr1 = new DoubleSidedLinkedList<Stadium>;
    arr1 = dynamic_cast<LinkedList<Stadium>*>(arr1);
    delete arr1;

    // save, load
    ofstream file("test.txt");
    s.save(file);
    file.close();
    ifstream input("test.txt");
    DoubleSidedLinkedList<Stadium> s3;
    s3.load(input);
    cout << s3;

    input.close();


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