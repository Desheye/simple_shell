#include "shell.h"

int exitShell(info_t *info)
{
    int exitCode;

    if (info->argv[1])
    {
        exitCode = _erratoi(info->argv[1]);
        if (exitCode == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = _erratoi(info->argv[1]);
        return -2;
    }
    info->err_num = -1;
    return -2;
}

int changeDirectory(info_t *info)
{
    char *currentDir, *newDir, buffer[1024];
    int chdirResult;

    currentDir = getcwd(buffer, 1024);
    if (!currentDir)
        _puts("TODO: >>getcwd failure msg here<<\n");
    if (!info->argv[1])
    {
        newDir = _getenv(info, "HOME=");
        if (!newDir)
            chdirResult = chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
        else
            chdirResult = chdir(newDir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(currentDir);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD=")), _putchar('\n');
        chdirResult = chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
    }
    else
        chdirResult = chdir(info->argv[1]);
    if (chdirResult == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]), _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

int displayHelp(info_t *info)
{
    char **argArray;

    argArray = info->argv;
    _puts(" Function not yet implemented \n");
    if (0)
        _puts(*argArray); /* Temp att_unused  */
    return 0;
}

