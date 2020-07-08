#include "wejson.h"
#include "str_buffer.h"

using namespace my_util;

enum EnumOption {
    EOption_Quit,
    EOption_Complete,
    EOption_Error,
    EOption_Help,
    EOption_Load,
    EOption_Write,
    EOption_Print,
    EOption_Set,
    EOption_Creat,
    EOption_Del,
    EOption_Size
};

void help_info(void);
vector<string> parse_arg(int argc, char *argv[]);

string g_json_file_path = "";
ValueTypeCast g_current_value = JsonNull();

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        help_info();
        return 1;
    }

    string file_path = argv[1];
    string json_key = argv[2];

    WeJson js;
    js.open_json(file_path);
    // cout << js.generate_to_json() << endl;
    cout  << js[json_key];
    

    return 0;
}

void help_info(void)
{
    cout << "parse_json [OPTION] param1 param2 param3 ..." << endl;
    cout << "help                        # 打印帮助信息" << endl;
    cout << "load  json_path             # 加载json文件到内存中" << endl;
    cout << "write                       # 将内存中的数据写入到文件中" << endl;
    cout << "quit                        # 退出json文件编辑模式" << endl;
    cout << "set   key/index   value     # 给key设置新值, 不存在打印failed" << endl;
    cout << "creat key         value     # 添加新的值，数组的话不考虑index直接将值添加到最后" << endl;
    cout << "del   key/index             # 删除key/index对应的元素" << endl;
    cout << "cd    key/index             # key是数组或是对象时，可以进入" << endl;
    cout << "ls                          # 打印当前对象/数组中的元素, 不存在返回 \"\"" << endl;

    return ;
}

EnumOption parse_arg(WeJson &js, string cmd)
{
    StrBuffer str(cmd);
    vector<string> cmd_list = str.split_str(" ");

    if (cmd_list.size() == 0) {
        return EOption_Error;
    }
    try {
        if (cmd_list[0] == "load") {
            js.open_json(cmd_list[1]);
            g_json_file_path = cmd_list[1];
        } else if (cmd_list[0] == "help") {
            help_info();
        }
        
        if (g_json_file_path != "") {
            if (cmd_list[0] == "write") {
                js.write_json(g_json_file_path);
                g_current_value = js.get_value();
            } else if (cmd_list[0] == "quit") {
                return EOption_Quit;
            } else if (cmd_list[0] == "set") {

            } else if (cmd_list[0] == "del") {

            } else if (cmd_list[0] == "cd") {

            } else if (cmd_list[0] == "ls") {
                if (js.get_type() == JSON_OBJECT_TYPE) {
                    auto js_element = 
                }
            } else {
                cerr << "Unknown option: " << cmd_list[0] << endl;
                return EOption_Error;
            }
        } else {
            cerr << "Load json file first" << endl;
            return EOption_Error;
        }
    } catch (runtime_error err) {
        cout << err.what();
        return EOption_Error;
    }

    return EOption_Complete;
}