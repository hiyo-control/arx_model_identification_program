#include <vector>
#include "1_preprocessing_function.h"
using namespace std;

// トレンドの除去--------------------------------------------------------------
vector<float> remove_trend( vector<float> data )
{
    float average_value = average_calc( data );
    vector<float> result;

    for ( int k=0; k<data.size(); k++ )
    {
        result.push_back( data[k] - average_value );
    }
    return result;
}