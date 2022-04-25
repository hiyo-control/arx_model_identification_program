#include <vector>
#include <bits/stdc++.h>
using namespace std;

const double  pi = acos(-1);

// ローパスフィルタ--------------------------------------------------------------------------------
vector<float> low_pass_filter( vector<float> data, float band_width, float sampling )
{
    vector<float> result;
    float time_constant = 1 / ( 2*pi*band_width );
    float             a = time_constant / ( sampling - time_constant );

    result.push_back( data[0] );

    for ( int k=1; k<data.size(); k++ )
    {
        result.push_back( a * result[k-1] + ( 1-a ) * data[k] );
    }
    return result;
}