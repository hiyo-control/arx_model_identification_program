#include <vector>
using namespace std;

// 平均値計算------------------------------------------------------------------------------------
float average_calc( vector<float> input );

// トレンドの除去--------------------------------------------------------------------------------
vector<float> remove_trend( vector<float> input );

// ローパスフィルタ------------------------------------------------------------------------------
vector<float> low_pass_filter( vector<float> input, float band_width, float sampling );