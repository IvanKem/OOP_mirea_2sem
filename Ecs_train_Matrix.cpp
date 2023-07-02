//
// Created by iv.kem on 7/2/23.
//

#include <iostream>
#include <cmath>
using namespace std;

class Matrix{
private:
    int a11;
    int a12;
    int a21;
    int a22;
public:
    Matrix( const Matrix & P){
        a11=P.a11;
        a12=P.a12;
        a21=P.a21;
        a22=P.a22;
    };

    Matrix(int a, int b, int  c, int d) : a11(a),a12(b),a21(c),a22(d){};

    Matrix():a11(0),a12(0),a21(0),a22(0){};

    ~Matrix(){};


    bool operator<(const Matrix & P) const{
        return a11*a22<P.a11*P.a22;

    }
    double operator+() const{
        return a11*a22;
    }

    friend ostream& operator<<(ostream& ustream, const Matrix & P ){
        ustream <<'('<< P.a11<<", " <<P.a12<<')'<< '('<< P.a21<<", " <<P.a22<<')'<<endl;
        return ustream;
    };



};

int main(){
    Matrix P(1,1,3,2);
    Matrix P1(1,1,3,3);

    cout<<+P<<endl;
    bool res =P<P1;
    cout<<res <<endl;
}
/*struct Vector
{
    public double X { get; }
    public double Y { get; }

    public Vector(double x, double y)
    {
        X = x; Y = y;
    }

    public static readonly Vector Reference = new Vector(1, 0);

    // Угол в градусах относительно опорного, возвращает значение из диапазона (-180°; 180°]
    public static double AngleOfReference(Vector v)
        => Math.Atan2(v.Y, v.X) / Math.PI * 180; !!!!!!!!!!!!!!!!!!!!!!<<<<<<<<<<<<<<<<<<
}*/