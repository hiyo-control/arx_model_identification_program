#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// ベクトルfの作成 -----------------------------------------------------------------------------------------------------------------------------
vector<float> vector_f( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input )
{
    int sum_order = input_order + output_order;
    int k_start   = max( output_order, dead_time+input_order );

    vector<float> result( sum_order );
    for ( int k=k_start; k<input.size(); k++ )
    {
        // k時点でのベクトルΦ(k)を求める
        vector<float> phi_k = vector_phi_k( output_order, input_order, dead_time, output, input, k );
        for ( int i=0; i<sum_order; i++ )
        {
            // ベクトルΦ(k)の各要素にy[k]を掛ける
            result[i] += phi_k[i] * output[k];
        }
    }

    // 各要素をデータ数で割る
    for ( int i=0; i<result.size(); i++ )
    {
        result[i] = result[i] / ( input.size() - k_start);
    }
    return result;
}