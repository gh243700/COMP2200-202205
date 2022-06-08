#include "character_deserializer.h"
#include <stdio.h>

#define LENGTH (2048)

char* tokenize(char* src_or_null, const char* dilm, char** out_end);
void deserialize_character_v1(character_v3_t* out_character, char* src);
void deserialize_character_v2(character_v3_t* out_character, char* src);
void deserialize_character_v3(character_v3_t* out_character, char* src);
int str_cmp(char* str1, char* str2);
void name_len(char* src);

int get_character(const char* filename, character_v3_t* out_character)
{
    char buffer[LENGTH] = {'\0', };
    char c;
    int version = 2;
    void (*deserialize_character)(character_v3_t* out_character, char* src) = deserialize_character_v2;

    FILE* fp = fopen(filename, "rb");
    c = fgetc(fp);
    while (c != '\n' && c != EOF) {
        if (c == ':') {
            deserialize_character = deserialize_character_v1;
            version = 1;
            break;
        } else if (c == '|') {
            deserialize_character = deserialize_character_v3;
            version = 3;
            break;
        }
        c = fgetc(fp);
    } 
    
    fseek(fp, 0, SEEK_SET);
    fread(buffer, sizeof(char), LENGTH, fp);
    fclose(fp);
    deserialize_character(out_character, buffer);

    return version;
}

void deserialize_character_v3(character_v3_t* out_character, char* src)
{
    char* ptr; 
    char* temp;
    char* dummy;
    size_t i;
    
    ptr = tokenize(src, "\n", &dummy);
    ptr = tokenize(NULL, "\n", &temp);

    ptr = tokenize(ptr, " |", &dummy);
    name_len(ptr);
    sprintf(out_character -> name, "%s", ptr);

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> level));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> health));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> mana));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> strength));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> dexterity));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> intelligence));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> armour));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> evasion));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> elemental_resistance.fire));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> elemental_resistance.cold));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> elemental_resistance.lightning));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> leadership));   

    ptr = tokenize(NULL, " |", &dummy);
    sscanf(ptr, "%d", &(out_character -> minion_count));   

    ptr = tokenize(temp, "\n", &temp);

    if (ptr == NULL) {
        return;
    }
    ptr = tokenize(NULL, "\n", &temp);
    i = 0;
    while(ptr != NULL) {
        ptr = tokenize(ptr, " |", &dummy);
        name_len(ptr);
        sprintf(out_character -> minions[i].name, "%s", ptr);
        ptr = tokenize(NULL, " |", &dummy);
        sscanf(ptr, "%d", &(out_character -> minions[i].health));
        ptr = tokenize(NULL, " |", &dummy);
        sscanf(ptr, "%d", &(out_character -> minions[i].strength));
        ptr = tokenize(NULL, " |", &dummy);
        sscanf(ptr, "%d", &(out_character -> minions[i].defence));
        ptr = tokenize(temp, "\n", &temp);
        i++;
    }

} 

void deserialize_character_v2(character_v3_t* out_character, char* src) 
{
    char* ptr;
    unsigned int magic_resistance;
    char* dummy;
    ptr = tokenize(src, "\n", &dummy);
    ptr = tokenize(NULL, "\n", &dummy);

    ptr = tokenize(ptr, ", ", &dummy);
    name_len(ptr);
    sprintf(out_character -> name, "%s", ptr);

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> level));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> strength));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> dexterity));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> intelligence));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> armour));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> evasion));

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &magic_resistance);
    out_character -> elemental_resistance.fire = magic_resistance / 3;
    out_character -> elemental_resistance.cold = magic_resistance / 3;
    out_character -> elemental_resistance.lightning = magic_resistance / 3;

    ptr = tokenize(NULL, ", ", &dummy);
    sscanf(ptr, "%d", &(out_character -> health));
    ptr = tokenize(NULL, ", ", &dummy);
       
    sscanf(ptr, "%d", &(out_character -> mana));

    out_character -> leadership = out_character -> level / 10;
    out_character -> minion_count = 0; 
}


void deserialize_character_v1(character_v3_t* out_character, char* src)
{
    char* ptr;
    char* dummy;
    int i;

    ptr = tokenize(src, ",: ", &dummy);

    for (i = 0; i< 8; i++) {
        if (str_cmp("id", ptr) == 0) {
            int id;
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &id);
            sprintf(out_character -> name, "player_%d", id);
        } else if (str_cmp("lvl", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> level));
        } else if (str_cmp("str", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> strength));
        } else if (str_cmp("dex", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> dexterity));
        } else if (str_cmp("intel", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> intelligence));
        } else if (str_cmp("def", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> armour));
        } else if (str_cmp("hp", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> health));
        } else if (str_cmp("mp", ptr) == 0) {
            ptr = tokenize(NULL, ",: ", &dummy);
            sscanf(ptr, "%d", &(out_character -> mana));
        }

        ptr = tokenize(NULL, ",: ", &dummy);

    }    
    
    out_character -> evasion = out_character -> dexterity / 2;
    out_character -> elemental_resistance.fire = (out_character -> armour) / 4 / 3;
    out_character -> elemental_resistance.cold = (out_character -> armour) / 4 / 3;
    out_character -> elemental_resistance.lightning = (out_character -> armour) / 4 / 3;
    out_character -> leadership = out_character -> level / 10;
    out_character -> minion_count = 0; 
}

int str_cmp(char* str1, char* str2) 
{
    while(*str1 == *str2 && *str1 != '\0') {
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

void name_len(char* src)
{
    char* ptr = src;
    while (*ptr != '\0') {
        if (ptr - src >= 50) {
            *ptr = '\0';
            break;
        }
        ptr++;
    }
}

char* tokenize(char* src_or_null, const char* dilm, char** out_end) {
    static char* src;
    char* ptr;
    char* start_ptr;
    
    if (src_or_null != (void*) 0) {
        src = src_or_null;
    }
    ptr = src;
    start_ptr = src;

    if (*ptr == '\0') {
        return (void*) 0;
    }

    while (*ptr != '\0') {
        const char* dilm_ptr = dilm;
        while (*dilm_ptr != '\0') {
            if (*ptr == *dilm_ptr) {
                *ptr = '\0';
                src = ptr + 1;
                *out_end = src;
                if (start_ptr - ptr == 0) {
                    return tokenize((void*) 0, dilm, out_end);
                }

                return start_ptr;
            }
            dilm_ptr++;
        }
        ptr++;
    }

    src = ptr;    
    *out_end = src;

    return start_ptr;
}



