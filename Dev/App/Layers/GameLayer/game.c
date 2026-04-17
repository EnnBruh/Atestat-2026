#include "Layers/layer.h"

#include "Layers/GameLayer/map.h"

LayerID game_layer_id;

void game_layer_init(void) {
}

void game_layer_term(void) {
}

void game_layer_on_render(void) {
        // render_proj_set((f32mat4) {
        //         1, 0, 0, 0,
        //         0, -1, 0, 0,
        //         0, 0, 1, 0,
        //         0, 0, 0, 1
        // });

        // render_rectangle_push(
        //         (f32vec2) { -1.0, -1.0 },
        //         (f32vec2) { 1.0, 1.0 },
        //         0x101214FF);
        
        // render_line_push(
        //         (f32vec2) { -1.0, -1.0 },
        //         (f32vec2) { 1.0, 1.0 },
        //         0.01, 0xFF0000FF);
}

void game_layer_on_update(f64 dt) {
}

void game_layer_on_event(Event* event) {
}