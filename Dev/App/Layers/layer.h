#ifndef LAYERS_H
#define LAYERS_H

#include "core.h"
#include "Rendering/render.h"

#define LAYER_DEFINE(name)                                                            \
        extern LayerID EXPAND(JOIN(name, _layer_id));                                 \
        ENNDEF_PRIVATE void EXPAND(JOIN(name, _layer_init))(void);                    \
        ENNDEF_PRIVATE void EXPAND(JOIN(name, _layer_term))(void);                    \
        ENNDEF_PRIVATE void EXPAND(JOIN(name, _layer_on_render))(void);               \
        ENNDEF_PRIVATE void EXPAND(JOIN(name, _layer_on_event))(Event* event);        \
        ENNDEF_PRIVATE void EXPAND(JOIN(name, _layer_on_update))(f64 dt)             

#define LAYER_ASSIGN(name)                                                            \
        .init = EXPAND(JOIN(name, _layer_init)),                                      \
        .term = EXPAND(JOIN(name, _layer_term)),                                      \
        .on_render = EXPAND(JOIN(name, _layer_on_render)),                            \
        .on_update = EXPAND(JOIN(name, _layer_on_update)),                            \
        .on_event  = EXPAND(JOIN(name, _layer_on_event))


LAYER_DEFINE(void);
LAYER_DEFINE(menu);
LAYER_DEFINE(settings);
LAYER_DEFINE(game);
LAYER_DEFINE(blur);

extern i32vec4 window_viewport;
ENNDEF_PUBLIC f32vec2 screen_to_ndc(f32vec2 screen) {
        return (f32vec2) {
                .x = (screen.x - window_viewport.x) / ((f32)(window_viewport.z) * 0.5) - 1.0,
                .y = (screen.y - window_viewport.y) / ((f32)(window_viewport.w) * 0.5) - 1.0
        };
}

extern struct GlobalState {
        bool is_key_down[GLFW_KEY_LAST];
        bool is_button_down[GLFW_MOUSE_BUTTON_LAST];
        f64vec2 mouse_pos;
} global_state;

#endif