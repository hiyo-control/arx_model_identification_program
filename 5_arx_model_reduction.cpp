#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "./include/csv_import.h"

using namespace std;

// =============================================================================================================================================
// 実行プログラム
// =============================================================================================================================================
int main()
{
    //------------------------------------------------------------------------------------------------------------------------------------------
    // インターフェース
    int reduced_output_order, reduced_input_order;
    cout << "Enter reduced output order" << endl;
    cin  >> reduced_output_order;
    cout << "Enter reduced input order" << endl;
    cin  >> reduced_input_order;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // 「0_0_condition.csv」から解析条件を読み取り
    ifstream inputfile( "./data_strage/0_0_condition.csv" );
    string   line;
    vector<string> strvec;

    getline(inputfile, line); // 1行目を捨てる

    getline(inputfile, line); // 出力次数の条件読み取り
    strvec = split(line, ',');
    int output_order_limit = stof( strvec[1] ); // 出力次数の上限

    getline(inputfile, line); // 入力次数の条件読み取り
    strvec = split(line, ',');
    int input_order_limit = stof( strvec[1] ); // 入力次数の上限

    getline(inputfile, line); // むだ時間の読み取り
    strvec = split(line, ',');
    int dead_time = stof( strvec[1] ); // 入力次数の上限

    //------------------------------------------------------------------------------------------------------------------------------------------
    // arxモデルの係数取り込み
    vector<float> arx_coefficient;
    ifstream inputfile1( "./data_strage/3_1_arx_coefficient.csv" );
    string    line1;
    vector<string> strvec1;

    getline( inputfile1, line1 ); // 第1行目を捨てる
    while( getline( inputfile1, line1 ) )
    {
        strvec1 = split(line1, ',');
        int output_order = stof( strvec1[0] );
        int  input_order = stof( strvec1[1] );

        if( (output_order==reduced_output_order)&&(input_order==reduced_input_order) )
        {
            for( int k=0; k<20; k++ )
            {
                arx_coefficient.push_back( stof(strvec1[k+4]) );
            }
        }
    }

    //------------------------------------------------------------------------------------------------------------------------------------------
    // 低次元arxモデルの損失関数取り込み
    float loss_function;
    int   output_order=1;
    ifstream inputfile2( "./data_strage/3_3_loss_function.csv" );
    string    line2;
    vector<string> strvec2;

    getline( inputfile2, line2 ); // 第1行目を捨てる
    while( getline( inputfile2, line2 ) )
    {
        strvec2 = split(line2, ',');
        if( output_order==reduced_output_order )
        {
            loss_function = stof( strvec2[reduced_input_order] );
        }
        output_order++;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------
    // arxモデルの推定値取り込み
    int row = 1;
    vector<float> estimate, time, experiment;
    ifstream inputfile3( "./data_strage/3_2_estimate.csv" );
    string    line3;
    vector<string> strvec3;

    getline( inputfile3, line3 ); // 第1行目を捨てる
    while( getline( inputfile3, line3 ) )
    {
        strvec3 = split(line3, ',');

        time.push_back( stof( strvec3[0] ) );
        experiment.push_back( stof( strvec3[1] ) );
        int data_num = 10*( reduced_output_order-1 ) + reduced_input_order - 1;
        estimate.push_back( stof( strvec3[data_num] ) );
    }

    //------------------------------------------------------------------------------------------------------------------------------------------
    // csv出力
    ofstream outputfile1("./data_strage/5_1_reduced_arx_model_coefficient.csv");

    // 第1行目の記入
    outputfile1 << "y_order" << "," << "u_order" << "," << "dead_time" << "," << ",";
    for ( int i=0; i<output_order_limit + input_order_limit; i++ )
    {
        if ( i<output_order_limit )
        {
            outputfile1 << "a_" << i+1 << ",";
        }
        else
        {
            outputfile1 << "b_" << i- (output_order_limit - 1) << ",";
        }
    }
    outputfile1 << endl;

    // 低次元化arxモデルの係数入力
    outputfile1 << reduced_output_order << "," << reduced_input_order << "," << dead_time << "," << ",";
    for ( int coefficient=0; coefficient < output_order_limit + input_order_limit; coefficient++ )
    {
        outputfile1 << arx_coefficient[coefficient] << ",";
    }

    ofstream outputfile2("./data_strage/5_2_reduced_arx_model_loss_funciton.csv");

    // 第1行目の記入
    outputfile2 << "y_order" << "," << "u_order" << "," << "dead_time" << "," << "loss_function_value" << endl;
    // 値の記入
    outputfile2 << reduced_output_order << "," << reduced_input_order << "," << dead_time << "," << loss_function << endl;

    ofstream outputfile3("./data_strage/5_3_reduced_arx_model_estimate.csv");
    // 第1行目の記入
    outputfile3 << "time[sec]" << "," << "experiment" << ",";
    outputfile3 << "y_" << reduced_output_order << "u_" << reduced_input_order << "estimate" << endl;
    // 推定値の出力
    for ( int k=0; k<time.size(); k++ )
    {
        outputfile3 << time[k] << "," << experiment[k] << "," << estimate[k] << endl;
    }

    cout << "reduced arx model output is completed" << endl;
}