#include "layer.h"
#include "UI/ui.h"
#include "Game/objects.h"
#include "Game/MapLayer/map.h"

extern LayerID menu_layer_id;

LayerID game_ui_layer_id;

#define ENN_UI_MENU_WIDTH               0.375
#define ENN_UI_MENU_BKG_COLOR           0x101214FF
#define ENN_UI_TOGGLE_BTN_COLOR         ENN_UI_MENU_BKG_COLOR
#define ENN_UI_MENU_SPEED               3.0

#define ENN_UI_BIG_BTN_WIDTH            0.2
#define ENN_UI_BIG_BTN_HEIGHT           (ENN_UI_BIG_BTN_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO)
#define ENN_UI_PADDING                  0.02

#define ENN_UI_BIG_BTN_COUNT            3

#define ENN_UI_TOGGLE_BTN_WIDTH         0.05
#define ENN_UI_TOGGLE_BTN_HEIGHT        0.2
#define ENN_UI_TOGGLE_BTN_POS_Y         -0.1

#define ENN_UI_TOGGLE_ICON_WIDTH        0.04
#define ENN_UI_TOGGLE_ICON_HEIGHT       (ENN_UI_TOGGLE_ICON_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO)
#define ENN_UI_TOGGLE_ICON_OFFSET_X     0.02

#define ENN_UI_MENU_MIN_COORD           -1.0
#define ENN_UI_MENU_MAX_COORD           1.0

#define ENN_UI_TITLE_TEXT_1             "SIMULATION"
#define ENN_UI_TITLE_TEXT_2             "MENU"
#define ENN_UI_TITLE_COLOR              0xFFFFFFFF
#define ENN_UI_TITLE_TEXT_HEIGHT_1      0.05
#define ENN_UI_TITLE_TEXT_HEIGHT_2      0.065
#define ENN_UI_TITLE_POS_Y              -0.85
#define ENN_UI_TITLE_SPACING            0.05

#define ENN_UI_TEXT_BTN_COUNT           4
#define ENN_UI_TEXT_BTN_START_Y         -0.6
#define ENN_UI_TEXT_BTN_SPACING         0.05
#define ENN_UI_TEXT_BTN_TEXT_HEIGHT     0.04
#define ENN_UI_TEXT_BTN_HOVER_COLOR     0x808080FF

#define ENN_UI_TEXT_SAVE                "SAVE CIRCUIT"
#define ENN_UI_TEXT_COMPILE             "COMPILE CIRCUIT"
#define ENN_UI_TEXT_MODE                "MODE:        "
#define ENN_UI_TEXT_QUIT                "QUIT"

#define ENN_UI_BIG_BTN_START_Y          -0.275

#define ENN_UI_BORDER_COLOR             0x7a7c7e80
#define ENN_UI_BORDER_WIDTH             0.0025
#define ENN_UI_HOVER_OVERLAY_COLOR      0xFFFFFF30
#define ENN_UI_BIG_BTN_COLOR            ENN_UI_MENU_BKG_COLOR
#define ENN_UI_CHIP_SCROLL_CHANGE       0.12
#define ENN_UI_CHIP_PREVIEW_PADDING     0.025
#define ENN_UI_SAVE_NOTIFICATION_TIME   3.0
#define ENN_UI_SAVE_NOTIFICATION_TEXT   "CIRCUIT SAVED"
#define ENN_UI_SAVE_NOTIFICATION_HEIGHT 0.04
#define ENN_UI_SAVE_NOTIFICATION_COLOR  0x98971aFF

#define ENN_UI_BTN_ID_TOGGLE            0x001
#define ENN_UI_BTN_ID_HAMBURGER         0x100
#define ENN_UI_BTN_ID_IN_IND            0x200
#define ENN_UI_BTN_ID_OUT_IND           0x201
#define ENN_UI_BTN_ID_CHIP              0x202

#define ENN_UI_BTN_ID_IN_IND_RED        0x210
#define ENN_UI_BTN_ID_IN_IND_ORANGE     0x211
#define ENN_UI_BTN_ID_IN_IND_YELLOW     0x212
#define ENN_UI_BTN_ID_IN_IND_GREEN      0x213
#define ENN_UI_BTN_ID_IN_IND_BLUE       0x214
#define ENN_UI_BTN_ID_IN_IND_PURPLE     0x215

#define ENN_UI_BTN_ID_OUT_IND_RED       0x220
#define ENN_UI_BTN_ID_OUT_IND_ORANGE    0x221
#define ENN_UI_BTN_ID_OUT_IND_YELLOW    0x222
#define ENN_UI_BTN_ID_OUT_IND_GREEN     0x223
#define ENN_UI_BTN_ID_OUT_IND_BLUE      0x224
#define ENN_UI_BTN_ID_OUT_IND_PURPLE    0x225

#define ENN_UI_BTN_ID_CHIP_NAND         0x230
#define ENN_UI_BTN_ID_CHIP_FIRST        ENN_UI_BTN_ID_CHIP_NAND

#define ENN_UI_BTN_ID_SAVE_CIRCUIT      0x300
#define ENN_UI_BTN_ID_COMPILE_CIRCUIT   0x301
#define ENN_UI_BTN_ID_SWITCH_STATE      0x302
#define ENN_UI_BTN_ID_QUIT              0x303

#define ENN_UI_EDIT_COLOR               0xd79921FF
#define ENN_UI_EXECUTE_COLOR            0x98971aFF

#define ENN_UI_MODE_LABEL_TEXT          "MODE: "
#define ENN_UI_MODE_EDIT_TEXT           "EDIT"
#define ENN_UI_MODE_EXECUTE_TEXT        "EXECUTE"

static const i32vec4 ENN_UI_SPRITE_TOGGLE    = { 83, 3, 91, 12 };
static const i32vec4 ENN_UI_SPRITE_IND       = { 1, 240, 24, 255 };
static const i32vec4 ENN_UI_SPRITE_CHIP      = { 65, 144, 89, 164 };

typedef struct UIMenuButton {
        i32                             id;
        f32vec2                         local_pos;
        f32vec2                         dim;
        u32                             color;
        Sprite*                         sprite;
        f32vec2                         sprite_dim;
        BlueprintChipIndex              blueprint;
        bool                            render_chip_preview : 1;
        vector(struct UIMenuButton)     sub_buttons;
} UIMenuButton;

static bool menu_expanded;
static f32 menu_offset_x;
static f32 chip_submenu_scroll;
static f64 save_notification_started;
static i32 hovered_button_id;
static i32 active_submenu_index;

static UIMenuButton big_buttons[ENN_UI_BIG_BTN_COUNT];

static Sprite big_sprites[3];
static Sprite toggle_sprite;

static Sprite in_sub_sprites[6];
static Sprite out_sub_sprites[6];
static Sprite chip_sub_sprites[1];

static UITextButtonList text_buttons;
static f32 text_btn_base_x[ENN_UI_TEXT_BTN_COUNT];

ENNDEF_PUBLIC bool game_ui_is_indicator_button(i32 button_id, bool* is_input, ENN_CIRCUIT_ELEMENT_COLORS* color) {
        DEBUG_TRACE();
        DEBUG_ASSERT(is_input != NULL);
        DEBUG_ASSERT(color != NULL);

        if (button_id >= ENN_UI_BTN_ID_IN_IND_RED && button_id <= ENN_UI_BTN_ID_IN_IND_PURPLE) {
                *is_input = true;
                *color = (ENN_CIRCUIT_ELEMENT_COLORS)(button_id - ENN_UI_BTN_ID_IN_IND_RED);
                DEBUG_UNTRACE();
                return true;
        }

        if (button_id >= ENN_UI_BTN_ID_OUT_IND_RED && button_id <= ENN_UI_BTN_ID_OUT_IND_PURPLE) {
                *is_input = false;
                *color = (ENN_CIRCUIT_ELEMENT_COLORS)(button_id - ENN_UI_BTN_ID_OUT_IND_RED);
                DEBUG_UNTRACE();
                return true;
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC void game_ui_close_submenu(void) {
        DEBUG_TRACE();
        active_submenu_index = -1;
        hovered_button_id = 0;
        text_buttons.hover = NULL;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC f32 game_ui_chip_submenu_min_scroll(void) {
        DEBUG_TRACE();
        UIMenuButton* chip_button = &big_buttons[2];
        i32 subs = vector_size(chip_button -> sub_buttons);
        f32 content_right = chip_button -> local_pos.x + subs * (chip_button -> dim.x + ENN_UI_PADDING) + chip_button -> dim.x + ENN_UI_PADDING;
        f32 visible_right = ENN_UI_MENU_MAX_COORD - menu_offset_x;
        f32 min_scroll = min(0.0, visible_right - content_right);
        DEBUG_UNTRACE();
        return min_scroll;
}

ENNDEF_PUBLIC void game_ui_clamp_chip_submenu_scroll(void) {
        DEBUG_TRACE();
        f32 min_scroll = game_ui_chip_submenu_min_scroll();
        if (chip_submenu_scroll < min_scroll) chip_submenu_scroll = min_scroll;
        if (chip_submenu_scroll > 0.0) chip_submenu_scroll = 0.0;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC f32 game_ui_submenu_scroll_offset(i32 submenu_index) {
        return (submenu_index == 2) ? chip_submenu_scroll : 0.0;
}

ENNDEF_PUBLIC f32vec4 game_ui_sub_button_rect(i32 submenu_index, UIMenuButton* sub) {
        f32 x = sub -> local_pos.x + menu_offset_x + game_ui_submenu_scroll_offset(submenu_index);
        return (f32vec4) { x, sub -> local_pos.y, sub -> dim.x, sub -> dim.y };
}

ENNDEF_PUBLIC bool game_ui_sub_button_is_visible(i32 submenu_index, UIMenuButton* sub) {
        f32vec4 rect = game_ui_sub_button_rect(submenu_index, sub);
        f32 visible_left = big_buttons[submenu_index].local_pos.x + big_buttons[submenu_index].dim.x + menu_offset_x;
        f32 visible_right = (submenu_index == 2) ? ENN_UI_MENU_MAX_COORD : rect.x + rect.z;
        if (submenu_index != 2) return true;
        return rect.x + rect.z > visible_left && rect.x < visible_right;
}

ENNDEF_PUBLIC f32vec4 game_ui_submenu_row_rect(i32 submenu_index) {
        UIMenuButton* button = &big_buttons[submenu_index];
        i32 subs = vector_size(button -> sub_buttons);
        f32 pad_x = ENN_UI_PADDING;
        f32 pad_y = ENN_UI_PADDING * ENN_FRAMEBUFF_ASPECT_RATIO;
        f32 total_w = button -> dim.x + subs * (button -> dim.x + ENN_UI_PADDING) + pad_x;
        f32 row_x = button -> local_pos.x + menu_offset_x;
        if (submenu_index == 2)
                total_w = ENN_UI_MENU_MAX_COORD - row_x;
        return (f32vec4) { row_x, button -> local_pos.y - pad_y, total_w, button -> dim.y + pad_y * 2.0f };
}

ENNDEF_PUBLIC void game_ui_summon_indicator_for_move(bool is_input, ENN_CIRCUIT_ELEMENT_COLORS color) {
        DEBUG_TRACE();
        if (global_state.game_state != ENN_EDIT_MODE) {
                DEBUG_UNTRACE();
                return;
        }

        f32vec2 map = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
        CircuitElement elem = {0};

        if (is_input) {
                elem = (CircuitElement) {
                        .index = circuit_summon_input_indicator(map, color),
                        .type = ENN_INPUT_INDICATOR
                };
        } else {
                elem = (CircuitElement) {
                        .index = circuit_summon_output_indicator(map, color),
                        .type = ENN_OUTPUT_INDICATOR
                };
        }

        circuit_selection_clear();
        circuit_selection_add_element(elem);
        circuit_selection_move_begin(map);
        current_action = ENN_ACTION_MOVING;
        game_ui_close_submenu();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void game_ui_summon_chip_for_move(BlueprintChipIndex blueprint) {
        DEBUG_TRACE();
        if (global_state.game_state != ENN_EDIT_MODE) {
                DEBUG_UNTRACE();
                return;
        }

        f32vec2 map = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
        CircuitElement elem = {
                .index = circuit_summon_chip(map, blueprint),
                .type = ENN_CHIP
        };

        circuit_selection_clear();
        circuit_selection_add_element(elem);
        circuit_selection_move_begin(map);
        current_action = ENN_ACTION_MOVING;
        game_ui_close_submenu();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool game_ui_is_chip_button(i32 button_id, BlueprintChipIndex* blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != NULL);
        if (button_id >= ENN_UI_BTN_ID_CHIP_FIRST && button_id < ENN_UI_BTN_ID_CHIP_FIRST + global_circuit.blueprints.end) {
                *blueprint = button_id - ENN_UI_BTN_ID_CHIP_FIRST;
                DEBUG_UNTRACE();
                return true;
        }
        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC void game_ui_reposition_chip_buttons(void) {
        DEBUG_TRACE();
        UIMenuButton* chip_button = &big_buttons[2];
        for (i32 i = chip_button -> sub_buttons.start; i < chip_button -> sub_buttons.end; ++i) {
                UIMenuButton* sub = &chip_button -> sub_buttons.data[i];
                sub -> local_pos = (f32vec2) {
                        chip_button -> local_pos.x + (i - chip_button -> sub_buttons.start + 1) * (ENN_UI_BIG_BTN_WIDTH + ENN_UI_PADDING),
                        chip_button -> local_pos.y
                };
        }
        DEBUG_UNTRACE();
}

void game_ui_register_chip_blueprint(BlueprintChipIndex blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        UIMenuButton* chip_button = &big_buttons[2];
        i32 button_id = ENN_UI_BTN_ID_CHIP_FIRST + blueprint;

        for (i32 i = chip_button -> sub_buttons.start; i < chip_button -> sub_buttons.end; ++i)
                if (chip_button -> sub_buttons.data[i].id == button_id) {
                        chip_button -> sub_buttons.data[i].color = ENN_UI_BIG_BTN_COLOR;
                        chip_button -> sub_buttons.data[i].blueprint = blueprint;
                        chip_button -> sub_buttons.data[i].render_chip_preview = true;
                        DEBUG_UNTRACE();
                        return;
                }

        UIMenuButton sub; memset(&sub, 0x0, (sizeof (UIMenuButton)));
        sub.id = button_id;
        sub.dim = chip_button -> dim;
        sub.color = ENN_UI_BIG_BTN_COLOR;
        sub.sprite = &chip_sub_sprites[0];
        sub.sprite_dim = chip_button -> sprite_dim;
        sub.blueprint = blueprint;
        sub.render_chip_preview = true;
        vector_push_back(chip_button -> sub_buttons, sub);
        game_ui_reposition_chip_buttons();
        game_ui_clamp_chip_submenu_scroll();
        DEBUG_UNTRACE();
}

void game_ui_save_circuit(void) {
        DEBUG_TRACE();
        game_save_current_workspace();
        save_notification_started = glfwGetTime();
        DEBUG_UNTRACE();
}

void game_ui_toggle_mode(void) {
        DEBUG_TRACE();
        if (current_action != ENN_ACTION_NOTHING) {
                DEBUG_UNTRACE();
                return;
        }

        if (global_state.game_state == ENN_EDIT_MODE) {
                global_state.game_state = ENN_EXECUTE_MODE;
                game_ui_close_submenu();
                circuit_prepare_execute_mode();
        } else {
                global_state.game_state = ENN_EDIT_MODE;
                circuit_prepare_edit_mode();
        }
        DEBUG_UNTRACE();
}

void game_ui_start_compile(void) {
        DEBUG_TRACE();
        if (global_state.game_state == ENN_EDIT_MODE && current_action == ENN_ACTION_NOTHING) {
                chip_layer_start_compile();
                layer_set_active(chip_layer_id);
        }
        DEBUG_UNTRACE();
}

void game_ui_layer_init(void) {
        menu_expanded = true;
        menu_offset_x = 0.0;
        chip_submenu_scroll = 0.0;
        save_notification_started = -ENN_UI_SAVE_NOTIFICATION_TIME;
        hovered_button_id = 0;
        active_submenu_index = -1;

        f32 left_x = ENN_UI_MENU_MIN_COORD + (ENN_UI_MENU_WIDTH - ENN_UI_BIG_BTN_WIDTH) * 0.25;

        ui_text_button_list_init(
                &text_buttons, ENN_LEFT_ALIGN, ENN_UI_TEXT_BTN_HOVER_COLOR,
                (UITextButtonData[]) {
                        (UITextButtonData) {
                                .id             = ENN_UI_BTN_ID_SAVE_CIRCUIT,
                                .pos            = { left_x, ENN_UI_TEXT_BTN_START_Y },
                                .color          = ENN_UI_TITLE_COLOR,
                                .text           = ENN_UI_TEXT_SAVE,
                                .text_height    = ENN_UI_TEXT_BTN_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_UI_BTN_ID_COMPILE_CIRCUIT,
                                .pos            = { left_x, ENN_UI_TEXT_BTN_START_Y + ENN_UI_TEXT_BTN_SPACING },
                                .color          = ENN_UI_TITLE_COLOR,
                                .text           = ENN_UI_TEXT_COMPILE,
                                .text_height    = ENN_UI_TEXT_BTN_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_UI_BTN_ID_SWITCH_STATE,
                                .pos            = { left_x, ENN_UI_TEXT_BTN_START_Y + ENN_UI_TEXT_BTN_SPACING * 2 },
                                .color          = ENN_UI_TITLE_COLOR,
                                .text           = ENN_UI_TEXT_MODE,
                                .text_height    = ENN_UI_TEXT_BTN_TEXT_HEIGHT
                        },
                        (UITextButtonData) {
                                .id             = ENN_UI_BTN_ID_QUIT,
                                .pos            = { left_x, ENN_UI_TEXT_BTN_START_Y + ENN_UI_TEXT_BTN_SPACING * 3 },
                                .color          = 0xd75f5fFF,
                                .text           = ENN_UI_TEXT_QUIT,
                                .text_height    = ENN_UI_TEXT_BTN_TEXT_HEIGHT
                        }
                },
                ENN_UI_TEXT_BTN_COUNT
        );

        for (i32 i = 0; i < ENN_UI_TEXT_BTN_COUNT; ++i) {
                text_btn_base_x[i] = text_buttons.list.data[i].pos.x;
        }

        i32 big_ids[ENN_UI_BIG_BTN_COUNT] = {
                ENN_UI_BTN_ID_IN_IND,
                ENN_UI_BTN_ID_OUT_IND,
                ENN_UI_BTN_ID_CHIP
        };

        i32 in_ind_ids[6] = {
                ENN_UI_BTN_ID_IN_IND_RED,
                ENN_UI_BTN_ID_IN_IND_ORANGE,
                ENN_UI_BTN_ID_IN_IND_YELLOW,
                ENN_UI_BTN_ID_IN_IND_GREEN,
                ENN_UI_BTN_ID_IN_IND_BLUE,
                ENN_UI_BTN_ID_IN_IND_PURPLE
        };

        i32 out_ind_ids[6] = {
                ENN_UI_BTN_ID_OUT_IND_RED,
                ENN_UI_BTN_ID_OUT_IND_ORANGE,
                ENN_UI_BTN_ID_OUT_IND_YELLOW,
                ENN_UI_BTN_ID_OUT_IND_GREEN,
                ENN_UI_BTN_ID_OUT_IND_BLUE,
                ENN_UI_BTN_ID_OUT_IND_PURPLE
        };

        i32 chip_ids[1] = {
                ENN_UI_BTN_ID_CHIP_NAND
        };

        i32* sub_ids[3] = { in_ind_ids, out_ind_ids, chip_ids };

        big_sprites[0] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){ ENN_UI_SPRITE_IND.x, ENN_UI_SPRITE_IND.y }, (i32vec2){ ENN_UI_SPRITE_IND.z, ENN_UI_SPRITE_IND.w });
        big_sprites[1] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){ ENN_UI_SPRITE_IND.x, ENN_UI_SPRITE_IND.y }, (i32vec2){ ENN_UI_SPRITE_IND.z, ENN_UI_SPRITE_IND.w });
        render_sprite_flip_horizontal(&big_sprites[1]);
        big_sprites[2] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){ ENN_UI_SPRITE_CHIP.x, ENN_UI_SPRITE_CHIP.y }, (i32vec2){ ENN_UI_SPRITE_CHIP.z, ENN_UI_SPRITE_CHIP.w });

        for (i32 j = 0; j < 6; ++j) {
                in_sub_sprites[j] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){1, 144 + j * 16}, (i32vec2){24, 159 + j * 16});
                out_sub_sprites[j] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){1, 144 + j * 16}, (i32vec2){24, 159 + j * 16});
                render_sprite_flip_horizontal(&out_sub_sprites[j]);
        }
        chip_sub_sprites[0] = render_sprite_create(&global_render.sprite_sheet, (i32vec2){ ENN_UI_SPRITE_CHIP.x, ENN_UI_SPRITE_CHIP.y }, (i32vec2){ ENN_UI_SPRITE_CHIP.z, ENN_UI_SPRITE_CHIP.w });

        Sprite* sub_sprites_0[6] = { &in_sub_sprites[0], &in_sub_sprites[1], &in_sub_sprites[2], &in_sub_sprites[3], &in_sub_sprites[4], &in_sub_sprites[5] };
        Sprite* sub_sprites_1[6] = { &out_sub_sprites[0], &out_sub_sprites[1], &out_sub_sprites[2], &out_sub_sprites[3], &out_sub_sprites[4], &out_sub_sprites[5] };
        Sprite* sub_sprites_2[1] = { &chip_sub_sprites[0] };

        Sprite** sub_sprites[3] = { sub_sprites_0, sub_sprites_1, sub_sprites_2 };

        for (i32 i = 0; i < ENN_UI_BIG_BTN_COUNT; ++i) {
                big_buttons[i].id = big_ids[i];
                big_buttons[i].local_pos = (f32vec2) { 
                        ENN_UI_MENU_MIN_COORD + (ENN_UI_MENU_WIDTH - ENN_UI_BIG_BTN_WIDTH) * 0.5, 
                        ENN_UI_BIG_BTN_START_Y + i * (ENN_UI_BIG_BTN_HEIGHT + ENN_UI_PADDING * ENN_FRAMEBUFF_ASPECT_RATIO) 
                };
                big_buttons[i].dim = (f32vec2) { ENN_UI_BIG_BTN_WIDTH, ENN_UI_BIG_BTN_HEIGHT };
                big_buttons[i].color = ENN_UI_BIG_BTN_COLOR;
                big_buttons[i].sprite = &big_sprites[i];
                
                i32 num_subs = (i == 2) ? 1 : 6;
                for (i32 j = 0; j < num_subs; ++j) {
                        UIMenuButton sub = {0};
                        sub.id = sub_ids[i][j];
                        sub.local_pos = (f32vec2) { 
                                big_buttons[i].local_pos.x + (j + 1) * (ENN_UI_BIG_BTN_WIDTH + ENN_UI_PADDING), 
                                big_buttons[i].local_pos.y 
                        };
                        sub.dim = big_buttons[i].dim;
                        sub.color = ENN_UI_BIG_BTN_COLOR;
                        sub.sprite = sub_sprites[i][j];
                        sub.blueprint = global_circuit.blueprints.end;
                        sub.render_chip_preview = false;
                        if (i == 2) {
                                sub.blueprint = j;
                                sub.render_chip_preview = true;
                        }
                        
                        f32 aspect = (i == 2) ? ((f32)(ENN_UI_SPRITE_CHIP.z - ENN_UI_SPRITE_CHIP.x + 1) / (f32)(ENN_UI_SPRITE_CHIP.w - ENN_UI_SPRITE_CHIP.y + 1)) : (24.0f / 16.0f);
                        sub.sprite_dim = (f32vec2) { ENN_UI_BIG_BTN_WIDTH, ENN_UI_BIG_BTN_WIDTH / aspect * ENN_FRAMEBUFF_ASPECT_RATIO };
                        
                        vector_push_back(big_buttons[i].sub_buttons, sub);
                }
        }

        f32 aspect_ind = (f32)(ENN_UI_SPRITE_IND.z - ENN_UI_SPRITE_IND.x + 1) / (f32)(ENN_UI_SPRITE_IND.w - ENN_UI_SPRITE_IND.y + 1);
        big_buttons[0].sprite_dim = (f32vec2) { ENN_UI_BIG_BTN_WIDTH, ENN_UI_BIG_BTN_WIDTH / aspect_ind * ENN_FRAMEBUFF_ASPECT_RATIO };
        big_buttons[1].sprite_dim = (f32vec2) { ENN_UI_BIG_BTN_WIDTH, ENN_UI_BIG_BTN_WIDTH / aspect_ind * ENN_FRAMEBUFF_ASPECT_RATIO };

        f32 aspect_chip = (f32)(ENN_UI_SPRITE_CHIP.z - ENN_UI_SPRITE_CHIP.x + 1) / (f32)(ENN_UI_SPRITE_CHIP.w - ENN_UI_SPRITE_CHIP.y + 1);
        big_buttons[2].sprite_dim = (f32vec2) { ENN_UI_BIG_BTN_WIDTH, ENN_UI_BIG_BTN_WIDTH / aspect_chip * ENN_FRAMEBUFF_ASPECT_RATIO };

        toggle_sprite = render_sprite_create(&global_render.sprite_sheet, (i32vec2){ ENN_UI_SPRITE_TOGGLE.x, ENN_UI_SPRITE_TOGGLE.y }, (i32vec2){ ENN_UI_SPRITE_TOGGLE.z, ENN_UI_SPRITE_TOGGLE.w });
}

void game_ui_layer_term(void) {
        ui_text_button_list_term(&text_buttons);
        for (i32 i = 0; i < ENN_UI_BIG_BTN_COUNT; ++i) {
                vector_destroy(big_buttons[i].sub_buttons);
        }
}

void game_ui_layer_on_render(void) {
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        if (menu_offset_x > -ENN_UI_MENU_WIDTH) {
                render_rectangle_push(
                        (f32vec2) { ENN_UI_MENU_MIN_COORD + menu_offset_x, ENN_UI_MENU_MIN_COORD },
                        (f32vec2) { ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x, ENN_UI_MENU_MAX_COORD },
                        ENN_UI_MENU_BKG_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x - ENN_UI_BORDER_WIDTH, ENN_UI_MENU_MIN_COORD },
                        (f32vec2) { ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x, ENN_UI_MENU_MAX_COORD },
                        ENN_UI_BORDER_COLOR
                );
        }

        f32 toggle_x1 = ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x;
        render_rectangle_push(
                (f32vec2) { toggle_x1, ENN_UI_TOGGLE_BTN_POS_Y - ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                (f32vec2) { toggle_x1 + ENN_UI_TOGGLE_BTN_WIDTH + ENN_UI_BORDER_WIDTH, ENN_UI_TOGGLE_BTN_POS_Y + ENN_UI_TOGGLE_BTN_HEIGHT + ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                ENN_UI_BORDER_COLOR
        );
        render_rectangle_push(
                (f32vec2) { toggle_x1, ENN_UI_TOGGLE_BTN_POS_Y },
                (f32vec2) { toggle_x1 + ENN_UI_TOGGLE_BTN_WIDTH, ENN_UI_TOGGLE_BTN_POS_Y + ENN_UI_TOGGLE_BTN_HEIGHT },
                ENN_UI_TOGGLE_BTN_COLOR
        );

        f32 tx = toggle_x1 + ENN_UI_TOGGLE_ICON_OFFSET_X;
        f32 ty = ENN_UI_TOGGLE_BTN_POS_Y + ENN_UI_TOGGLE_BTN_HEIGHT * 0.5;
        render_sprite_push((f32vec2) { tx - ENN_UI_TOGGLE_ICON_WIDTH * 0.5, ty - ENN_UI_TOGGLE_ICON_HEIGHT * 0.5 }, (f32vec2) { tx + ENN_UI_TOGGLE_ICON_WIDTH * 0.5, ty + ENN_UI_TOGGLE_ICON_HEIGHT * 0.5 }, &toggle_sprite);

        if (hovered_button_id == ENN_UI_BTN_ID_TOGGLE) {
                render_rectangle_push((f32vec2) { toggle_x1, ENN_UI_TOGGLE_BTN_POS_Y }, (f32vec2) { toggle_x1 + ENN_UI_TOGGLE_BTN_WIDTH, ENN_UI_TOGGLE_BTN_POS_Y + ENN_UI_TOGGLE_BTN_HEIGHT }, ENN_UI_HOVER_OVERLAY_COLOR);
        }

        if (menu_offset_x > -ENN_UI_MENU_WIDTH) {
                f32 center_x = ENN_UI_MENU_MIN_COORD + (ENN_UI_MENU_WIDTH * 0.5) + menu_offset_x;
                render_text_push((f32vec2) { center_x, ENN_UI_TITLE_POS_Y }, (f32vec2) { center_x, ENN_UI_TITLE_POS_Y }, ENN_UI_TITLE_TEXT_1, ENN_UI_TITLE_COLOR, ENN_UI_TITLE_TEXT_HEIGHT_1, ENN_CENTER_ALIGN);
                render_text_push((f32vec2) { center_x, ENN_UI_TITLE_POS_Y + ENN_UI_TITLE_SPACING }, (f32vec2) { center_x, ENN_UI_TITLE_POS_Y + ENN_UI_TITLE_SPACING }, ENN_UI_TITLE_TEXT_2, ENN_UI_TITLE_COLOR, ENN_UI_TITLE_TEXT_HEIGHT_2, ENN_CENTER_ALIGN);

                ui_text_button_list_render(&text_buttons);

                f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
                for (i32 i = text_buttons.list.start; i < text_buttons.list.end; ++i) {
                        UITextButton* btn = &text_buttons.list.data[i];
                        f32vec2 pos = { btn->pos.x, btn->pos.y };

                        if (btn->id == ENN_UI_BTN_ID_SWITCH_STATE) {
                                f32 label_w = strlen(ENN_UI_MODE_LABEL_TEXT) * btn->dim.y * render_text_ratio;
                                f32 start_x = pos.x;
                                bool hovered = (btn == text_buttons.hover);
                                u32 label_color = hovered ? ENN_UI_TEXT_BTN_HOVER_COLOR : ENN_UI_TITLE_COLOR;
                                u32 state_color = hovered ? ENN_UI_TEXT_BTN_HOVER_COLOR : ((global_state.game_state == ENN_EDIT_MODE) ? ENN_UI_EDIT_COLOR : ENN_UI_EXECUTE_COLOR);

                                render_text_push((f32vec2){ start_x, pos.y }, (f32vec2){ start_x, pos.y }, ENN_UI_MODE_LABEL_TEXT, label_color, btn->dim.y, ENN_LEFT_ALIGN);
                                if (global_state.game_state == ENN_EDIT_MODE) {
                                        render_text_push((f32vec2){ start_x + label_w, pos.y }, (f32vec2){ start_x + label_w, pos.y }, ENN_UI_MODE_EDIT_TEXT, state_color, btn->dim.y, ENN_LEFT_ALIGN);
                                } else {
                                        render_text_push((f32vec2){ start_x + label_w, pos.y }, (f32vec2){ start_x + label_w, pos.y }, ENN_UI_MODE_EXECUTE_TEXT, state_color, btn->dim.y, ENN_LEFT_ALIGN);
                                }
                        }
                }

                for (i32 i = 0; i < ENN_UI_BIG_BTN_COUNT; ++i) {
                        if (active_submenu_index == i) {
                                if (i == 2) game_ui_clamp_chip_submenu_scroll();
                                i32 subs = vector_size(big_buttons[i].sub_buttons);
                                f32 pad_x = ENN_UI_PADDING;
                                f32 pad_y = ENN_UI_PADDING * ENN_FRAMEBUFF_ASPECT_RATIO;
                                f32 extra_w = subs * (big_buttons[i].dim.x + ENN_UI_PADDING) + pad_x;
                                f32 menu_right_x = ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x;
                                f32 submenu_right_x = big_buttons[i].local_pos.x + big_buttons[i].dim.x + extra_w + menu_offset_x;
                                if (i == 2) submenu_right_x = ENN_UI_MENU_MAX_COORD;

                                render_rectangle_push(
                                        (f32vec2) { menu_right_x, big_buttons[i].local_pos.y - pad_y - ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                        (f32vec2) { submenu_right_x + ENN_UI_BORDER_WIDTH, big_buttons[i].local_pos.y + big_buttons[i].dim.y + pad_y + ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                        ENN_UI_BORDER_COLOR
                                );

                                render_rectangle_push(
                                        (f32vec2) { menu_right_x - ENN_UI_BORDER_WIDTH, big_buttons[i].local_pos.y - pad_y },
                                        (f32vec2) { submenu_right_x, big_buttons[i].local_pos.y + big_buttons[i].dim.y + pad_y },
                                        ENN_UI_MENU_BKG_COLOR
                                );

                                for (i32 j = big_buttons[i].sub_buttons.start; j < big_buttons[i].sub_buttons.end; ++j) {
                                        UIMenuButton* sub = &big_buttons[i].sub_buttons.data[j];
                                        if (!game_ui_sub_button_is_visible(i, sub)) continue;

                                        f32vec4 sub_rect = game_ui_sub_button_rect(i, sub);

                                        render_rectangle_push(
                                                (f32vec2) { sub_rect.x - ENN_UI_BORDER_WIDTH, sub_rect.y - ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                                (f32vec2) { sub_rect.x + sub_rect.z + ENN_UI_BORDER_WIDTH, sub_rect.y + sub_rect.w + ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                                ENN_UI_BORDER_COLOR
                                        );

                                        render_rectangle_push(
                                                (f32vec2) { sub_rect.x, sub_rect.y },
                                                (f32vec2) { sub_rect.x + sub_rect.z, sub_rect.y + sub_rect.w },
                                                sub->color
                                        );

                                        if (sub -> render_chip_preview && sub -> blueprint != global_circuit.blueprints.end && sub -> blueprint < global_circuit.blueprints.end) {
                                                circuit_render_blueprint_chip_preview(
                                                        sub -> blueprint,
                                                        (f32vec2) { sub_rect.x + ENN_UI_CHIP_PREVIEW_PADDING, sub_rect.y + ENN_UI_CHIP_PREVIEW_PADDING * ENN_FRAMEBUFF_ASPECT_RATIO },
                                                        (f32vec2) { sub_rect.x + sub_rect.z - ENN_UI_CHIP_PREVIEW_PADDING, sub_rect.y + sub_rect.w - ENN_UI_CHIP_PREVIEW_PADDING * ENN_FRAMEBUFF_ASPECT_RATIO }
                                                );
                                        } else if (sub->sprite != NULL) {
                                                f32 cx = sub_rect.x + sub_rect.z * 0.5f;
                                                f32 cy = sub_rect.y + sub_rect.w * 0.5f;
                                                f32 sw = sub->sprite_dim.x;
                                                f32 sh = sub->sprite_dim.y;
                                                render_sprite_push(
                                                        (f32vec2) { cx - sw * 0.5f, cy - sh * 0.5f },
                                                        (f32vec2) { cx + sw * 0.5f, cy + sh * 0.5f },
                                                        sub->sprite
                                                );
                                        }

                                        if (hovered_button_id == sub->id) {
                                                render_rectangle_push(
                                                        (f32vec2) { sub_rect.x, sub_rect.y },
                                                        (f32vec2) { sub_rect.x + sub_rect.z, sub_rect.y + sub_rect.w },
                                                        ENN_UI_HOVER_OVERLAY_COLOR
                                                );
                                        }
                                }
                        }

                        render_rectangle_push(
                                (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x - ENN_UI_BORDER_WIDTH, big_buttons[i].local_pos.y - ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x + big_buttons[i].dim.x + ENN_UI_BORDER_WIDTH, big_buttons[i].local_pos.y + big_buttons[i].dim.y + ENN_UI_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                                ENN_UI_BORDER_COLOR
                        );

                        render_rectangle_push(
                                (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x, big_buttons[i].local_pos.y },
                                (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x + big_buttons[i].dim.x, big_buttons[i].local_pos.y + big_buttons[i].dim.y },
                                big_buttons[i].color
                        );

                        if (big_buttons[i].sprite != NULL) {
                                f32 cx = big_buttons[i].local_pos.x + menu_offset_x + big_buttons[i].dim.x * 0.5;
                                f32 cy = big_buttons[i].local_pos.y + big_buttons[i].dim.y * 0.5;
                                f32 sw = big_buttons[i].sprite_dim.x;
                                f32 sh = big_buttons[i].sprite_dim.y;
                                render_sprite_push(
                                        (f32vec2) { cx - sw * 0.5, cy - sh * 0.5 },
                                        (f32vec2) { cx + sw * 0.5, cy + sh * 0.5 },
                                        big_buttons[i].sprite
                                );
                        }

                        if (hovered_button_id == big_buttons[i].id) {
                                render_rectangle_push(
                                        (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x, big_buttons[i].local_pos.y },
                                        (f32vec2) { big_buttons[i].local_pos.x + menu_offset_x + big_buttons[i].dim.x, big_buttons[i].local_pos.y + big_buttons[i].dim.y },
                                        ENN_UI_HOVER_OVERLAY_COLOR
                                );
                        }
                }
        }

        f64 time_since_save = glfwGetTime() - save_notification_started;
        if (time_since_save >= 0.0 && time_since_save < ENN_UI_SAVE_NOTIFICATION_TIME) {
                render_text_push(
                        (f32vec2) { 0.98, 0.88 },
                        (f32vec2) { 0.98, 0.88 },
                        ENN_UI_SAVE_NOTIFICATION_TEXT,
                        ENN_UI_SAVE_NOTIFICATION_COLOR,
                        ENN_UI_SAVE_NOTIFICATION_HEIGHT,
                        ENN_RIGHT_ALIGN
                );
        }
}

void game_ui_layer_on_update(f64 dt) {
        f32 target_offset = menu_expanded ? 0.0 : -ENN_UI_MENU_WIDTH;
        if (menu_offset_x != target_offset) {
                f32 dir = (target_offset > menu_offset_x) ? 1.0 : -1.0;
                menu_offset_x += dir * ENN_UI_MENU_SPEED * dt;
                if ((dir > 0.0 && menu_offset_x > target_offset) || (dir < 0.0 && menu_offset_x < target_offset)) {
                        menu_offset_x = target_offset;
                }
        }

        for (i32 i = 0; i < ENN_UI_TEXT_BTN_COUNT; ++i) {
                text_buttons.list.data[i].pos.x = text_btn_base_x[i] + menu_offset_x;
        }
}

void game_ui_layer_on_event(Event* event) {
        switch (event -> type) {
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        if (current_action != ENN_ACTION_NOTHING) {
                                hovered_button_id = 0;
                                text_buttons.hover = NULL;
                                event -> handled = false;
                                break;
                        }

                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        
                        hovered_button_id = 0;
                        bool handled = false;

                        if (ndc.x <= ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x) {
                                handled = true;
                        }

                        bool in_submenu = false;
                        if (active_submenu_index != -1) {
                                i32 i = active_submenu_index;
                                f32vec4 row_rect = game_ui_submenu_row_rect(i);
                                if (is_inside_rectangle(ndc, row_rect)) {
                                        in_submenu = true;
                                        handled = true;
                                } else {
                                        active_submenu_index = -1;
                                }
                        }

                        if (!in_submenu) {
                                f32 toggle_x1 = ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x;
                                f32vec4 toggle_rect = { toggle_x1, ENN_UI_TOGGLE_BTN_POS_Y, ENN_UI_TOGGLE_BTN_WIDTH, ENN_UI_TOGGLE_BTN_HEIGHT };
                                
                                if (is_inside_rectangle(ndc, toggle_rect)) {
                                        hovered_button_id = ENN_UI_BTN_ID_TOGGLE;
                                        handled = true;
                                }
                        }

                        if (menu_expanded && hovered_button_id == 0) {
                                ui_text_button_list_check_hover(&text_buttons, ndc);
                                if (text_buttons.hover != NULL) {
                                        hovered_button_id = text_buttons.hover -> id;
                                        handled = true;
                                } else {
                                        if (active_submenu_index != -1) {
                                                i32 i = active_submenu_index;
                                                f32vec4 btn_rect = { big_buttons[i].local_pos.x + menu_offset_x, big_buttons[i].local_pos.y, big_buttons[i].dim.x, big_buttons[i].dim.y };
                                                if (is_inside_rectangle(ndc, btn_rect)) {
                                                        hovered_button_id = big_buttons[i].id;
                                                } else {
                                                        for (i32 j = big_buttons[i].sub_buttons.start; j < big_buttons[i].sub_buttons.end; ++j) {
                                                                UIMenuButton* sub = &big_buttons[i].sub_buttons.data[j];
                                                                if (!game_ui_sub_button_is_visible(i, sub)) continue;
                                                                f32vec4 sub_rect = game_ui_sub_button_rect(i, sub);
                                                                if (is_inside_rectangle(ndc, sub_rect)) {
                                                                        hovered_button_id = sub->id;
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }

                                        if (active_submenu_index == -1) {
                                                for (i32 i = 0; i < ENN_UI_BIG_BTN_COUNT; ++i) {
                                                        f32vec4 btn_rect = { big_buttons[i].local_pos.x + menu_offset_x, big_buttons[i].local_pos.y, big_buttons[i].dim.x, big_buttons[i].dim.y };
                                                        if (is_inside_rectangle(ndc, btn_rect)) {
                                                                hovered_button_id = big_buttons[i].id;
                                                                active_submenu_index = i;
                                                                handled = true;
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        } else {
                                text_buttons.hover = NULL;
                        }

                        event -> handled = handled;

                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        if (current_action != ENN_ACTION_NOTHING) {
                                event -> handled = false;
                                break;
                        }

                        struct { i32 button, action; }* data = event -> data;
                        
                        f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                        bool handled = false;
                        
                        if (ndc.x <= ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x) {
                                handled = true;
                        }
                        
                        bool in_submenu = false;
                        if (active_submenu_index != -1) {
                                i32 i = active_submenu_index;
                                f32vec4 row_rect = game_ui_submenu_row_rect(i);
                                if (is_inside_rectangle(ndc, row_rect)) {
                                        in_submenu = true;
                                        handled = true;
                                }
                        }

                        if (!in_submenu) {
                                f32 toggle_x1 = ENN_UI_MENU_MIN_COORD + ENN_UI_MENU_WIDTH + menu_offset_x;
                                f32vec4 toggle_rect = { toggle_x1, ENN_UI_TOGGLE_BTN_POS_Y, ENN_UI_TOGGLE_BTN_WIDTH, ENN_UI_TOGGLE_BTN_HEIGHT };
                                if (is_inside_rectangle(ndc, toggle_rect)) {
                                        handled = true;
                                }
                        }

                        event -> handled = handled;

                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS) {
                                if (hovered_button_id == ENN_UI_BTN_ID_TOGGLE) {
                                        menu_expanded = !menu_expanded;
                                        render_sprite_flip_horizontal(&toggle_sprite);
                                        if (!menu_expanded) {
                                                hovered_button_id = 0;
                                                active_submenu_index = -1;
                                        }
                                } else if (text_buttons.hover != NULL) {
                                        switch (text_buttons.hover -> id) {
                                                case ENN_UI_BTN_ID_SWITCH_STATE:
                                                {
                                                        game_ui_toggle_mode();
                                                        break;
                                                }
                                                case ENN_UI_BTN_ID_SAVE_CIRCUIT:
                                                {
                                                        game_ui_save_circuit();
                                                        break;
                                                }
                                                case ENN_UI_BTN_ID_COMPILE_CIRCUIT:
                                                {
                                                        game_ui_start_compile();
                                                        break;
                                                }
                                                case ENN_UI_BTN_ID_QUIT: 
                                                {
                                                        game_stop();
                                                        layer_set_active(menu_layer_id);
                                                        break;
                                                }
                                        }
                                } else {
                                        bool is_input = false;
                                        ENN_CIRCUIT_ELEMENT_COLORS color = ENN_INTERNAL_COLOR_LAST;
                                        if (global_state.game_state == ENN_EDIT_MODE && game_ui_is_indicator_button(hovered_button_id, &is_input, &color)) {
                                                game_ui_summon_indicator_for_move(is_input, color);
                                        } else {
                                                BlueprintChipIndex blueprint = global_circuit.blueprints.end;
                                                if (global_state.game_state == ENN_EDIT_MODE && game_ui_is_chip_button(hovered_button_id, &blueprint)) {
                                                        game_ui_summon_chip_for_move(blueprint);
                                                }
                                        }
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_SCROLL_EVENT:
                {
                        if (current_action != ENN_ACTION_NOTHING || !menu_expanded || active_submenu_index != 2) {
                                event -> handled = false;
                                break;
                        }

                        f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                        f32vec4 row_rect = game_ui_submenu_row_rect(active_submenu_index);
                        if (is_inside_rectangle(ndc, row_rect)) {
                                f64* offset = event -> data;
                                chip_submenu_scroll += (f32)(*offset) * ENN_UI_CHIP_SCROLL_CHANGE;
                                game_ui_clamp_chip_submenu_scroll();
                                event -> handled = true;
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_TAB && data -> action == GLFW_PRESS) {
                                menu_expanded = !menu_expanded;
                                render_sprite_flip_horizontal(&toggle_sprite);
                                if (!menu_expanded) {
                                        hovered_button_id = 0;
                                        active_submenu_index = -1;
                                }
                                event -> handled = true;
                        }

                        break;
                }
                default: break;
        }
}
