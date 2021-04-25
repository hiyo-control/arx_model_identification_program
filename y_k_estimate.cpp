#include <vector>
#include "3_arx_structure_function.h"

using namespace std;

// 推定値の算出 ---------------------------------------------------------------------------------------------------------------------------------
float y_k_estimate( int output_order_limit, int output_order, int input_order, int dead_time, vector<float> output, vector<float> input, vector<float> coefficient, int k )
{
    float result = 0;

    if ( k==0 )
    {
        result = output[0];
    }
    else
    {
        for ( int i=0; i<min(output_order,k); i++ )
        {
            result += -coefficient[i] * output[ k-i-1 ];
        }
        for ( int i=0; i<min(input_order,k); i++ )
        {
            result += coefficient[i+output_order_limit] * input[ k-dead_time-i ];
        }
    }
    return result;
}