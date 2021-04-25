#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "1_preprocessing_function.h"
#include "csv_import.h"

using namespace std;

// ==================================================================================
// 実行プログラム
// ==================================================================================
int main()
{
    //-------------------------------------------------------------------------------
    // インターフェース
    string input_file_name;
    cout << "Enter raw data file name" << endl;
    cin  >> input_file_name;

    //-------------------------------------------------------------------------------
    // csv取り込み
    vector<float> time, input, output;
    vector< vector<float> >  data = csv_import( input_file_name );
    
    for (int k=0; k<data[0].size(); k++ )
    {
          time.push_back( data[0][k] );
         input.push_back( data[1][k] );
        output.push_back( data[2][k] );
    }

    //-------------------------------------------------------------------------------
    // トレンド除去
    vector<float>  input_remove_trend  = remove_trend( input  );
    vector<float>  output_remove_trend = remove_trend( output );

    //-------------------------------------------------------------------------------
    // ローパスフィルタ
    ifstream inputfile( "./data_strage/0_0_condition.csv" );
    string   line;

    getline(inputfile, line);
    vector<string> strvec = split(line, ',');  
    float band_width = stof( strvec[1] ); // カットオフ周波数の読み取り
    float sampling   = time[1] - time[0]; // サンプリング周期の読み取り

    vector<float> input_LPF  = low_pass_filter( input_remove_trend,  band_width, sampling );
    vector<float> output_LPF = low_pass_filter( output_remove_trend, band_width, sampling );
    
    //-------------------------------------------------------------------------------
    // csv出力（全データ）
    ofstream outputfile("./data_strage/1_process_data_all.csv");

    outputfile << "time[sec]" << "," << "input" << "," << "output" << endl;
    for ( int k=0; k<time.size(); k++ )
    {
        outputfile << time[k]       << ",";
        outputfile << input_LPF[k]  << ",";
        outputfile << output_LPF[k] << endl;
    }

    //-------------------------------------------------------------------------------
    // csv出力（クロスバリデーション）
    ofstream outputfile1("./data_strage/1_process_data_formulation.csv");
    ofstream outputfile2("./data_strage/1_process_data_validation.csv");

    outputfile1 << "time[sec]" << "," << "input" << "," << "output" << endl;
    outputfile2 << "time[sec]" << "," << "input" << "," << "output" << endl;
    for ( int k=0; k<time.size(); k++ )
    {
        // 解析用データ
        if ( ( time[k]>=1 )&&( time[k]<=time[ time.size()*0.5 ] ) )
        {
            outputfile1 << time[k]       << ",";
            outputfile1 << input_LPF[k]  << ",";
            outputfile1 << output_LPF[k] << ",";
            outputfile1 << endl;
        }

        // バリデーション用データ
        else if( time[k]>time[ time.size()*0.5 ] )
        {
            outputfile2 << time[k]       << ",";
            outputfile2 << input_LPF[k]  << ",";
            outputfile2 << output_LPF[k] << ",";
            outputfile2 << endl;
        }
    }

    cout << "Preprocessing is completed" << endl;
}