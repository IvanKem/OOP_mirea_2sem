// MultInherit.cpp:
//

#include <iostream>


using namespace std;

class A1
{
protected:
	int a1;
public:
	A1() { a1 = 0; cout << "\nA1 default constructor " << a1 << "\n"; }
	A1(int b) { a1 = b; cout << "\nA1 constructor " << a1 << "\n"; }
	~A1() { cout << "\nA1 destructor"; }

    virtual void print() {cout<<"\nVarible of A1 class ";};
    virtual void Show() {cout<<"\na1="<<a1;};

};

class B1 : virtual public A1
{
protected:
	int b1;
public:
	B1(int D, int b) : A1(b)
	{
		b1 = D; cout << "\nB1 constructor " << b1 << "\n";
	}

    virtual void print() {cout<<"\nVarible of B1 class ";};
    virtual void Show() { cout << "\nb1=" << b1 << "\ta1=" << a1; };
};

class B2 : virtual public A1
{
protected:
	int b2;
public:
	B2(int D, int b) : A1(b)
	{
		b2 = D; cout << "\nB2 constructor " << b2 << "\n";
	}
    virtual void print() {cout<<"\nVarible of B2 class ";};
    virtual void Show() { cout << "\nb1=" << b2 << "\ta1=" << a1; };
};

class C1 : virtual public B1,  virtual public B2
{
private:
	int c1;
public:
	C1(int D, int b1, int b2) : B1(D, b1), B2(D, b2)
	{
		c1 = D; cout << "\nC1 constructor " << c1 << "\n";
	}
    virtual void print() {cout<<"\nVarible of C1 class ";};
    virtual void Show() { cout << "\nb1=" << b1 << "\tb2=" << b2 << "\ta1=" << a1 << "\tc1=" << c1; };
};

class C2 : virtual public B1,  virtual public B2
{
private:
    int c2;
public:
    C2(int D, int b1, int b2) : B1(D, b1), B2(D, b2)
    {
        c2 = D; cout << "\nC1 constructor " << c2 << "\n";
    }
    virtual void print() {cout<<"\nVarible of C2 class ";};
    virtual void Show() { cout << "\nb1=" << b1 << "\tb2=" << b2 << "\ta1=" << a1 << "\tc2=" << c2; };
};

class C3 : virtual public B1,  virtual public B2
{
private:
    int c3;
public:
    C3(int D, int b1, int b2) : B1(D, b1), B2(D, b2)
    {
        c3 = D; cout << "\nC1 constructor " << c3 << "\n";
    }
    virtual void print() {cout<<"\nVarible of C3 class ";};
    virtual void Show() { cout << "\nb1=" << b1 << "\tb2=" << b2 << "\ta1=" << a1 << "\tc3=" << c3; };
};


int main()
{

	B1 b1(1, 2);
	B2 b2(3, 4);

	C1 c1(11,12,13);
    C2 c2(21,22,23);
    C3 c3(31,32,33);
    A1* a; //Указатель на базовый класс

    a=&b1; a->print();a->Show();//Адресация на b1
    a=&b2; a->print();a->Show();//Адресация на b2
    a=&c1; a->print();a->Show();//Адресация на c1
    a=&c2; a->print();a->Show();//Адресация на c2
    a=&c3; a->print();a->Show();//Адресация на c3

	char c; cin>>c;
	return 0;
}

