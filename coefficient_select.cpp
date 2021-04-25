#include <vector>
using namespace std;

// arx係数行列から，指定の出力次数・入力次数の係数ベクトルを選択-------------------------------------------------------------------------------------
vector<float> coefficient_select( int output_order, int input_order, vector< vector<float> > coefficient_matrix )
{
    vector<float> result;
    int row = 10*(output_order-1) + (input_order-1);

    for ( int col=0; col<20; col++ )
    {
        result.push_back( coefficient_matrix[row][col] );
    }
    return result;
}