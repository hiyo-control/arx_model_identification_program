#include <vector>
#include <bits/stdc++.h>
using namespace std;

//-----------------------------------------------------------------------------------
// 相関解析法によるインパルス応答計算
vector<float> impulse_function( vector<float> input, vector<float> output )
{
    vector<float> result;
    int tau_max = 50;
    int k_end = output.size() - tau_max;
    
    // 分母計算
    float den=0;
    for (int k=0; k<k_end; k++)
    {
        den += pow( input[k], 2 );
    }

    // インパルス応答の計算
    for ( int tau=0; tau<tau_max; tau++ )
    {
        // 分子計算
        float num=0;
        for ( int k=0; k<k_end; k++ )
        {
            num += output[k+tau] * input[k];
        }

        result.push_back( num/den );
    }
    return result;
}