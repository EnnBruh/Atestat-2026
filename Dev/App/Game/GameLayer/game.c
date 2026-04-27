#include "layer.h"

#include "Game/MapLayer/map.h"
#include "Game/objects.h"

LayerID game_layer_id;

void game_layer_init(void) {
        LOG("sizeof internal pin = %zu", (sizeof (InternalPin)));
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
        switch (event -> type) {
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;

                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS && !global_state.pause) {
                                global_state.pause = true;
                                // blur_layer_update_texture();

                                // layer_set_active(blur_layer_id);
                                layer_set_active(escape_menu_layer_id);
                                event -> handled = true;
                        }
                        break;
                }
                default: break;
        }
}