#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int cnt = 0; // 统计数
    
	char current_path[1024];
    getcwd(current_path, sizeof(current_path));

    // 拼接完整路径
    char full_path[1024];
    sprintf(full_path, "%s/%s", current_path, argv[2]);

    // 检查命令行参数
    if (argc != 3) {
        printf("Usage: %s [-w|-c] <filename>\n", argv[0]);
        return 1;
    }

    // 打印文件路径
    printf("File path: %s\n", argv[2]);

    // 检查文件是否存在
    if (access(argv[2], F_OK) == -1) {
        printf("Error: File not found.\n");
        return 1;
    }
    // 打开文件
    if ((fp=fopen(argv[2], "r")) == NULL)
    {
        puts("error!\n"); // 打开文件失败，输出错误信息
        return 0; // 退出程序
    }

    // 判断命令行参数
    if (argv[1][1] == 'w') // 统计单词
    {
        char s[1024]; // 存储单词的字符数组
        while (fscanf(fp, "%s", s) != EOF) // 从文件中读取单词，直到文件末尾
        {
            cnt ++; // 统计单词数量
            for (int i = 1; i < strlen(s) - 1; i ++) // 遍历单词字符串
                if (s[i] == ',' && s[i - 1] != ',' && s[i + 1] != ',') // 判断是否为独立的逗号
                    cnt ++; // 统计逗号作为单词的个数
        }
        printf("单词数=%d\n", cnt); // 输出单词数量
    }
    else if (argv[1][1] == 'c') // 统计字符
    {
        char c; // 存储字符的变量
        while ((c = fgetc(fp)) != EOF) // 从文件中读取字符，直到文件末尾
            cnt ++; // 统计字符数量
        printf("字符数=%d", cnt); // 输出字符数量
    }

    fclose(fp); // 关闭文件
    return 0;
}
