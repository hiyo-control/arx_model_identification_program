#include <vector>
using namespace std;

// 平均値計算---------------------------------------------------------------------------------
float average_calc( vector<float> data )
{
    float sum = 0, result = 0;

    for ( int k = 0; k<data.size(); k++ )
    {
        sum += data[k];
    }
    result = sum / data.size();
    return result;
}
