#include "shell.h"

int handleExitCommand(info_t *info)
{
        int exitCode;

        if (info->argv[1]) 
        {
                exitCode = parseExitCode(info->argv[1]);
                if (exitCode == -1)
                {
                        info->status = 2;
                        printError(info, "Illegal number: ");
                        printErrorMessage(info->argv[1]);
                        printNewLine();
                        return 1;
                }
                info->errorNumber = parseExitCode(info->argv[1]);
                return -2;
        }

        info->errorNumber = -1;
        return -2;
}

int handleChangeDirectory(info_t *info)
{
        char *currentDir, *targetDir, buffer[1024];
        int chdirResult;

        currentDir = getCurrentWorkingDirectory(buffer, 1024);
        if (!currentDir)
                printError("TODO: >>getcwd failure emsg here<<\n");

        if (!info->argv[1])
        {
                targetDir = getEnvironmentVariable(info, "HOME=");
                if (!targetDir)
                        chdirResult = chdir((targetDir = getEnvironmentVariable(info, "PWD=")) ? targetDir : "/");
                else
                        chdirResult = chdir(targetDir);
        }
        else if (compareStrings(info->argv[1], "-") == 0)
        {
                if (!getEnvironmentVariable(info, "OLDPWD="))
                {
                        printString(currentDir);
                        printNewLine();
                        return 1;
                }
                printString(getEnvironmentVariable(info, "OLDPWD="));
                printNewLine();
                chdirResult = chdir((targetDir = getEnvironmentVariable(info, "OLDPWD=")) ? targetDir : "/");
        }
        else
                chdirResult = chdir(info->argv[1]);

        if (chdirResult == -1)
        {
                printError("can't cd to ");
                printErrorMessage(info->argv[1]);
                printNewLine();
        }
        else
        {
                setEnvironmentVariable(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
                setEnvironmentVariable(info, "PWD", getCurrentWorkingDirectory(buffer, 1024));
        }
        return 0;
}

int handleHelpCommand(info_t *info)
{
        char **argArray;

        argArray = info->argv;
        printString("help call works. Function not yet implemented \n");

        if (0)
                printString(*argArray); /* temp att_unused workaround */

        return 0;
}
