#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "./include/3_arx_structure_function.h"
#include "./include/csv_import.h"

using namespace std;

// =============================================================================================================================================
// 実行プログラム
// =============================================================================================================================================
int main()
{
    //------------------------------------------------------------------------------------------------------------------------------------------
    // インターフェース
    string analysis_file_name, validation_file_name;
    cout << "Enter analysis data file name" << endl;
    cin  >> analysis_file_name;
    cout << "Enter validation data file name" << endl;
    cin  >> validation_file_name;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // csv取り込み
    vector<float> time, input, output;
    vector< vector<float> >  data = csv_import( analysis_file_name );
    
    for (int k=0; k<data[0].size(); k++ )
    {
          time.push_back( data[0][k] );
         input.push_back( data[1][k] );
        output.push_back( data[2][k] );
    }

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
    // arxモデルの係数計算・行列に保存
    vector< vector< vector<float> > > arx_coefficient( output_order_limit + 1, vector<vector<float>>( input_order_limit + 1, vector<float>( output_order_limit + input_order_limit ) ) );
    arx_coefficient = arx_coefficient_matrix( output_order_limit, input_order_limit, dead_time, output, input );

    // csv出力
    ofstream outputfile1("./data_strage/3_1_arx_coefficient.csv");
    
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

    // 算出した係数の記入
    for ( int output_order = 1; output_order <= output_order_limit; output_order++ )
    {
        for ( int input_order = 1; input_order <= input_order_limit; input_order++ )
        {
            outputfile1 << output_order << "," << input_order << "," << dead_time << "," << ",";

            for ( int coefficient = 0; coefficient < output_order_limit + input_order_limit; coefficient++ )
            {
                outputfile1 << arx_coefficient[output_order][input_order][coefficient] << ",";
            }
            outputfile1 << endl;
        }
    }
    cout << "arx coefficient calculation is completed" << endl;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // 推定値計算
    // csv取り込み
    vector<float> time_validation, input_validation, output_validation;
    vector< vector<float> >  data_validation = csv_import( validation_file_name );

    for (int k=0; k<data_validation[0].size(); k++ )
    {
          time_validation.push_back( data_validation[0][k] );
         input_validation.push_back( data_validation[1][k] );
        output_validation.push_back( data_validation[2][k] );
    }

    // 推定値の計算・行列に保存
    vector< vector< vector<float> > > output_estimate( output_order_limit + 1, vector<vector<float>>( input_order_limit + 1, vector<float>( time_validation.size() ) ) );
    output_estimate = y_estimate_matrix( output_order_limit, input_order_limit, dead_time, output_validation, input_validation, arx_coefficient );

    // CSV出力
    ofstream outputfile2("./data_strage/3_2_estimate.csv");

    // 第1行目の記入
    outputfile2 << "time[sec]" << "," << "experiment" << ",";
    for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            outputfile2 << "y" << output_order << "-u" << input_order << "estimate" << ",";
        }
    }
    outputfile2 << endl;

    // 実験データ・推定値の出力
    for ( int k=0; k<time_validation.size(); k++ )
    {
        outputfile2 << time_validation[k]  << "," << output_validation[k] << ",";
        for ( int output_order=1; output_order<=output_order_limit; output_order++ )
        {
            for ( int input_order=1; input_order<=input_order_limit; input_order++ )
            {
                outputfile2 << output_estimate[output_order][input_order][k] << ",";
            }
        }
        outputfile2 << endl;
    }
    cout << "estimate values calculation is completed" << endl;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // 損失関数の計算
    vector< vector<float> > loss_function_values( 11, vector<float>(11) );

    for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            loss_function_values[output_order][input_order] = loss_function_calc( output_order, input_order, dead_time, output_validation, output_estimate[output_order][input_order] );
        }
    }

    // CSV出力
    ofstream outputfile3("./data_strage/3_3_loss_function.csv");

    // 第1行目の記入
    outputfile3 << ",";
    for (  int input_order=1; input_order<=input_order_limit; input_order++)
    {
        outputfile3 << "u" << input_order << ",";
    }
    outputfile3 << endl;

    // 実験データと第1行目の記入
    for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        outputfile3 << "y" << output_order << ",";
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            outputfile3 << loss_function_values[output_order][input_order];
            outputfile3 << ",";
        }
        outputfile3 << endl;
    }
    cout << "loss function calculation is completed" << endl;

    //------------------------------------------------------------------------------------------------------------------------------------------
    // 損失関数が最小となる出力次数、入力次数を探す
    int   output_order_min=1, input_order_min=1;
    float loss_function_values_min = loss_function_values[1][1];
    
    for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            float temp = loss_function_values[output_order][input_order];
            if ( loss_function_values_min > temp )
            {
                loss_function_values_min = temp;
                output_order_min         = output_order;
                input_order_min          = input_order;
            }
        }
    }

    //CSV出力（損失関数が最小となるarxモデルの次数と係数）
    ofstream outputfile4("./data_strage/3_4_arx_model_coefficient.csv");

    // 第1行目の記入
    outputfile4 << "y_order" << "," << "u_order" << "," << "dead_time" << "," << ",";
    for ( int i=0; i<output_order_limit + input_order_limit; i++ )
    {
        if ( i<output_order_limit )
        {
            outputfile4 << "a_" << i+1 << ",";
        }
        else
        {
            outputfile4 << "b_" << i - (output_order_limit - 1) << ",";
        }
    }
    outputfile4 << endl;

    // 損失関数が最小となるarxモデルの係数を出力
    outputfile4 << output_order_min << "," << input_order_min << "," << dead_time << "," << ",";
    for ( int coefficient=0; coefficient < output_order_limit + input_order_limit; coefficient++ )
    {
        outputfile4 << arx_coefficient[output_order_min][input_order_min][coefficient] << ",";
    }

    //CSV出力（損失関数が最小となるarxモデルの推定値）
    ofstream outputfile5("./data_strage/3_5_arx_model_estimate.csv");

    // 第1行目の記入
    outputfile5 << "time[sec]" << "," << "experiment" << "," << "estimate" << endl;
    // 推定値の出力
    for ( int k=0; k<time_validation.size(); k++ )
    {
        outputfile5 << time_validation[k] << "," << output_validation[k] << "," << output_estimate[output_order_min][input_order_min][k] << endl;
    }

    cout << "arx structure calculation is completed" << endl;
}