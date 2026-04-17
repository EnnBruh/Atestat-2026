#include "Layers/layer.h"

LayerID void_layer_id;

i32vec4 window_viewport;
struct GlobalState global_state;

void void_layer_init(void) {
        i32vec2 window_dim = window_get_framebuff_dim();
        f64 original_aspect_ratio = (f64)16 / (f64)9;
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
} 

void void_layer_term(void) {
}

static char fps_buff[32];
static char vertex_info[64];
static char mouse_info[64];
void void_layer_on_render(void) {
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        render_text_push(
                (f32vec2) { -0.95, -0.95 },
                fps_buff, 0xFFFFFFFF, 0.05);

        render_text_push(
                (f32vec2) { -0.95, -0.85 },
                mouse_info, 0xFFFFFFFF, 0.05);

        sprintf(vertex_info, "%" PRIi32 " VERTICES DRAWN", global_render.buff_size);

        render_text_push(
                (f32vec2) { -0.95, -0.9 },
                vertex_info, 0xFFFFFFFF, 0.05);

        render_buff_draw();
}

void void_layer_on_update(f64 dt) {
        static f64 last_refresh = 0.0;
        last_refresh += dt;
        if (last_refresh >= 0.5) {
                sprintf(fps_buff, "%lf FRAMETIME | %" PRIi32 " FPS", dt, (i32)(1.0 / dt));
                last_refresh = 0.0;
        }
}

void void_layer_on_event(Event* event) {
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
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        global_state.is_key_down[data -> key] = (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT);
                        if (data -> key == GLFW_KEY_F11 && data -> action == GLFW_PRESS) {
                                window_flip_fullscreen();
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        global_state.mouse_pos = *data;
                        sprintf(mouse_info, "%" PRIi32 " , %" PRIi32, (i32)data -> x, (i32)data -> y);
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
}