// ==================== Changes to GAME_LAYER.C ====================

#include "layer.h"

#include "Game/MapLayer/map.h"
#include "Game/objects.h"

#define ENN_MAGNETIZATION_THRESHOLD 0.1

LayerID game_layer_id;

static DataFile game_save;
Circuit global_circuit;
ENN_GAME_ACTION current_action;

static ExternalWire input_wire;

void game_start(const char* save_filepath) {
        DEBUG_TRACE();
        datafile_create(&game_save);
        datafile_read(&game_save, save_filepath);

        layer_set_active(game_ui_layer_id);
        layer_set_active(game_layer_id);
        layer_set_active(map_layer_id);
        DEBUG_UNTRACE();
}

void game_stop(void) {
        DEBUG_TRACE();
        datafile_write(&game_save, game_save.filepath);
        datafile_destroy(&game_save);

        layer_set_inactive(game_ui_layer_id);
        layer_set_inactive(game_layer_id);
        layer_set_inactive(map_layer_id);
        DEBUG_UNTRACE();
}

void game_layer_init(void) {
        DEBUG_TRACE();
        current_action = ENN_ACTION_NOTHING;
        circuit_summon_input_indicator((f32vec2) { 0, 0 }, ENN_INTERNAL_COLOR_RED);
        circuit_summon_input_indicator((f32vec2) { 0, CIRCUIT_INDICATOR_HITBOX_HEIGHT }, ENN_INTERNAL_COLOR_ORANGE);
        circuit_summon_input_indicator((f32vec2) { 0, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 2 }, ENN_INTERNAL_COLOR_YELLOW);
        circuit_summon_input_indicator((f32vec2) { 0, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 3 }, ENN_INTERNAL_COLOR_GREEN);
        circuit_summon_input_indicator((f32vec2) { 0, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 4 }, ENN_INTERNAL_COLOR_BLUE);
        circuit_summon_input_indicator((f32vec2) { 0, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 5 }, ENN_INTERNAL_COLOR_PURPLE);

        circuit_summon_output_indicator((f32vec2) { 20, 0 }, ENN_INTERNAL_COLOR_RED);
        circuit_summon_output_indicator((f32vec2) { 20, CIRCUIT_INDICATOR_HITBOX_HEIGHT }, ENN_INTERNAL_COLOR_ORANGE);
        circuit_summon_output_indicator((f32vec2) { 20, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 2 }, ENN_INTERNAL_COLOR_YELLOW);
        circuit_summon_output_indicator((f32vec2) { 20, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 3 }, ENN_INTERNAL_COLOR_GREEN);
        circuit_summon_output_indicator((f32vec2) { 20, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 4 }, ENN_INTERNAL_COLOR_BLUE);
        circuit_summon_output_indicator((f32vec2) { 20, CIRCUIT_INDICATOR_HITBOX_HEIGHT * 5 }, ENN_INTERNAL_COLOR_PURPLE);

        global_circuit.hovered_pin = global_circuit.external_pins.end;
        DEBUG_UNTRACE();
}

void game_layer_term(void) {
}

void game_layer_on_render(void) {
        DEBUG_TRACE();
        render_proj_set((f32mat4) {
                2 / map_view.visible_pixels.x * map_view.zoom, 0, 0, -(2 * map_view.camera_offset.x ) / map_view.visible_pixels.x * map_view.zoom - 1.0,
                0, -(2 / map_view.visible_pixels.y * map_view.zoom), 0, (2 * map_view.camera_offset.y) / map_view.visible_pixels.y * map_view.zoom + 1.0,
                0, 0, -1, 0,
                0, 0, 0, 1
        });

        switch (global_state.game_state) {
                case ENN_EDIT_MODE:
                {
                        if (current_action == ENN_ACTION_WIRING) {
                                f32vec2 map = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                                map = circuit_magnetize_line(input_wire.anchors.data[input_wire.anchors.end - 1], map, ENN_MAGNETIZATION_THRESHOLD);
                                vector_push_back(input_wire.anchors, map);
                                render_multiline_push(
                                        input_wire.anchors.data + input_wire.anchors.start, 
                                        vector_size(input_wire.anchors), CIRCUIT_WIRE_WIDTH, 
                                        color_dark_get_by_circuit_color(input_wire.color)
                                );
                                vector_pop_back(input_wire.anchors);
                        }
                        circuit_render_objects_edit();
                        break;
                }
                case ENN_EXECUTE_MODE:
                {
                        circuit_render_objects_execute();
                        break;
                }
        }

        DEBUG_UNTRACE();
}

void game_layer_on_update(f64 dt) {
        DEBUG_TRACE();
        if (global_state.game_state == ENN_EXECUTE_MODE) {
                static f64 last_tick = 0.0;
                last_tick += dt;
                if (last_tick >= ((f64)1.0 / (f64)settings.simulaton_tps))
                        circuit_update_tick();
        }
        DEBUG_UNTRACE();
}

void game_layer_on_event(Event* event) {
        switch (event -> type) {
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;

                        if (data -> key == GLFW_KEY_ESCAPE && data -> action == GLFW_PRESS) {
                                switch (current_action) {

                                        case ENN_ACTION_NOTHING:
                                        {
                                                if (!global_state.pause) {
                                                        global_state.pause = true;
                                                        layer_set_active(escape_menu_layer_id);
                                                        event -> handled = true;
                                                }
                                                break;
                                        }
                                        case ENN_ACTION_WIRING:
                                        {
                                                vector_clear(input_wire.anchors);
                                                input_wire.from = global_circuit.external_pins.end;
                                                input_wire.to = global_circuit.external_pins.end;
                                                current_action = ENN_ACTION_NOTHING;
                                                event -> handled = true;
                                                break;
                                        }
                                        default: break;
                                }
                        }


                        break;
                }
                case ENN_INPUT_MOUSE_MOVE_EVENT:
                {
                        f64vec2* data = event -> data;
                        f32vec2 map = screen_to_map((f32vec2) { data -> x, data -> y });
                        switch (global_state.game_state) {
                                case ENN_EDIT_MODE:
                                {
                                        circuit_check_hovered_pin(map);
                                        break;
                                }
                                case ENN_EXECUTE_MODE:
                                {
                                        break;
                                }
                        }
                        break;
                }
                case ENN_INPUT_MOUSE_BUTTON_EVENT:
                {
                        struct { i32 button, action; }* data = event -> data;
                        f32vec2 map = screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y });
                        if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_PRESS) {
                                switch (global_state.game_state) {
                                        case ENN_EDIT_MODE:
                                        {
                                                switch (current_action) {
                                                        case ENN_ACTION_NOTHING:
                                                        {
                                                                if (global_circuit.hovered_pin != global_circuit.external_pins.end) {
                                                                        vector_clear(input_wire.anchors);
                                                                        input_wire.from = global_circuit.external_pins.end;
                                                                        input_wire.to = global_circuit.external_pins.end;

                                                                        input_wire.from = global_circuit.hovered_pin;
                                                                        input_wire.color = circuit_get_pin_color(global_circuit.hovered_pin);
                                                                        f32vec2 pin_anchor = {
                                                                                .x = global_circuit.external_pins.data[global_circuit.hovered_pin].pos.x + CIRCUIT_PIN_WIDTH * 0.5,
                                                                                .y = global_circuit.external_pins.data[global_circuit.hovered_pin].pos.y + CIRCUIT_PIN_HEIGHT * 0.5
                                                                        };
                                                                        vector_push_back(input_wire.anchors, pin_anchor);
                                                                        current_action = ENN_ACTION_WIRING;
                                                                        event -> handled = true;
                                                                }

                                                                break;
                                                        }
                                                        case ENN_ACTION_WIRING:
                                                        {
                                                                if (global_circuit.hovered_pin != global_circuit.external_pins.end) {
                                                                        f32vec2 pin_anchor = {
                                                                                .x = global_circuit.external_pins.data[global_circuit.hovered_pin].pos.x + CIRCUIT_PIN_WIDTH * 0.5,
                                                                                .y = global_circuit.external_pins.data[global_circuit.hovered_pin].pos.y + CIRCUIT_PIN_HEIGHT * 0.5
                                                                        };
                                                                        vector_push_back(input_wire.anchors, pin_anchor);
                                                                        circuit_summon_external_wire(
                                                                                input_wire.anchors.data + input_wire.anchors.start,
                                                                                vector_size(input_wire.anchors),
                                                                                input_wire.from,
                                                                                global_circuit.hovered_pin
                                                                        );
                                                                        current_action = ENN_ACTION_NOTHING;
                                                                        event -> handled = true;
                                                                } else {
                                                                        vector_push_back(input_wire.anchors, map);
                                                                        event -> handled = true;
                                                                }

                                                                break;
                                                        }
                                                        default: break;
                                                }

                                                break;
                                        }
                                        case ENN_EXECUTE_MODE:
                                        {
                                                break;
                                        }
                                }
                        } 
                        break;
                }
                default: break;
        }
}