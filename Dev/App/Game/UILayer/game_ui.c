#include "layer.h"

LayerID game_ui_layer_id;

static Sprite hamburger_menu_sprite;
static Sprite play_sprite;
static UITextButtonList text_buttons;
static UISpriteButtonList sprite_buttons;

#define ENN_HAMBURGER_MENU_BUTTON_ID    0x001
#define ENN_PLAY_BUTTON_ID              0x002
#define ENN_COMPILE_CHIP_BUTTON_ID      0x003

void game_ui_layer_init(void) {
        DEBUG_TRACE();
        
        hamburger_menu_sprite = render_sprite_create(
                &global_render.sprite_sheet, 
                (i32vec2) { 32, 6 },
                (i32vec2) { 42, 16 }
        );

        play_sprite = render_sprite_create(
                &global_render.sprite_sheet,
                (i32vec2) { 45, 7 },
                (i32vec2) { 53, 15 }
        );

        ui_sprite_button_list_init(
                &sprite_buttons, 0x505050FF, 
                (UISpriteButtonData[]) {
                        (UISpriteButtonData) {
                                .id = ENN_HAMBURGER_MENU_BUTTON_ID,
                                .pos = (f32vec2) { -0.95, -0.85 },
                                .dim = (f32vec2) { 0.075, 0.075 },
                                .sprite = &hamburger_menu_sprite
                        },
                        (UISpriteButtonData) {
                                .id = ENN_PLAY_BUTTON_ID,
                                .pos = (f32vec2) { -0.85, -0.85 },
                                .dim = (f32vec2) { 0.075, 0.075 },
                                .sprite = &play_sprite
                        }
                },
                2 
        );

        ui_text_button_list_init(
                &text_buttons, ENN_RIGHT_ALIGN, 0x505050FF,
                (UITextButtonData[]) {
                        (UITextButtonData) { 
                                .id             = ENN_COMPILE_CHIP_BUTTON_ID,
                                .pos            = { 0.95, 0.85 },
                                .color          = 0xFFFFFFFF,
                                .text           = "CREATE CHIP",
                                .text_height    = 0.075
                        }
                },
                1
        );


        DEBUG_UNTRACE();
}

void game_ui_layer_term(void) {
        DEBUG_TRACE();
        ui_sprite_button_list_term(&sprite_buttons);
        ui_text_button_list_term(&text_buttons);
        DEBUG_UNTRACE();
}

void game_ui_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        ui_sprite_button_list_render(&sprite_buttons);
        ui_text_button_list_render(&text_buttons);
        DEBUG_UNTRACE();
}

void game_ui_layer_on_update(f64 dt) {
}

void game_ui_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        ui_sprite_button_list_check_hover(&sprite_buttons, ndc);
                        ui_text_button_list_check_hover(&text_buttons, ndc);
                        break;
                }
                default: break;
        }
        DEBUG_UNTRACE();
}