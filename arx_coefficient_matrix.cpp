#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// arxモデルの係数を行列として保存する
vector< vector< vector<float> > > arx_coefficient_matrix( int output_order_limit, int input_order_limit, int dead_time, vector<float> output, vector<float> input )
{
    vector< vector< vector<float> > > result( output_order_limit + 1, vector<vector<float>>( input_order_limit + 1, vector<float>( output_order_limit + input_order_limit ) ) );
    vector<float> arx_coefficient_buf( output_order_limit + input_order_limit );
    
     for ( int output_order=1; output_order<=output_order_limit; output_order++ )
    {
        for ( int input_order=1; input_order<=input_order_limit; input_order++ )
        {
            int element = 0;
            vector<float> arx_coefficient_buf = arx_coefficient_calc( output_order, input_order, dead_time, output, input );

            for ( int coefficient=0; coefficient<output_order_limit + input_order_limit; coefficient++ )
            {
                if ( coefficient<output_order )
                {
                    result[output_order][input_order][coefficient] = arx_coefficient_buf[element];
                    element ++;
                }
                else if( ( coefficient>=output_order_limit ) && ( coefficient<output_order_limit+input_order ) )
                {
                    result[output_order][input_order][coefficient] = arx_coefficient_buf[element];
                    element ++;
                }
                else
                {
                    result[output_order][input_order][coefficient] = 0;
                }
            }
        }
    }
    
    return result;
}

