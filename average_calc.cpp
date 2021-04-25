#include <vector>
using namespace std;

// 平均値計算---------------------------------------------------------------------------------
float average_calc( vector<float> input )
{
    float sum = 0, result = 0;

    for ( int k = 0; k<input.size(); k++ )
    {
        sum += input[k];
    }
    result = sum / input.size();
    return result;
}
