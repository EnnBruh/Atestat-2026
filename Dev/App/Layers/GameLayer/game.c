#include "Layers/layer.h"

#include "Layers/GameLayer/map.h"

LayerID game_layer_id;

void game_layer_init(void) {
}

void game_layer_term(void) {
}

void game_layer_on_render(void) {
        map_render();
        render_rectangle_push(
                (f32vec2) { -20, -20 },
                (f32vec2) { 20, 20 },
                0xFF0000FF);
}

void game_layer_on_update(f64 dt) {
}

void game_layer_on_event(Event* event) {
        map_on_event(event);
}