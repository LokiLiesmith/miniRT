#include "mini_rt.h"

//get random number from seed - scrambles bits
// based off of wang_hash
static double hash_double(unsigned int seed)
{
    seed ^= seed >> 17;// shift and XOR
    seed *= 0xed5ad4bbU;// 3981806795
    seed ^= seed >> 11;
    seed *= 0xac4c1b51U;// 2891336457
    seed ^= seed >> 15;
    seed *= 0x31848babU;// 830770091
    seed ^= seed >> 14;
    return (seed & 0xFFFFFFu) / (double)0x1000000u; // [0,1) - normalize(divide by max)
}

static unsigned int build_seed(unsigned int x, unsigned int y, unsigned int sample_id)
{
    unsigned int    s;

    s = 0;
    s ^= x * 73856093u;
    s ^= y * 19349663u;
    s ^= sample_id * 83492791u;

    if (s == 0)
        s = 1;
    return (s);
}

// double wang_hash(uint32_t x)
// {
//     x ^= 61U;//U for unsigned so it wraps
//     x ^= x >> 16;//shift 16 and XOR
//     x += x << 3;
//     x ^= x >> 4;
//     x *= 0x27d4eb2dU;
//     x ^= x >> 15;

//     return((x & 0xFFFFFFu) / (double)0x1000000u);
// }

// samples the volume of a sphere
// returns a random vector inside the sphere of size 1;
t_vec3  random_in_unit_sphere(unsigned int seed)
{
    double  x;
    double  y;
    double  z;
    double  r2;
    t_vec3  result;
    
    while (1)
    {
        // / RAND_MAX to get in range of [0,..,1]
        // multiply by 2 to extend it to [0,..., 2]
        // shift -1 so the range is from [-1, ... , 1]
        
        // // Using Rand leads to lower performance because the threads need to wait for rand
        // x = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
        // y = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
        // z = 2.0 * ((double)rand() / RAND_MAX) - 1.00;
        
       
        x = 2.0 * hash_double(seed + 1) - 1.00;
        y = 2.0 * hash_double(seed + 2) - 1.00;
        z = 2.0 * hash_double(seed + 3) - 1.00;
       
        //check sphere equation x^2 + y^2 + z^2 = 1
        r2 = x*x + y*y + z*z;
        if (r2 > 0.0 && r2 <= 1.0)
        {
            result.x = x;
            result.y = y;
            result.z = z;
            return (result);
        }
        seed += 0x9E3779B9u;
    }
}
// static t_vec3 random_on_unit_sphere(unsigned int seed)
// {
//     double z = 2.0 * hash_double(seed) - 1.0;
//     double a = 2.0 * M_PI * hash_double(seed + 1);
//     double r = sqrt(1.0 - z*z);
//     t_vec3 v = { r * cos(a), r * sin(a), z };
//     return v;
// }

static t_vec3 random_on_unit_disk(unsigned int seed)
{
    t_vec3  random;
    double  u1;
    double  u2;
    double  r;
    double  theta;
    double  x;
    double  y;

    u1 = hash_double(seed);
    u2 = hash_double(seed + 1);
    r = sqrt(u1);
    theta = 2 * M_PI * u2;
    x = r * cos(theta);
    y = r * sin(theta);
    random.x = x;
    random.y = y;
    random.z = 0.0;
    return (random);
}

// // visibility = calc_soft_shadow(rt, hit, x, y);
//     // generate 16 shadow rays and shoot them at the light
//     // check if they hit the random_in_unit_sphere generated vector + light location
//     // return how many hit/nr_shot
// double calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
// {
//     unsigned int    samples = 4;
//     int             visible = 0;
//     unsigned int    i = 0;
//     unsigned int    seed;
//     t_vec3          jitter;
//     double          light_radius = 5;//TODO add to light struct

//     t_vec3 origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));

//     while(i < samples)
//     {
//         seed = build_seed(x, y, i);
//         // jitter = random_in_unit_sphere(seed);
//         jitter = random_on_unit_sphere(seed ^ (i * 0x9e3779b9u));
//         t_vec3 sample_pos = vec_add(rt->scene.light.pos, vec_scale(jitter, light_radius));

//         //build shadow_ray
//         t_vec3 to_light = vec_subtract(sample_pos, origin);

//         double  light_dist = vec_len(to_light);
//         if (light_dist <= 0.0)//check cuz floating point math
//         {
//             i++;
//             continue;
//         }
//         t_ray shadow_ray;
//         shadow_ray.origin = origin;
//         shadow_ray.dir = vec_normalize(to_light);

//         t_hit shadow_hit = check_intersections(shadow_ray, rt);
//         if(shadow_hit.t <= 0.0 || shadow_hit.t >= light_dist)
//             visible++;

//         i++;
//     }
//     return((double)visible / (double)samples);
// }

double calc_soft_shadow(t_rt *rt, t_hit hit, unsigned int x, unsigned int y)
{
    unsigned int    samples = rt->samples;
    int             visible = 0;
    unsigned int    i = 0;
    unsigned int    seed;
    double          light_radius = 2;//TODO add to light struct


    t_vec3 origin = vec_add(hit.point, vec_scale(hit.normal, 1e-4));
    t_vec3 to_light = vec_subtract(rt->scene.light.pos, origin);
    t_vec3 disk_normal = vec_normalize(vec_scale(to_light, -1.00));
    t_view  disk_view = rotate_disk_to_world_view(disk_normal);

    while (i < samples)
    {
        seed = build_seed(x, y, i);
        t_vec3 sample = random_on_unit_disk(seed);
        t_vec3 sample_pos = vec_add(rt->scene.light.pos,
            vec_add(vec_scale(disk_view.right, sample.x * light_radius),
            vec_scale(disk_view.up, sample.y * light_radius)));
        t_vec3 to_sample = vec_subtract(sample_pos, origin);
        if (vec_len(to_sample) <= 0.0)
        {
            i++;
            continue;
        }
        t_ray shadow_ray;
        shadow_ray.origin = origin;
        shadow_ray.dir = vec_normalize(to_sample);

        t_hit shadow_hit = check_intersections(shadow_ray, rt);
        if (shadow_hit.t <= 0.0 || shadow_hit.t >= vec_len(to_sample))
			visible++;
		i++;
	}
    return ((double)visible / (double)samples);
}
