#include <vector>
using namespace std;

// 最大値の選択（2値）--------------------------------------------------------------------------------------------------------------------------
float max( float input1, float input2 )
{
    float result=0;

    if( input1<=input2 )
    {
        result = input2;
    }
    else if( input1>input2 )
    {
        result = input1;
    }
    return result;
}