#include <vector>
using namespace std;

// 逆行列計算 ---------------------------------------------------------------------------------------------------------------------------------
vector< vector<float> > inv_matrix( vector< vector<float> > matrix )
{
    int order = matrix[0].size();
    vector< vector<float> > result( order, vector<float>(order) );
    int i, j, k;
    float buf;

    // 単位行列をつくる
    for ( i=0; i<order; i++ )
    {
        for ( j=0; j<order; j++ )
        {
            if ( i==j )
            {
                result[i][j] = 1;
            }
            else
            {
                result[i][j] = 0;
            }
        }
    }

    // 掃き出し法
    for ( i=0; i<order; i++ )
    {
        buf = 1 / matrix[i][i];
        for ( j=0; j<order; j++ )
        {
            matrix[i][j] *= buf;
            result[i][j] *= buf;
        }
        for ( j=0; j<order; j++ )
        {
            if( i!=j )
            {
                buf = matrix[j][i];
                for( k=0; k<order; k++ )
                {
                    matrix[j][k] -= matrix[i][k]*buf;
                    result[j][k] -= result[i][k]*buf;
                }
            }
        }
    }
    return result;
}