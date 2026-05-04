#include "layer.h"
#include "Game/objects.h"

LayerID chip_layer_id;

#define ENN_CHIP_LAYER_BKG_COLOR                0x000000B0
#define ENN_CHIP_LAYER_PANEL_COLOR              0x101214FF
#define ENN_CHIP_LAYER_PANEL_BORDER_COLOR       0x7a7c7e80
#define ENN_CHIP_LAYER_TEXT_COLOR               0xFFFFFFFF
#define ENN_CHIP_LAYER_MUTED_TEXT_COLOR         0x80808080
#define ENN_CHIP_LAYER_ERROR_COLOR              0xd75f5fFF
#define ENN_CHIP_LAYER_CURSOR_TIME              0.5

#define ENN_CHIP_LAYER_PANEL_X1                 -0.55
#define ENN_CHIP_LAYER_PANEL_Y1                 -0.45
#define ENN_CHIP_LAYER_PANEL_X2                  0.55
#define ENN_CHIP_LAYER_PANEL_Y2                  0.45
#define ENN_CHIP_LAYER_BORDER_WIDTH              0.01

#define ENN_CHIP_LAYER_TITLE_TEXT               "NEW CHIP BLUEPRINT"
#define ENN_CHIP_LAYER_NAME_PLACEHOLDER         "NAME"
#define ENN_CHIP_LAYER_EMPTY_ERROR              "TYPE A NAME"
#define ENN_CHIP_LAYER_DUPLICATE_ERROR          "ERROR: Chip Blueprint with the same name already exists"

#define ENN_CHIP_LAYER_TITLE_HEIGHT              0.075
#define ENN_CHIP_LAYER_INPUT_HEIGHT              0.13
#define ENN_CHIP_LAYER_HINT_HEIGHT               0.04
#define ENN_CHIP_LAYER_SWATCH_SIZE               0.09
#define ENN_CHIP_LAYER_SWATCH_SPACING            0.035

static vector(char) input_string;
static ENN_CIRCUIT_ELEMENT_COLORS selected_color;
static ENN_CIRCUIT_ELEMENT_COLORS hovered_color;
static bool cursor_state;
static bool empty_name_error;
static bool duplicate_name_error;
static f64 last_cursor_change;

ENNDEF_PUBLIC f32vec4 chip_layer_color_rect(ENN_CIRCUIT_ELEMENT_COLORS color) {
        f32 total_width = ENN_INTERNAL_COLOR_LAST * ENN_CHIP_LAYER_SWATCH_SIZE + (ENN_INTERNAL_COLOR_LAST - 1) * ENN_CHIP_LAYER_SWATCH_SPACING;
        f32 x = -total_width * 0.5 + color * (ENN_CHIP_LAYER_SWATCH_SIZE + ENN_CHIP_LAYER_SWATCH_SPACING);
        return (f32vec4) {
                .x = x,
                .y = 0.17,
                .z = ENN_CHIP_LAYER_SWATCH_SIZE,
                .w = ENN_CHIP_LAYER_SWATCH_SIZE * ENN_FRAMEBUFF_ASPECT_RATIO
        };
}

ENNDEF_PUBLIC void chip_layer_finish(void) {
        DEBUG_TRACE();
        layer_set_inactive(chip_layer_id);
        vector_clear(input_string);
        empty_name_error = false;
        duplicate_name_error = false;
        hovered_color = ENN_INTERNAL_COLOR_LAST;
        DEBUG_UNTRACE();
}

void chip_layer_start_compile(void) {
        DEBUG_TRACE();
        vector_clear(input_string);
        if (input_string.capacity > 0) input_string.data[input_string.start] = 0;
        selected_color = ENN_INTERNAL_COLOR_RED;
        hovered_color = ENN_INTERNAL_COLOR_LAST;
        cursor_state = true;
        empty_name_error = false;
        duplicate_name_error = false;
        last_cursor_change = glfwGetTime();
        DEBUG_UNTRACE();
}

void chip_layer_init(void) {
        DEBUG_TRACE();
        selected_color = ENN_INTERNAL_COLOR_RED;
        hovered_color = ENN_INTERNAL_COLOR_LAST;
        cursor_state = true;
        empty_name_error = false;
        duplicate_name_error = false;
        last_cursor_change = 0.0;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void chip_layer_try_create(void) {
        DEBUG_TRACE();
        if (vector_size(input_string) == 0) {
                empty_name_error = true;
                duplicate_name_error = false;
        } else if (circuit_find_blueprint_by_name(input_string.data + input_string.start) != global_circuit.blueprints.end) {
                empty_name_error = false;
                duplicate_name_error = true;
        } else {
                BlueprintChipIndex blueprint = circuit_compile_current_to_blueprint(input_string.data + input_string.start, selected_color);
                circuit_save_blueprint_to_disk(blueprint);
                game_ui_register_chip_blueprint(blueprint);
                chip_layer_finish();
        }
        DEBUG_UNTRACE();
}

void chip_layer_term(void) {
        DEBUG_TRACE();
        vector_destroy(input_string);
        DEBUG_UNTRACE();
}

void chip_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                1, 0, 0, 0,
                0, -1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        });

        render_rectangle_push((f32vec2) { -1.0, -1.0 }, (f32vec2) { 1.0, 1.0 }, ENN_CHIP_LAYER_BKG_COLOR);
        render_rectangle_push(
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X1 - ENN_CHIP_LAYER_BORDER_WIDTH, ENN_CHIP_LAYER_PANEL_Y1 - ENN_CHIP_LAYER_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X2 + ENN_CHIP_LAYER_BORDER_WIDTH, ENN_CHIP_LAYER_PANEL_Y2 + ENN_CHIP_LAYER_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                ENN_CHIP_LAYER_PANEL_BORDER_COLOR
        );
        render_rectangle_push(
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X1, ENN_CHIP_LAYER_PANEL_Y1 },
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X2, ENN_CHIP_LAYER_PANEL_Y2 },
                ENN_CHIP_LAYER_PANEL_COLOR
        );

        render_text_push(
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X1, -0.33 },
                (f32vec2) { ENN_CHIP_LAYER_PANEL_X2, -0.25 },
                ENN_CHIP_LAYER_TITLE_TEXT,
                ENN_CHIP_LAYER_TEXT_COLOR,
                ENN_CHIP_LAYER_TITLE_HEIGHT,
                ENN_CENTER_ALIGN
        );

        f64 now = glfwGetTime();
        if (now - last_cursor_change >= ENN_CHIP_LAYER_CURSOR_TIME) {
                cursor_state = !cursor_state;
                last_cursor_change = now;
        }

        f32vec2 input_pos1 = { ENN_CHIP_LAYER_PANEL_X1 + 0.08, -0.11 };
        f32vec2 input_pos2 = { ENN_CHIP_LAYER_PANEL_X2 - 0.08, 0.04 };
        if (vector_size(input_string) > 0) {
                render_text_push(input_pos1, input_pos2, input_string.data + input_string.start, ENN_CHIP_LAYER_TEXT_COLOR, ENN_CHIP_LAYER_INPUT_HEIGHT, ENN_CENTER_ALIGN);
        } else {
                render_text_push(input_pos1, input_pos2, ENN_CHIP_LAYER_NAME_PLACEHOLDER, ENN_CHIP_LAYER_MUTED_TEXT_COLOR, ENN_CHIP_LAYER_INPUT_HEIGHT, ENN_CENTER_ALIGN);
        }

        if (cursor_state) {
                f32 render_text_ratio = ((f32)global_render.font_atlas.char_dim.x / (f32)global_render.font_atlas.char_dim.y);
                f32 text_width = vector_size(input_string) * ENN_CHIP_LAYER_INPUT_HEIGHT * render_text_ratio;
                f32 cursor_x = text_width * 0.5 + ENN_CHIP_LAYER_INPUT_HEIGHT * render_text_ratio * 0.25;
                render_rectangle_push(
                        (f32vec2) { cursor_x, input_pos1.y },
                        (f32vec2) { cursor_x + ENN_CHIP_LAYER_INPUT_HEIGHT * render_text_ratio * 0.25, input_pos2.y },
                        ENN_CHIP_LAYER_TEXT_COLOR
                );
        }

        for (ENN_CIRCUIT_ELEMENT_COLORS color = 0; color < ENN_INTERNAL_COLOR_LAST; ++color) {
                f32vec4 rect = chip_layer_color_rect(color);
                u32 border_color = (color == selected_color || color == hovered_color) ? ENN_CHIP_LAYER_TEXT_COLOR : ENN_CHIP_LAYER_PANEL_BORDER_COLOR;
                render_rectangle_push(
                        (f32vec2) { rect.x - ENN_CHIP_LAYER_BORDER_WIDTH, rect.y - ENN_CHIP_LAYER_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                        (f32vec2) { rect.x + rect.z + ENN_CHIP_LAYER_BORDER_WIDTH, rect.y + rect.w + ENN_CHIP_LAYER_BORDER_WIDTH * ENN_FRAMEBUFF_ASPECT_RATIO },
                        border_color
                );
                render_rectangle_push(
                        (f32vec2) { rect.x, rect.y },
                        (f32vec2) { rect.x + rect.z, rect.y + rect.w },
                        color_light_get_by_circuit_color(color)
                );
        }

        if (empty_name_error || duplicate_name_error) {
                render_text_push(
                        (f32vec2) { ENN_CHIP_LAYER_PANEL_X1, 0.415 },
                        (f32vec2) { ENN_CHIP_LAYER_PANEL_X2, 0.445 },
                        empty_name_error ? ENN_CHIP_LAYER_EMPTY_ERROR : ENN_CHIP_LAYER_DUPLICATE_ERROR,
                        ENN_CHIP_LAYER_ERROR_COLOR,
                        ENN_CHIP_LAYER_HINT_HEIGHT,
                        ENN_CENTER_ALIGN
                );
        }

        DEBUG_UNTRACE();
}

void chip_layer_on_update(f64 dt) {
}

void chip_layer_on_event(Event* event) {
        DEBUG_TRACE();
        switch (event -> type) {
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 ndc = screen_to_ndc((f32vec2) { data -> x, data -> y });
                        hovered_color = ENN_INTERNAL_COLOR_LAST;
                        for (ENN_CIRCUIT_ELEMENT_COLORS color = 0; color < ENN_INTERNAL_COLOR_LAST; ++color)
                                if (is_inside_rectangle(ndc, chip_layer_color_rect(color))) {
                                        hovered_color = color;
                                        break;
                                }
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS) {
                                f32vec2 ndc = screen_to_ndc((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                for (ENN_CIRCUIT_ELEMENT_COLORS color = 0; color < ENN_INTERNAL_COLOR_LAST; ++color)
                                        if (is_inside_rectangle(ndc, chip_layer_color_rect(color))) {
                                                selected_color = color;
                                                break;
                                        }
                        }
                        break;
                }
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                chip_layer_finish();
                        } else if (data -> key == GLFW_KEY_BACKSPACE && (data -> action == GLFW_PRESS || data -> action == GLFW_REPEAT)) {
                                if (vector_size(input_string) > 0) {
                                        vector_pop_back(input_string);
                                        input_string.data[input_string.end] = 0;
                                        cursor_state = true;
                                        last_cursor_change = glfwGetTime();
                                        empty_name_error = false;
                                        duplicate_name_error = false;
                                }
                        } else if (data -> key == GLFW_KEY_ENTER && data -> action == GLFW_PRESS) {
                                chip_layer_try_create();
                        }
                        break;
                }
                case ENN_INPUT_TEXT_EVENT:
                {
                        u32* code = event -> data;
                        if (*code >= ENN_FONT_ATLAS_FIRST_CHAR && *code <= ENN_FONT_ATLAS_LAST_CHAR && vector_size(input_string) < min(CIRCUIT_CHIP_MAX_NAME_LEN, ENN_DATAFILE_MAX_STRING_SIZE) - 1) {
                                char ch = (char)*code;
                                vector_push_back(input_string, ch);
                                input_string.data[input_string.end] = 0;
                                cursor_state = true;
                                last_cursor_change = glfwGetTime();
                                empty_name_error = false;
                                duplicate_name_error = false;
                        }
                        break;
                }
                default: break;
        }
        event -> handled = true;
        DEBUG_UNTRACE();
}
