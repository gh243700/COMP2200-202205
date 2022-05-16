#include "cyber_spaceship.h"
#include <assert.h>
#include <stdio.h>

#define CAB_LENGTH (50)
int main(void)
{
{
    const char cyber_asteroid_belt[30];
    const char* cluster_start_addresses[2];
    size_t cluster_lengths[2];
    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    const char* cluster1 = &cyber_asteroid_belt[12];
    const char* cluster2 = &cyber_asteroid_belt[3];

    cluster_start_addresses[0] = cluster1;
    cluster_start_addresses[1] = cluster2;

    cluster_lengths[0] = 15U;
    cluster_lengths[1] = 25U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p); /* longest_safe_cluster_start_address: (cyber_asteroid_belt + 12), out_longest_safe_area_length: 15 */
    printf("%d\n", longest_safe_cluster_start_address - cyber_asteroid_belt);
    printf("%d\n", out_longest_safe_area_length);
    assert(longest_safe_cluster_start_address == cyber_asteroid_belt + 12);
    assert(out_longest_safe_area_length == 15);
} 

{
    const char cyber_asteroid_belt[30];
    const char* cluster_start_addresses[1];
    size_t cluster_lengths[1];
    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;
    
    const char* cluster1 = &cyber_asteroid_belt[0];
    cluster_start_addresses[0] = cluster1;
    cluster_lengths[0] = 26U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 1, out_longest_safe_area_length_p); /* longest_safe_cluster_start_address: (cyber_asteroid_belt + 12), out_longest_safe_area_length: 15 */
    printf("sss is %d\n", out_longest_safe_area_length);
    assert(out_longest_safe_area_length == 4);
    assert(longest_safe_cluster_start_address == cyber_asteroid_belt + 26);
}

{
    const char cyber_asteroid_belt[30];
    const char* cluster_start_addresses[2];
    size_t cluster_lengths[2];
    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    const char* cluster1 = &cyber_asteroid_belt[5];
    const char* cluster2 = &cyber_asteroid_belt[15];

    cluster_start_addresses[0] = cluster1;
    cluster_start_addresses[1] = cluster2;

    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p); /* longest_safe_cluster_start_address: (cyber_asteroid_belt + 12), out_longest_safe_area_length: 15 */
    printf("%d\n", longest_safe_cluster_start_address - cyber_asteroid_belt);
    printf("%d\n", out_longest_safe_area_length);
    assert(longest_safe_cluster_start_address == cyber_asteroid_belt + 25);
    assert(out_longest_safe_area_length == 5);
}


{
const char cyber_asteroid_belt[30];
const char* cluster_start_addresses[2];
size_t cluster_lengths[2];
int time_in_mins;

const char* cluster1 = &cyber_asteroid_belt[12];
const char* cluster2 = &cyber_asteroid_belt[3];

cluster_start_addresses[0] = cluster1;
cluster_start_addresses[1] = cluster2;

cluster_lengths[0] = 15U;
cluster_lengths[1] = 25U;

time_in_mins = get_travel_time(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 2); /* 4 */


assert(time_in_mins == 4);


}
{
    char cab[CAB_LENGTH];
    const char* cluster_start_addresses[5];
    size_t cluster_lengths[5];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;
    int time_in_mins;
    const char* cab_start_address = cab;

    cluster_start_addresses[0] = &cab[8];
    cluster_start_addresses[1] = &cab[1];
    cluster_start_addresses[2] = &cab[13];
    cluster_start_addresses[3] = &cab[33];
    cluster_start_addresses[4] = &cab[38];

    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 22U;
    cluster_lengths[2] = 10U;
    cluster_lengths[3] = 13U;
    cluster_lengths[4] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 15);
    assert(longest_safe_cluster_start_address == cab_start_address + 18);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5);
    printf("times in min %d\n", time_in_mins);
    assert(time_in_mins == 7);
}


{
const char cyber_asteroid_belt[30];
int time_in_mins;

time_in_mins = get_travel_time(cyber_asteroid_belt, 30, (void*)0, (void*)0, 0); /* 4 */


assert(time_in_mins == 3);





}

   printf("fin\n");
   return 0;
}
