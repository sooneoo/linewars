#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <raylib.h>


typedef struct Object {
    void (*draw)(struct Object *);
    Vector2 (*size)(struct Object *);
    Vector2 (*position)(struct Object *);
} Object;


#define object_draw(T) (T)->draw((T))

#define object_size(T) (T)->size((T))

#define object_position(T) (T)->position((T))


#endif



