#include "Layers/GameLayer/map.h"

struct MapView map_view = {
        .visible_pixels = { .x = 160, .y = 90 },
        .camera_offset = { .x = 10, .y = 0 },
        .zoom = 1.0
};


void map_render(void) {
        render_proj_set((f32mat4) {
                2 / map_view.visible_pixels.x * map_view.zoom, 0, 0, -(2 * map_view.camera_offset.x ) / map_view.visible_pixels.x * map_view.zoom,
                0, -(2 / map_view.visible_pixels.y * map_view.zoom), 0, (2 * map_view.camera_offset.y) / map_view.visible_pixels.y * map_view.zoom,
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

void map_on_event(Event* event) {
        switch (event -> type) {
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        f64* offset = event -> data;
                        if (*offset > 0.0) {
                                if (map_view.zoom < ENN_MAP_ZOOM_MAX) map_view.zoom *= ENN_MAP_ZOOM_PLUS;
                        } else {
                                if (map_view.zoom > ENN_MAP_ZOOM_MIN) map_view.zoom *= ENN_MAP_ZOOM_MINUS;
                        }
                }
                default: break;
        }
}

