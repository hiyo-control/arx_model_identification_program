#include <vector>
#include <complex>
#include <bits/stdc++.h>

#include "4_zero_pole_calculation_function.h"

using namespace std;

const double  pi = acos(-1);

//---------------------------------------------------------------------------------------
// 多項式の根の計算
vector< complex<float> > polynomial_roots_calculation( int order, vector<float> coefficient )
{
    vector< complex<float> > result( order ); // 多項式の根
    complex<float> value;                     // 多項式の値
    complex<float> derivative;                // 多項式の導関数

    // 初期条件のパラメータ
    float a1 = coefficient[1];
    float a0 = coefficient[0];
    float  R = 100;
    int    n = order;

    // 多項式の根の導出
    for ( int root_number=0; root_number<order; root_number++ )
    {
        // 初期値の計算
        float initial_real = -a1/(n*a0) + R*cos( 2*pi/n*(root_number-3/4) );
        float initial_imag =              R*sin( 2*pi/n*(root_number-3/4) );
        complex<float> initial( initial_real, initial_imag );
        
        // 初期値に対する多項式の値
        result[root_number] = initial;
        value = polynomial_value( order, coefficient, result[root_number] );

        // 多項式の1つの根を求めるループ
        while( abs(value)>0.001 )
        {
            value      =      polynomial_value( order, coefficient, result[root_number] ); // result[root_number]に対する多項式の値
            derivative = polynomial_derivative( order, coefficient, result[root_number] ); // result[root_number]に対する導関数

            result[root_number] = result[root_number] - value/derivative; // ニュートン法の式
        }
    }

    return result;
}