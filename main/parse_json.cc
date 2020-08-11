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
ValueTypeCast &g_current_value = g_json;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "input json path!" << endl;
        return 0;
    }

    g_json_file_path = argv[argc-1];
    g_json.open_json(g_json_file_path);

    string input;
    while (true) {
        cout << ">";
        getline(cin, input);
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
    cout << "   write                       # 将内存中的数据写入到文件中" << endl;
    cout << "   quit                        # 退出json文件编辑模式" << endl;
    cout << "   set   key/index   value     # 给key设置新值, 不存在打印failed" << endl;
    cout << "   add   key         value     # 添加新的值，数组的话不考虑index直接将值添加到最后" << endl;
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

    if (cmd_list.size() == 0) {
        return EOption_Error;
    }
    try {
        if (cmd_list[0] == "help") {
            help_info();
            return EOption_Complete;
        }
        
        if (g_json_file_path != "") {
            if (cmd_list[0] == "write") {
                g_json.write_json(g_json_file_path);
                g_current_value = g_json;
            } else if (cmd_list[0] == "quit") {
                return EOption_Quit;
            } else if (cmd_list[0] == "mod") {
                // to-do
            } else if (cmd_list[0] == "add") { // 存在问题，要改成绝对路径的值
                if (g_current_value.get_type() == JSON_OBJECT_TYPE && cmd_list.size() == 3) {
                    if (cmd_list[2][0] == '"') {
                        g_current_value.add(cmd_list[1], cmd_list[2]);
                    } else {
                        double value = stod(cmd_list[2]);
                        g_current_value.add(cmd_list[1], value);
                    }
                } else if (g_current_value.get_type() == JSON_ARRAY_TYPE && cmd_list.size() == 2) {
                    if (cmd_list[2][0] == '"') {
                        g_current_value.add(cmd_list[1], cmd_list[2]);
                    } else {
                        double value = stod(cmd_list[2]);
                        g_current_value.add(cmd_list[1], value);
                    }
                }
            } else if (cmd_list[0] == "del" && cmd_list.size() == 2) { //存在问题，改成绝对路径，比如删除 /friends/0/id 对应的值
                if (g_current_value.get_type() == JSON_OBJECT_TYPE) {
                    g_current_value.erase(cmd_list[1]);
                } else if (g_current_value.get_type() == JSON_ARRAY_TYPE) {
                    g_current_value.erase(stoi(cmd_list[1]));
                }
            } else if (cmd_list[0] == "cd" && cmd_list.size() == 2) { // 无法进入关键字中带有空格的类型, 无法回到上级目录
                if (g_current_value.get_type() == JSON_OBJECT_TYPE) {
                    g_current_value = g_current_value[cmd_list[1]];
                } else if (g_current_value.get_type() == JSON_ARRAY_TYPE) {
                    g_current_value = g_current_value[stoi(cmd_list[1])];
                }
            } else if (cmd_list[0] == "ls") { // 支持打印对应key或是index指向的值
                if (g_current_value.get_type() == JSON_OBJECT_TYPE || g_current_value.get_type() == JSON_ARRAY_TYPE) {
                    int arr_index = 0;
                    auto iter_begin = g_current_value.begin();
                    auto iter_end = g_current_value.end();
                    for (auto iter = iter_begin; iter != iter_end; ++iter) {
                        auto tmp = *iter;

                        if (g_current_value.get_type() == JSON_OBJECT_TYPE) {
                            cout << " " << tmp.first;
                        } else if (g_current_value.get_type() == JSON_ARRAY_TYPE) {
                            cout << " " << arr_index++;
                        }

                        if (tmp.second.get_type() == JSON_OBJECT_TYPE) {
                            cout <<  " -> " << "obj_value" << endl;
                        } else if (tmp.second.get_type() == JSON_ARRAY_TYPE) {
                            cout << " -> " << "arr_value" << endl;
                        } else {
                            cout << " -- " << tmp.second << endl;
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