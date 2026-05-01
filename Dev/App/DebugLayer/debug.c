#include "layer.h"

LayerID debug_layer_id;

void debug_layer_init(void) {
        DEBUG_TRACE();
        DEBUG_UNTRACE();
}

void debug_layer_term(void) {
        DEBUG_TRACE();
        DEBUG_UNTRACE();
}

static char fps_buff[32];
static char vertex_info[64];
void debug_layer_on_render(void) {
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        render_text_push(
                (f32vec2) { -0.95, -0.95 },
                (f32vec2) { -0.95, -0.9 },
                fps_buff, 0xFFFFFFFF, 0.05, ENN_LEFT_ALIGN);

        // render_text_push(
        //         (f32vec2) { -0.95, -0.85 },
        //         (f32vec2) { -0.95, -0.8  },
        //         mouse_info, 0xFFFFFFFF, 0.05, ENN_LEFT_ALIGN);

        sprintf(vertex_info, "%" PRIi32 " VERTICES DRAWN", global_state.drawn_vertices);

        render_text_push(
                (f32vec2) { -0.95, -0.9 },
                (f32vec2) { -0.95, -0.85 },
                vertex_info, 0xFFFFFFFF, 0.05, ENN_LEFT_ALIGN);

        render_buff_draw();
        global_state.drawn_vertices = 0;
}

void debug_layer_on_update(f64 dt) {
        static f64 last_refresh = 0.0;
        last_refresh += dt;

        if (last_refresh >= 0.5) {
                sprintf(fps_buff, "FRAMETIME: %lf | FPS: %" PRIi32, dt, (i32)(1.0 / dt));
                last_refresh = 0.0;
        }
}

void debug_layer_on_event(Event* event) {
}