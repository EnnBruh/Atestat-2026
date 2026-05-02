#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "layer.h"


extern struct MapView {
        f32vec2 visible_pixels;
        f32vec2 camera_offset;
        f32     zoom;

        f32vec2 start_pan;
} map_view;

ENNDEF_PUBLIC f32vec2 map_to_ndc(f32vec2 map_pos) {
        return (f32vec2){
                (2.0 * map_view.zoom * (map_pos.x - map_view.camera_offset.x)) / map_view.visible_pixels.x - 1.0,
                1.0 - (2.0 * map_view.zoom * (map_pos.y - map_view.camera_offset.y)) / map_view.visible_pixels.y
        };
}

ENNDEF_PUBLIC f32vec2 ndc_to_map(f32vec2 ndc_pos) {
        return (f32vec2){
                map_view.camera_offset.x + ((ndc_pos.x + 1.0) * map_view.visible_pixels.x) / (2.0 * map_view.zoom),
                map_view.camera_offset.y + ((1.0 - ndc_pos.y) * map_view.visible_pixels.y) / (2.0 * map_view.zoom)
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