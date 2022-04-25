#include <vector>
#include <bits/stdc++.h>
#include "3_arx_structure_function.h"

using namespace std;

// 損失関数
float loss_function_calc(int output_order, int input_order, int dead_time, vector<float> experiment, vector<float> estimate )
{
    float result = 0;
    int   k_start = max(output_order, input_order+dead_time);

    for ( int k=k_start; k<experiment.size(); k++ )
    {
        result += pow( experiment[k] - estimate[k], 2 );
    }
    result = result / (experiment.size() - k_start);
    return result;
}