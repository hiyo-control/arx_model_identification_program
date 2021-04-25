#include <vector>
#include <string>
using namespace std;

// 文字列分割
vector<string> split( string& input, char delimiter );

// CSV取り込み
vector< vector<float> > csv_import( string& filename );

