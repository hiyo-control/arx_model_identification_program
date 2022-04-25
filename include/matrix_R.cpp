#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// 行列Rの作成 ---------------------------------------------------------------------------------------------------------------------------------
vector<vector<float>> matrix_R( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input )
{
    int sum_order = input_order + output_order;
    int k_start   = max(output_order, dead_time+input_order);
    
    vector< vector<float> > result( sum_order, vector<float>( sum_order ) );
    for ( int k=k_start; k<output.size(); k++ )
    {
        // k時点でのベクトルΦ(k)
        vector<float> phi_k = vector_phi_k( output_order, input_order, dead_time, output, input, k );
        
        // Φ(k)とΦ(k)^Tの積
        for( int row=0; row<sum_order; row++ )
        {
            for ( int col=0; col<sum_order; col++ )
            {
                result[row][col] += phi_k[row]*phi_k[col];
            }
        }
    }

    // 行列の各要素をデータ数で割る
    for( int row=0; row<sum_order; row++ )
    {
        for ( int col=0; col<sum_order; col++ )
        {
            result[row][col] = result[row][col] / ( input.size() - k_start );
        }
    }
    return result;
}