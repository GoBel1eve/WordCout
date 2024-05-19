#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    FILE *fp;
    int cnt = 0; // ͳ����
    
	char current_path[1024];
    getcwd(current_path, sizeof(current_path));

    // ƴ������·��
    char full_path[1024];
    sprintf(full_path, "%s/%s", current_path, argv[2]);

    // ��������в���
    if (argc != 3) {
        printf("Usage: %s [-w|-c] <filename>\n", argv[0]);
        return 1;
    }

    // ��ӡ�ļ�·��
    printf("File path: %s\n", argv[2]);

    // ����ļ��Ƿ����
    if (access(argv[2], F_OK) == -1) {
        printf("Error: File not found.\n");
        return 1;
    }
    // ���ļ�
    if ((fp=fopen(argv[2], "r")) == NULL)
    {
        puts("error!\n"); // ���ļ�ʧ�ܣ����������Ϣ
        return 0; // �˳�����
    }

    // �ж������в���
    if (argv[1][1] == 'w') // ͳ�Ƶ���
    {
        char s[1024]; // �洢���ʵ��ַ�����
        while (fscanf(fp, "%s", s) != EOF) // ���ļ��ж�ȡ���ʣ�ֱ���ļ�ĩβ
        {
            cnt ++; // ͳ�Ƶ�������
            for (int i = 1; i < strlen(s) - 1; i ++) // ���������ַ���
                if (s[i] == ',' && s[i - 1] != ',' && s[i + 1] != ',') // �ж��Ƿ�Ϊ�����Ķ���
                    cnt ++; // ͳ�ƶ�����Ϊ���ʵĸ���
        }
        printf("������=%d\n", cnt); // �����������
    }
    else if (argv[1][1] == 'c') // ͳ���ַ�
    {
        char c; // �洢�ַ��ı���
        while ((c = fgetc(fp)) != EOF) // ���ļ��ж�ȡ�ַ���ֱ���ļ�ĩβ
            cnt ++; // ͳ���ַ�����
        printf("�ַ���=%d", cnt); // ����ַ�����
    }

    fclose(fp); // �ر��ļ�
    return 0;
}
