/*
 *  Library to create folders, get the current directory path,
 *  and complement the file names with the current directory path
 *  and delete files and directory trees
 *  
 *  Author: Quemuel Alves Nassor
 *  Date: 27/12/20
 */


#ifndef DIR_MGMT_H
#define DIR_MGMT_H

#include <limits.h>
#include <stdlib.h>
#define MAX_ERROR_MESS (PATH_MAX + NAME_MAX)

#if defined(_WIN32) || defined(WIN32)
    #include <direct.h>
    #define ___getcwd _getcwd
    const char DIR_SEPARATOR_CHR = '\\';
#elif defined(__unix__)
    #include <unistd.h>
    #define ___getcwd getcwd
    const char DIR_SEPARATOR_CHR = '/';
#endif

char *error_mess(char *msg, char *path);
int mk_dir(char *path);
int get_parent_dir(char *path, char *parent_path);
int mk_dir_tree(char *path);
int rm_dir_tree(char *path);
char *get_cur_dir(void);
int join_path(char *path, char *folder_or_filename);
char *list_dir(char *path);
int rm_files(char *path);
int rm_all(char *path);

#endif
