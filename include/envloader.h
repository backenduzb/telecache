#ifndef ENVLOADER_H
#define ENVLOADER_H

#include <stdio.h>
#include <string.h>

static char env_value[512];

#include <unistd.h>

static char *load_env(const char *variable)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("CWD = %s\n", cwd);
    FILE *fp = fopen("../.env", "r");

    if (!fp) {
        perror("fopen");
        return NULL;
    }

    printf(".env opened successfully\n");

    char line[512];

    while (fgets(line, sizeof(line), fp)) {
        printf("LINE: %s", line);

        line[strcspn(line, "\r\n")] = '\0';

        char *eq = strchr(line, '=');
        if (!eq)
            continue;

        *eq = '\0';

        printf("KEY=[%s] VALUE=[%s]\n", line, eq + 1);

        if (strcmp(line, variable) == 0) {
            strcpy(env_value, eq + 1);
            fclose(fp);
            return env_value;
        }
    }

    fclose(fp);
    return NULL;
}

#endif