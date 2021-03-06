#ifndef __FILE_H__
#define __FILE_H__

#include "basic_head.h"
#include "byte_buffer.h"

namespace my_util {
#define DEFAULT_OPEN_FLAG   O_RDWR
#define DEFAULT_FILE_RIGHT  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

class FileOperate {
public:
    FileOperate(void);
    ~FileOperate(void);

    // 根据文件路径打开文件
    int open(const string file_path, int flag = DEFAULT_OPEN_FLAG, int file_right = DEFAULT_FILE_RIGHT);
    // 根据文件描述符打开文件
    int set_fd(int fd, bool open_when_exit = true);

    // 返回文件信息
    int fileinfo(struct stat &file_info);
    // 返回文件的大小
    off_t file_size() {return file_info_.st_size;}
    // 关闭文件
    int close_file(void);
    // 检查文件描述符
    int check_fd(int fd);
    // 错误打印
    void print_errno(void);
    // 清空文件
    int clear_file(void);
    
    // 设置文件偏移
    off_t seek(off_t offset, int whence);
    // 返回当前位置
    off_t curr_pos(void);

    // 从当前位置读取任意数据
    ssize_t read(ByteBuffer &buff, size_t buf_size);
    // 从某一位置读取数据
    ssize_t read_from_pos(ByteBuffer &buff, size_t buf_size, off_t pos, int whence);

    // 写数据
    ssize_t write(ByteBuffer &buff, size_t buf_size);
    // 从某一位置写数据
    ssize_t write_to_pos(ByteBuffer &buff, size_t buf_size ,off_t pos, int whence);

    // 从标准输入读
    static ssize_t read_from_stdin(ByteBuffer &buff);
    // 写到标准输出
    static ssize_t write_to_stdout(ByteBuffer &buff, size_t buf_size);
    // 写到标准出错
    static ssize_t write_to_stderr(ByteBuffer &buff, size_t buf_size);

private:
    int errno_;
    int fd_;
    bool open_on_exit_;
    bool file_open_flag_;
    unsigned max_lines_;
    struct stat file_info_;
};

}
#endif