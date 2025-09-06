#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_file.h"

int main(int argc, char* argv[])
{

   
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-help") == 0)) 
    {
        printf("MP3 Tag Reader Help Menu:\n");
        printf(" To View tags in MP3 file  -->>>   ./a.out -v <filename>\n");
        printf(" To Edit a tag in MP3 file -->>>   ./a.out -e <filename> <tag_option> <new_value>\n");
        printf("Tag options:\n");
        printf("  -t    Title\n");
        printf("  -a    Artist\n");
        printf("  -A    Album\n");
        printf("  -y    Year\n");
        printf("  -c    Composer\n");
        printf("  -g    Genre\n");

        return 0;
    }

    // View mode: ./a.out -v <filename>
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        FILE* fptr = fopen(argv[2], "r");
        if (fptr == NULL)
        {
            printf("\033[1;31mUnable to open file '%s'\n\033[0m", argv[2]);
            return 1;
        }
        read_tags(fptr);
        fclose(fptr);
        return 0;
    }

 
    if (argc == 5 && strcmp(argv[1], "-e") == 0) 
    {
        const char* tag_flag = argv[3];
        const char* tag_code = NULL;

        if (strcmp(tag_flag, "-t") == 0)
            tag_code = "TIT2";  // Title
        else if (strcmp(tag_flag, "-a") == 0)
            tag_code = "TPE1";  // Artist
        else if (strcmp(tag_flag, "-A") == 0)
            tag_code = "TALB";  // Album
        else if (strcmp(tag_flag, "-y") == 0)
            tag_code = "TYER";  // Year
        else if (strcmp(tag_flag, "-c") == 0)
            tag_code = "COMM";  // Composer
        else if (strcmp(tag_flag, "-g") == 0)
            tag_code = "TCON";  // Genre
       else 
       {
        printf("\033[1;31mInvalid tag flag '%s'. Use -t, -a, -A, -y, -c, -g.\n\033[0m", tag_flag);
        return 1;
        }
        
        char new_value[150];
        strncpy(new_value, argv[4], sizeof(new_value)-1);
        new_value[sizeof(new_value)-1] = '\0';

        // Check ID3 version
        FILE* ver_file = fopen(argv[2], "r");
        if (!ver_file || !check_id3_version(ver_file)) 
        {
            printf("\033[1;31mUnsupported or corrupt MP3 file.\n\033[0m");
            if (ver_file) fclose(ver_file);
            return 1;
        }
        fclose(ver_file);

        FILE* src = fopen("temp.mp3", "w");
        FILE* des = fopen(argv[2], "r");
        if (!src || !des) 
        {
            printf("\033[1;31mError opening files for editing.\n\033[0m");
            if (src) fclose(src);
            if (des) fclose(des);
            return 1;
        }

        int status = copy_remain(src, des, new_value, tag_code);
        fclose(src);
        fclose(des);

        if (status == 0) 
        {
            if (remove(argv[2]) != 0) 
            {
                printf("\033[1;31mError deleting original file.\n\033[0m");
                remove("temp.mp3");
                return 1;
            }
            if (rename("temp.mp3", argv[2]) != 0)
            {
                printf("\033[1;31mError renaming temp file.\n\033[0m");
                return 1;
            }
            printf("\033[1;32mTag updated successfully!\n\033[0m");
        } else
        {
            printf("\033[1;31mFailed to update tag.\n\033[0m");
            remove("temp.mp3");
            return 1;
        }
        return 0;
    }

   
        printf("MP3 Tag Reader Help Menu:\n");
        printf(" To View tags in MP3 file  -->>>   ./a.out -v <filename>\n");
        printf(" To Edit a tag in MP3 file -->>>   ./a.out -e <filename> <tag_option> <new_value>\n");
        printf("Tag options:\n");
        printf("  -t    Title\n");
        printf("  -a    Artist\n");
        printf("  -A    Album\n");
        printf("  -y    Year\n");
        printf("  -c    Composer\n");
        printf("  -g    Genre\n");

        
        return 1;
}
