#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <complex>
#include "./include/csv_import.h"
#include "./include/4_zero_pole_calculation_function.h"

using namespace std;

// =============================================================================================================================================
// 実行プログラム
// =============================================================================================================================================
int main()
{
    //------------------------------------------------------------------------------------------------------------------------------------------
    // インターフェース
    string arx_model_coefficient_file_name;
    cout << "Enter arx model coefficient data file name" << endl;
    cin  >> arx_model_coefficient_file_name;
    
    //------------------------------------------------------------------------------------------------------------------------------------------
    // arxモデルの係数取り込み
    ifstream inputfile( "./data_strage/" + arx_model_coefficient_file_name + ".csv" );
    string   line;
    vector<string> strvec;
    getline( inputfile, line ); // 第1行目を捨てる

    getline( inputfile, line ); 
    strvec = split(line, ',');
    int output_order = stof( strvec[0] );
    int  input_order = stof( strvec[1] );
    int    dead_time = stof( strvec[2] );

    vector<float> output_coef;
    output_coef.push_back( 1 );
    for( int i=0; i<output_order; i++ )
    {
        // 出力の係数
        output_coef.push_back( stof( strvec[i+4] ) );
    }

    vector<float> input_coef;
    for( int i=0; i<input_order; i++ )
    {
        // 入力の係数
        input_coef.push_back( stof( strvec[i+4+output_order] ) );
    }
    for( int i=0; i<dead_time; i++ )
    {
        input_coef.push_back( 0 );
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------
    // 極の導出
    vector< complex<float> > pole( output_order );
    pole = polynomial_roots_calculation( output_order, output_coef );

    //--------------------------------------------------------------------------------------------------------------------------------------------
    // 零点の導出
    vector< complex<float> > zero( input_order );
    zero = polynomial_roots_calculation( input_order, input_coef );

    // --------------------------------------------------------------------------------------------------------------------------------------------
    // CSV出力（arxモデルの極とゼロを出力）
    ofstream outputfile("./data_strage/4_poles_and_zeros.csv");

    // 第1行目の記入
    outputfile << "poles list" << "," << "," << "," << "zeros list" << endl;

    // 第2行目の記入
    outputfile << "Real part" << "," << "Imaginary part" << "," << ",";
    outputfile << "Real part" << "," << "Imaginary part" << endl ;
    
    // 極と零点の出力
    for ( int i=0; i<10; i++ )
    {
        // 極の出力
        if( i<pole.size() )
        {
            outputfile << real( pole[i] ) << "," << imag( pole[i] ) << "," << ",";
        }
        else
        {
        } 

        // 零点の出力
        if( i<zero.size() )
        {
            outputfile << real( zero[i] ) << "," << imag( zero[i] );
        }
        else
        {
        }
        outputfile << endl;
        
    }
    cout << "poles and zeros calculation is completed" << endl;
}




