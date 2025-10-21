#ifndef _SOLDIER_H_
#define _SOLDIER_H_

#include <raylib.h>
#include "object.h"


typedef struct {
    Object super;
    Texture2D walk_texture;
    Vector2 position;
} Soldier;


Soldier soldier(Vector2 init_position, Texture2D walk_texture);


#endif



