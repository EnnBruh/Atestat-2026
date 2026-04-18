#include "Layers/layer.h"

#include "Layers/MapLayer/map.h"

LayerID game_layer_id;

void game_layer_init(void) {
}

void game_layer_term(void) {
}

void game_layer_on_render(void) {
        // render_proj_set((f32mat4) {
        //         2 / map_view.visible_pixels.x * map_view.zoom, 0, 0, -(2 * map_view.camera_offset.x ) / map_view.visible_pixels.x * map_view.zoom - 1.0,
        //         0, -(2 / map_view.visible_pixels.y * map_view.zoom), 0, (2 * map_view.camera_offset.y) / map_view.visible_pixels.y * map_view.zoom + 1.0,
        //         0, 0, -1, 0,
        //         0, 0, 0, 1
        // });
        render_rectangle_push(
                (f32vec2) { -20, -20 },
                (f32vec2) { 20, 20 },
                0xFF0000FF);
}

void game_layer_on_update(f64 dt) {
}

void game_layer_on_event(Event* event) {
}