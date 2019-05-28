#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// Метод высчитывает права доступа файла и переносит их в строку
void parse_mode(int mode, char* string_mode) {
    string_mode[0] = (mode & S_IRUSR) == S_IRUSR ? 'r' : '-';
    string_mode[1] = (mode & S_IWUSR) == S_IWUSR ? 'w' : '-';
    string_mode[2] = (mode & S_IXUSR) == S_IXUSR ? 'x' : '-';
    string_mode[3] = (mode & S_IRGRP) == S_IRGRP ? 'r' : '-';
    string_mode[4] = (mode & S_IWGRP) == S_IWGRP ? 'w' : '-';
    string_mode[5] = (mode & S_IXGRP) == S_IXGRP ? 'x' : '-';
    string_mode[6] = (mode & S_IROTH) == S_IROTH ? 'r' : '-';
    string_mode[7] = (mode & S_IWOTH) == S_IWOTH ? 'w' : '-';
    string_mode[8] = (mode & S_IXOTH) == S_IXOTH ? 'x' : '-';
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
    while((dir = readdir(d)) != NULL) {
        // Определяем - директория ли это, или что-то иное (как правило, файл)
        char type = dir->d_type == DT_DIR ? 'd' : '-';

        // Получаем информацию о файле/папке
        struct stat st;
        stat(dir->d_name, &st);

        // Получаем строку с данными доступа
        char string_mode[9];
        parse_mode(st.st_mode, string_mode);

        // Считываем имя владельца
        struct passwd *pws = getpwuid(st.st_uid);

        // Считываем группу владельца
        struct group *grp = getgrgid(st.st_gid);

        // Высчитываем последнее время изменения в человекочитаемом формате
        struct tm *time = gmtime(&st.st_mtimespec.tv_sec);
        char date[200];
        strftime(date, 200, "%b %d %H:%M", time);

        // Выводим значения с отступами
        printf("%c%.9s %3d %s %s %8lld %s %s\n", type, string_mode, st.st_nlink, pws->pw_name, grp->gr_name, st.st_size, date, dir->d_name);
    }

    return 0;
}