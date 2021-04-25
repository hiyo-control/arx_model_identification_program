#include <vector>
#include <complex>
using namespace std;

// 多項式の根の計算
vector< complex<float> > polynomial_roots_calculation( int order, vector<float> coefficient );

// 多項式の値
complex<float> polynomial_value( int order, vector<float> coefficient, complex<float> value );

// 多項式の値
complex<float> polynomial_derivative( int order, vector<float> coefficient, complex<float> value );