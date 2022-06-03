#include "receipter.h"
#include <stdio.h>

#define ITEM_NAME_LENGTH (25)
#define MAX_ITEM_COUNT (10)

#define MAX_MESSAGE_LENGTH (75)

struct item {
    char name[ITEM_NAME_LENGTH + 1];
    int name_length;
    double price;
};

typedef struct item item_t;

static size_t s_order_number = 0;

static item_t s_items[MAX_ITEM_COUNT];
static int s_items_index = 0;

static double s_tip = 0.0;

static char s_message[MAX_MESSAGE_LENGTH + 1];
static char s_message_length = 0;

int add_item(const char* name, double price)
{
    item_t item; 
    char* item_name_ptr = item.name;
    int i;
    
    if (s_items_index >= 10) {
        return FALSE;
    }   
   
    for (i = 0; i < ITEM_NAME_LENGTH && *name != '\0'; i++) {
        *item_name_ptr++ = *name++;
     }
    *item_name_ptr = '\0';
    
    item.name_length = i;
    item.price = price;
    
    s_items[s_items_index] = item;
    s_items_index++;

    return TRUE;
}

void set_tip(double tip)
{
    s_tip = tip;
}

void set_message(const char* message)
{
    int i;
    char* s_message_ptr = s_message;

    for (i = 0; i < MAX_MESSAGE_LENGTH && *message != '\0'; i++) {
        *s_message_ptr++ = *message++;
    }
    s_message_length = s_message_ptr - s_message;
    *s_message_ptr = '\0';
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* fs; 
    int i;
    double subtotal = 0.0;
    struct tm* t = localtime(&timestamp);
    
    char buffer[2048]; 
    char* buffer_ptr = buffer;    

    if (s_items_index <= 0) {
        return FALSE;
    }

    sprintf(buffer_ptr, "Charles' Seafood\r\n");
    buffer_ptr += 18;
    sprintf(buffer_ptr, "--------------------------------------------------\r\n");
    buffer_ptr += 52;
    sprintf(buffer_ptr, "%04d-%02d-%02d.%02d:%02d:%02d                          %05d\r\n", t -> tm_year + 1900, t -> tm_mon + 1, t -> tm_mday, t -> tm_hour, t -> tm_min, t -> tm_sec, s_order_number);
    buffer_ptr += 52;
    sprintf(buffer_ptr, "--------------------------------------------------\r\n");
    buffer_ptr += 52;

    for (i = 0; i < s_items_index; i++) {
        item_t item = s_items[i];
        sprintf(buffer_ptr, "        %25s           %6.2f\r\n", item.name, item.price);
        buffer_ptr += 52;
        subtotal += item.price;
    }
    sprintf(buffer_ptr, "\r\n");
    buffer_ptr += 2;
    sprintf(buffer_ptr, "                         Subtotal           %6.2f\r\n", subtotal);
    buffer_ptr += 52;

    if (s_tip > 0.0) {
        sprintf(buffer_ptr, "                              Tip           %6.2f\r\n", s_tip);
        buffer_ptr += 52;
    }
    
    sprintf(buffer_ptr, "                              Tax%17.2f\r\n", subtotal * 0.05);
    buffer_ptr += 52;
    sprintf(buffer_ptr, "                            Total%17.2f\r\n", subtotal + s_tip + subtotal * 0.05);
    buffer_ptr += 52;

    sprintf(buffer_ptr, "\r\n");
    buffer_ptr += 2;
    
    if (s_message_length > 0) {
        sprintf(buffer_ptr, "%s\r\n", s_message);
        buffer_ptr += s_message_length + 2;

        sprintf(buffer_ptr, "\r\n");
        buffer_ptr += 2;
    }

    sprintf(buffer_ptr, "==================================================\r\n");
    buffer_ptr += 52;

    sprintf(buffer_ptr, "                                        Tax#-51234");
    buffer_ptr += 50;
    
    fs = fopen(filename, "wb");
    fwrite(buffer, sizeof(buffer[0]), buffer_ptr - buffer, fs);
    fclose(fs);

    s_items_index = 0;
    s_tip = 0.0; 
    *s_message = '\0';
    s_message_length = 0;
    s_order_number++;
    
    return TRUE;
}
