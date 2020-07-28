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
EnumOption parse_arg(string cmd);

string g_json_file_path = "";
WeJson g_json;
ValueTypeCast g_current_value = JsonNull();

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "input json path!" << endl;
        return 0;
    }

    g_json_file_path = argv[argc-1];
    g_json.open_json(g_json_file_path);
    g_current_value = g_json.get_value();

    string input;
    while (true) {
        cout << ">";
        cin >> input;
        if (input == "quit") {
            break;
        }
        parse_arg(input);
    }
    
    cout << "edit over!" << endl; 
    return 0;
}

void help_info(void)
{
    cout << endl;
    cout << "   parse_json [OPTION] param1 param2 param3 ..." << endl;
    cout << "   help                        # 打印帮助信息" << endl;
    cout << "   load  json_path             # 加载json文件到内存中" << endl;
    cout << "   write                       # 将内存中的数据写入到文件中" << endl;
    cout << "   quit                        # 退出json文件编辑模式" << endl;
    cout << "   set   key/index   value     # 给key设置新值, 不存在打印failed" << endl;
    cout << "   creat key         value     # 添加新的值，数组的话不考虑index直接将值添加到最后" << endl;
    cout << "   del   key/index             # 删除key/index对应的元素" << endl;
    cout << "   cd    key/index             # key是数组或是对象时，可以进入" << endl;
    cout << "   ls                          # 打印当前对象/数组中的元素, 不存在返回 \"\"" << endl;
    cout << endl;

    return ;
}

EnumOption parse_arg(string cmd)
{
    StrBuffer str(cmd);
    vector<string> cmd_list = str.split_str(" ");
    
    for (auto iter = cmd_list.begin(); iter != cmd_list.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    if (cmd_list.size() == 0) {
        return EOption_Error;
    }
    try {
        if (cmd_list[0] == "help") {
            help_info();
            return EOption_Complete;
        }
        cout << "g_json_file_path: " << g_json_file_path << endl;
        if (g_json_file_path != "") {
            if (cmd_list[0] == "write") {
                g_json.write_json(g_json_file_path);
                g_current_value = g_json.get_value();
            } else if (cmd_list[0] == "quit") {
                return EOption_Quit;
            } else if (cmd_list[0] == "set") {

            } else if (cmd_list[0] == "del") {

            } else if (cmd_list[0] == "cd") {
                if (g_current_value.get_type() == JSON_OBJECT_TYPE ||
                    g_current_value.get_type() == JSON_ARRAY_TYPE)
                {
                    
                }
            } else if (cmd_list[0] == "ls") {
                if (g_current_value.get_type() == JSON_OBJECT_TYPE) {
                    auto iter_begin = g_current_value.begin();
                    auto iter_end = g_current_value.end();
                    for (auto iter = iter_begin; iter != iter_end; ++iter) {
                        auto tmp = *iter;
                        if (iter.get_type() == JSON_OBJECT_TYPE) {
                            cout << "\t" << tmp.first << " -> " << "obj_value" << endl;
                        } else if (iter.get_type() == JSON_ARRAY_TYPE) {
                            cout << "\t" << tmp.first << " -> " << "arr_value" << endl;
                        } else {
                            cout << "\t" << tmp.first << " -- " << tmp.second << endl;
                        }
                    }
                }
            } else {
                cerr << "Unknown option: " << cmd_list[0] << endl;
                return EOption_Error;
            }
        } else {
            cerr << "\n\nLoad json file first\n\n" << endl;
            return EOption_Error;
        }
    } catch (runtime_error err) {
        cout << err.what();
        return EOption_Error;
    }

    return EOption_Complete;
}