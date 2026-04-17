#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Rendering/render.h"
#include "state.h"

#define ENN_MAP_ZOOM_MAX 5.0
#define ENN_MAP_ZOOM_MIN 0.2

#define ENN_MAP_ZOOM_PLUS 1.1
#define ENN_MAP_ZOOM_MINUS 0.9

#define ENN_MAP_BCKG_COLOR 0x101214FF
#define ENN_MAP_GRID_MAIN_COLOR 0x252728FF
#define ENN_MAP_GRID_SECOND_COLOR 0x151719FF

#define ENN_MAP_GRID_CELL_SIZE 10
#define ENN_MAP_GRID_LINE_WIDTH 0.25

extern struct MapView {
        f32vec2 visible_pixels;
        f32vec2 camera_offset;
        f32     zoom;
} map_view;

ENNDEF_PRIVATE void map_render(void);
ENNDEF_PRIVATE void map_on_event(Event* event);


ENNDEF_PUBLIC f32vec2 map_to_ndc(f32vec2 map_pos) {
        return (f32vec2){
                (2.0f * map_view.zoom * (map_pos.x - map_view.camera_offset.x)) / map_view.visible_pixels.x - 1.0f,
                1.0f - (2.0f * map_view.zoom * (map_pos.y - map_view.camera_offset.y)) / map_view.visible_pixels.y
        };
}

ENNDEF_PUBLIC f32vec2 ndc_to_map(f32vec2 ndc_pos) {
        return (f32vec2){
                map_view.camera_offset.x + ((ndc_pos.x + 1.0f) * map_view.visible_pixels.x) / (2.0f * map_view.zoom),
                map_view.camera_offset.y + ((1.0f - ndc_pos.y) * map_view.visible_pixels.y) / (2.0f * map_view.zoom)
        };
}

ENNDEF_PUBLIC f32vec2 screen_to_map(f32vec2 screen) {
        return (f32vec2) {
                .x = map_view.camera_offset.x + ((screen.x - window_viewport.x) * map_view.visible_pixels.x) / ((f32)window_viewport.z * map_view.zoom),
                .y = map_view.camera_offset.y + ((screen.y - window_viewport.y) * map_view.visible_pixels.y) / ((f32)window_viewport.w * map_view.zoom)
        };
}

ENNDEF_PUBLIC f32vec2 map_to_screen(f32vec2 map_pos) {
        return (f32vec2) {
                .x = window_viewport.x + ((map_pos.x - map_view.camera_offset.x) * map_view.zoom * (f32)window_viewport.z) / map_view.visible_pixels.x,
                .y = window_viewport.y + ((map_pos.y - map_view.camera_offset.y) * map_view.zoom * (f32)window_viewport.w) / map_view.visible_pixels.y
        };
}

#endif