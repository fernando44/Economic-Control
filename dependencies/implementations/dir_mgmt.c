/*
 *  Library to create folders, get the current directory path,
 *  and complement the file names with the current directory path
 *  and delete files and directory trees
 *  
 *  Author: Quemuel Alves Nassor
 *  Date: 27/12/20
*/

/*
    Dependencies
*/
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#if defined(_WIN32) || defined(WIN32)
    #include "..\include\dir_mgmt.h"
#elif defined(__unix__)
    #include "../include/dir_mgmt.h"
#endif

/*
    Function to validate error message
        parameter: msg, error message to return
        parameter: path, place of error
        return: validated error message on success or empty on failure
*/
char *error_mess(char *msg, char *path)
{

    char *errorMessage = (char *)malloc(MAX_ERROR_MESS * sizeof(char));
    errorMessage[0] = '\0';

    if ((int)strlen(msg) == 0 && (int)strlen(path) == 0)
    {
        errorMessage = NULL;
        errno = ENODATA;
        perror("Invalid message");
    }
    else if ((int)strlen(msg) + (int)strlen(path) > MAX_ERROR_MESS)
    {
        errorMessage = NULL;
        errno = EMSGSIZE;
        perror("The error message is too long");
    }
    else
    {
        strcpy(errorMessage, msg);
        strcat(errorMessage, " (");
        strcat(errorMessage, path);
        strcat(errorMessage, ")\0");
    }

    return errorMessage;
}

/*
    Function to create a single folder
        parameter: path, place where the folder will be created
        return: errno code on error or EXIT_SUCCESS on success;
*/

#if defined(_WIN32) || defined(WIN32)
#include <direct.h>
int mk_dir(char *path)
{

    if (mkdir(path) != 0)
    {
        char *errorMessage = ERROR_MESS("Failed to create folder", path);
        perror(errorMessage);
    }

    return errno;
}
#elif __unix__
#include <unistd.h>

int mk_dir(char *path)
{

    if (mkdir(path, 0777) != 0)
    {
        char *errorMessage = error_mess("Failed to create folder", path);
        perror(errorMessage);
    }

    return errno;
}

#endif

/*
    Function to get the parent directory of a path
        parameter: path, path from where will get parent
        parameter: parent_path, path parent directory
        return: errno code on error or EXIT_SUCCESS on success;
*/
int get_parent_dir(char *path, char *parent_path)
{
    struct stat st = {0};                                         /*File structure*/
    char *last_file_or_folder = strrchr(path, DIR_SEPARATOR_CHR); /*Find and retrieve the string starting with the last character DIR_SEPARATOR_CHR*/
    int size = (int)(strlen(path) - strlen(last_file_or_folder));

    parent_path = (char *)malloc(size * sizeof(char));
    parent_path[0] = '\0';

    if (last_file_or_folder != NULL)
    {
        strncpy(parent_path, path, size); /*Copy path without the last folder*/
        parent_path[size] = '\0';
    }

    return stat(path, &st); /*Testing if path is valid*/
}

/*
    Function to create directory tree
        parameter: path, place where the folder(s) will be created
        return: errno code on error or EXIT_SUCCESS on success;
*/
int mk_dir_tree(char *path)
{

    /* struct stat st = {0};                               /*File structure*/
    /* char *sep = strrchr(path, DIR_SEPARATOR_CHR);       /*Find and retrieve the string from the last character DIR_SEPARATOR_CHR*/
    /* char new_path[(int)strlen(path)];                   /*New path without the last folder*/
    /* new_path[0] = '\0';*/
    /* if(sep != NULL){*/
    /*     strncpy(new_path,path,(sep-path));              /*Copy path without the last folder*/
    /*     new_path[(sep-path)] = '\0';*/
    /* }*/

    /* int result = stat(path, &st);                       /*Testing if path is valid*/

    char *parent_path;
    int result = get_parent_dir(path, parent_path);

    if (result == 0 && errno == 0)
    {
        errno = EEXIST;
        char *errorMessage = error_mess("Directory tree exist", path);
        perror(errorMessage);
    }

    if (result == EXIT_FAILURE && errno == ENOENT && (int)strlen(parent_path) != 0)
    {
        mk_dir_tree(parent_path); /*Recursion call*/
        mk_dir(path);             /*Return of recursion*/
        /* result = stat(path, &st);                       /*Testing if path is valid*/
        get_parent_dir(path, parent_path) == 0 ? errno = EXIT_SUCCESS : 0;
    }
    else if ((result == EXIT_FAILURE && errno != ENOENT) || (result == EXIT_FAILURE && errno == ENOENT && (int)strlen(parent_path) == 0))
    {
        char *errorMessage = error_mess("Failed to create directory tree", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to remove directory tree
        parameter: path, place where the folder (s) are
        return: errno code on error or EXIT_SUCCESS on success;
*/
int rm_dir_tree(char *path)
{

    /* struct stat st = {0};                               /*File structure*/
    /* char new_path[(int)strlen(path)];                        /*New path without the last folder*/
    /* char *sep = strrchr(path, DIR_SEPARATOR_CHR);       /*Find and retrieve the string from the last character DIR_SEPARATOR_CHR*/
    /* new_path[0] = '\0';*/
    /* if(sep != NULL){*/
    /*     strncpy(new_path,path,(sep-path));              /*Copy path without the last folder*/
    /*     new_path[(sep-path)] = '\0';*/
    /* }*/

    rmdir(path);

    char *parent_path;
    int result = get_parent_dir(path, parent_path);

    /* int result = stat(path, &st);                       /*Testing if path is valid*/

    if ((int)strlen(parent_path) != 0 && errno == ENOENT)
    {
        rm_dir_tree(parent_path);
        /* result = stat(path, &st);                       /*Testing if path is valid*/
        get_parent_dir(path, parent_path) == EXIT_FAILURE ? errno = EXIT_SUCCESS : 0;
    }
    else if ((int)strlen(parent_path) == 0 && errno != ENOENT)
    {
        char *errorMessage = error_mess("Failed to remove directory tree", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to get current directory path
        parameter: void
        return: NULL on error or current directory path on success;
*/
char *get_cur_dir(void)
{
    size_t size = PATH_MAX * sizeof(char);
    char *BASE_PATH = (char *)malloc(size);

    if (___getcwd(BASE_PATH, size) == NULL)
    {
        BASE_PATH = NULL;
        perror("Failed to get the current working directory");
    }

    return BASE_PATH;
}

/*
    Function to join directory path with file name or folder name
        parameter: path, where the name of the file or folder will be concatenated
        parameter: folder_or_filename, the file or folder that will be concatenated
        return: errno code on error or EXIT_SUCCESS on success;
*/
int join_path(char *path, char *folder_or_filename)
{
    if ((int)strlen(path) > 0 || (int)strlen(folder_or_filename) > 0)
    {
        path[(int)strlen(path)] = (int)strlen(path) > 0 ? DIR_SEPARATOR_CHR : '\0';
        path[(int)strlen(path) + (int)strlen(folder_or_filename)] = '\0';
        strcat(path, folder_or_filename);
    }
    else
    {
        char msg[MAX_ERROR_MESS] = "Failed to join paths (";
        strcat(msg, path);
        strcat(msg, " and\0");
        char *errorMessage = error_mess(msg, folder_or_filename);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to list content of an folder
        parameter: path, location of the content that will be listed
        return: list of strings with content of the informed path
*/
char *list_dir(char *path)
{
    char *listContent = (char *)malloc((NAME_MAX + 1) * sizeof(char));
    char *errorMessage = "\0";
    listContent[0] = '\0';

    DIR *directory = opendir(path);
    struct dirent *lsdir;

    if (errno == 0)
    {

        /*Loop to search and concatenate content*/
        while ((lsdir = readdir(directory)) != NULL)
        {
            if (strcmp(lsdir->d_name, ".") != 0 && strcmp(lsdir->d_name, "..") != 0)
            {
                char *aux = listContent;
                listContent = (char *)malloc(sizeof(lsdir->d_name) + sizeof(aux));
                strcpy(listContent, aux);
                strcat(listContent, lsdir->d_name);
                listContent[(int)strlen(listContent)] = ',';
            }
        };

        listContent[(int)strlen(listContent) - 1] = '\0';
    }

    if (errno == ENOENT || errno != 0)
    {
        listContent = NULL;
        errorMessage = error_mess("Failed to list content of informed path", path);
        perror(errorMessage);
    }
    else if ((int)strlen(listContent) == 0 && errno == 0)
    {
        listContent = NULL;
        errno = ENODATA;
        errorMessage = error_mess("Directory is empty", path);
        perror(errorMessage);
    }

    return listContent;
}

/*
    Function to remove multiple files from one place
        parameter: path, place of the content to be removed
        return: errno code in error or EXIT_SUCCESS in success;
*/
int rm_files(char *path)
{

    char *listContent = list_dir(path); /*Informed directory contents*/
    int i = 0, size = (int)strlen(listContent);
    char name[NAME_MAX + 1] = "\0";

    if (errno == 0)
    {
        /*Loop to identify and remove files*/
        for (i = 0; i <= size; i++)
        {

            if (listContent[i] != ',' && listContent[i] != '\0')
            {
                name[(int)strlen(name)] = listContent[i];
            }
            else
            {
                char *extension = strrchr(name, '.'); /*Find and retrieve the string starting with the last character '.'*/
                char fullpath[PATH_MAX] = "\0";
                join_path(fullpath, path);
                join_path(fullpath, name);

                if (extension != NULL)
                {
                    remove(fullpath);

                    if (errno != 0 || (strcmp(fullpath, path) == 0 || (int)strlen(name) == 0))
                    {
                        i = size + 1;
                        char *errorMessage = error_mess("Failed to clean item", fullpath);
                        perror(errorMessage);
                    }
                }

                int j;
                for (j = 0; j < PATH_MAX + 1; j++)
                {
                    fullpath[j] = '\0';
                    j < (NAME_MAX + 1) ? name[j] = '\0' : 0;
                }
            }
        }
    }

    if ((int)strlen(path) == 0 || errno != 0)
    {
        char *errorMessage = error_mess("Failed to clean items of informed path", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to remove multiple contents into directory
        parameter: path, place of the content to be removed
        return: errno code in error or EXIT_SUCCESS in success;
*/
int rm_all(char *path)
{

    printf("\ninicio da função\n");

    /* printf("\ncaminho {%s}", path);*/

    /* printf("\nconteudo do diretorio {%s}", LIST_DIR(path));*/

    /* struct stat st = {0};                               /*File structure*/
    char *listContent = list_dir(path), *parent; /*Informed directory contents*/
    int i = 0, size = 0;
    char name[NAME_MAX + 1] = "\0";
    size = listContent != NULL ? (int)strlen(listContent) : 0;

    /* printf("\nconteudo do diretorio {%s}", listContent);*/
    /* printf("\nsize {%i}", size);*/

    int result = get_parent_dir(path, parent);
    printf("result {%i}", result);

    if (result == 0 && size > 0)
    {
        rm_files(path); /*cleaning files from current dir*/
        /* listContent = LIST_DIR(path);*/
        printf("\nremovendo arquivos do diretorio {%s}\0", path);
        setbuf(stdin, NULL);
        getchar();
    }

    printf("\nremoveu os arquivos\0");

    if ((errno == 0 || errno == ENODATA) && size > 0)
    {
        /*Loop to identify and remove files*/
        for (i = 0; i <= size; i++)
        {

            if (listContent[i] != ',' && listContent[i] != '\0')
            {
                name[(int)strlen(name)] = listContent[i];
            }
            else
            {

                char *extension = strrchr(name, '.'); /*Find and retrieve the string starting with the last character '.'*/
                char fullpath[PATH_MAX] = "\0";
                int j;

                join_path(fullpath, path);
                join_path(fullpath, name);

                if (extension == NULL)
                {

                    if (errno == 0 || errno == ENODATA)
                    {
                        printf("\n\n recursive to {%s}\n\n", fullpath);
                        setbuf(stdin, NULL);
                        getchar();
                        rm_all(fullpath); /*Recursive call*/
                        printf("removendo arvore de diretorio {%s}", name);
                        rm_dir_tree(name); /* Removing dir tree*/
                    }
                    printf("\n\n recursive out {%s}\n\n", path);
                    setbuf(stdin, NULL);
                    getchar();
                    /**/
                    /* remove(fullpath);*/

                    if (errno != 0 || (strcmp(fullpath, path) == 0 || (int)strlen(name) == 0))
                    {
                        i = size + 1;
                        char *errorMessage = error_mess("Failed to clean item", fullpath);
                        perror(errorMessage);
                    }
                }

                for (j = 0; j < PATH_MAX + 1; j++)
                {
                    fullpath[j] = '\0';
                    j < (NAME_MAX + 1) ? name[j] = '\0' : 0;
                }
            }
        }
    }

    if ((int)strlen(path) == 0 || errno != 0)
    {
        printf("errno {%i}", errno);
        char *errorMessage = error_mess("Failed to clean items of informed path", path);
        perror(errorMessage);
    }
    else if (errno == ENOTEMPTY)
    {
        char *errorMessage = error_mess("Found and directory that not can be deleted (", path);
        perror(errorMessage);
    }

    return errno;
}
