#include <vector>
#include <complex>
#include <bits/stdc++.h>
using namespace std;

//---------------------------------------------------------------------------------------
// ある値での多項式の値の計算
complex<float> polynomial_value( int order, vector<float> coefficient, complex<float> value )
{
    int term_size = coefficient.size(); // 多項式の項の数
    complex<float> result; // ある値での多項式の値
    complex<float> term; // 各項の値

    // ある値での多項式の値を求めるループ
    for ( int term_number=0; term_number<term_size; term_number++ )
    {
        term = term + coefficient[term_number] * pow( value, order-term_number ); 
    }
    result = term;

    return result;
}




