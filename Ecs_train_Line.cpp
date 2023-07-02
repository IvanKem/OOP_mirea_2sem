//
// Created by iv.kem on 7/2/23.
//

#include <iostream>
#include <cmath>
using namespace std;

class Line{
private:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    Line( const Line & P){
        x1=P.x1;
        y1=P.y2;
        x2=P.y2;
        y2=P.y2;
    };

    Line(int a, int b, int  c, int d) : x1(a),y1(b),x2(c),y2(d){};

    Line():x1(0),y1(0),x2(0),y2(0){};

    ~Line(){};


    Line operator+(int n) const{
        Line res;
        res.x1=x1+n;
        res.y1=y1+n;
        res.x2=x2+n;
        res.y2=y2+n;
        return res;

    }
    double operator+() const{
        return sqrt((x2-x1)*(x2-x1)-(y2-y1)*(y2-y1));
    }

    friend ostream& operator<<(ostream& ustream, const Line & P ){
        ustream <<'('<< P.x1<<", " <<P.y1<<')'<< '('<< P.x2<<", " <<P.y2<<')'<<endl;
        return ustream;
    };



};

int main(){
    Line P(1,1,3,1);

    cout<<+P<<endl;
    cout<< P+3<< endl;
}