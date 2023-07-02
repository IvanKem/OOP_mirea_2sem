/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// Complex.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include <iostream>
#include <math.h>

using namespace std;

class Complex
{
private:
    double real;
    double image;
public:
    //êîíñòðóêòîð Complex z;
    Complex() {real = 0; image = 0;}
    Complex(double r , double im) {real = r; image = im;}
    Complex(double r) {real = r; image = 0;}

    void print()
    {
        if (image == 0)
        {
            cout << "\n" << real << "\n";
            return;
        }
        if (real == 0)
        {
            cout << "\n" << image << "i\n";
            return;
        }
        if (image > 0)
            cout << "\n" << real << " + " << image << "i\n";
        else
            cout << "\n" << real << " - " << -image << "i\n";
    }

    double getReal() {return real;}
    double getImage() {return image;}

    void SetReal(double value) { real = value; }
    void SetImage(double value) { image = value; }

    double Module() {return sqrt(real*real + image*image);}

    Complex add(Complex z)
    {
        Complex res;
        res.real= real + z.real;
        res.image= image + z.image;
        return res;
    }

    Complex add(int z)
    {
        Complex res;
        res.real= real + z;
        res.image= image;
        return res;
    }

    Complex operator+(Complex z)
    {
        Complex res;
        res.real= real + z.real;
        res.image= image + z.image;
        return res;
    }

    Complex operator+(int z)
    {
        Complex res;
        res.real= real + z;
        res.image= image;
        return res;
    }

    Complex operator+()
    {
        Complex res;
        res.real= real;
        res.image= -image;
        return res;
    }

    Complex operator-()
    {
        Complex res;
        res.real= -real;
        res.image= -image;
        return res;
    }

    bool operator==(Complex z)
    {
        return (real == z.real && image == z.image);
    }

    bool operator!=(Complex z)
    {
        return (real != z.real || image != z.image);
    }

    Complex operator=(Complex z)
    {
        real = z.real;
        image = z.image;
        return *this;
    }
    Complex operator=(double z)
    {
        real= z;
        image= 0;
        return *this;
    }

    Complex operator++()
    {
        real++;
        image++;
        return *this;
    }

    Complex operator++(int notused)
    {
        real++;
        return *this;
    }

    friend Complex operator+(double d,Complex z);

};


Complex operator+(double d,Complex z)
{
    Complex res;
    res.real= d + z.real;
    res.image= z.image;
    return res;
}
/*
Complex operator+(double d, Complex z)
	{
	    Complex res(d+z.getReal(),z.getImage());
	    return res;
	}
*/
int main()
{
    //Complex Z(1, 1);
    //Complex W(1, -1);
    //Complex H = Z + W;
    Complex H; H.SetReal(1); H.SetImage(-1);
    Complex W; W.SetReal(1); W.SetImage(-3);
    //Complex U; U=H+W; U.print();
    Complex X; X=H+5;X.print();(++X).print();
    cout << "\n" << (W!=H) << "\n";



    //H.print();

    char c; cin>>c;
    return 0;
}

