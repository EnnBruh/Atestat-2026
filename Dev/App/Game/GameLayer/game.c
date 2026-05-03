#include "layer.h"

#include "Game/MapLayer/map.h"
#include "Game/objects.h"

LayerID game_layer_id;

static DataFile game_save;
Circuit global_circuit;

void game_start(const char* save_filepath) {
        DEBUG_TRACE();
        datafile_create(&game_save);
        datafile_read(&game_save, save_filepath);

        layer_set_active(game_ui_layer_id);
        layer_set_active(game_layer_id);
        layer_set_active(map_layer_id);
        DEBUG_UNTRACE();
}

void game_stop(void) {
        DEBUG_TRACE();
        datafile_write(&game_save, game_save.filepath);
        datafile_destroy(&game_save);

        layer_set_inactive(game_ui_layer_id);
        layer_set_inactive(game_layer_id);
        layer_set_inactive(map_layer_id);
        DEBUG_UNTRACE();
}

void game_layer_init(void) {
        DEBUG_TRACE();
        DEBUG_UNTRACE();
}

void game_layer_term(void) {
}

void game_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                2 / map_view.visible_pixels.x * map_view.zoom, 0, 0, -(2 * map_view.camera_offset.x ) / map_view.visible_pixels.x * map_view.zoom - 1.0,
                0, -(2 / map_view.visible_pixels.y * map_view.zoom), 0, (2 * map_view.camera_offset.y) / map_view.visible_pixels.y * map_view.zoom + 1.0,
                0, 0, -1, 0,
                0, 0, 0, 1
        });

        circuit_render_objects();
        DEBUG_UNTRACE();
}

void game_layer_on_update(f64 dt) {
}

void game_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;

                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS && !global_state.pause) {
                                global_state.pause = true;
                                layer_set_active(escape_menu_layer_id);
                                event -> handled = true;
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 map = screen_to_map((f32vec2) { data -> x, data -> y });
                        circuit_check_hovered_pin(map);
                        break;
                }
                default: break;
        }
        DEBUG_UNTRACE();
}