#ifndef STATE_H
#define STATE_H

#include "core.h"

extern struct GlobalState {
        bool            is_key_down[GLFW_KEY_LAST];
        bool            is_button_down[GLFW_MOUSE_BUTTON_LAST];
        f64vec2         mouse_pos;
        f64vec2         prev_mouse_pos;
        bool            pause;
        i32             drawn_vertices;
} global_state;

extern i32vec4 window_viewport;
ENNDEF_PUBLIC f32vec2 screen_to_ndc(f32vec2 screen) {
        return (f32vec2) {
                .x = (screen.x - window_viewport.x) / ((f32)(window_viewport.z) * 0.5) - 1.0,
                .y = (screen.y - window_viewport.y) / ((f32)(window_viewport.w) * 0.5) - 1.0
        };
}

ENNDEF_PUBLIC f32vec2 ndc_to_screen(f32vec2 ndc_pos) {
        return (f32vec2) {
                .x = window_viewport.x + (ndc_pos.x + 1.0) * ((f32)window_viewport.z * 0.5),
                .y = window_viewport.y + (ndc_pos.y + 1.0) * ((f32)window_viewport.w * 0.5)
        };
}
#endif