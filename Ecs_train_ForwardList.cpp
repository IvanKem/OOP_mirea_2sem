//
// Created by iv.kem on 7/2/23.
//
//
#include <iostream>
#include <exception>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;



class Exception : public exception
{
protected:
    //сообщение об ошибке
    char* str;
public:
    Exception(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    Exception(const Exception& e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }

    //функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
    virtual void print()
    {
        cout << "Exception: " << str << "; " << what();
    }
};

class InvalidOperationException : public Exception {
public:
    InvalidOperationException(const char* s, int width, int height) : Exception(s) {}
    InvalidOperationException(const InvalidOperationException& e) : Exception(e) {}

    virtual void print() {
        cout << "InvalidOperationException: " << str << what();
    }
};



class IndexOutOfBoundsException : public Exception {
    int count;
public:
    IndexOutOfBoundsException(const char* s, int Count) : Exception(s) { count = Count ;}
    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { count= e.count;}

    virtual void print() {
        cout << "IndexOutOfBoundsException: " << str << "; count: " <<count << what();
    }
};




class NonPositiveIndexExceptionArray : public IndexOutOfBoundsException {
public:
    NonPositiveIndexExceptionArray(const char* s,int Count) : IndexOutOfBoundsException(s, Count) {}
    virtual void print() {
        cout << "NonPositiveSizeExceptionArray: " << str << "<0"<< what();
    }
};


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
class Forwardlist: public LinkedList<T> {
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
    Forwardlist<T>() : LinkedList<T>() {}

    virtual ~Forwardlist() { cout << "\nStack destructor"; }/*

    Forwardlist()
    {
        head = tail = NULL;
        count = 0;
    }
    */
    virtual Element<T>& operator[](int index)
    {
        if(index>=LinkedList<T>::count) throw IndexOutOfBoundsException("Неправильный индекс",index);
        if (index<0 ) throw NonPositiveIndexExceptionArray((char*)LinkedList<T>::count,index);
        Element<T>* current = LinkedList<T>::head;
        for (int i=0; current != NULL && i<index; current = current->next, i++);
        return *current;
    }

    virtual Element<T> *pop_end() {
        if (LinkedList<T>::tail == NULL) return NULL;
        Element<T> *current = LinkedList<T>::tail;
        if (LinkedList<T>::head == LinkedList<T>::tail == NULL) {

            return current;
        }


        current->next = NULL;
        LinkedList<T>::tail = LinkedList<T>::head->getNext();
        LinkedList<T>::count--;
        return current;
    }


    virtual Element<T> *push_stay_monoton(T value) {
        Element<T> *newElem = new Element<T>(value);
        if (LinkedList<T>::head == NULL) return NULL;

        else {
            Element<T> *current = LinkedList<T>::head->getNext();
            if (current == NULL) {
                newElem->setNext(current);
                return newElem;
            }
            else {
                for (; current != LinkedList<T>::head && value.getName() <= current->getInfo().getName(); current = current->getNext()) {
                    if (value.getName() > current->getInfo().getName()) {
                        newElem->setNext(current->getNext());
                        current->setNext(newElem);
                    }
                    return newElem;
                }
            }
            return NULL;
        }
    }

    virtual Element<T> *find(T value) {
        if (LinkedList<T>::head == NULL) return NULL;
        Element<T> *current = LinkedList<T>::head->getNext();
        for (; current != LinkedList<T>::head; current = current->getNext()) {
            if (value.getName() == current->getInfo().getName()) {
                return current;
            }
        }
        return NULL;
    }

    virtual Element<T> *predessesor(Element<T> & Tek ) {
        if (LinkedList<T>::head == NULL) return NULL; //throw
        if (LinkedList<T>::head == Tek ) return NULL;
        Element<T> *current = LinkedList<T>::head;
        for (; current != LinkedList<T>::tail && current->getNext()!=Tek; current = current->getNext()) {
            if (current->getNext()==Tek) {
                return current;
            }
        }
        return NULL;
    }
    virtual Element<T> *reverse_find(T  & value ) {
        if (LinkedList<T>::head == NULL) return NULL; //throw
        if (LinkedList<T>::head->getInfo().getName() ==value.getName() ) return LinkedList<T>::head;
        Element<T> *current = LinkedList<T>::tail;
        for (; current != LinkedList<T>::head && predessesor(current)->getInfo().getName()!=value.getName(); current = predessesor(current)) {
            if (predessesor(current)->getInfo().getName()==value.getName()) {
                return current;
            }
        }
        return NULL;
    }


    template<typename T1>
    friend istream &operator>>(istream &s, Forwardlist<T1> &el) {
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

int main(){
    try{}
    catch (NonPositiveIndexExceptionArray & e) {
        cout << "\nCaught: "; e.print();
    }
    catch (IndexOutOfBoundsException & e) {
        cout << "\nCaught: "; e.print();
    }

    catch (Exception& e) {
        cout << "\nCaught: "; e.print();
    }
    catch (exception& e) {
        cout << "\nCaught: "; cout << e.what();
    }

    return 0;
}