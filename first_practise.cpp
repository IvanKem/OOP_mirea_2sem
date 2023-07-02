//
// Created by iv.kem on 2/19/23.
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

    Complex operator/(Complex z)
    {
        Complex res;
        res.real= (real*z.real+image*z.image)/(z.image*z.image+z.real*z.real);
        res.image= (image*z.real-real*z.image)/(z.image*z.image+z.real*z.real);
        return res;
    }

    Complex operator/(int z)
    {
        Complex res;
        res.real= real/z;
        res.image= image/z;
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
        res.real= sqrt(real*real + image*image)+real;
        res.image= sqrt(real*real + image*image)+image;
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
    friend Complex operator/(double d,Complex z);
};


Complex operator+(double d,Complex z)
{
    Complex res;
    res.real= d + z.real;
    res.image= z.image;
    return res;
}

Complex operator/(double d, Complex z) {
    Complex res;
    res.real= (d*z.real+0*z.image)/(z.image*z.image+z.real*z.real);
    res.image= (0*z.real-d*z.image)/(z.image*z.image+z.real*z.real);
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
    Complex H; H.SetReal(-2); H.SetImage(1);
    Complex W; W.SetReal(1); W.SetImage(-1);
    //Complex U; U=H+W; U.print();
    //Complex X; X=H+5;X.print();(++X).print();
    cout << "\n" << "Унарный плюс" << "\n";
    cout << "\n" << (H.Module()) << "\n";
    H.print();(+H).print();
    cout << "\n" << "Деление на комплексное " << "\n";
    H.print(); W.print();
    cout << "\n" << "Результат" << "\n";
    (H/W).print();
    cout << "\n" << "Деление на действительное(2) " << "\n";
    (H/2).print();
    cout << "\n" << "Деление действительного(2) на комплексное " << "\n";
    (2/H).print();

    char c; cin>>c;
    return 0;
}

