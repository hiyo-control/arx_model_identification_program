#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// 同定モデルの係数導出 --------------------------------------------------------------------------------------------------------------------------
vector<float> arx_coefficient_calc( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input )
{
    int sum_order = input_order + output_order;
    vector<float> result( sum_order );

    // ベクトルfを作る
    vector<float> f = vector_f( output_order, input_order, dead_time, output, input );

    // 行列Rを作る
    vector< vector<float> > R = matrix_R( output_order, input_order, dead_time, output, input );
    
    // 行列Rの逆行列
    vector< vector<float> > inv_R = inv_matrix( R );

    // result = inv_R × f
    for ( int i=0; i<sum_order; i++ )
    {
        for ( int j=0; j<sum_order; j++ )
        {
            result[i] += inv_R[i][j] * f[j];
        }
    }
    return result;
}