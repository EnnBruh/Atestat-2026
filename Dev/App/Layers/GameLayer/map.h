#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Rendering/render.h"

#define ENN_MAP_ZOOM_MAX 20.0
#define ENN_MAP_ZOOM_MIN 0.0001

#define ENN_MAP_ZOOM_PLUS 1.1
#define ENN_MAP_ZOOM_MINUS 0.9

#define ENN_MAP_BCKG_COLOR 0x101214FF
#define ENN_MAP_GRID_MAIN_COLOR 0x252728FF
#define ENN_MAP_GRID_SECOND_COLOR 0x151719FF

#define ENN_MAP_GRID_CELL_SIZE 50
#define ENN_MAP_GRID_LINE_WIDTH 2

extern struct MapView {
        f32vec2 visible_pixels;
        f32vec2 camera_offset;
        f32     zoom;
} map_view;

ENNDEF_PRIVATE void map_render(void);
ENNDEF_PRIVATE void map_on_event(Event* event);

ENNDEF_PUBLIC f32vec2 map_to_ndc(f32vec2 map) {
        return (f32vec2) {
                .x = 2 * map_view.zoom * (map.x - map_view.camera_offset.x) / map_view.visible_pixels.x,
                .y = -2 * map_view.zoom * (map.y - map_view.camera_offset.y) / map_view.visible_pixels.y
        };
}
ENNDEF_PUBLIC f32vec2 ndc_to_map(f32vec2 ndc) {
        return (f32vec2) {
                .x = (ndc.x * map_view.visible_pixels.x) / 2 * map_view.zoom + map_view.camera_offset.x,
                .y = (ndc.y * map_view.visible_pixels.y) / -2 * map_view.zoom + map_view.camera_offset.y
        };
}

#endif