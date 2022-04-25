#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// --------------------------------------------------------------------------------------
// 文字列分割
vector<string> split( string& input, char delimiter )
{
    istringstream stream(input);
    string field;
    vector<string> result;

    while ( getline(stream, field, delimiter) ) 
    {
        result.push_back(field);
    }
    return result;
} 

// --------------------------------------------------------------------------------------
// CSV取り込み
vector< vector<float> > csv_import( string& filename )
{
    ifstream inputfile( "./data_strage/" + filename + ".csv" );
    string   line;
    vector<float> result1, result2, result3;

    getline(inputfile, line);
    while ( getline(inputfile, line) ) 
    {
        vector<string> strvec = split(line, ',');
        result1.push_back( stof( strvec[0] ) );
        result2.push_back( stof( strvec[1] ) );
        result3.push_back( stof( strvec[2] ) );
    }

    vector< vector<float> > result( 3, vector<float>( result1.size() ) );
    for( int k=0; k<result1.size(); k++ )
    {
        result[0][k] = result1[k];
        result[1][k] = result2[k];
        result[2][k] = result3[k];
    }

    return result;
}
