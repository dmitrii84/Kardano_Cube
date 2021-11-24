#include <iostream>
#include <locale.h>
#include <math.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");
    double A,B,C,D,q,r,r2,q3;
    double x[3];
    double pi = 3.141592653589793;

    cout << "Начало работы с программой для решения кубических уравнений" << endl;
    cout << "Введите коэффициенты уравнения:" << endl;
    cout << "A = ";
    cin >> A;
    cout << "B = ";
    cin >> B;
    cout << "C = ";
    cin >> C;
    cout << "D = ";
    cin >> D;

    q=(A*A-3*B)/9.;
    r=(2*A*A*A-9*A*B+27*C)/54;
    r2=r*r;
    q3=q*q*q;

    //Три действительных корня
    if(r2<q3) {
        double t=acos(r/sqrt(q3))/3;
        x[0]=-2*sqrt(q)*cos(t)-A/3;
        x[1]=-2*sqrt(q)*cos(t+(2*pi/3))-A/3;
        x[2]=-2*sqrt(q)*cos(t-(2*pi/3))-A/3;
        cout << "X1 = " << x[0] << endl;
        cout << "X2 = " << x[1] << endl;
        cout << "X3 = " << x[2] << endl;
    }

    // Один действительный корень и 2 комплексных
    else {
        double aa,bb;

        if(r<0)
            r=-r;
        aa=-pow(r+sqrt(r2-q3),1/3);

        if(aa!=0)
            bb=q/aa;
        else bb=0;

        x[0]=(aa+bb)-A/3;
        cout << "X1 = " << x[0] << endl;
        if (aa==bb)
        {
            x[1]=-aa-A/3;
            cout << "X2 = X3 = " << x[1] << endl;
        }
        else
        {
        double cel = -(aa+bb)/2-A/3;
        double komp = sqrt(3)*(A-B)/2;

        cout << "X2 = " << cel << " + i*" << komp << endl;
        cout << "X3 = " << cel << " - i*" << komp << endl;
        }
 }
    return 0;
}
