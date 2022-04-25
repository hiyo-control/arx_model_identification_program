#include <vector>
using namespace std;

// 逆行列計算
vector< vector<float> > inv_matrix( vector< vector<float> > matrix );

// 最大値選択（2値）
float max( float input1, float input2 );

// 最小値選択（2値）
float min( float input1, float input2 );

// arxモデルの係数同定用関数（システム同定の基礎P131）---------------------------------------------------------------------------------------------------------
// ベクトルΦ(k)の導出
vector<float> vector_phi_k( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input, int k );

// ベクトルfの導出
vector<float> vector_f( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input );

// 行列Rの導出
vector<vector<float>> matrix_R( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input );

// arxモデルの係数導出
vector<float> arx_coefficient_calc( int output_order, int input_order, int dead_time, vector<float> output, vector<float> input );

// arxモデルの係数を行列として保存する
vector< vector< vector<float> > > arx_coefficient_matrix( int output_order_limit, int input_order_limit, int dead_time, vector<float> output, vector<float> input );

// 損失関数導出関連の関数------------------------------------------------------------------------------------------------------------------------------------------
// k時点の推定値の算出
float y_k_estimate( int output_order_limit, int output_order, int input_order, int dead_time, vector<float> output, vector<float> input, vector<float> coefficient, int k );

// 出力次数・入力次数・各時間の推定値を行列として保存
vector< vector< vector<float> > > y_estimate_matrix( int output_order_limit, int input_order_limit, int dead_time, vector<float> output, vector<float> input, vector< vector< vector<float> > > coefficient);

// 損失関数の算出
float loss_function_calc(int output_order, int input_order, int dead_time, vector<float> experiment, vector<float> estimate );


// arx係数行列から，指定の出力次数・入力次数の係数ベクトルを選択
vector<float> coefficient_select( int output_order, int input_order, vector< vector<float> > coefficient_matrix );

