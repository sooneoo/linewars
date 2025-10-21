#include "linewars/soldier.h"


static void soldier_draw(Soldier * self) {

}


static Vector2 soldier_size(Soldier * self) {
    
}



static Vector2 soldier_position(Soldier * self) {
    return self->position;
}



Soldier soldier(Vector2 init_position, Texture2D walk_texture) {
    return (Soldier) {
        .super = {
            .draw = (void(*)(Object*)) soldier_draw
            , .size = (Vector2(*)(Object*)) soldier_size
            , .position = (Vector2 (*)(Object*)) soldier_position
        }
        , .walk_texture = walk_texture
        , .position = init_position
    };
}

