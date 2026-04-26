#include "layer.h"

LayerID escape_menu_layer_id;

static UITextButtonList buttons;

#define RESUME_BUTTON_ID        0x001
#define SETTINGS_BUTTON_ID      0x002
#define QUIT_MAINMENU_BUTTON_ID 0x003
#define EXIT_BUTTON_ID          0x004

void escape_menu_layer_init(void) {
        DEBUG_TRACE();
        ui_text_button_list_init(
                &buttons, ENN_CENTER_ALIGN, 0x505050FF,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = RESUME_BUTTON_ID,
                                .pos            = { 0.0, -0.15 },
                                .color          = 0xFFFFFFFF,
                                .text           = "RESUME",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = SETTINGS_BUTTON_ID,
                                .pos            = { 0.0, -0.075 },
                                .color          = 0xFFFFFFFF,
                                .text           = "SETTINGS",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = QUIT_MAINMENU_BUTTON_ID,
                                .pos            = { 0.0, 0.0 },
                                .color          = 0xd75f5fFF,
                                .text           = "QUIT TO MAIN MENU",
                                .text_height    = 0.075
                        },
                        (UITextButtonData) {
                                .id             = EXIT_BUTTON_ID,
                                .pos            = { 0.0, 0.075 },
                                .color          = 0xd75f5fFF,
                                .text           = "EXIT TO DESKTOP",
                                .text_height    = 0.075
                        }
                },
                4
        );
        DEBUG_UNTRACE();
}

void escape_menu_layer_term(void) {
        DEBUG_TRACE();
        ui_text_button_list_term(&buttons);
        DEBUG_UNTRACE();
}

void escape_menu_layer_on_render(void) {
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
                0x00000050);

        render_text_push(
                (f32vec2) { -0.45, -0.6 },
                (f32vec2) { 0.45, -0.5 },
                "SIMULATION PAUSED", 0xFFFFFFFF, 0.1, ENN_CENTER_ALIGN);
                
        ui_text_button_list_render(&buttons);
        DEBUG_UNTRACE();
}

void escape_menu_layer_on_update(f64 dt) {
}

void escape_menu_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        ui_text_button_list_check_hover(&buttons, ndc);
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button , action; }* data = event -> data;
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS && buttons.hover != NULL) {
                                switch (buttons.hover -> id) {
                                        case EXIT_BUTTON_ID: 
                                        {
                                                core_stop(); 
                                                break;
                                        }
                                        case RESUME_BUTTON_ID:
                                        {
                                                global_state.pause = false;
                                                // layer_set_inactive(blur_layer_id);
                                                layer_set_inactive(escape_menu_layer_id);
                                                break;
                                        }
                                        case QUIT_MAINMENU_BUTTON_ID:
                                        {
                                                global_state.pause = false;
                                                // layer_set_inactive(blur_layer_id);
                                                layer_set_active(menu_layer_id);
                                                layer_set_inactive(escape_menu_layer_id);
                                                layer_set_inactive(map_layer_id);
                                                layer_set_inactive(game_layer_id);
                                                break;
                                        }
                                        default: break;
                                }
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                global_state.pause = false;
                                // layer_set_inactive(blur_layer_id);
                                layer_set_inactive(escape_menu_layer_id);
                        }
                        break;
                }
                default: break;
        }
        event -> handled = true;
        DEBUG_UNTRACE();
}
