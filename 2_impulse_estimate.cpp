#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "./include/csv_import.h"
#include "./include/2_impulse_estimate_function.h"

using namespace std;

// ==================================================================================
// 実行プログラム
// ==================================================================================
int main()
{
    //-------------------------------------------------------------------------------
    // インターフェース
    string input_file_name, output_file_name;
    cout << "Enter analysis file name" << endl;
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
    // 相関解析法によるインパルス応答計算
    vector<float> impulse_response = correlation_analysis( input, output );

    //-------------------------------------------------------------------------------
    // csv出力
    ofstream outputfile("./data_strage/2_impulse_response.csv");

    outputfile << "Lag" << "," << "response" << endl;
    for ( int k=0; k<impulse_response.size(); k++ )
    {
        outputfile << k << ",";
        outputfile << impulse_response[k] << ",";
        outputfile << endl;
    }
    cout << "Impulse response estiamtion is completed" << endl;
}