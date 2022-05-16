#include "cyber_spaceship.h"


const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    const char* cab_location_ptr = cab_start_location;
    size_t i; 
    size_t j;  
    const char* safe_zone_start_ptr = (void*) 0;
    const char* safe_zone_start_temp_ptr = (void*) 0;
    size_t safe_zone_count_temp = 0;

    *out_longest_safe_area_length = 0;

    if (cab_length == 0) {
        return (void*) 0;
    }

    if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    }
    
    for (i = 0; i < cab_length; i++) {
        size_t cluster_overlap = 0;
        
        for (j = 0; j < cluster_count; j++) {
            const char* cluster_ptr = cluster_start_locations[j];
            const size_t cluster_length = cluster_lengths[j]; 
            if (cab_location_ptr >= cluster_ptr && (cab_location_ptr < cluster_ptr + cluster_length)) {
                cluster_overlap++;    
            }
        }

        if (cluster_overlap % 2 == 0) {
            if (safe_zone_count_temp == 0) {
                safe_zone_start_temp_ptr = cab_location_ptr;
            }
            safe_zone_count_temp++;
            if (i == cab_length - 1) {
                goto label1;
            }
        } else {
label1:
            if (*out_longest_safe_area_length <= safe_zone_count_temp) {
                safe_zone_start_ptr = safe_zone_start_temp_ptr;
                *out_longest_safe_area_length = safe_zone_count_temp;
            }
            safe_zone_count_temp = 0;
        }
        cab_location_ptr++;
    }

     return safe_zone_start_ptr;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    const char* cab_location_ptr = cab_start_location;
    size_t i;
    size_t j;
    double travel_time = 0;
    size_t zone_count = 0;
    int is_safe = -1;    

    if (cluster_count == 0) { 
        return cab_length / 10;
    }

    for (i = 0; i < cab_length; i++) {
        size_t overlap_count = 0;   
        const size_t* cluster_length_ptr = cluster_lengths;
        for (j = 0; j < cluster_count; j++) {
            const char* cluster_start_location = cluster_start_locations[j];    
            if (cab_location_ptr >= cluster_start_location && cab_location_ptr < cluster_start_location + *cluster_length_ptr) {
                    overlap_count++;
                }
            cluster_length_ptr++; 
        }

        if (is_safe == -1) {
            is_safe = (overlap_count % 2) ? 0 : 1;
            goto label3;
        }
    
        if (i == cab_length - 1) {
            if (is_safe) {
                goto label1;
            } else {
                goto label2;
            }
        }

        if (overlap_count % 2) {
label1:
            if (is_safe) {
                travel_time += zone_count / 5.0;
                printf("safezone : %d\n", zone_count);
                zone_count = 0;
            }
            is_safe = 0;
        } else {
label2:
            if (!is_safe) {
                travel_time += zone_count / 10.0;
                printf("danger : %d\n", zone_count);
                zone_count = 0;
            }
            is_safe = 1;
        }
label3:
        zone_count++;        
        cab_location_ptr++;
    }

    printf("%f\n", travel_time);
    
    return (int)(travel_time);
}
