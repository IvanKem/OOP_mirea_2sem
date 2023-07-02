//
// Created by iv.kem on 7/2/23.
//

#include <iostream>
#include <cmath>
using namespace std;

class Polynom{
private:
    int a;
    int b;
    int c;
public:
    Polynom( const Polynom & P){
        a=P.a;
        b=P.b;
        c=P.c;
    };

    Polynom(int a, int b, int  c) : a(a),b(b),c(c){};

    Polynom():a(0),b(0),c(0){};

    ~Polynom(){};


    double operator+() const{
        double k1 = (-b+ sqrt(b*b-4*a*c))/(2*a);
        double k2 = (-b- sqrt(b*b-4*a*c))/(2*a);
        return k2>=k1 ? k2 : k1;
    }
    Polynom operator+(const Polynom & P) const{
        Polynom res;
        res.a=a+P.a;
        res.b=b+P.b;
        res.c=c+P.c;
        return res;
    }

    friend ostream& operator<<(ostream& ustream, const Polynom & P ){
        ustream << P.a<<" " << P.b<< " " << P.c;
        return ustream;
    };



};

int main(){
    Polynom P(1,-12,36);
    Polynom P2(1,1,1);
    cout<<+P<<endl;
    cout<< (P+P2)<< endl;
}