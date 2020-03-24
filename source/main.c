// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

extern const char* do_the_thing();

// Main program entrypoint
int main(int argc, char* argv[])
{
    const char* ptr = NULL;

    consoleInit(NULL);

    printf("Hello World!\n");

    printf("ptr = %p\n", ptr);
    consoleUpdate(NULL);
    printf("*ptr = %s\n", ptr);
    consoleUpdate(NULL);

    consoleUpdate(NULL);

    ptr = do_the_thing();

    printf("ptr = %p\n", ptr);
    consoleUpdate(NULL);
    printf("*ptr = %s\n", ptr);
    consoleUpdate(NULL);

    while (appletMainLoop())
    {
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
            break;
        } else if (kDown & KEY_MINUS) {
            printf("ptr = %p\n", ptr);
        } else if (kDown & KEY_A) {
            printf("*ptr = %s\n", ptr);
        }

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
