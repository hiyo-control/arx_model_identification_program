#include <vector>
#include <bits/stdc++.h>
using namespace std;

const double  pi = acos(-1);

// ローパスフィルタ--------------------------------------------------------------------------------
vector<float> low_pass_filter( vector<float> input, float band_width, float sampling )
{
    vector<float> result;
    float time_constant = 1 / ( 2*pi*band_width );
    float coefficient = time_constant / ( sampling - time_constant );

    result.push_back( input[0] );

    for ( int k=1; k<input.size(); k++ )
    {
        result.push_back( coefficient * result[k-1] + (1-coefficient)*input[k] );
    }
    return result;
}