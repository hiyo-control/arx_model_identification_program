#include <vector>
#include <complex>
#include <bits/stdc++.h>
using namespace std;

//---------------------------------------------------------------------------------------
// ある値での多項式の導関数の導出
complex<float> polynomial_derivative( int order, vector<float> coefficient, complex<float> value )
{
    int term_size = coefficient.size() - 1; // 多項式の項の数
    complex<float> result; // ある値での多項式の導関数
    complex<float> term; // 各項の値

    // ある値での多項式の導関数を求めるループ
    for ( int term_number=0; term_number<term_size; term_number++ )
    {
        term = term + coefficient[term_number] * ( order-term_number ) * pow( value, order-term_number-1 ); 
    }
    result = term;

    return result;
}