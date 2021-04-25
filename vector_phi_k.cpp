#include <vector>
using namespace std;

vector<float> vector_phi_k( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input, int k )
{
    int sum_order = input_order + output_order;
    int i_out = 1, i_in = 0;

    vector<float> result;
    for ( int i=0; i<sum_order; i++ )
    {
        if( i<output_order )
        {
            result.push_back( -output[ k - i_out ] );
            i_out++;
        }
        else
        {
            result.push_back( input[ k - dead_time - i_in ] );
            i_in++;
        }
    }
    return result;
}