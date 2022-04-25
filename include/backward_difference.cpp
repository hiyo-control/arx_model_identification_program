#include <vector>
using namespace std;

vector<float> backward_difference( vector<float> input, float sampling)
{
    vector<float> result;
    int k = 1;

    result.push_back( 0 );
    while( input[k] )
    {
        result.push_back( ( input[k]-input[k-1] )/sampling );
        k++;
    }
    return result;
}