#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

// Метод перевода целого числа типа в строку
char* parse_type(int type) {
    switch (type) {
        case DT_BLK:
            return "BLOCK";
        case DT_CHR:
            return "CHARACTER";
        case DT_DIR:
            return "DIRECTORY";
        case DT_FIFO:
            return "FIFO";
        case DT_LNK:
            return "LINK";
        case DT_REG:
            return "FILE";
        case DT_SOCK:
            return "SOCKET";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char* argv[])
{
    // Берем директорию как первый аргумент консоли, либо текущую папку, если директория не передана
    char* directory = ".";
    if (argc > 1)
        directory = argv[1];

    // Открываем директорию, чтобы считать файлы
    DIR *d = opendir(directory);

    // Считываем файлы в папке и выводим их
    struct dirent *dir;
    while((dir = readdir(d)) != NULL)
        printf("Type: %-10s Name: %s\n", parse_type(dir->d_type), dir->d_name);

    return 0;
}