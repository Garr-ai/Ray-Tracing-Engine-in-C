#include <stdlib.h>
#include "spheres.h"
#include "vector.h"
#include "math.h"
#include <stdio.h>

void worldInit(World *world) {
    world->spheres = malloc(sizeof(Sphere*));
    world->size = 0;
    world->capacity = 1;
}

void freeWorld(World *world) {
    for (int i = 0; i < world->size; i++) {
        free(world->spheres[i]);
    }
    free(world->spheres);
    world->spheres = NULL;
    world->size = 0;
    world->capacity = 0;
}

void addSphere(World *world, Sphere *sphere) {
    if (world->size >= world->capacity) {
        world->capacity *= 2;
        world->spheres = realloc(world->spheres, sizeof(Sphere*));
    }
    world->spheres[world->size++] = sphere;
}

Sphere *createSphere(float radius, Vec3 position, Vec3 color) {
    Sphere *sphere = malloc(sizeof(Sphere));
    sphere->r = radius;
    sphere->pos = position;
    sphere->color = color;
    return sphere;
}

int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t) {
    Vec3 V = subtract(rayPos, sphere->pos);
    float a = dot(rayDir, rayDir);
    float b = 2 * dot(rayDir, V);
    float c = dot(V, V) - (sphere->r * sphere->r);
    float discriminant = b * b - 4 * a * c;


    if (discriminant < 0) {
        return 0;
    }

    float sqrtDiscriminant = sqrt(discriminant);
    float t1 = (-b - sqrtDiscriminant) / (2 * a);
    float t2 = (-b + sqrtDiscriminant) / (2 * a);

    if (t1 > 0 && t2 > 0) {
        *t = fmin(t1, t2); // Choose the closer intersection
        return 1;
    } else if (t1 > 0) {
        *t = t1;
        return 1;
    } else if (t2 > 0) {
        *t = t2;
        return 1;
    }

    return 0;
}

