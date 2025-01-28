#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include <string.h>

void main(void)
{
    // if (IS_MOBILE_PHONE_CALL_ONGOING())
    // {

    // }
    if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
        char* txt = (char*)malloc(40*sizeof(char));
        if (txt != NULL)
        {
            strcpy(txt, "Test hello world");
            PRINT_STRING_IN_STRING("string", txt, 5000, 1);
        }
    }
}