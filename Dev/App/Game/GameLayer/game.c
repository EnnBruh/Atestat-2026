#include "layer.h"

#include "Game/MapLayer/map.h"
#include "Game/objects.h"

#define ENN_MAGNETIZATION_THRESHOLD 0.1

LayerID game_layer_id;

static char* game_save_filepath;
Circuit global_circuit;
CircuitClipboard circuit_clipboard;
ENN_GAME_ACTION current_action;
CircuitSelectionPane selection_pane;

static ExternalWire input_wire;

void game_save_current_workspace(void) {
        DEBUG_TRACE();
        if (game_save_filepath != NULL)
                circuit_save_workspace(game_save_filepath);
        DEBUG_UNTRACE();
}

void game_start(const char* save_filepath) {
        DEBUG_TRACE();
        free(game_save_filepath);
        game_save_filepath = calloc(strlen(save_filepath) + 1, (sizeof (char)));
        strcpy(game_save_filepath, save_filepath);

        global_state.game_state = ENN_EDIT_MODE;
        circuit_load_workspace(game_save_filepath);

        layer_set_active(game_ui_layer_id);
        layer_set_active(game_layer_id);
        layer_set_active(map_layer_id);
        DEBUG_UNTRACE();
}

void game_stop(void) {
        DEBUG_TRACE();
        game_save_current_workspace();
        free(game_save_filepath);
        game_save_filepath = NULL;

        layer_set_inactive(game_ui_layer_id);
        layer_set_inactive(game_layer_id);
        layer_set_inactive(map_layer_id);
        DEBUG_UNTRACE();
}

void game_layer_init(void) {
        DEBUG_TRACE();
        current_action = ENN_ACTION_NOTHING;
        circuit_get_nand_blueprint();
        circuit_load_blueprints_from_disk();
        for (i32 i = global_circuit.blueprints.start; i < global_circuit.blueprints.end; ++i)
                game_ui_register_chip_blueprint(i);
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        DEBUG_UNTRACE();
}

void game_layer_term(void) {
        game_save_current_workspace();
        circuit_clipboard_destroy();
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
                        if (current_action == ENN_ACTION_SELECTING)
                                circuit_render_selection_pane();
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
        static f64 last_tick = 0.0;
        if (global_state.game_state == ENN_EXECUTE_MODE) {
                last_tick += dt;
                f64 tick_time = ((f64)1.0 / (f64)settings.simulaton_tps);
                while (last_tick >= tick_time) {
                        circuit_update_tick();
                        last_tick -= tick_time;
                }
        } else {
                last_tick = 0.0;
        }
        DEBUG_UNTRACE();
}

void game_layer_on_event(Event* event) {
        switch (event -> type) {
                case ENN_INPUT_KEY_EVENT:
                {
                        struct { i32 key, action; }* data = event -> data;
                        bool ctrl_down = global_state.is_key_down[GLFW_KEY_LEFT_CONTROL] || global_state.is_key_down[GLFW_KEY_RIGHT_CONTROL];

                        if (data -> action == GLFW_PRESS && current_action == ENN_ACTION_NOTHING) {
                                if (ctrl_down && data -> key == GLFW_KEY_S) {
                                        game_ui_save_circuit();
                                        event -> handled = true;
                                } else if (ctrl_down && data -> key == GLFW_KEY_X) {
                                        game_ui_start_compile();
                                        event -> handled = true;
                                } else if (global_state.game_state == ENN_EDIT_MODE && ctrl_down && data -> key == GLFW_KEY_A) {
                                        circuit_selection_select_all();
                                        event -> handled = true;
                                } else if (global_state.game_state == ENN_EDIT_MODE && ctrl_down && data -> key == GLFW_KEY_C) {
                                        circuit_clipboard_copy(screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y }));
                                        event -> handled = true;
                                } else if (global_state.game_state == ENN_EDIT_MODE && ctrl_down && data -> key == GLFW_KEY_V) {
                                        circuit_clipboard_paste(screen_to_map((f32vec2) { global_state.mouse_pos.x, global_state.mouse_pos.y }));
                                        event -> handled = true;
                                } else if (data -> key == GLFW_KEY_LEFT_SHIFT || data -> key == GLFW_KEY_RIGHT_SHIFT) {
                                        game_ui_toggle_mode();
                                        event -> handled = true;
                                }
                        }

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
                                        case ENN_ACTION_SELECTING:
                                        {
                                                current_action = ENN_ACTION_NOTHING;
                                                event -> handled = true;
                                                break;
                                        }
                                        case ENN_ACTION_MOVING:
                                        {
                                                circuit_selection_move_revert();
                                                current_action = ENN_ACTION_NOTHING;
                                                event -> handled = true;
                                                break;
                                        }
                                        default: break;
                                }
                        }

                        if (data -> key == GLFW_KEY_DELETE && data -> action == GLFW_PRESS && current_action == ENN_ACTION_NOTHING && global_state.game_state == ENN_EDIT_MODE) {
                                circuit_selection_destroy();
                                event -> handled = true;
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
                                        if (current_action == ENN_ACTION_SELECTING) {
                                                circuit_selection_pane_extend(map);
                                                event -> handled = true;
                                        } else if (current_action == ENN_ACTION_MOVING) {
                                                f32vec2 delta = {
                                                        .x = map.x - selection_pane.last_move.x,
                                                        .y = map.y - selection_pane.last_move.y
                                                };
                                                circuit_move_selection(delta);
                                                selection_pane.last_move = map;
                                                circuit_selection_check_collisions();
                                                event -> handled = true;
                                        } else {
                                                circuit_check_hovered_pin(map);
                                        }
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
                                                bool additive_selection = global_state.is_key_down[GLFW_KEY_LEFT_CONTROL] || global_state.is_key_down[GLFW_KEY_RIGHT_CONTROL];
                                                switch (current_action) {
                                                        case ENN_ACTION_NOTHING:
                                                        {
                                                                if (global_state.is_key_down[GLFW_KEY_SPACE]) break;

                                                                if (global_circuit.hovered_pin != global_circuit.external_pins.end) {
                                                                        circuit_selection_clear();
                                                                        vector_clear(input_wire.anchors);
                                                                        input_wire.from = global_circuit.external_pins.end;
                                                                        input_wire.to = global_circuit.external_pins.end;

                                                                        input_wire.from = global_circuit.hovered_pin;
                                                                        input_wire.color = circuit_get_pin_color(global_circuit.hovered_pin);
                                                                        f32vec2 pin_anchor = circuit_external_pin_center(global_circuit.hovered_pin);
                                                                        vector_push_back(input_wire.anchors, pin_anchor);
                                                                        current_action = ENN_ACTION_WIRING;
                                                                        event -> handled = true;
                                                                } else {
                                                                        CircuitElement elem;
                                                                        if (circuit_find_selectable_at_pos(map, &elem)) {
                                                                                if (!circuit_is_element_selected(elem)) {
                                                                                        if (!additive_selection) circuit_selection_clear();
                                                                                        circuit_selection_add_element(elem);
                                                                                        circuit_selection_add_connected_wires();
                                                                                }
                                                                                circuit_selection_move_begin(map);
                                                                                current_action = ENN_ACTION_MOVING;
                                                                                event -> handled = true;
                                                                        } else {
                                                                                if (!additive_selection) circuit_selection_clear();
                                                                                circuit_selection_pane_start(map);
                                                                                current_action = ENN_ACTION_SELECTING;
                                                                                event -> handled = true;
                                                                        }
                                                                }

                                                                break;
                                                        }
                                                        case ENN_ACTION_WIRING:
                                                        {
                                                                if (global_circuit.hovered_pin != global_circuit.external_pins.end) {
                                                                        f32vec2 pin_anchor = circuit_external_pin_center(global_circuit.hovered_pin);
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
                                                                        map = circuit_magnetize_line(input_wire.anchors.data[input_wire.anchors.end - 1], map, ENN_MAGNETIZATION_THRESHOLD);
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
                                                if (circuit_toggle_input_indicator_at_pos(map))
                                                        event -> handled = true;
                                                break;
                                        }
                                }
                        } else if (data -> button == GLFW_MOUSE_BUTTON_LEFT && data -> action == GLFW_RELEASE) {
                                switch (global_state.game_state) {
                                        case ENN_EDIT_MODE:
                                        {
                                                if (current_action == ENN_ACTION_SELECTING) {
                                                        circuit_selection_pane_extend(map);
                                                        circuit_selection_add_intersections(circuit_rect_from_points(selection_pane.start, selection_pane.end));
                                                        current_action = ENN_ACTION_NOTHING;
                                                        event -> handled = true;
                                                } else if (current_action == ENN_ACTION_MOVING) {
                                                        if (selection_pane.has_collision)
                                                                circuit_selection_move_revert();
                                                        else
                                                                circuit_selection_move_end();
                                                        current_action = ENN_ACTION_NOTHING;
                                                        event -> handled = true;
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
