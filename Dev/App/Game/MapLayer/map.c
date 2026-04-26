#include "Game/MapLayer/map.h"

LayerID map_layer_id;

struct MapView map_view = {
        .visible_pixels = { .x = 320, .y = 180 },
        .camera_offset = { .x = 0, .y = 0 },
        .zoom = 1.0,
        .start_pan = { .x = 0, .y = 0 }
};

void map_layer_init(void) {
}

void map_layer_term(void) {
}

void map_layer_on_render(void) {
        render_proj_set((f32mat4) {
                2 / map_view.visible_pixels.x * map_view.zoom, 0, 0, -(2 * map_view.camera_offset.x ) / map_view.visible_pixels.x * map_view.zoom - 1.0,
                0, -(2 / map_view.visible_pixels.y * map_view.zoom), 0, (2 * map_view.camera_offset.y) / map_view.visible_pixels.y * map_view.zoom + 1.0,
                0, 0, -1, 0,
                0, 0, 0, 1
        });

        f32vec2 top_left = ndc_to_map((f32vec2) { -1.0, 1.0 });
        f32vec2 bott_right = ndc_to_map((f32vec2) { 1.0, -1.0 });

        render_rectangle_push(
                top_left, bott_right,
                ENN_MAP_BCKG_COLOR);

        for (i32 x = floor(top_left.x / ENN_MAP_GRID_CELL_SIZE) * ENN_MAP_GRID_CELL_SIZE; x <= bott_right.x; x += ENN_MAP_GRID_CELL_SIZE) {
                render_line_push(
                        (f32vec2) { x + ENN_MAP_GRID_CELL_SIZE / 2, top_left.y },
                        (f32vec2) { x + ENN_MAP_GRID_CELL_SIZE / 2, bott_right.y },
                        ENN_MAP_GRID_LINE_WIDTH, ENN_MAP_GRID_SECOND_COLOR);

        }

        for (i32 y = floor(top_left.y / ENN_MAP_GRID_CELL_SIZE) * ENN_MAP_GRID_CELL_SIZE; y <= bott_right.y; y += ENN_MAP_GRID_CELL_SIZE) {
                render_line_push(
                        (f32vec2) { top_left.x, y + ENN_MAP_GRID_CELL_SIZE / 2 },
                        (f32vec2) { bott_right.x, y + ENN_MAP_GRID_CELL_SIZE / 2 },
                        ENN_MAP_GRID_LINE_WIDTH, ENN_MAP_GRID_SECOND_COLOR);

        }

        for (i32 x = floor(top_left.x / ENN_MAP_GRID_CELL_SIZE) * ENN_MAP_GRID_CELL_SIZE; x <= bott_right.x; x += ENN_MAP_GRID_CELL_SIZE) {
                render_line_push(
                        (f32vec2) { x, top_left.y },
                        (f32vec2) { x, bott_right.y },
                        ENN_MAP_GRID_LINE_WIDTH, ENN_MAP_GRID_MAIN_COLOR);
        }

        for (i32 y = floor(top_left.y / ENN_MAP_GRID_CELL_SIZE) * ENN_MAP_GRID_CELL_SIZE; y <= bott_right.y; y += ENN_MAP_GRID_CELL_SIZE) {
                render_line_push(
                        (f32vec2) { top_left.x, y },
                        (f32vec2) { bott_right.x, y },
                        ENN_MAP_GRID_LINE_WIDTH, ENN_MAP_GRID_MAIN_COLOR);
        }
}

void map_layer_on_update(f64 dt) {
}

void map_layer_on_event(Event* event) {
        switch (event -> type) {
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        f64* offset = event -> data;

                        f32vec2 before = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });

                        if (*offset > 0.0) {
                                if (map_view.zoom < ENN_MAP_ZOOM_MAX)
                                        map_view.zoom *= ENN_MAP_ZOOM_PLUS;
                        }
                        else {
                                if (map_view.zoom > ENN_MAP_ZOOM_MIN)
                                        map_view.zoom *= ENN_MAP_ZOOM_MINUS;
                        }

                        f32vec2 after = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });

                        map_view.camera_offset.x += (before.x - after.x);
                        map_view.camera_offset.y += (before.y - after.y);
                        event -> handled = true;
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;

                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS && global_state.is_key_down[GLFW_KEY_SPACE]) {
                                map_view.start_pan = (f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y };
                                event->handled = true;
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_SPACE && data -> action == GLFW_PRESS && global_state.is_button_down[GLFW_MOUSE_BUTTON_LEFT]) {
                                map_view.start_pan = (f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y };
                                event -> handled = true;
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        if (global_state.is_button_down[GLFW_MOUSE_BUTTON_LEFT] && global_state.is_key_down[GLFW_KEY_SPACE]) {
                                f32vec2 pos = ((f32vec2) { data -> x, data -> y });

                                f32vec2 before = screen_to_map(map_view.start_pan);
                                f32vec2 after = screen_to_map(pos);

                                map_view.camera_offset.x += (before.x - after.x);
                                map_view.camera_offset.y += (before.y - after.y);

                                map_view.start_pan = pos;
                                event -> handled = true;
                        }
                        break;
                }
                default: break;
        } 
}
