#include "wejson.h"

using namespace my_util;

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cerr << argv[0] << " json_file_path key" << endl;
        return 0;
    }

    string file_path = argv[1];
    string json_key = argv[2];

    WeJson js;
    js.open_json(file_path);
    cout  << js[json_key];

    return 0;
}