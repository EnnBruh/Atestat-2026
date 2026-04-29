#include "layer.h"

LayerID settings_layer_id;

struct Settings settings;
DataFile settings_data;

static UITextButtonList buttons;

static vector(char) input_string;
static vector(char) simulation_tps_string;
static bool typing_state;

static bool cursor_state = true;
static f64 last_cursor_change;

void settings_get_init(void) {
        DEBUG_TRACE();
        datafile_create(&settings_data);
        if (file_exists(ENN_APP_DIRECTORY "/settings.enn")) {
                datafile_read(&settings_data, ENN_APP_DIRECTORY "/settings.enn");
                #ifdef ENN_DEBUG_MODE
                settings.debug_mode = true;
                #else
                settings.debug_mode     = datafile_get_i32(&settings_data, "Settings|Debug Info");
                #endif
                settings.fullscreen     = datafile_get_i32(&settings_data, "Settings|Fullscreen");
                settings.vsync          = datafile_get_i32(&settings_data, "Settings|VSync");
                settings.resolution.x   = datafile_get_i32(&settings_data, "Settings|Resolution|width");
                settings.resolution.y   = datafile_get_i32(&settings_data, "Settings|Resolution|height");
                settings.simulaton_tps  = datafile_get_i32(&settings_data, "Settings|Simulation TPS");

                if (settings.resolution.x == 0 || settings.resolution.y == 0) {
                        settings.resolution.x = 1280;
                        settings.resolution.y = 720;
                }
                if (settings.simulaton_tps <= 0) {
                        settings.simulaton_tps = 20;
                }
        } else {
                #ifdef ENN_DEBUG_MODE
                settings.debug_mode = true;
                #else
                settings.debug_mode = false;
                #endif
                settings.fullscreen = false;
                settings.resolution = (i32vec2) { .x = 1280, .y = 720 };
                settings.vsync = true;
                settings.simulaton_tps = 20;
        }
        DEBUG_UNTRACE();
}

#define DEBUG_MODE_BUTTON_ID     0x001
#define VSYNC_BUTTON_ID          0x002
#define FULLSCREEN_BUTTON_ID     0x003
#define RESOLUTION_BUTTON_ID     0x004
#define SIM_TPS_BUTTON_ID        0x005
#define CLOSE_BUTTON_ID          0x006

#define ENN_CURSOR_CHANGE_TIME 0.5

void settings_layer_init(void) {
        DEBUG_TRACE();

        ui_text_button_list_init(
                &buttons, ENN_LEFT_ALIGN, 0x505050FF,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = DEBUG_MODE_BUTTON_ID,
                                .pos            = { -0.7, -0.15 },
                                .color          = 0xFFFFFFFF,
                                .text           = "DEBUG INFORMATION                ",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = FULLSCREEN_BUTTON_ID,
                                .pos            = { -0.7, -0.075 },
                                .color          = 0xFFFFFFFF,
                                .text           = "FULLSCREEN MODE                  ",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = VSYNC_BUTTON_ID,
                                .pos            = { -0.7, 0.0 },
                                .color          = 0xFFFFFFFF,
                                .text           = "VSYNC                            ",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = SIM_TPS_BUTTON_ID,
                                .pos            = { -0.7, 0.15 },
                                .color          = 0xFFFFFFFF,
                                .text           = "SIMULATION TICKS PER SECOND   ",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = CLOSE_BUTTON_ID,
                                .pos            = { -0.9, 0.85 },
                                .color          = 0xd75f5fFF,
                                .text           = "CLOSE",
                                .text_height    = 0.075
                        }
                },
               5
        );

        vector_reserve(simulation_tps_string, 64);
        snprintf(simulation_tps_string.data + simulation_tps_string.start, simulation_tps_string.capacity, "%" PRIi32, settings.simulaton_tps);
        DEBUG_UNTRACE();
}

void settings_layer_term(void) {
        DEBUG_TRACE();
        datafile_put_i32(&settings_data, "Settings|Debug Info", settings.debug_mode);
        datafile_put_i32(&settings_data, "Settings|Fullscreen", settings.fullscreen);
        datafile_put_i32(&settings_data, "Settings|VSync", settings.vsync);
        datafile_put_i32(&settings_data, "Settings|Resolution|width", settings.resolution.x);
        datafile_put_i32(&settings_data, "Settings|Resolution|height", settings.resolution.y);
        datafile_put_i32(&settings_data, "Settings|Simulation TPS", settings.simulaton_tps);
        datafile_write(&settings_data, ENN_APP_DIRECTORY "/settings.enn");
        datafile_destroy(&settings_data);
        ui_text_button_list_term(&buttons);
        vector_destroy(input_string);
        vector_destroy(simulation_tps_string);
        DEBUG_UNTRACE();
}

void settings_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        render_rectangle_push(
                (f32vec2) { -1.0, -1.0 },
                (f32vec2) { 1.0, 1.0 },
                0x101214FF);

        render_text_push(
                (f32vec2) { -0.15, -0.8 },
                (f32vec2) { 0.15, -0.7 },
                "SETTINGS", 0xFFFFFFFF, 0.1, ENN_CENTER_ALIGN);

        ui_text_button_list_render(&buttons);

        f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
        for (i32 i = buttons.list.start; i < buttons.list.end; ++i) {
                bool setting = false;
                switch (buttons.list.data[i].id) {
                        case DEBUG_MODE_BUTTON_ID:
                        {
                                setting = settings.debug_mode;
                                goto render_button_status;
                                break;
                        }
                        case FULLSCREEN_BUTTON_ID:
                        {
                                setting = settings.fullscreen;
                                goto render_button_status;
                                break;
                        }
                        case VSYNC_BUTTON_ID:
                        {
                                setting = settings.vsync;
                                goto render_button_status;
                                break;
                        }
                        case SIM_TPS_BUTTON_ID:
                        {
                                if (typing_state) {
                                        f64 time = glfwGetTime();
                                        if (time - last_cursor_change >= ENN_CURSOR_CHANGE_TIME) {
                                                cursor_state = !cursor_state;
                                                last_cursor_change = time;
                                        }

                                        render_text_push(
                                                (f32vec2) { buttons.list.data[i].pos.x + buttons.list.data[i].dim.x, buttons.list.data[i].pos.y },
                                                (f32vec2) { buttons.list.data[i].pos.x + buttons.list.data[i].dim.x + vector_size(input_string) * buttons.list.data[i].dim.y * render_text_ratio, buttons.list.data[i].pos.y + buttons.list.data[i].dim.y },
                                                input_string.data + input_string.start, buttons.hover == &buttons.list.data[i] ? buttons.button_hover_color : 0xFFFFFFFF, buttons.list.data[i].dim.y, ENN_LEFT_ALIGN
                                        );

                                        if (cursor_state)
                                                render_rectangle_push(
                                                    (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x + vector_size(input_string) * buttons.list.data[i].dim.y * render_text_ratio, buttons.list.data[i].pos.y},
                                                    (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x + vector_size(input_string) * buttons.list.data[i].dim.y * render_text_ratio + buttons.list.data[i].dim.y * render_text_ratio / 2, buttons.list.data[i].pos.y + buttons.list.data[i].dim.y},
                                                    buttons.hover == &buttons.list.data[i] ? buttons.button_hover_color : 0xFFFFFFFF
                                                );
                                } else {
                                        render_text_push(
                                                (f32vec2) { buttons.list.data[i].pos.x + buttons.list.data[i].dim.x, buttons.list.data[i].pos.y },
                                                (f32vec2) { buttons.list.data[i].pos.x + buttons.list.data[i].dim.x + vector_size(simulation_tps_string) * buttons.list.data[i].dim.y * render_text_ratio, buttons.list.data[i].pos.y + buttons.list.data[i].dim.y },
                                                simulation_tps_string.data + simulation_tps_string.start, buttons.hover == &buttons.list.data[i] ? buttons.button_hover_color : 0xFFFFFFFF, buttons.list.data[i].dim.y, ENN_LEFT_ALIGN
                                        );
                                }
                                break;
                        }
                        default: break;
                }

                continue;
                render_button_status:
                if (setting)
                {
                        render_text_push(
                            (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x - buttons.list.data[i].dim.y * render_text_ratio * (sizeof "ON"), buttons.list.data[i].pos.y},
                            (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x, buttons.list.data[i].pos.y + buttons.list.data[i].dim.y},
                            "ON", buttons.hover == &buttons.list.data[i] ? buttons.button_hover_color : 0xafd75fFF, buttons.list.data[i].dim.y, ENN_LEFT_ALIGN);
                }
                else
                {
                        render_text_push(
                            (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x - buttons.list.data[i].dim.y * render_text_ratio * (sizeof "OFF"), buttons.list.data[i].pos.y},
                            (f32vec2){buttons.list.data[i].pos.x + buttons.list.data[i].dim.x, buttons.list.data[i].pos.y + buttons.list.data[i].dim.y},
                            " OFF", buttons.hover == &buttons.list.data[i] ? buttons.button_hover_color : 0xd75f5fFF, buttons.list.data[i].dim.y, ENN_LEFT_ALIGN);
                }
        }

        DEBUG_UNTRACE();
}

void settings_layer_on_update(f64 dt) {
}

void settings_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                if (typing_state) {
                                        typing_state = false;
                                        sscanf(input_string.data + input_string.start, "%" SCNi32, &settings.simulaton_tps);
                                        snprintf(simulation_tps_string.data + simulation_tps_string.start, simulation_tps_string.capacity, "%" PRIi32, settings.simulaton_tps);
                                } else layer_set_inactive(settings_layer_id);
                        }

                        if (data -> key == GLFW_KEY_BACKSPACE && (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT)) {
                                if (typing_state) {
                                        if (vector_size(input_string) <= 0) break;
                                        vector_pop_back(input_string);
                                        input_string.data[input_string.end] = 0;
                                        cursor_state = true;
                                        last_cursor_change = glfwGetTime();
                                }
                        }
                        
                        if (data -> key == GLFW_KEY_ENTER && data -> action == GLFW_PRESS) {
                                if (typing_state) {
                                        typing_state = false;
                                        sscanf(input_string.data + input_string.start, "%" SCNi32, &settings.simulaton_tps);
                                        snprintf(simulation_tps_string.data + simulation_tps_string.start, simulation_tps_string.capacity, "%" PRIi32, settings.simulaton_tps);
                                }
                        }

                        break;
                }
                case ENN_INPUT_TEXT_EVENT:
                {
                        u32* code = event -> data;
                        if (*code < ENN_FONT_ATLAS_FIRST_CHAR || *code > ENN_FONT_ATLAS_LAST_CHAR) break;
                        char ch = (char)*code;
                        vector_push_back(input_string, ch);
                        input_string.data[input_string.end] = 0;
                        cursor_state = true;
                        last_cursor_change = glfwGetTime();
                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        ui_text_button_list_check_hover(&buttons, ndc);
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS) {
                                if (buttons.hover != NULL) {
                                        switch (buttons.hover -> id) {
                                        case DEBUG_MODE_BUTTON_ID:
                                        {
                                                settings.debug_mode = !settings.debug_mode;
                                                if (settings.debug_mode)
                                                        layer_set_active(debug_layer_id);
                                                else
                                                        layer_set_inactive(debug_layer_id);
                                                break;
                                        }
                                        case FULLSCREEN_BUTTON_ID:
                                        {
                                                settings.fullscreen = !settings.fullscreen;
                                                window_flip_fullscreen();
                                                break;
                                        }
                                        case VSYNC_BUTTON_ID:
                                        {
                                                settings.vsync = !settings.vsync;
                                                window_flip_vsync();
                                                break;
                                        }
                                        case SIM_TPS_BUTTON_ID:
                                        {
                                                typing_state = true;
                                                break;
                                        }
                                        case CLOSE_BUTTON_ID:
                                        {
                                                layer_set_inactive(settings_layer_id);
                                                break;
                                        }
                                        default:
                                                break;
                                        }
                                }
                                if (typing_state) {
                                        if (buttons.hover == NULL) {
                                                typing_state = false;
                                                sscanf(input_string.data + input_string.start, "%" SCNi32, &settings.simulaton_tps);
                                                snprintf(simulation_tps_string.data + simulation_tps_string.start, simulation_tps_string.capacity, "%" PRIi32, settings.simulaton_tps);
                                        } else if (buttons.hover -> id != SIM_TPS_BUTTON_ID) {
                                                typing_state = false;
                                                sscanf(input_string.data + input_string.start, "%" SCNi32, &settings.simulaton_tps);
                                                snprintf(simulation_tps_string.data + simulation_tps_string.start, simulation_tps_string.capacity, "%" PRIi32, settings.simulaton_tps);
                                        }
                                }
                        }
                        break;
                }
                case ENN_WINDOW_RESIZE_EVENT:
                {
                        i32vec2* data = event -> data;
                        settings.resolution = *data;
                        break;
                }
                default: break;
        }
        event -> handled = true;
        DEBUG_UNTRACE();
}