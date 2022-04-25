#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "./include/csv_import.h"
#include "./include/0_output_backward_difference_function.h"

#include <stdint.h>

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
    //生データ取り込み
    vector<float> time, input, output;
    vector< vector<float> >  data = csv_import( input_file_name );
    
    for (int k=0; k<data[0].size(); k++ )
    {
          time.push_back( data[0][k] );
         input.push_back( data[1][k] );
        output.push_back( data[2][k] );
    }

    //-------------------------------------------------------------------------------
    // 出力の後退差分 
    float sampling = time[1] - time[0];
    vector<float> output_backward = backward_difference( output, sampling );

    //-------------------------------------------------------------------------------
    // csv出力
    ofstream outputfile("./data_strage/" + input_file_name + "_backward_difference.csv");

    outputfile << "time[sec]" << "," << "input" << "," << "output" << endl;
    for ( int k=0; k<output.size(); k++ )
    {
        outputfile << time[k]            << ",";
        outputfile << input[k]           << ",";
        outputfile << output_backward[k] << endl;
    }

    cout << "Backward difference calculation is completed" << endl;
}



