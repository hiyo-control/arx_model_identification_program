#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// 推定値を行列として保存
vector< vector< vector<float> > > y_estimate_matrix( int output_order_limit, int input_order_limit, int dead_time, vector<float> output, vector<float> input, vector< vector< vector<float> > > arx_coefficient)
{
    vector< vector< vector<float> > > result( output_order_limit + 1, vector<vector<float>>( input_order_limit + 1, vector<float>( output.size() ) ) );

    for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            int k_start = max( output_order, input_order+dead_time );
            for ( int k=0; k<output.size(); k++ )
            {
                float tmp = y_k_estimate( output_order_limit, output_order, input_order, dead_time, output, input, arx_coefficient[output_order][input_order], k );
                result[output_order][input_order][k] = tmp;
            }
        }
    }
    return result;
}