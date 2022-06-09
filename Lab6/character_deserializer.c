#include "character_deserializer.h"
#include <stdio.h> 
#include <string.h>

typedef enum version {
    VERSION_ONE = 1, 
    VERSION_TWO = 2, 
    VERSION_THREE = 3
} version_t;

void get_character_v1(FILE* fp, character_v3_t* out_character);
void get_character_v2(FILE* fp, character_v3_t* out_character);
void get_character_v3(FILE* fp, character_v3_t* out_character);
void get_name(char* out, char* cp);

int get_character(const char* filename, character_v3_t* out_character) 
{
    FILE* fp = fopen(filename, "r");
    version_t file_version = 0;
    char c;
    
    c = getc(fp);
    while (c != EOF && file_version == 0) {
        switch (c) {
        case ':':
            file_version = VERSION_ONE;
            break;
        case ',': 
            file_version = VERSION_TWO;
            break;
        case '|':
            file_version = VERSION_THREE;
            break;
        default: 
            file_version = 0;
            break;
        }
        c = getc(fp);
    }
    
    
    printf("file_version : %d\n", file_version);
    
   
    fseek(fp, 0, SEEK_SET);
    switch (file_version) {
    case VERSION_ONE:    
        get_character_v1(fp, out_character);
        break;
    case VERSION_TWO: 
        get_character_v2(fp, out_character);
        break;
    case VERSION_THREE:
        get_character_v3(fp, out_character);
        break;
    default: 
        break;
    } 
    
    fclose(fp);
    return file_version;
}

void get_character_v1(FILE* fp, character_v3_t* out_character) 
{
    char buffer[256];     
    char* attribute;
    size_t index;
    int i;
    int magic_resistance;
    fgets(buffer, 256, fp);

    attribute = strtok(buffer, ",");

    for (i = 0; i < 8; i++) {

        index = 0;
        
        while (*attribute != '\0') {
            if (*attribute == ':') {
                *attribute = '\0';
                break;
            }
            index++;
            attribute++;
        }
        
        attribute -= index;

        
        if (strcmp(attribute, "id") == 0) {
            char name[51] = "player_";
            strcat(name, attribute + index + 1);
            name[50] = '\0';
            strncpy(out_character->name, name, 51);
        } else if (strcmp(attribute, "lvl") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->level));
        } else if (strcmp(attribute, "str") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->strength));
        } else if (strcmp(attribute, "dex") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->dexterity));
        } else if (strcmp(attribute, "intel") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->intelligence));
        } else if (strcmp(attribute, "def") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->armour));
        } else if (strcmp(attribute, "hp") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->health));
        } else if (strcmp(attribute, "mp") == 0) {
            sscanf(attribute + index + 1, "%d", &(out_character->mana));
        }
        attribute = strtok(NULL, ",");
    }
    magic_resistance = out_character->armour / 4;
    out_character->elemental_resistance.fire = magic_resistance / 3;
    out_character->elemental_resistance.cold = magic_resistance / 3;
    out_character->elemental_resistance.lightning = magic_resistance / 3;
    out_character->minion_count = 0;
    out_character->leadership = out_character->level / 10;
    out_character->evasion = out_character->dexterity / 2;
}


void get_character_v2(FILE* fp, character_v3_t* out_character) 
{
    char buffer[512];
    char name[128];
    char* cp;
    int magic_resistance;
    fgets(buffer, 512, fp);
    fgets(buffer, 512, fp);
    
    cp = strtok(buffer, ",");
    get_name(name, cp);
    name[50] = '\0';
    strncpy(out_character->name, name, 51);
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->level));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->strength));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->dexterity));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->intelligence));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->armour));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->evasion));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &magic_resistance);
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->health));
    cp = strtok(NULL, ",");
    sscanf(cp, "%d", &(out_character->mana));
    
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
    out_character->elemental_resistance.fire = magic_resistance / 3;
    out_character->elemental_resistance.cold = magic_resistance / 3;
    out_character->elemental_resistance.lightning = magic_resistance / 3;
}


void get_character_v3(FILE* fp, character_v3_t* out_character)
{
    
    char buffer[512];
    char* cp;
    char name[128];
    int i;
    
    fgets(buffer, 512, fp);
    fgets(buffer, 512, fp);
    
    cp = strtok(buffer, "|");
    get_name(name, cp);
    name[50] = '\0';
    strncpy(out_character->name, name, 51);
    cp = strtok(NULL, "|");
    
    sscanf(cp, "%d", &(out_character->level));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->health));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->mana));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->strength));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->dexterity));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->intelligence));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->armour));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->evasion));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->elemental_resistance.fire));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->elemental_resistance.cold));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->elemental_resistance.lightning));
    cp = strtok(NULL, "|");
    sscanf(cp, "%d", &(out_character->leadership));
    cp = strtok(NULL, "|");
    sscanf(cp, "%zu", &(out_character->minion_count));
    
    {
        int count = out_character->minion_count;
        if (count == 0) {
            return;
        }
        
        fgets(buffer, 512, fp);
        
        printf("minion count : %d \n", count);
    
        for (i = 0; i < count; i++) {
            minion_t minion;
            
            fgets(buffer, 512, fp);
        
            cp = strtok(buffer, "|");
            get_name(name, cp);
            name[50] = '\0';
            strncpy(minion.name, name, 51);
            cp = strtok(NULL, "|");
            sscanf(cp, "%d", &(minion.health));
            
            cp = strtok(NULL, "|");
            sscanf(cp, "%d", &(minion.strength));
            
            cp = strtok(NULL, "|");
            sscanf(cp, "%d", &(minion.defence));
            out_character->minions[i] = minion;   
        } 
        
    }
    
    
    
}

void get_name(char* out, char* cp) 
{
    
    int i = 0;
    while (*cp != '\0') {
        if (i >= 50) {
            break;
        }
        
        if ((*cp >= 'A' && *cp <= 'Z') || (*cp >= 'a' && *cp <= 'z') || (*cp >= '0' && *cp <= '9') || *cp == '_') {
            *out++ = *cp;
            i++;
        }
        cp++;
    }
    *out = '\0';
}


