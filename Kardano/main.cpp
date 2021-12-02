#include <iostream>
#include <locale.h>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

struct answer
{
    double first;
    double second;
};

double croot(double x)
{
    if (x < 0)
        return -pow(-x, 1.0/3.0);
    return pow(x, 1.0/3.0);
}

void kardano(double A, double B, double C, double D)
{
    answer x1,x2,x3;
    double p=0,q=0;
    double pi = 3.141592653589793;

    //простейший случай
    if(B==0 && C==0 && D!=0 && A!=0){
        cout << "Х = " << croot(D) << endl;
        return;
    }

    p=(3.0*A*C-B*B)/(3.0*A*A);
    q=(2.0*B*B*B-9.0*A*B*C+27.0*A*A*D)/(27.0*A*A*A);
    double S = (q*q/4.0) + (p*p*p/27.0);

    double F;
    if (q == 0)
        F = pi/2.0;
    if (q < 0)
        F = atan(-2.0*sqrt(-S)/q);
    if (q > 0)
        F = atan(-2.0*sqrt(-S)/q) + pi;

    x1.first=0;
    x1.second=0;
    x2.first=0;
    x2.second=0;
    x3.first=0;
    x3.second=0;

    if (S < 0)
    {
        x1.first = 2.0*sqrt(-p/3.0)*cos(F/3.0)-B/(3.0*A);
        x2.first = 2.0*sqrt(-p/3.0)*cos((F/3.0)+2.0*pi/3.0)-B/(3.0*A);
        x3.first = 2.0*sqrt(-p/3.0)*cos((F/3.0)+4.0*pi/3.0)-B/(3.0*A);
    }
    if (S == 0)
    {
        x1.first = 2.0*croot(-q/2.0)-B/(3.0*A);
        x2.first = -croot(-q/2.0)-B/(3.0*A);
        x3.first = -croot(-q/2.0)-B/(3.0*A);
    }
    if (S > 0)
    {
        double temp1 = croot((-q/2.0)+sqrt(S)) + croot((-q/2.0)-sqrt(S));
        double temp2 = croot((-q/2.0)+sqrt(S)) - croot((-q/2.0)-sqrt(S));
        x1.first = temp1 - B/(3.0*A);
        x2.first = -temp1/2.0 - B/(3.0*A);
        x2.second = sqrt(3)*temp2/2.0;
        x3.first = -temp1/2.0 - B/(3.0*A);
        x3.second = -sqrt(3)*temp2/2.0;
    }

    bool check2=false;
    int boob=0;
    while (check2==false)
    {
        cout << "Выберите способ вывода:\n1 - На экран\n2 - В файл" << endl;
        cin >> boob;
        if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
        if(boob==1 || boob==2)
            check2=true;
        else
            cout << "Неверный ввод\n" << endl;
    }



    x1.second = (int)(x1.second*100000)/100000.;
    x2.first = (int)(x2.first*1000000)/1000000.;
    x2.second = (int)(x2.second*1000000)/1000000.;
    x3.first = (int)(x3.first*1000000)/1000000.;
    x3.second = (int)(x3.second*1000000)/1000000.;

    if(boob==1)
    {
        cout << endl;
        //
        cout << "x1 = " << x1.first;
        //
        if(x1.second!=0)
        {
            if (x1.second>0)
                cout << " + " << " + " << x1.second << "*i" << endl;
            else
                cout << " - " << (x1.second*(-1)) << "*i" << endl;
        }
        else
            cout << endl;

        cout << "x2 = " ;
        //
        cout << x2.first;
        //
        if(x2.second!=0)
        {
            if (x2.second>0)
                cout << " + " << x2.second << "*i" << endl;
            else
                cout << " - " << (x2.second*(-1)) << "*i" << endl;
        }
        else
            cout << endl;

        cout << "x3 = ";
        //
        cout << x3.first;
        //
        if(x3.second!=0)
        {
            if (x3.second>0)
                cout << " + " << x3.second << "*i" << endl;
            else
                cout << " - " << (x3.second*(-1)) << "*i" << endl;
        }
        else
            cout << endl;
        if(x2.first==x3.first && x2.second==0 && x3.second==0)
            cout << "Корни Х2 и Х3 совпадают" << endl;
    }

    if(boob==2)
    {
        ofstream out;          // поток для записи
        out.open("output.txt"); // окрываем файл для записи
        if (out.is_open())
        {
            out << "x1 = " << x1.first;
            if(x1.second!=0)
            {
                if (x1.second>0)
                out << " + " << x1.second << "*i" << endl;
                else
                out << " - " << (x1.second*(-1)) << "*i" << endl;
            }
            else
                out << endl;

            out << "x2 = " << x2.first;
            if(x2.second!=0)
            {
                if (x2.second>0)
                out << " + " << x2.second << "*i" << endl;
                else
                out << " - " << (x2.second*(-1)) << "*i" << endl;
            }
            else
                out << endl;

            out << "x3 = " << x3.first;
            if(x3.second!=0)
            {
                if (x3.second>0)
                out << " + " << x3.second << "*i" << endl;
                else
                out << " - " << (x3.second*(-1)) << "*i" << endl;
            }
            else
                out << endl;


            //if(x2.first==x3.first && x2.second==0 && x3.second==0);
            //out << "Корень Х2 является двойным вещественным корнем" << endl;

        }
        cout << "\nРезультат записан в файл output.txt, он находится в корневой папке программы" << endl;
        cout << "Работа программы завершена" << endl;
    }
}

void vvod(double &A, double &B,double &C,double &D)
{
    bool check2=false;
    int boob=0;
    while (check2==false)
    {
        cout << "Выберите способ ввода:\n1 - С клавиатуры\n2 - Считать из файла" << endl;
        cin >> boob;
        if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            cin.clear(); // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
        }
        if(boob==1 || boob==2)
            check2=true;
        else
            cout << "Неверный ввод" << endl;
    }

    if(boob==1)
    {
        check2=false;
        while (check2==false)
        {
            cout << "Введите коэффициенты уравнения:" << endl;
            cout << "A = ";
            cin >> A;
            if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
            {
                cin.clear(); // то возвращаем cin в 'обычный' режим работы
                cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "\nНекорректный ввод!" << endl;
                continue;
            }
            cout << "B = ";
            cin >> B;
            if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
            {
                cin.clear(); // то возвращаем cin в 'обычный' режим работы
                cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "\nНекорректный ввод!" << endl;
                continue;
            }
            cout << "C = ";
            cin >> C;
            if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
            {
                cin.clear(); // то возвращаем cin в 'обычный' режим работы
                cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "\nНекорректный ввод!" << endl;
                continue;
            }
            cout << "D = ";
            cin >> D;
            if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
            {
                cin.clear(); // то возвращаем cin в 'обычный' режим работы
                cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
                cout << "\nНекорректный ввод!" << endl;
                continue;
            }


            if(A==0 && B==0 && C==0 && D==0)
                cout << "Все коэффициенты равны нулю! Повторите ввод." << endl;
            if(A!=0 && (B!=0 || C!=0 || D!=0))
                check2=true;
            if(check2==false)
                cout << "Уравнение не является кубическим. Нулевые значения более двух коэффициентов недопустимы" << endl;
        }
    }

    if(boob==2)
    {
        ifstream input("input.txt");
        double ch;
        int Count = 0;
        while (input >> ch)
            Count++;
        if(Count == 4)
            cout << "Коэффициентов в файле : 4. Верный формат." << endl;
        else
        {
            cout << "Коэффициентов в файле : " << Count << " - Ошибка считывания. Введите 4 коэффециента, каждый с новой строки." << endl;
            return;
        }

        input.close();

        ifstream file("input.txt");
        file>>A;
        file>>B;
        file>>C;
        file>>D;
        input.close();
    }

    cout << "\nВведенное уравнение:" << endl;
    cout << A << "*X^3" ;
    if (B!=0){
            if(B>0)
                cout << "+" << B;
            else
                cout << B;
            cout << "*X^2" ;
    }
    if (C!=0){
            if(C>0)
                cout << "+" << C;
            else
                cout << C;
            cout << "*X" ;
    }
    if (D!=0){
            if(D>0)
                cout << "+" << D;
            else
                cout << D;
    }
    cout << "=0" << endl << endl;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    double A=0,B=0,C=0,D=0,r2=0,q3=0;
    double cel=0,komp=0;
    bool check=false;
    cout << "=============================================================" << endl;
    cout << "=Начало работы с программой для решения кубических уравнений=" << endl;

    vvod(A,B,C,D);
    if (A==0 && B==0 && C==0 && D==0)
        return 0;
    kardano(A,B,C,D);

    return 0;
}
