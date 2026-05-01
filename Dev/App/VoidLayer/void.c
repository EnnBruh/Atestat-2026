#include "layer.h"

LayerID void_layer_id;

i32vec4 window_viewport;
struct GlobalState global_state;

void void_layer_init(void) {
        DEBUG_TRACE();

        global_state.pause = false;

        i32vec2 window_dim = window_get_framebuff_dim();
        f64 original_aspect_ratio = ENN_FRAMEBUFF_ASPECT_RATIO;
        f64 new_aspect_ratio = (f64)window_dim.x / (f64)window_dim.y;

        if (new_aspect_ratio > original_aspect_ratio) {
                window_viewport.x = (f64)window_dim.x * 0.5 - original_aspect_ratio * (f64)window_dim.y * 0.5;
                window_viewport.y = 0;

                window_viewport.z = original_aspect_ratio * (f64)window_dim.y;
                window_viewport.w = window_dim.y;
        } else { 
                window_viewport.x = 0;
                window_viewport.y = (f64)window_dim.y * 0.5 - (f64)window_dim.x * 0.5 / original_aspect_ratio;

                window_viewport.z = window_dim.x;
                window_viewport.w = window_dim.x / original_aspect_ratio;
        }

        window_set_viewport(window_viewport.x, window_viewport.y, window_viewport.z, window_viewport.w);
        DEBUG_UNTRACE();
} 

void void_layer_term(void) {
}

void void_layer_on_render(void) {
        DEBUG_TRACE();
        render_buff_draw();
        DEBUG_UNTRACE();
}

void void_layer_on_update(f64 dt) {
}

void void_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_WINDOW_RESIZE_EVENT:
                {
                        i32vec2* window_dim = event -> data;

                        f64 original_aspect_ratio = (f64)16 / (f64)9;
                        f64 new_aspect_ratio = (f64)window_dim -> x / (f64)window_dim -> y;

                        if (new_aspect_ratio > original_aspect_ratio) {
                                window_viewport.x = (f64)window_dim -> x * 0.5 - original_aspect_ratio * (f64)window_dim -> y * 0.5;
                                window_viewport.y = 0;

                                window_viewport.z = original_aspect_ratio * (f64)window_dim -> y;
                                window_viewport.w = window_dim -> y;
                        } else { 
                                window_viewport.x = 0;
                                window_viewport.y = (f64)window_dim -> y * 0.5 - (f64)window_dim -> x * 0.5 / original_aspect_ratio;

                                window_viewport.z = window_dim -> x;
                                window_viewport.w = window_dim -> x / original_aspect_ratio;
                        }

                        window_set_viewport(window_viewport.x, window_viewport.y, window_viewport.z, window_viewport.w);

                        settings.resolution = *window_dim;
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        global_state.is_key_down[data -> key] = (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT);
                        if (data -> key == GLFW_KEY_F11 && data -> action == GLFW_PRESS) {
                                settings.fullscreen = !settings.fullscreen;
                                window_flip_fullscreen();
                        }

                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        global_state.prev_mouse_pos = global_state.mouse_pos;
                        global_state.mouse_pos = *data;
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;
                        global_state.is_button_down[data -> button] = (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT);
                        break;
                }
                default: break;
        }
        DEBUG_UNTRACE();
}