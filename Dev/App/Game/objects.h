#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "layer.h"

#define CIRCUIT_PIN_WIDTH                               2
#define CIRCUIT_PIN_HEIGHT                              3
#define CIRCUIT_PIN_COLOR                               0x202020FF
#define CIRCUIT_PIN_HOVER_COLOR                         0xFFFFFFFF

#define CIRCUIT_WIRE_WIDTH                              0.75

#define CIRCUIT_INDICATOR_BODY_WIDTH                    10
#define CIRCUIT_INDICATOR_BODY_HEIGHT                   10
#define CIRCUIT_INDICATOR_CONNECTOR_WIDTH               4
#define CIRCUIT_INDICATOR_CONNECTOR_HEIGHT              1.25
#define CIRCUIT_INDICATOR_CONNECTOR_COLOR               CIRCUIT_PIN_COLOR
#define CIRCUIT_INDICATOR_HARD_BORDER_PADDING           0.75
#define CIRCUIT_INDICATOR_SOFT_BORDER_PADDING           0.75
#define CIRCUIT_INDICATOR_HARD_BORDER_COLOR             CIRCUIT_PIN_COLOR
#define CIRCUIT_INDICATOR_OVERLAY_PADDING               2
#define CIRCUIT_INDICATOR_HITBOX_WIDTH                  (CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_PIN_WIDTH)
#define CIRCUIT_INDICATOR_HITBOX_HEIGHT                 (CIRCUIT_INDICATOR_BODY_HEIGHT)

#define CIRCUIT_COLOR_RED_DARK                          0x801f1bFF
#define CIRCUIT_COLOR_ORANGE_DARK                       0x9d5511FF
#define CIRCUIT_COLOR_YELLOW_DARK                       0x86631eFF
#define CIRCUIT_COLOR_GREEN_DARK                        0x626219FF
#define CIRCUIT_COLOR_BLUE_DARK                         0x325759FF
#define CIRCUIT_COLOR_PURPLE_DARK                       0x714358FF

#define CIRCUIT_COLOR_RED_DARK_DARK                     0x571d1aFF
#define CIRCUIT_COLOR_ORANGE_DARK_DARK                  0x693d15FF
#define CIRCUIT_COLOR_YELLOW_DARK_DARK                  0x5b461cFF
#define CIRCUIT_COLOR_GREEN_DARK_DARK                   0x454519FF
#define CIRCUIT_COLOR_BLUE_DARK_DARK                    0x283f40FF
#define CIRCUIT_COLOR_PURPLE_DARK_DARK                  0x4e323fFF

#define CIRCUIT_COLOR_RED_LIGHT                         0xcc241dFF
#define CIRCUIT_COLOR_ORANGE_LIGHT                      0xfe8109FF
#define CIRCUIT_COLOR_YELLOW_LIGHT                      0xd79921FF
#define CIRCUIT_COLOR_GREEN_LIGHT                       0x98971aFF
#define CIRCUIT_COLOR_BLUE_LIGHT                        0x458588FF
#define CIRCUIT_COLOR_PURPLE_LIGHT                      0xb16286FF

#define CIRCUIT_COLOR_RED_LIGHT_DARK                    0xcc241dFF
#define CIRCUIT_COLOR_ORANGE_LIGHT_DARK                 0xfe8109FF
#define CIRCUIT_COLOR_YELLOW_LIGHT_DARK                 0xd79921FF
#define CIRCUIT_COLOR_GREEN_LIGHT_DARK                  0x98971aFF
#define CIRCUIT_COLOR_BLUE_LIGHT_DARK                   0x458588FF
#define CIRCUIT_COLOR_PURPLE_LIGHT_DARK                 0xb16286FF

#define CIRCUIT_CHIP_BORDER_PADDING                     1
#define CIRCUIT_CHIP_NAME_PADDING                       2.5
#define CIRCUIT_CHIP_NAME_TEXT_HEIGHT                   4
#define CIRCUIT_CHIP_NAME_TEXT_WIDTH                    4
#define CIRCUIT_CHIP_NAME_TEXT_COLOR                    0xFFFFFFFF
#define CIRCUIT_CHIP_PIN_PADDING                        3
#define CIRCUIT_CHIP_MAX_NAME_LEN                       128
#define CIRCUIT_CHIP_OVERLAY_PADDING                    2

#define CIRCUIT_SELECTION_BOX_COLOR                     0xFFFFFF50

#define CIRCUIT_CHIP_DATA_DIRECTORY                     ENN_APP_DIRECTORY ENN_DATA_PATH "Chips"
#define CIRCUIT_SERIAL_KEY_MAX                          256
#define CIRCUIT_SERIAL_PATH_MAX                         512

#define CIRCUIT_ELEMENT_OVERLAY_COLOR                   0xFFFFFF80
#define CIRCUIT_ELEMENT_OVERLAY_COLLISION_COLOR         0xcc241d80

#define CIRCUIT_BLUEPRINT_PARENT_INPUT                  -1
#define CIRCUIT_BLUEPRINT_PARENT_OUTPUT                 -2

typedef enum {
        ENN_ACTION_NOTHING,
        ENN_ACTION_PANNING,
        ENN_ACTION_SELECTING,
        ENN_ACTION_MOVING,
        ENN_ACTION_WIRING
} ENN_GAME_ACTION;

extern ENN_GAME_ACTION current_action;

typedef enum ENN_CIRCUIT_ELEMENT_COLORS {
        ENN_INTERNAL_COLOR_RED,
        ENN_INTERNAL_COLOR_ORANGE,
        ENN_INTERNAL_COLOR_YELLOW,
        ENN_INTERNAL_COLOR_GREEN,
        ENN_INTERNAL_COLOR_BLUE,
        ENN_INTERNAL_COLOR_PURPLE,
        ENN_INTERNAL_COLOR_LAST,
} ENN_CIRCUIT_ELEMENT_COLORS;

ENNDEF_PUBLIC u32 color_dark_get_by_circuit_color(ENN_CIRCUIT_ELEMENT_COLORS internal_color) {
        switch (internal_color) {
                case ENN_INTERNAL_COLOR_RED: return CIRCUIT_COLOR_RED_DARK;
                case ENN_INTERNAL_COLOR_ORANGE: return CIRCUIT_COLOR_ORANGE_DARK;
                case ENN_INTERNAL_COLOR_YELLOW: return CIRCUIT_COLOR_YELLOW_DARK;
                case ENN_INTERNAL_COLOR_GREEN: return CIRCUIT_COLOR_GREEN_DARK;
                case ENN_INTERNAL_COLOR_BLUE: return CIRCUIT_COLOR_BLUE_DARK;
                case ENN_INTERNAL_COLOR_PURPLE: return CIRCUIT_COLOR_PURPLE_DARK;
                default: return 0xFFFFFFFF;
        }
}

ENNDEF_PUBLIC u32 color_light_get_by_circuit_color(ENN_CIRCUIT_ELEMENT_COLORS internal_color) {
        switch (internal_color) {
                case ENN_INTERNAL_COLOR_RED: return CIRCUIT_COLOR_RED_LIGHT;
                case ENN_INTERNAL_COLOR_ORANGE: return CIRCUIT_COLOR_ORANGE_LIGHT;
                case ENN_INTERNAL_COLOR_YELLOW: return CIRCUIT_COLOR_YELLOW_LIGHT;
                case ENN_INTERNAL_COLOR_GREEN: return CIRCUIT_COLOR_GREEN_LIGHT;
                case ENN_INTERNAL_COLOR_BLUE: return CIRCUIT_COLOR_BLUE_LIGHT;
                case ENN_INTERNAL_COLOR_PURPLE: return CIRCUIT_COLOR_PURPLE_LIGHT;
                default: return 0xFFFFFFFF;
        }
}

ENNDEF_PUBLIC u32 color_dark_dark_get_by_circuit_color(ENN_CIRCUIT_ELEMENT_COLORS internal_color) {
        switch (internal_color) {
                case ENN_INTERNAL_COLOR_RED: return CIRCUIT_COLOR_RED_DARK_DARK;
                case ENN_INTERNAL_COLOR_ORANGE: return CIRCUIT_COLOR_ORANGE_DARK_DARK;
                case ENN_INTERNAL_COLOR_YELLOW: return CIRCUIT_COLOR_YELLOW_DARK_DARK;
                case ENN_INTERNAL_COLOR_GREEN: return CIRCUIT_COLOR_GREEN_DARK_DARK;
                case ENN_INTERNAL_COLOR_BLUE: return CIRCUIT_COLOR_BLUE_DARK_DARK;
                case ENN_INTERNAL_COLOR_PURPLE: return CIRCUIT_COLOR_PURPLE_DARK_DARK;
                default: return 0xFFFFFFFF;
        }
}

ENNDEF_PUBLIC u32 color_light_dark_get_by_circuit_color(ENN_CIRCUIT_ELEMENT_COLORS internal_color) {
        switch (internal_color) {
                case ENN_INTERNAL_COLOR_RED: return CIRCUIT_COLOR_RED_LIGHT_DARK;
                case ENN_INTERNAL_COLOR_ORANGE: return CIRCUIT_COLOR_ORANGE_LIGHT_DARK;
                case ENN_INTERNAL_COLOR_YELLOW: return CIRCUIT_COLOR_YELLOW_LIGHT_DARK;
                case ENN_INTERNAL_COLOR_GREEN: return CIRCUIT_COLOR_GREEN_LIGHT_DARK;
                case ENN_INTERNAL_COLOR_BLUE: return CIRCUIT_COLOR_BLUE_LIGHT_DARK;
                case ENN_INTERNAL_COLOR_PURPLE: return CIRCUIT_COLOR_PURPLE_LIGHT_DARK;
                default: return 0xFFFFFFFF;
        }
}

typedef i32 GenericIndex;
typedef i32 InternalPinIndex;
typedef i32 InternalWireIndex;
typedef i32 InternalNANDGateIndex;
typedef i32 ExternalPinIndex;
typedef i32 ExternalWireIndex;
typedef i32 ExternalChipIndex;
typedef i32 BlueprintChipIndex;
typedef i32 InputIndicatorIndex;
typedef i32 OutputIndicatorIndex;

typedef enum ENN_CIRCUIT_ELEMENT_TYPE {
        ENN_INTERNAL_PIN,
        ENN_EXTERNAL_PIN,

        ENN_INPUT_INDICATOR,
        ENN_OUTPUT_INDICATOR,

        ENN_INTERNAL_WIRE,
        ENN_EXTERNAL_WIRE,
        
        ENN_INTERNAL_GATE,
        ENN_CHIP
} ENN_CIRCUIT_ELEMENT_TYPE;

typedef struct CircuitElement {
        GenericIndex                    index;
        ENN_CIRCUIT_ELEMENT_TYPE        type;
} CircuitElement;

typedef struct CircuitSelectionMoveState {
        CircuitElement elem;
        f32vec2 pos;
        i32 anchor_start;
        i32 anchor_count;
        bool colliding : 1;
} CircuitSelectionMoveState;

typedef struct CircuitSelectionPane {
        f32vec2 start;
        f32vec2 end;
        f32vec2 last_move;
        vector(CircuitSelectionMoveState) move_states;
        vector(f32vec2) original_anchors;
        bool has_collision : 1;
} CircuitSelectionPane;

extern CircuitSelectionPane selection_pane;

typedef struct InternalPin {
        InternalPinIndex id;
        bool    curr_state : 1;
        bool    next_state : 1;
        CircuitElement                  parent;
        vector(InternalWireIndex)       connections;
} InternalPin;

typedef struct InternalNANDGate {
        InternalNANDGateIndex id;
        InternalPinIndex input_a;
        InternalPinIndex input_b;
        InternalPinIndex output;
} InternalNANDGate;

typedef enum ExternalPinType {
        ENN_INPUT_PIN,
        ENN_OUTPUT_PIN
} ExternalPinType;

typedef struct ExternalPin {
        ExternalPinIndex                id;
        InternalPinIndex                internal;
        f32vec2                         pos;
        ExternalPinType                 type;
        CircuitElement                  parent;
        vector(ExternalWireIndex)       connections;
} ExternalPin;

typedef struct InternalWire {
        InternalWireIndex       id;
        InternalPinIndex        from;
        InternalPinIndex        to;
} InternalWire;

typedef struct ExternalWire {
        ExternalWireIndex               id;
        InternalWireIndex               internal;
        ExternalPinIndex                from;
        ExternalPinIndex                to;
        ENN_CIRCUIT_ELEMENT_COLORS      color;
        vector(f32vec2)                 anchors;
} ExternalWire;

typedef struct BlueprintWire {
        BlueprintChipIndex      from_sub_chip;
        InternalPinIndex        from_pin;

        BlueprintChipIndex      to_sub_chip;
        InternalPinIndex        to_pin;
} BlueprintWire;

typedef struct BlueprintChip {
        BlueprintChipIndex              id;
        char                            name[CIRCUIT_CHIP_MAX_NAME_LEN];
        ENN_CIRCUIT_ELEMENT_COLORS      color;
        i32                             num_inputs;
        i32                             num_outputs; 
        bool                            is_primitive_nand : 1;

        vector(BlueprintChipIndex)      sub_chips;
        vector(BlueprintWire)           wires;
} BlueprintChip;

typedef struct ExternalChip {
        ExternalChipIndex               id;
        BlueprintChipIndex              blueprint;
        f32vec2                         pos;
        f32vec2                         dim;
        vector(ExternalPinIndex)        input_pins;
        vector(ExternalPinIndex)        output_pins;
} ExternalChip;

typedef struct InputIndicator {
        InputIndicatorIndex             id;
        f32vec2                         pos;
        ExternalPinIndex                output_pin;
        ENN_CIRCUIT_ELEMENT_COLORS      color;
        bool                            state : 1;
} InputIndicator;

typedef struct OutputIndicator {
        OutputIndicatorIndex            id;
        f32vec2                         pos;
        ExternalPinIndex                input_pin;
        ENN_CIRCUIT_ELEMENT_COLORS      color;
} OutputIndicator;

typedef struct Circuit {
        vector(InternalPin)             internal_pins;
        vector(InternalWire)            internal_wires;
        vector(InternalNANDGate)        internal_gates;

        vector(BlueprintChip)           blueprints;

        vector(ExternalPin)             external_pins;
        ExternalPinIndex                hovered_pin;

        vector(ExternalWire)            external_wires;
        vector(ExternalChip)            external_chips;
        vector(InputIndicator)          input_indicators;
        vector(OutputIndicator)         output_indicators;

        vector(CircuitElement)          selected_elements;
        bool                            defer_internal_rebuild : 1;
} Circuit;

extern Circuit global_circuit;

ENNDEF_PRIVATE void game_ui_register_chip_blueprint(BlueprintChipIndex blueprint);

ENNDEF_PUBLIC bool circuit_cstring_has_suffix(const char* str, const char* suffix) {
        DEBUG_TRACE();
        if (str == NULL || suffix == NULL) {
                DEBUG_UNTRACE();
                return false;
        }

        i32 str_len = strlen(str);
        i32 suffix_len = strlen(suffix);
        bool result = str_len >= suffix_len && strcmp(str + str_len - suffix_len, suffix) == 0;
        DEBUG_UNTRACE();
        return result;
}

ENNDEF_PUBLIC char* circuit_filename_from_name(const char* name) {
        DEBUG_TRACE();
        if (name == NULL || name[0] == 0) name = "Chip";

        i32 len = strlen(name);
        char* filename = calloc(len + 1, (sizeof (char)));
        DEBUG_ASSERT(filename != NULL);

        for (i32 i = 0; i < len; ++i) {
                char c = name[i];
                bool valid = (c >= 'a' && c <= 'z') ||
                             (c >= 'A' && c <= 'Z') ||
                             (c >= '0' && c <= '9') ||
                             c == ' ' || c == '_' || c == '-';
                filename[i] = valid ? c : '_';
        }

        if (filename[0] == 0) strcpy(filename, "Chip");
        DEBUG_UNTRACE();
        return filename;
}

ENNDEF_PUBLIC char* circuit_chip_blueprint_filepath(BlueprintChip* blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != NULL);

        char* filename = circuit_filename_from_name(blueprint -> name);
        i32 path_len = snprintf(NULL, 0, "%s/%s%s", CIRCUIT_CHIP_DATA_DIRECTORY, filename, ENN_DATAFILE_FILE_EXTENSION) + 1;
        char* filepath = calloc(path_len, (sizeof (char)));
        DEBUG_ASSERT(filepath != NULL);
        snprintf(filepath, path_len, "%s/%s%s", CIRCUIT_CHIP_DATA_DIRECTORY, filename, ENN_DATAFILE_FILE_EXTENSION);
        free(filename);

        DEBUG_UNTRACE();
        return filepath;
}

ENNDEF_PUBLIC f32vec2 circuit_blueprint_chip_dim(BlueprintChipIndex blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        i32 name_len = max((i32)strlen(bp -> name), 1);
        i32 max_pin_count = max(bp -> num_inputs, bp -> num_outputs);

        f32 width = name_len * CIRCUIT_CHIP_NAME_TEXT_WIDTH + CIRCUIT_CHIP_NAME_PADDING * 2.0;
        f32 height = CIRCUIT_CHIP_NAME_TEXT_HEIGHT + CIRCUIT_CHIP_NAME_PADDING * 2.0;
        if (max_pin_count > 0)
                height = max_pin_count * CIRCUIT_PIN_HEIGHT + (max_pin_count + 1) * CIRCUIT_CHIP_PIN_PADDING;

        DEBUG_UNTRACE();
        return (f32vec2) { width, height };
}

ENNDEF_PUBLIC f32 circuit_chip_pin_offset_y(f32 chip_height, i32 pin_count, i32 slot) {
        if (pin_count <= 0) return (chip_height - CIRCUIT_PIN_HEIGHT) * 0.5;

        f32 pin_group_height = pin_count * CIRCUIT_PIN_HEIGHT + (pin_count + 1) * CIRCUIT_CHIP_PIN_PADDING;
        f32 top_padding = (chip_height - pin_group_height) * 0.5 + CIRCUIT_CHIP_PIN_PADDING;
        return top_padding + slot * (CIRCUIT_PIN_HEIGHT + CIRCUIT_CHIP_PIN_PADDING);
}

ENNDEF_PUBLIC f32vec4 circuit_rect_from_points(f32vec2 p1, f32vec2 p2) {
        f32 x1 = min(p1.x, p2.x);
        f32 y1 = min(p1.y, p2.y);
        f32 x2 = max(p1.x, p2.x);
        f32 y2 = max(p1.y, p2.y);

        return (f32vec4) {
                .x = x1,
                .y = y1,
                .z = x2 - x1,
                .w = y2 - y1
        };
}

ENNDEF_PUBLIC f32vec2 circuit_external_pin_center(ExternalPinIndex pin) {
        DEBUG_TRACE();
        DEBUG_ASSERT(pin != global_circuit.external_pins.end);
        f32vec2 center = (f32vec2) {
                .x = global_circuit.external_pins.data[pin].pos.x + CIRCUIT_PIN_WIDTH * 0.5,
                .y = global_circuit.external_pins.data[pin].pos.y + CIRCUIT_PIN_HEIGHT * 0.5
        };
        DEBUG_UNTRACE();
        return center;
}

ENNDEF_PUBLIC f32vec4 circuit_input_indicator_hitbox(InputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);
        f32vec4 hitbox = (f32vec4) {
                .x = global_circuit.input_indicators.data[indicator].pos.x - CIRCUIT_INDICATOR_OVERLAY_PADDING,
                .y = global_circuit.input_indicators.data[indicator].pos.y - CIRCUIT_INDICATOR_OVERLAY_PADDING,
                .z = CIRCUIT_INDICATOR_HITBOX_WIDTH + CIRCUIT_INDICATOR_OVERLAY_PADDING * 2,
                .w = CIRCUIT_INDICATOR_HITBOX_HEIGHT + CIRCUIT_INDICATOR_OVERLAY_PADDING * 2
        };
        DEBUG_UNTRACE();
        return hitbox;
}

ENNDEF_PUBLIC f32vec4 circuit_output_indicator_hitbox(OutputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.output_indicators.end);
        f32vec4 hitbox = (f32vec4) {
                .x = global_circuit.output_indicators.data[indicator].pos.x - CIRCUIT_PIN_WIDTH - CIRCUIT_INDICATOR_OVERLAY_PADDING,
                .y = global_circuit.output_indicators.data[indicator].pos.y - CIRCUIT_INDICATOR_OVERLAY_PADDING,
                .z = CIRCUIT_INDICATOR_HITBOX_WIDTH + CIRCUIT_INDICATOR_OVERLAY_PADDING * 2,
                .w = CIRCUIT_INDICATOR_HITBOX_HEIGHT + CIRCUIT_INDICATOR_OVERLAY_PADDING * 2
        };
        DEBUG_UNTRACE();
        return hitbox;
}

ENNDEF_PUBLIC f32vec4 circuit_chip_hitbox(ExternalChipIndex chip) {
        DEBUG_TRACE();
        DEBUG_ASSERT(chip != global_circuit.external_chips.end);
        f32vec4 hitbox = (f32vec4) {
                .x = global_circuit.external_chips.data[chip].pos.x - CIRCUIT_PIN_WIDTH - CIRCUIT_CHIP_OVERLAY_PADDING,
                .y = global_circuit.external_chips.data[chip].pos.y - CIRCUIT_CHIP_OVERLAY_PADDING,
                .z = global_circuit.external_chips.data[chip].dim.x + CIRCUIT_PIN_WIDTH * 2 + CIRCUIT_CHIP_OVERLAY_PADDING * 2,
                .w = global_circuit.external_chips.data[chip].dim.y + CIRCUIT_CHIP_OVERLAY_PADDING * 2
        };
        DEBUG_UNTRACE();
        return hitbox;
}

ENNDEF_PUBLIC f32 circuit_cross(f32vec2 a, f32vec2 b, f32vec2 c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

ENNDEF_PUBLIC bool circuit_point_in_convex_quad(f32vec2 point, f32vec2 quad[4]) {
        bool has_negative = false;
        bool has_positive = false;

        for (i32 i = 0; i < 4; ++i) {
                f32 cross = circuit_cross(quad[i], quad[(i + 1) % 4], point);
                if (cross < -0.0001) has_negative = true;
                if (cross >  0.0001) has_positive = true;
        }

        return !(has_negative && has_positive);
}

ENNDEF_PUBLIC bool circuit_point_on_segment(f32vec2 a, f32vec2 b, f32vec2 point) {
        return point.x >= min(a.x, b.x) - 0.0001 &&
               point.x <= max(a.x, b.x) + 0.0001 &&
               point.y >= min(a.y, b.y) - 0.0001 &&
               point.y <= max(a.y, b.y) + 0.0001 &&
               fabsf(circuit_cross(a, b, point)) <= 0.0001;
}

ENNDEF_PUBLIC bool circuit_segments_intersect(f32vec2 a, f32vec2 b, f32vec2 c, f32vec2 d) {
        if (max(a.x, b.x) < min(c.x, d.x) - 0.0001 ||
            max(c.x, d.x) < min(a.x, b.x) - 0.0001 ||
            max(a.y, b.y) < min(c.y, d.y) - 0.0001 ||
            max(c.y, d.y) < min(a.y, b.y) - 0.0001)
                return false;

        f32 d1 = circuit_cross(a, b, c);
        f32 d2 = circuit_cross(a, b, d);
        f32 d3 = circuit_cross(c, d, a);
        f32 d4 = circuit_cross(c, d, b);

        if (((d1 > 0.0001 && d2 < -0.0001) || (d1 < -0.0001 && d2 > 0.0001)) &&
            ((d3 > 0.0001 && d4 < -0.0001) || (d3 < -0.0001 && d4 > 0.0001)))
                return true;

        return circuit_point_on_segment(a, b, c) ||
               circuit_point_on_segment(a, b, d) ||
               circuit_point_on_segment(c, d, a) ||
               circuit_point_on_segment(c, d, b);
}

ENNDEF_PUBLIC bool circuit_quad_intersects_rect(f32vec2 quad[4], f32vec4 rect) {
        f32vec2 rect_points[4] = {
                { rect.x,          rect.y          },
                { rect.x + rect.z, rect.y          },
                { rect.x + rect.z, rect.y + rect.w },
                { rect.x,          rect.y + rect.w }
        };

        for (i32 i = 0; i < 4; ++i)
                if (is_inside_rectangle(quad[i], rect)) return true;

        for (i32 i = 0; i < 4; ++i)
                if (circuit_point_in_convex_quad(rect_points[i], quad)) return true;

        for (i32 i = 0; i < 4; ++i)
                for (i32 j = 0; j < 4; ++j)
                        if (circuit_segments_intersect(quad[i], quad[(i + 1) % 4], rect_points[j], rect_points[(j + 1) % 4]))
                                return true;

        return false;
}

ENNDEF_PUBLIC bool circuit_wire_segment_intersects_rect(f32vec2 p1, f32vec2 p2, f32 width, f32vec4 rect) {
        f32 dx = p2.x - p1.x;
        f32 dy = p2.y - p1.y;
        f32 len = dx * dx + dy * dy;
        if (len == 0.0) return false;

        f32 half = (width * 0.5) / sqrtf(len);
        f32vec2 normal = {
                .x = -dy * half,
                .y =  dx * half
        };

        f32vec2 quad[4] = {
                { p1.x + normal.x, p1.y + normal.y },
                { p2.x + normal.x, p2.y + normal.y },
                { p2.x - normal.x, p2.y - normal.y },
                { p1.x - normal.x, p1.y - normal.y }
        };

        return circuit_quad_intersects_rect(quad, rect);
}

ENNDEF_PUBLIC bool circuit_wire_intersects_rect(ExternalWireIndex wire, f32vec4 rect) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.external_wires.end);
        ExternalWire* external_wire = &global_circuit.external_wires.data[wire];
        if (vector_size(external_wire -> anchors) < 2) {
                DEBUG_UNTRACE();
                return false;
        }

        for (i32 i = external_wire -> anchors.start; i < external_wire -> anchors.end - 1; ++i) {
                if (circuit_wire_segment_intersects_rect(external_wire -> anchors.data[i], external_wire -> anchors.data[i + 1], CIRCUIT_WIRE_WIDTH, rect)) {
                        DEBUG_UNTRACE();
                        return true;
                }
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC bool circuit_wire_segment_quad(f32vec2 p1, f32vec2 p2, f32 width, f32vec2 quad[4]) {
        f32 dx = p2.x - p1.x;
        f32 dy = p2.y - p1.y;
        f32 len = dx * dx + dy * dy;
        if (len == 0.0) return false;

        f32 half = (width * 0.5) / sqrtf(len);
        f32vec2 normal = {
                .x = -dy * half,
                .y =  dx * half
        };

        quad[0] = (f32vec2) { p1.x + normal.x, p1.y + normal.y };
        quad[1] = (f32vec2) { p2.x + normal.x, p2.y + normal.y };
        quad[2] = (f32vec2) { p2.x - normal.x, p2.y - normal.y };
        quad[3] = (f32vec2) { p1.x - normal.x, p1.y - normal.y };

        return true;
}

ENNDEF_PUBLIC bool circuit_quads_intersect(f32vec2 a[4], f32vec2 b[4]) {
        for (i32 i = 0; i < 4; ++i)
                if (circuit_point_in_convex_quad(a[i], b)) return true;

        for (i32 i = 0; i < 4; ++i)
                if (circuit_point_in_convex_quad(b[i], a)) return true;

        for (i32 i = 0; i < 4; ++i)
                for (i32 j = 0; j < 4; ++j)
                        if (circuit_segments_intersect(a[i], a[(i + 1) % 4], b[j], b[(j + 1) % 4]))
                                return true;

        return false;
}

ENNDEF_PUBLIC bool circuit_wire_segments_intersect(f32vec2 a1, f32vec2 a2, f32vec2 b1, f32vec2 b2, f32 width) {
        f32vec2 a[4];
        f32vec2 b[4];
        if (!circuit_wire_segment_quad(a1, a2, width, a)) return false;
        if (!circuit_wire_segment_quad(b1, b2, width, b)) return false;

        return circuit_quads_intersect(a, b);
}

ENNDEF_PUBLIC bool circuit_wires_intersect(ExternalWireIndex a, ExternalWireIndex b) {
        DEBUG_TRACE();
        DEBUG_ASSERT(a != global_circuit.external_wires.end);
        DEBUG_ASSERT(b != global_circuit.external_wires.end);
        ExternalWire* wire_a = &global_circuit.external_wires.data[a];
        ExternalWire* wire_b = &global_circuit.external_wires.data[b];

        if (vector_size(wire_a -> anchors) < 2 || vector_size(wire_b -> anchors) < 2) {
                DEBUG_UNTRACE();
                return false;
        }

        for (i32 i = wire_a -> anchors.start; i < wire_a -> anchors.end - 1; ++i)
                for (i32 j = wire_b -> anchors.start; j < wire_b -> anchors.end - 1; ++j)
                        if (circuit_wire_segments_intersect(
                                wire_a -> anchors.data[i],
                                wire_a -> anchors.data[i + 1],
                                wire_b -> anchors.data[j],
                                wire_b -> anchors.data[j + 1],
                                CIRCUIT_WIRE_WIDTH
                        )) {
                                DEBUG_UNTRACE();
                                return true;
                        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC bool circuit_find_selectable_at_pos(f32vec2 pos, CircuitElement* elem) {
        DEBUG_TRACE();
        DEBUG_ASSERT(elem != NULL);

        for (i32 i = global_circuit.output_indicators.end - 1; i >= global_circuit.output_indicators.start; --i) {
                if (is_inside_rectangle(pos, circuit_output_indicator_hitbox(i))) {
                        *elem = (CircuitElement) { .index = i, .type = ENN_OUTPUT_INDICATOR };
                        DEBUG_UNTRACE();
                        return true;
                }
        }

        for (i32 i = global_circuit.input_indicators.end - 1; i >= global_circuit.input_indicators.start; --i) {
                if (is_inside_rectangle(pos, circuit_input_indicator_hitbox(i))) {
                        *elem = (CircuitElement) { .index = i, .type = ENN_INPUT_INDICATOR };
                        DEBUG_UNTRACE();
                        return true;
                }
        }

        for (i32 i = global_circuit.external_chips.end - 1; i >= global_circuit.external_chips.start; --i) {
                if (is_inside_rectangle(pos, circuit_chip_hitbox(i))) {
                        *elem = (CircuitElement) { .index = i, .type = ENN_CHIP };
                        DEBUG_UNTRACE();
                        return true;
                }
        }

        f32vec4 pick_rect = (f32vec4) {
                .x = pos.x - CIRCUIT_WIRE_WIDTH,
                .y = pos.y - CIRCUIT_WIRE_WIDTH,
                .z = CIRCUIT_WIRE_WIDTH * 2,
                .w = CIRCUIT_WIRE_WIDTH * 2
        };

        for (i32 i = global_circuit.external_wires.end - 1; i >= global_circuit.external_wires.start; --i) {
                if (circuit_wire_intersects_rect(i, pick_rect)) {
                        *elem = (CircuitElement) { .index = i, .type = ENN_EXTERNAL_WIRE };
                        DEBUG_UNTRACE();
                        return true;
                }
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC ENN_CIRCUIT_ELEMENT_COLORS circuit_get_pin_color(ExternalPinIndex pin) {
        DEBUG_TRACE();
        DEBUG_ASSERT(pin != global_circuit.external_pins.end);
        ENN_CIRCUIT_ELEMENT_COLORS color = ENN_INTERNAL_COLOR_LAST;
        switch (global_circuit.external_pins.data[pin].parent.type) {
                case ENN_INPUT_INDICATOR:
                {
                        color = global_circuit.input_indicators.data[global_circuit.external_pins.data[pin].parent.index].color;
                        break;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        color = global_circuit.output_indicators.data[global_circuit.external_pins.data[pin].parent.index].color;
                        break;
                }
                case ENN_CHIP:
                {
                        color = global_circuit.blueprints.data[global_circuit.external_chips.data[global_circuit.external_pins.data[pin].parent.index].blueprint].color;
                        break;
                }
                default: break;

        }
        DEBUG_UNTRACE();
        return color;
}

ENNDEF_PUBLIC InternalPinIndex circuit_summon_internal_pin(CircuitElement parent) {
        DEBUG_TRACE();
        InternalPin new_pin; memset(&new_pin, 0x0, (sizeof (InternalPin)));
        new_pin.id = global_circuit.internal_pins.end;
        new_pin.parent = parent;
        vector_push_back(global_circuit.internal_pins, new_pin);
        DEBUG_UNTRACE();
        return new_pin.id;
}

ENNDEF_PUBLIC InternalWireIndex circuit_summon_internal_wire(InternalPinIndex from, InternalPinIndex to) {
        DEBUG_TRACE();
        DEBUG_ASSERT(from != global_circuit.internal_pins.end);
        DEBUG_ASSERT(to != global_circuit.internal_pins.end);
        InternalWire new_wire; memset(&new_wire, 0x0, (sizeof (InternalWire)));
        new_wire.id = global_circuit.internal_wires.end;
        new_wire.from = from;
        new_wire.to = to;
        vector_push_back(global_circuit.internal_wires, new_wire);
        vector_push_back(global_circuit.internal_pins.data[from].connections, new_wire.id);
        vector_push_back(global_circuit.internal_pins.data[to].connections, new_wire.id);
        DEBUG_UNTRACE();
        return new_wire.id;
}

ENNDEF_PUBLIC InternalNANDGateIndex circuit_summon_internal_nand_gate(InternalPinIndex input_a, InternalPinIndex input_b, InternalPinIndex output) {
        DEBUG_TRACE();
        DEBUG_ASSERT(input_a != global_circuit.internal_pins.end);
        DEBUG_ASSERT(input_b != global_circuit.internal_pins.end);
        DEBUG_ASSERT(output != global_circuit.internal_pins.end);
        InternalNANDGate new_gate; memset(&new_gate, 0x0, (sizeof (InternalNANDGate)));
        new_gate.id = global_circuit.internal_gates.end;
        new_gate.input_a = input_a;
        new_gate.input_b = input_b;
        new_gate.output = output;
        vector_push_back(global_circuit.internal_gates, new_gate);
        DEBUG_UNTRACE();
        return new_gate.id;
}

ENNDEF_PUBLIC BlueprintChipIndex circuit_summon_blueprint(const char* name, ENN_CIRCUIT_ELEMENT_COLORS color, i32 num_inputs, i32 num_outputs, bool is_primitive_nand) {
        DEBUG_TRACE();
        BlueprintChip new_blueprint; memset(&new_blueprint, 0x0, (sizeof (BlueprintChip)));
        new_blueprint.id = global_circuit.blueprints.end;
        new_blueprint.color = color;
        new_blueprint.num_inputs = num_inputs;
        new_blueprint.num_outputs = num_outputs;
        new_blueprint.is_primitive_nand = is_primitive_nand;
        strncpy(new_blueprint.name, name, CIRCUIT_CHIP_MAX_NAME_LEN - 1);
        vector_push_back(global_circuit.blueprints, new_blueprint);
        DEBUG_UNTRACE();
        return new_blueprint.id;
}

ENNDEF_PUBLIC BlueprintChipIndex circuit_get_nand_blueprint(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.blueprints.start; i < global_circuit.blueprints.end; ++i)
                if (global_circuit.blueprints.data[i].is_primitive_nand) {
                        DEBUG_UNTRACE();
                        return i;
                }

        BlueprintChipIndex blueprint = circuit_summon_blueprint("NAND", ENN_INTERNAL_COLOR_RED, 2, 1, true);
        DEBUG_UNTRACE();
        return blueprint;
}

ENNDEF_PUBLIC BlueprintChipIndex circuit_find_blueprint_by_name(const char* name) {
        DEBUG_TRACE();
        if (name == NULL) {
                DEBUG_UNTRACE();
                return global_circuit.blueprints.end;
        }

        for (i32 i = global_circuit.blueprints.start; i < global_circuit.blueprints.end; ++i)
                if (strcmp(global_circuit.blueprints.data[i].name, name) == 0) {
                        DEBUG_UNTRACE();
                        return i;
                }

        DEBUG_UNTRACE();
        return global_circuit.blueprints.end;
}

ENNDEF_PUBLIC bool circuit_blueprint_endpoint_valid(BlueprintChip* bp, i32 parent, i32 pin, bool is_source) {
        DEBUG_TRACE();
        DEBUG_ASSERT(bp != NULL);

        if (parent == CIRCUIT_BLUEPRINT_PARENT_INPUT) {
                bool result = is_source && pin >= 0 && pin < bp -> num_inputs;
                DEBUG_UNTRACE();
                return result;
        }

        if (parent == CIRCUIT_BLUEPRINT_PARENT_OUTPUT) {
                bool result = !is_source && pin >= 0 && pin < bp -> num_outputs;
                DEBUG_UNTRACE();
                return result;
        }

        i32 sub_count = vector_size(bp -> sub_chips);
        if (parent < 0 || parent >= sub_count) {
                DEBUG_UNTRACE();
                return false;
        }

        BlueprintChipIndex sub_index = bp -> sub_chips.data[bp -> sub_chips.start + parent];
        if (sub_index < global_circuit.blueprints.start || sub_index >= global_circuit.blueprints.end) {
                DEBUG_UNTRACE();
                return false;
        }

        BlueprintChip* sub_bp = &global_circuit.blueprints.data[sub_index];
        bool result = pin >= 0 && pin < (is_source ? sub_bp -> num_outputs : sub_bp -> num_inputs);
        DEBUG_UNTRACE();
        return result;
}

ENNDEF_PUBLIC void circuit_save_blueprint_to_disk(BlueprintChipIndex blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);

        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        if (bp -> is_primitive_nand) {
                DEBUG_UNTRACE();
                return;
        }

        directory_create(CIRCUIT_CHIP_DATA_DIRECTORY);

        DataFile df;
        datafile_create(&df);
        char key[CIRCUIT_SERIAL_KEY_MAX];

        snprintf(key, (sizeof key), "Chip|Name");
        datafile_put_cstring(&df, key, bp -> name);
        snprintf(key, (sizeof key), "Chip|Color");
        datafile_put_i32(&df, key, bp -> color);
        snprintf(key, (sizeof key), "Chip|Inputs");
        datafile_put_i32(&df, key, bp -> num_inputs);
        snprintf(key, (sizeof key), "Chip|Outputs");
        datafile_put_i32(&df, key, bp -> num_outputs);
        snprintf(key, (sizeof key), "Chip|SubChipCount");
        datafile_put_i32(&df, key, vector_size(bp -> sub_chips));
        snprintf(key, (sizeof key), "Chip|WireCount");
        datafile_put_i32(&df, key, vector_size(bp -> wires));

        for (i32 i = bp -> sub_chips.start; i < bp -> sub_chips.end; ++i) {
                i32 slot = i - bp -> sub_chips.start;
                BlueprintChipIndex sub = bp -> sub_chips.data[i];

                snprintf(key, (sizeof key), "Chip|SubChips|%d|BlueprintId", slot);
                datafile_put_i32(&df, key, sub);
                snprintf(key, (sizeof key), "Chip|SubChips|%d|BlueprintName", slot);
                datafile_put_cstring(&df, key, global_circuit.blueprints.data[sub].name);
        }

        for (i32 i = bp -> wires.start; i < bp -> wires.end; ++i) {
                i32 slot = i - bp -> wires.start;
                BlueprintWire* wire = &bp -> wires.data[i];

                snprintf(key, (sizeof key), "Chip|Wires|%d|FromSubChip", slot);
                datafile_put_i32(&df, key, wire -> from_sub_chip);
                snprintf(key, (sizeof key), "Chip|Wires|%d|FromPin", slot);
                datafile_put_i32(&df, key, wire -> from_pin);
                snprintf(key, (sizeof key), "Chip|Wires|%d|ToSubChip", slot);
                datafile_put_i32(&df, key, wire -> to_sub_chip);
                snprintf(key, (sizeof key), "Chip|Wires|%d|ToPin", slot);
                datafile_put_i32(&df, key, wire -> to_pin);
        }

        char* filepath = circuit_chip_blueprint_filepath(bp);
        datafile_write(&df, filepath);
        free(filepath);
        datafile_destroy(&df);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_load_blueprint_file_shell(const char* filepath) {
        DEBUG_TRACE();
        DataFile df;
        datafile_create(&df);
        if (!file_exists(filepath) || file_get_size(filepath) <= 0) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }
        datafile_read(&df, filepath);
        if (df.root == NULL) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }

        char* name = datafile_get_cstring(&df, "Chip|Name");
        i32 color = ENN_INTERNAL_COLOR_RED;

        if (name != NULL) {
                color = datafile_get_i32(&df, "Chip|Color");
                if (circuit_find_blueprint_by_name(name) == global_circuit.blueprints.end) {
                        if (color < ENN_INTERNAL_COLOR_RED || color >= ENN_INTERNAL_COLOR_LAST)
                                color = ENN_INTERNAL_COLOR_RED;
                        circuit_summon_blueprint(
                                name,
                                (ENN_CIRCUIT_ELEMENT_COLORS)color,
                                max(datafile_get_i32(&df, "Chip|Inputs"), 0),
                                max(datafile_get_i32(&df, "Chip|Outputs"), 0),
                                false
                        );
                }
        }

        datafile_destroy(&df);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_load_blueprint_file_contents(const char* filepath) {
        DEBUG_TRACE();
        DataFile df;
        datafile_create(&df);
        if (!file_exists(filepath) || file_get_size(filepath) <= 0) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }
        datafile_read(&df, filepath);
        if (df.root == NULL) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }

        char* name = datafile_get_cstring(&df, "Chip|Name");
        if (name == NULL) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }

        BlueprintChipIndex blueprint = circuit_find_blueprint_by_name(name);
        if (blueprint == global_circuit.blueprints.end || global_circuit.blueprints.data[blueprint].is_primitive_nand) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }

        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        vector_clear(bp -> sub_chips);
        vector_clear(bp -> wires);

        char key[CIRCUIT_SERIAL_KEY_MAX];
        i32 sub_count = datafile_get_i32(&df, "Chip|SubChipCount");
        i32 wire_count = datafile_get_i32(&df, "Chip|WireCount");
        if (sub_count < 0) sub_count = 0;
        if (wire_count < 0) wire_count = 0;

        for (i32 i = 0; i < sub_count; ++i) {
                i32 sub_id = global_circuit.blueprints.end;

                snprintf(key, (sizeof key), "Chip|SubChips|%d|BlueprintName", i);
                char* sub_name = datafile_get_cstring(&df, key);
                snprintf(key, (sizeof key), "Chip|SubChips|%d|BlueprintId", i);
                sub_id = datafile_get_i32(&df, key);

                BlueprintChipIndex sub = circuit_find_blueprint_by_name(sub_name);
                if (sub == global_circuit.blueprints.end && sub_id >= global_circuit.blueprints.start && sub_id < global_circuit.blueprints.end)
                        sub = sub_id;

                if (sub != global_circuit.blueprints.end && sub != blueprint)
                        vector_push_back(bp -> sub_chips, sub);
        }

        for (i32 i = 0; i < wire_count; ++i) {
                BlueprintWire wire = {0};
                snprintf(key, (sizeof key), "Chip|Wires|%d|FromSubChip", i);
                wire.from_sub_chip = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Chip|Wires|%d|FromPin", i);
                wire.from_pin = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Chip|Wires|%d|ToSubChip", i);
                wire.to_sub_chip = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Chip|Wires|%d|ToPin", i);
                wire.to_pin = datafile_get_i32(&df, key);

                if (circuit_blueprint_endpoint_valid(bp, wire.from_sub_chip, wire.from_pin, true) &&
                    circuit_blueprint_endpoint_valid(bp, wire.to_sub_chip, wire.to_pin, false))
                        vector_push_back(bp -> wires, wire);
        }

        datafile_destroy(&df);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_load_blueprints_from_disk(void) {
        DEBUG_TRACE();
        directory_create(CIRCUIT_CHIP_DATA_DIRECTORY);

        DIR* chip_dir = directory_open(CIRCUIT_CHIP_DATA_DIRECTORY);
        if (chip_dir == NULL) {
                DEBUG_UNTRACE();
                return;
        }

        DirEntry* entry = NULL;
        while ((entry = directory_read(chip_dir))) {
                if (!circuit_cstring_has_suffix(entry -> d_name, ENN_DATAFILE_FILE_EXTENSION)) continue;

                char filepath[CIRCUIT_SERIAL_PATH_MAX];
                snprintf(filepath, (sizeof filepath), "%s/%s", CIRCUIT_CHIP_DATA_DIRECTORY, entry -> d_name);
                circuit_load_blueprint_file_shell(filepath);
        }
        directory_close(chip_dir);

        chip_dir = directory_open(CIRCUIT_CHIP_DATA_DIRECTORY);
        if (chip_dir == NULL) {
                DEBUG_UNTRACE();
                return;
        }

        while ((entry = directory_read(chip_dir))) {
                if (!circuit_cstring_has_suffix(entry -> d_name, ENN_DATAFILE_FILE_EXTENSION)) continue;

                char filepath[CIRCUIT_SERIAL_PATH_MAX];
                snprintf(filepath, (sizeof filepath), "%s/%s", CIRCUIT_CHIP_DATA_DIRECTORY, entry -> d_name);
                circuit_load_blueprint_file_contents(filepath);
        }
        directory_close(chip_dir);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_internal_state(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.internal_pins.start; i < global_circuit.internal_pins.end; ++i)
                vector_destroy(global_circuit.internal_pins.data[i].connections);

        vector_clear(global_circuit.internal_pins);
        vector_clear(global_circuit.internal_wires);
        vector_clear(global_circuit.internal_gates);
        DEBUG_UNTRACE();
}

static void circuit_instantiate_blueprint_internal(BlueprintChipIndex blueprint, InternalPinIndex* inputs, InternalPinIndex* outputs) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];

        if (bp -> is_primitive_nand) {
                if (bp -> num_inputs >= 2 && bp -> num_outputs >= 1)
                        circuit_summon_internal_nand_gate(inputs[0], inputs[1], outputs[0]);
                DEBUG_UNTRACE();
                return;
        }

        typedef struct CircuitBlueprintInstancePins {
                InternalPinIndex* inputs;
                InternalPinIndex* outputs;
        } CircuitBlueprintInstancePins;

        i32 sub_count = vector_size(bp -> sub_chips);
        CircuitBlueprintInstancePins* instances = NULL;
        if (sub_count > 0)
                instances = calloc(sub_count, (sizeof (CircuitBlueprintInstancePins)));

        for (i32 i = bp -> sub_chips.start; i < bp -> sub_chips.end; ++i) {
                i32 slot = i - bp -> sub_chips.start;
                BlueprintChip* sub_bp = &global_circuit.blueprints.data[bp -> sub_chips.data[i]];
                instances[slot].inputs = calloc(sub_bp -> num_inputs, (sizeof (InternalPinIndex)));
                instances[slot].outputs = calloc(sub_bp -> num_outputs, (sizeof (InternalPinIndex)));

                for (i32 j = 0; j < sub_bp -> num_inputs; ++j)
                        instances[slot].inputs[j] = circuit_summon_internal_pin((CircuitElement) { .index = slot, .type = ENN_CHIP });

                for (i32 j = 0; j < sub_bp -> num_outputs; ++j)
                        instances[slot].outputs[j] = circuit_summon_internal_pin((CircuitElement) { .index = slot, .type = ENN_CHIP });

                circuit_instantiate_blueprint_internal(bp -> sub_chips.data[i], instances[slot].inputs, instances[slot].outputs);
        }

        for (i32 i = bp -> wires.start; i < bp -> wires.end; ++i) {
                BlueprintWire* wire = &bp -> wires.data[i];
                InternalPinIndex from = global_circuit.internal_pins.end;
                InternalPinIndex to = global_circuit.internal_pins.end;

                if (wire -> from_sub_chip == CIRCUIT_BLUEPRINT_PARENT_INPUT)
                        from = inputs[wire -> from_pin];
                else if (wire -> from_sub_chip == CIRCUIT_BLUEPRINT_PARENT_OUTPUT)
                        from = outputs[wire -> from_pin];
                else if (wire -> from_sub_chip >= 0 && wire -> from_sub_chip < sub_count)
                        from = instances[wire -> from_sub_chip].outputs[wire -> from_pin];

                if (wire -> to_sub_chip == CIRCUIT_BLUEPRINT_PARENT_INPUT)
                        to = inputs[wire -> to_pin];
                else if (wire -> to_sub_chip == CIRCUIT_BLUEPRINT_PARENT_OUTPUT)
                        to = outputs[wire -> to_pin];
                else if (wire -> to_sub_chip >= 0 && wire -> to_sub_chip < sub_count)
                        to = instances[wire -> to_sub_chip].inputs[wire -> to_pin];

                if (from != global_circuit.internal_pins.end && to != global_circuit.internal_pins.end)
                        circuit_summon_internal_wire(from, to);
        }

        for (i32 i = 0; i < sub_count; ++i) {
                free(instances[i].inputs);
                free(instances[i].outputs);
        }
        free(instances);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_rebuild_internal_state(void) {
        DEBUG_TRACE();
        circuit_destroy_internal_state();

        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                global_circuit.external_pins.data[i].internal = circuit_summon_internal_pin((CircuitElement) { .index = i, .type = ENN_EXTERNAL_PIN });

        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                ExternalChip* chip = &global_circuit.external_chips.data[i];
                BlueprintChip* bp = &global_circuit.blueprints.data[chip -> blueprint];
                InternalPinIndex* inputs = calloc(bp -> num_inputs, (sizeof (InternalPinIndex)));
                InternalPinIndex* outputs = calloc(bp -> num_outputs, (sizeof (InternalPinIndex)));

                for (i32 j = chip -> input_pins.start; j < chip -> input_pins.end; ++j)
                        inputs[j - chip -> input_pins.start] = global_circuit.external_pins.data[chip -> input_pins.data[j]].internal;

                for (i32 j = chip -> output_pins.start; j < chip -> output_pins.end; ++j)
                        outputs[j - chip -> output_pins.start] = global_circuit.external_pins.data[chip -> output_pins.data[j]].internal;

                circuit_instantiate_blueprint_internal(chip -> blueprint, inputs, outputs);
                free(inputs);
                free(outputs);
        }

        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                ExternalWire* wire = &global_circuit.external_wires.data[i];
                wire -> internal = circuit_summon_internal_wire(global_circuit.external_pins.data[wire -> from].internal, global_circuit.external_pins.data[wire -> to].internal);
        }

        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC ExternalPinIndex circuit_summon_external_pin(f32vec2 pos, ExternalPinType type, CircuitElement parent) {
        DEBUG_TRACE();
        ExternalPin new_pin;
        memset(&new_pin, 0x0, (sizeof (ExternalPin)));
        new_pin.id = global_circuit.external_pins.end;
        new_pin.pos = pos;
        new_pin.type = type;
        new_pin.parent = parent;
        new_pin.internal = circuit_summon_internal_pin((CircuitElement) { .index = new_pin.id, ENN_EXTERNAL_PIN });
        vector_push_back(global_circuit.external_pins, new_pin);
        DEBUG_UNTRACE();
        return new_pin.id;
}

ENNDEF_PUBLIC ExternalWireIndex circuit_summon_external_wire(f32vec2* anchors, i32 anchor_count, ExternalPinIndex from, ExternalPinIndex to) {
        DEBUG_TRACE();
        DEBUG_ASSERT(from != global_circuit.external_pins.end);
        DEBUG_ASSERT(to != global_circuit.external_pins.end);

        if (global_circuit.external_pins.data[from].type == global_circuit.external_pins.data[to].type) {
                DEBUG_LOG("[Game Objects] Tried summoning a wire between 2 pins of the same type");
                DEBUG_UNTRACE();
                return global_circuit.external_wires.end;
        }

        ExternalWire new_wire; memset(&new_wire, 0x0, (sizeof (ExternalWire)));
        bool reverse_anchors = false;
        if (global_circuit.external_pins.data[from].type == ENN_INPUT_PIN) {
                swap(from, to);
                reverse_anchors = true;
        }
        new_wire.color = circuit_get_pin_color(from);

        new_wire.id = global_circuit.external_wires.end;
        new_wire.internal = circuit_summon_internal_wire(global_circuit.external_pins.data[from].internal, global_circuit.external_pins.data[to].internal);
        new_wire.from = from;
        new_wire.to = to;
        if (anchor_count > 0 && anchors != NULL) {
                vector_reserve(new_wire.anchors, anchor_count);
                for (i32 i = 0; i < anchor_count; ++i)
                        new_wire.anchors.data[new_wire.anchors.start + i] = reverse_anchors ? anchors[anchor_count - i - 1] : anchors[i];
                new_wire.anchors.end += anchor_count;
        }
        vector_push_back(global_circuit.external_wires, new_wire);
        vector_push_back(global_circuit.external_pins.data[from].connections, new_wire.id);
        vector_push_back(global_circuit.external_pins.data[to].connections, new_wire.id);
        DEBUG_UNTRACE();
        return new_wire.id;
}

ENNDEF_PUBLIC InputIndicatorIndex circuit_summon_input_indicator(f32vec2 pos, ENN_CIRCUIT_ELEMENT_COLORS color) {
        DEBUG_TRACE();
        InputIndicator new_indicator; memset(&new_indicator, 0x0, (sizeof (InputIndicator)));
        new_indicator.id = global_circuit.input_indicators.end;
        new_indicator.pos = pos;
        new_indicator.color = color;
        new_indicator.output_pin = circuit_summon_external_pin(
                (f32vec2) { new_indicator.pos.x + CIRCUIT_INDICATOR_HITBOX_WIDTH - CIRCUIT_PIN_WIDTH, new_indicator.pos.y + (CIRCUIT_INDICATOR_HITBOX_HEIGHT - CIRCUIT_PIN_HEIGHT) * 0.5 },
                ENN_OUTPUT_PIN,
                (CircuitElement) { .index = new_indicator.id, .type = ENN_INPUT_INDICATOR }
        );
        vector_push_back(global_circuit.input_indicators, new_indicator);
        DEBUG_UNTRACE();
        return new_indicator.id;
}

ENNDEF_PUBLIC OutputIndicatorIndex circuit_summon_output_indicator(f32vec2 pos, ENN_CIRCUIT_ELEMENT_COLORS color) {
        DEBUG_TRACE();
        OutputIndicator new_indicator; memset(&new_indicator, 0x0, (sizeof (OutputIndicator)));
        new_indicator.id = global_circuit.output_indicators.end;
        new_indicator.pos = pos;
        new_indicator.color = color;
        new_indicator.input_pin = circuit_summon_external_pin(
                (f32vec2) { new_indicator.pos.x - CIRCUIT_PIN_WIDTH, new_indicator.pos.y + (CIRCUIT_INDICATOR_HITBOX_HEIGHT - CIRCUIT_PIN_HEIGHT) * 0.5 },
                ENN_INPUT_PIN,
                (CircuitElement) { .index = new_indicator.id, .type = ENN_OUTPUT_INDICATOR }
        );
        vector_push_back(global_circuit.output_indicators, new_indicator);
        DEBUG_UNTRACE();
        return new_indicator.id;
}

ENNDEF_PUBLIC ExternalChipIndex circuit_summon_chip(f32vec2 pos, BlueprintChipIndex blueprint) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        ExternalChip new_chip; memset(&new_chip, 0x0, (sizeof (ExternalChip)));
        new_chip.id = global_circuit.external_chips.end;
        new_chip.blueprint = blueprint;
        new_chip.pos = pos;
        new_chip.dim = circuit_blueprint_chip_dim(blueprint);

        for (i32 i = 0; i < bp -> num_inputs; ++i) {
                ExternalPinIndex pin = circuit_summon_external_pin(pos, ENN_INPUT_PIN, (CircuitElement) { .index = new_chip.id, .type = ENN_CHIP });
                vector_push_back(new_chip.input_pins, pin);
        }

        for (i32 i = 0; i < bp -> num_outputs; ++i) {
                ExternalPinIndex pin = circuit_summon_external_pin(pos, ENN_OUTPUT_PIN, (CircuitElement) { .index = new_chip.id, .type = ENN_CHIP });
                vector_push_back(new_chip.output_pins, pin);
        }

        vector_push_back(global_circuit.external_chips, new_chip);

        ExternalChip* chip = &global_circuit.external_chips.data[new_chip.id];
        for (i32 i = chip -> input_pins.start; i < chip -> input_pins.end; ++i) {
                i32 slot = i - chip -> input_pins.start;
                global_circuit.external_pins.data[chip -> input_pins.data[i]].pos = (f32vec2) {
                        .x = chip -> pos.x - CIRCUIT_PIN_WIDTH,
                        .y = chip -> pos.y + circuit_chip_pin_offset_y(chip -> dim.y, bp -> num_inputs, slot)
                };
        }

        for (i32 i = chip -> output_pins.start; i < chip -> output_pins.end; ++i) {
                i32 slot = i - chip -> output_pins.start;
                global_circuit.external_pins.data[chip -> output_pins.data[i]].pos = (f32vec2) {
                        .x = chip -> pos.x + chip -> dim.x,
                        .y = chip -> pos.y + circuit_chip_pin_offset_y(chip -> dim.y, bp -> num_outputs, slot)
                };
        }

        circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
        return new_chip.id;
}

ENNDEF_PUBLIC void circuit_remove_selected_refs(ENN_CIRCUIT_ELEMENT_TYPE type, GenericIndex index) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end;) {
                CircuitElement* elem = &global_circuit.selected_elements.data[i];
                if (elem -> type == type && elem -> index == index) {
                        vector_remove_at_index_keep_order(global_circuit.selected_elements, i);
                        continue;
                }
                if (elem -> type == type && elem -> index > index)
                        --elem -> index;
                ++i;
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_external_pin_remove_wire_ref(ExternalPinIndex pin, ExternalWireIndex wire) {
        DEBUG_TRACE();
        if (pin == global_circuit.external_pins.end) {
                DEBUG_UNTRACE();
                return;
        }

        for (i32 i = global_circuit.external_pins.data[pin].connections.start; i < global_circuit.external_pins.data[pin].connections.end;) {
                ExternalWireIndex* connection = &global_circuit.external_pins.data[pin].connections.data[i];
                if (*connection == wire) {
                        vector_remove_at_index_keep_order(global_circuit.external_pins.data[pin].connections, i);
                        continue;
                }
                if (*connection > wire)
                        --(*connection);
                ++i;
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_external_wire(ExternalWireIndex wire) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.external_wires.end);

        vector_destroy(global_circuit.external_wires.data[wire].anchors);
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                circuit_external_pin_remove_wire_ref(i, wire);

        vector_remove_at_index_keep_order(global_circuit.external_wires, wire);
        for (i32 i = wire; i < global_circuit.external_wires.end; ++i)
                global_circuit.external_wires.data[i].id = i;

        circuit_remove_selected_refs(ENN_EXTERNAL_WIRE, wire);
        if (!global_circuit.defer_internal_rebuild)
                circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_reindex_external_pin_refs(ExternalPinIndex pin) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                global_circuit.external_pins.data[i].id = i;

        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i)
                if (global_circuit.input_indicators.data[i].output_pin > pin)
                        --global_circuit.input_indicators.data[i].output_pin;

        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i)
                if (global_circuit.output_indicators.data[i].input_pin > pin)
                        --global_circuit.output_indicators.data[i].input_pin;

        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                ExternalChip* chip = &global_circuit.external_chips.data[i];
                for (i32 j = chip -> input_pins.start; j < chip -> input_pins.end;) {
                        if (chip -> input_pins.data[j] == pin) {
                                vector_remove_at_index_keep_order(chip -> input_pins, j);
                                continue;
                        }
                        if (chip -> input_pins.data[j] > pin)
                                --chip -> input_pins.data[j];
                        ++j;
                }

                for (i32 j = chip -> output_pins.start; j < chip -> output_pins.end;) {
                        if (chip -> output_pins.data[j] == pin) {
                                vector_remove_at_index_keep_order(chip -> output_pins, j);
                                continue;
                        }
                        if (chip -> output_pins.data[j] > pin)
                                --chip -> output_pins.data[j];
                        ++j;
                }
        }

        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                if (global_circuit.external_wires.data[i].from > pin)
                        --global_circuit.external_wires.data[i].from;
                if (global_circuit.external_wires.data[i].to > pin)
                        --global_circuit.external_wires.data[i].to;
        }

        if (global_circuit.hovered_pin == pin)
                global_circuit.hovered_pin = global_circuit.external_pins.end;
        else if (global_circuit.hovered_pin > pin)
                --global_circuit.hovered_pin;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_external_pin(ExternalPinIndex pin) {
        DEBUG_TRACE();
        DEBUG_ASSERT(pin != global_circuit.external_pins.end);

        while (vector_size(global_circuit.external_pins.data[pin].connections) > 0)
                circuit_destroy_external_wire(global_circuit.external_pins.data[pin].connections.data[global_circuit.external_pins.data[pin].connections.start]);

        vector_destroy(global_circuit.external_pins.data[pin].connections);
        vector_remove_at_index_keep_order(global_circuit.external_pins, pin);
        circuit_reindex_external_pin_refs(pin);
        if (!global_circuit.defer_internal_rebuild)
                circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_input_indicator(InputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);

        circuit_destroy_external_pin(global_circuit.input_indicators.data[indicator].output_pin);
        vector_remove_at_index_keep_order(global_circuit.input_indicators, indicator);
        for (i32 i = indicator; i < global_circuit.input_indicators.end; ++i)
                global_circuit.input_indicators.data[i].id = i;

        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                if (global_circuit.external_pins.data[i].parent.type == ENN_INPUT_INDICATOR &&
                    global_circuit.external_pins.data[i].parent.index > indicator)
                        --global_circuit.external_pins.data[i].parent.index;

        circuit_remove_selected_refs(ENN_INPUT_INDICATOR, indicator);
        if (!global_circuit.defer_internal_rebuild)
                circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_output_indicator(OutputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.output_indicators.end);

        circuit_destroy_external_pin(global_circuit.output_indicators.data[indicator].input_pin);
        vector_remove_at_index_keep_order(global_circuit.output_indicators, indicator);
        for (i32 i = indicator; i < global_circuit.output_indicators.end; ++i)
                global_circuit.output_indicators.data[i].id = i;

        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                if (global_circuit.external_pins.data[i].parent.type == ENN_OUTPUT_INDICATOR &&
                    global_circuit.external_pins.data[i].parent.index > indicator)
                        --global_circuit.external_pins.data[i].parent.index;

        circuit_remove_selected_refs(ENN_OUTPUT_INDICATOR, indicator);
        if (!global_circuit.defer_internal_rebuild)
                circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_chip(ExternalChipIndex chip) {
        DEBUG_TRACE();
        DEBUG_ASSERT(chip != global_circuit.external_chips.end);

        bool old_defer = global_circuit.defer_internal_rebuild;
        global_circuit.defer_internal_rebuild = true;
        while (vector_size(global_circuit.external_chips.data[chip].input_pins) > 0)
                circuit_destroy_external_pin(global_circuit.external_chips.data[chip].input_pins.data[global_circuit.external_chips.data[chip].input_pins.start]);

        while (vector_size(global_circuit.external_chips.data[chip].output_pins) > 0)
                circuit_destroy_external_pin(global_circuit.external_chips.data[chip].output_pins.data[global_circuit.external_chips.data[chip].output_pins.start]);

        vector_destroy(global_circuit.external_chips.data[chip].input_pins);
        vector_destroy(global_circuit.external_chips.data[chip].output_pins);
        vector_remove_at_index_keep_order(global_circuit.external_chips, chip);
        for (i32 i = chip; i < global_circuit.external_chips.end; ++i)
                global_circuit.external_chips.data[i].id = i;

        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                if (global_circuit.external_pins.data[i].parent.type == ENN_CHIP &&
                    global_circuit.external_pins.data[i].parent.index > chip)
                        --global_circuit.external_pins.data[i].parent.index;

        circuit_remove_selected_refs(ENN_CHIP, chip);
        global_circuit.defer_internal_rebuild = old_defer;
        if (!global_circuit.defer_internal_rebuild)
                circuit_rebuild_internal_state();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_runtime_objects(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i)
                vector_destroy(global_circuit.external_wires.data[i].anchors);

        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                vector_destroy(global_circuit.external_pins.data[i].connections);

        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                vector_destroy(global_circuit.external_chips.data[i].input_pins);
                vector_destroy(global_circuit.external_chips.data[i].output_pins);
        }

        circuit_destroy_internal_state();
        vector_clear(global_circuit.external_pins);
        vector_clear(global_circuit.external_wires);
        vector_clear(global_circuit.external_chips);
        vector_clear(global_circuit.input_indicators);
        vector_clear(global_circuit.output_indicators);
        vector_clear(global_circuit.selected_elements);
        vector_clear(selection_pane.move_states);
        vector_clear(selection_pane.original_anchors);
        selection_pane.has_collision = false;
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        global_circuit.defer_internal_rebuild = false;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool circuit_blueprint_endpoint_from_external_pin(ExternalPinIndex pin, bool is_source, i32* parent, i32* pin_slot) {
        DEBUG_TRACE();
        DEBUG_ASSERT(parent != NULL);
        DEBUG_ASSERT(pin_slot != NULL);
        ExternalPin* external_pin = &global_circuit.external_pins.data[pin];

        switch (external_pin -> parent.type) {
                case ENN_INPUT_INDICATOR:
                {
                        if (!is_source) break;
                        *parent = CIRCUIT_BLUEPRINT_PARENT_INPUT;
                        *pin_slot = external_pin -> parent.index;
                        DEBUG_UNTRACE();
                        return true;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        if (is_source) break;
                        *parent = CIRCUIT_BLUEPRINT_PARENT_OUTPUT;
                        *pin_slot = external_pin -> parent.index;
                        DEBUG_UNTRACE();
                        return true;
                }
                case ENN_CHIP:
                {
                        ExternalChip* chip = &global_circuit.external_chips.data[external_pin -> parent.index];
                        *parent = external_pin -> parent.index;
                        if (is_source) {
                                for (i32 i = chip -> output_pins.start; i < chip -> output_pins.end; ++i)
                                        if (chip -> output_pins.data[i] == pin) {
                                                *pin_slot = i - chip -> output_pins.start;
                                                DEBUG_UNTRACE();
                                                return true;
                                        }
                        } else {
                                for (i32 i = chip -> input_pins.start; i < chip -> input_pins.end; ++i)
                                        if (chip -> input_pins.data[i] == pin) {
                                                *pin_slot = i - chip -> input_pins.start;
                                                DEBUG_UNTRACE();
                                                return true;
                                        }
                        }
                        break;
                }
                default: break;
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC BlueprintChipIndex circuit_compile_current_to_blueprint(const char* name, ENN_CIRCUIT_ELEMENT_COLORS color) {
        DEBUG_TRACE();
        BlueprintChipIndex blueprint = circuit_summon_blueprint(name, color, vector_size(global_circuit.input_indicators), vector_size(global_circuit.output_indicators), false);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];

        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i)
                vector_push_back(bp -> sub_chips, global_circuit.external_chips.data[i].blueprint);

        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                BlueprintWire wire = {0};
                if (!circuit_blueprint_endpoint_from_external_pin(global_circuit.external_wires.data[i].from, true, &wire.from_sub_chip, &wire.from_pin))
                        continue;
                if (!circuit_blueprint_endpoint_from_external_pin(global_circuit.external_wires.data[i].to, false, &wire.to_sub_chip, &wire.to_pin))
                        continue;
                vector_push_back(bp -> wires, wire);
        }

        circuit_destroy_runtime_objects();
        current_action = ENN_ACTION_NOTHING;
        DEBUG_UNTRACE();
        return blueprint;
}

ENNDEF_PUBLIC bool circuit_serial_endpoint_from_external_pin(ExternalPinIndex pin, bool is_source, i32* type, i32* index, i32* pin_slot) {
        DEBUG_TRACE();
        DEBUG_ASSERT(type != NULL);
        DEBUG_ASSERT(index != NULL);
        DEBUG_ASSERT(pin_slot != NULL);
        if (pin < global_circuit.external_pins.start || pin >= global_circuit.external_pins.end) {
                DEBUG_UNTRACE();
                return false;
        }

        ExternalPin* external_pin = &global_circuit.external_pins.data[pin];
        *type = external_pin -> parent.type;
        *index = external_pin -> parent.index;
        *pin_slot = 0;

        switch (external_pin -> parent.type) {
                case ENN_INPUT_INDICATOR:
                {
                        bool result = is_source && external_pin -> parent.index >= global_circuit.input_indicators.start && external_pin -> parent.index < global_circuit.input_indicators.end;
                        DEBUG_UNTRACE();
                        return result;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        bool result = !is_source && external_pin -> parent.index >= global_circuit.output_indicators.start && external_pin -> parent.index < global_circuit.output_indicators.end;
                        DEBUG_UNTRACE();
                        return result;
                }
                case ENN_CHIP:
                {
                        if (external_pin -> parent.index < global_circuit.external_chips.start || external_pin -> parent.index >= global_circuit.external_chips.end) {
                                DEBUG_UNTRACE();
                                return false;
                        }

                        ExternalChip* chip = &global_circuit.external_chips.data[external_pin -> parent.index];
                        if (is_source) {
                                for (i32 i = chip -> output_pins.start; i < chip -> output_pins.end; ++i)
                                        if (chip -> output_pins.data[i] == pin) {
                                                *pin_slot = i - chip -> output_pins.start;
                                                DEBUG_UNTRACE();
                                                return true;
                                        }
                        } else {
                                for (i32 i = chip -> input_pins.start; i < chip -> input_pins.end; ++i)
                                        if (chip -> input_pins.data[i] == pin) {
                                                *pin_slot = i - chip -> input_pins.start;
                                                DEBUG_UNTRACE();
                                                return true;
                                        }
                        }
                        break;
                }
                default: break;
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC ExternalPinIndex circuit_external_pin_from_serial_endpoint(i32 type, i32 index, i32 pin_slot, bool is_source, ExternalChipIndex* chip_map, i32 chip_count) {
        DEBUG_TRACE();
        switch ((ENN_CIRCUIT_ELEMENT_TYPE)type) {
                case ENN_INPUT_INDICATOR:
                {
                        if (!is_source || index < global_circuit.input_indicators.start || index >= global_circuit.input_indicators.end) break;
                        DEBUG_UNTRACE();
                        return global_circuit.input_indicators.data[index].output_pin;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        if (is_source || index < global_circuit.output_indicators.start || index >= global_circuit.output_indicators.end) break;
                        DEBUG_UNTRACE();
                        return global_circuit.output_indicators.data[index].input_pin;
                }
                case ENN_CHIP:
                {
                        if (index < 0 || index >= chip_count || chip_map == NULL || chip_map[index] < global_circuit.external_chips.start || chip_map[index] >= global_circuit.external_chips.end)
                                break;

                        ExternalChip* chip = &global_circuit.external_chips.data[chip_map[index]];
                        if (is_source) {
                                if (pin_slot < 0 || pin_slot >= vector_size(chip -> output_pins)) break;
                                DEBUG_UNTRACE();
                                return chip -> output_pins.data[chip -> output_pins.start + pin_slot];
                        } else {
                                if (pin_slot < 0 || pin_slot >= vector_size(chip -> input_pins)) break;
                                DEBUG_UNTRACE();
                                return chip -> input_pins.data[chip -> input_pins.start + pin_slot];
                        }
                }
                default: break;
        }

        DEBUG_UNTRACE();
        return global_circuit.external_pins.end;
}

ENNDEF_PUBLIC void circuit_save_workspace(const char* filepath) {
        DEBUG_TRACE();
        DEBUG_ASSERT(filepath != NULL);

        DataFile df;
        datafile_create(&df);
        char key[CIRCUIT_SERIAL_KEY_MAX];

        snprintf(key, (sizeof key), "Circuit|InputCount");
        datafile_put_i32(&df, key, vector_size(global_circuit.input_indicators));
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i) {
                i32 slot = i - global_circuit.input_indicators.start;
                InputIndicator* input = &global_circuit.input_indicators.data[i];
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|X", slot);
                datafile_put_f32(&df, key, input -> pos.x);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|Y", slot);
                datafile_put_f32(&df, key, input -> pos.y);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|Color", slot);
                datafile_put_i32(&df, key, input -> color);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|State", slot);
                datafile_put_i32(&df, key, input -> state ? 1 : 0);
        }

        snprintf(key, (sizeof key), "Circuit|OutputCount");
        datafile_put_i32(&df, key, vector_size(global_circuit.output_indicators));
        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i) {
                i32 slot = i - global_circuit.output_indicators.start;
                OutputIndicator* output = &global_circuit.output_indicators.data[i];
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|X", slot);
                datafile_put_f32(&df, key, output -> pos.x);
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|Y", slot);
                datafile_put_f32(&df, key, output -> pos.y);
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|Color", slot);
                datafile_put_i32(&df, key, output -> color);
        }

        snprintf(key, (sizeof key), "Circuit|ChipCount");
        datafile_put_i32(&df, key, vector_size(global_circuit.external_chips));
        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                i32 slot = i - global_circuit.external_chips.start;
                ExternalChip* chip = &global_circuit.external_chips.data[i];
                BlueprintChip* bp = &global_circuit.blueprints.data[chip -> blueprint];
                snprintf(key, (sizeof key), "Circuit|Chips|%d|X", slot);
                datafile_put_f32(&df, key, chip -> pos.x);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|Y", slot);
                datafile_put_f32(&df, key, chip -> pos.y);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|BlueprintId", slot);
                datafile_put_i32(&df, key, chip -> blueprint);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|BlueprintName", slot);
                datafile_put_cstring(&df, key, bp -> name);
        }

        i32 saved_wire_count = 0;
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                ExternalWire* wire = &global_circuit.external_wires.data[i];
                i32 from_type = 0, from_index = 0, from_pin = 0;
                i32 to_type = 0, to_index = 0, to_pin = 0;
                if (!circuit_serial_endpoint_from_external_pin(wire -> from, true, &from_type, &from_index, &from_pin))
                        continue;
                if (!circuit_serial_endpoint_from_external_pin(wire -> to, false, &to_type, &to_index, &to_pin))
                        continue;

                i32 slot = saved_wire_count++;
                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromType", slot);
                datafile_put_i32(&df, key, from_type);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromIndex", slot);
                datafile_put_i32(&df, key, from_index);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromPin", slot);
                datafile_put_i32(&df, key, from_pin);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToType", slot);
                datafile_put_i32(&df, key, to_type);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToIndex", slot);
                datafile_put_i32(&df, key, to_index);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToPin", slot);
                datafile_put_i32(&df, key, to_pin);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|Color", slot);
                datafile_put_i32(&df, key, wire -> color);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|AnchorCount", slot);
                datafile_put_i32(&df, key, vector_size(wire -> anchors));

                for (i32 j = wire -> anchors.start; j < wire -> anchors.end; ++j) {
                        i32 anchor_slot = j - wire -> anchors.start;
                        snprintf(key, (sizeof key), "Circuit|Wires|%d|Anchors|%d|X", slot, anchor_slot);
                        datafile_put_f32(&df, key, wire -> anchors.data[j].x);
                        snprintf(key, (sizeof key), "Circuit|Wires|%d|Anchors|%d|Y", slot, anchor_slot);
                        datafile_put_f32(&df, key, wire -> anchors.data[j].y);
                }
        }

        snprintf(key, (sizeof key), "Circuit|WireCount");
        datafile_put_i32(&df, key, saved_wire_count);

        datafile_write(&df, filepath);
        datafile_destroy(&df);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_load_workspace(const char* filepath) {
        DEBUG_TRACE();
        DEBUG_ASSERT(filepath != NULL);

        circuit_destroy_runtime_objects();
        current_action = ENN_ACTION_NOTHING;

        DataFile df;
        datafile_create(&df);
        if (!file_exists(filepath) || file_get_size(filepath) <= 0) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }
        datafile_read(&df, filepath);
        if (df.root == NULL) {
                datafile_destroy(&df);
                DEBUG_UNTRACE();
                return;
        }

        char key[CIRCUIT_SERIAL_KEY_MAX];
        i32 input_count = datafile_get_i32(&df, "Circuit|InputCount");
        i32 output_count = datafile_get_i32(&df, "Circuit|OutputCount");
        i32 chip_count = datafile_get_i32(&df, "Circuit|ChipCount");
        i32 wire_count = datafile_get_i32(&df, "Circuit|WireCount");
        if (input_count < 0) input_count = 0;
        if (output_count < 0) output_count = 0;
        if (chip_count < 0) chip_count = 0;
        if (wire_count < 0) wire_count = 0;

        for (i32 i = 0; i < input_count; ++i) {
                f32vec2 pos = {0};
                i32 color = ENN_INTERNAL_COLOR_RED;
                i32 state = 0;
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|X", i);
                pos.x = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|Y", i);
                pos.y = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|Color", i);
                color = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Inputs|%d|State", i);
                state = datafile_get_i32(&df, key);
                if (color < ENN_INTERNAL_COLOR_RED || color >= ENN_INTERNAL_COLOR_LAST)
                        color = ENN_INTERNAL_COLOR_RED;
                InputIndicatorIndex input = circuit_summon_input_indicator(pos, (ENN_CIRCUIT_ELEMENT_COLORS)color);
                global_circuit.input_indicators.data[input].state = state != 0;
        }

        for (i32 i = 0; i < output_count; ++i) {
                f32vec2 pos = {0};
                i32 color = ENN_INTERNAL_COLOR_RED;
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|X", i);
                pos.x = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|Y", i);
                pos.y = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Outputs|%d|Color", i);
                color = datafile_get_i32(&df, key);
                if (color < ENN_INTERNAL_COLOR_RED || color >= ENN_INTERNAL_COLOR_LAST)
                        color = ENN_INTERNAL_COLOR_RED;
                circuit_summon_output_indicator(pos, (ENN_CIRCUIT_ELEMENT_COLORS)color);
        }

        ExternalChipIndex* chip_map = NULL;
        if (chip_count > 0) {
                chip_map = calloc(chip_count, (sizeof (ExternalChipIndex)));
                for (i32 i = 0; i < chip_count; ++i)
                        chip_map[i] = -1;
        }

        for (i32 i = 0; i < chip_count; ++i) {
                f32vec2 pos = {0};
                i32 blueprint_id = global_circuit.blueprints.end;
                char blueprint_name[CIRCUIT_CHIP_MAX_NAME_LEN] = {0};

                snprintf(key, (sizeof key), "Circuit|Chips|%d|X", i);
                pos.x = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|Y", i);
                pos.y = datafile_get_f32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|BlueprintId", i);
                blueprint_id = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Chips|%d|BlueprintName", i);
                char* stored_name = datafile_get_cstring(&df, key);
                if (stored_name != NULL)
                        strncpy(blueprint_name, stored_name, (sizeof blueprint_name) - 1);

                BlueprintChipIndex blueprint = circuit_find_blueprint_by_name(blueprint_name);
                if (blueprint == global_circuit.blueprints.end && blueprint_id >= global_circuit.blueprints.start && blueprint_id < global_circuit.blueprints.end)
                        blueprint = blueprint_id;

                if (blueprint != global_circuit.blueprints.end)
                        chip_map[i] = circuit_summon_chip(pos, blueprint);
        }

        for (i32 i = 0; i < wire_count; ++i) {
                i32 from_type = 0, from_index = 0, from_pin = 0;
                i32 to_type = 0, to_index = 0, to_pin = 0;
                i32 anchor_count = 0;
                i32 color = ENN_INTERNAL_COLOR_RED;

                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromType", i);
                from_type = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromIndex", i);
                from_index = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|FromPin", i);
                from_pin = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToType", i);
                to_type = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToIndex", i);
                to_index = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|ToPin", i);
                to_pin = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|Color", i);
                color = datafile_get_i32(&df, key);
                snprintf(key, (sizeof key), "Circuit|Wires|%d|AnchorCount", i);
                anchor_count = datafile_get_i32(&df, key);
                if (anchor_count < 0) anchor_count = 0;

                ExternalPinIndex from = circuit_external_pin_from_serial_endpoint(from_type, from_index, from_pin, true, chip_map, chip_count);
                ExternalPinIndex to = circuit_external_pin_from_serial_endpoint(to_type, to_index, to_pin, false, chip_map, chip_count);
                if (from == global_circuit.external_pins.end || to == global_circuit.external_pins.end)
                        continue;

                f32vec2* anchors = NULL;
                if (anchor_count > 0) {
                        anchors = calloc(anchor_count, (sizeof (f32vec2)));
                        for (i32 j = 0; j < anchor_count; ++j) {
                                snprintf(key, (sizeof key), "Circuit|Wires|%d|Anchors|%d|X", i, j);
                                anchors[j].x = datafile_get_f32(&df, key);
                                snprintf(key, (sizeof key), "Circuit|Wires|%d|Anchors|%d|Y", i, j);
                                anchors[j].y = datafile_get_f32(&df, key);
                        }
                } else {
                        anchor_count = 2;
                        anchors = calloc(anchor_count, (sizeof (f32vec2)));
                        anchors[0] = circuit_external_pin_center(from);
                        anchors[1] = circuit_external_pin_center(to);
                }

                ExternalWireIndex wire = circuit_summon_external_wire(anchors, anchor_count, from, to);
                if (wire != global_circuit.external_wires.end && color >= ENN_INTERNAL_COLOR_RED && color < ENN_INTERNAL_COLOR_LAST)
                        global_circuit.external_wires.data[wire].color = (ENN_CIRCUIT_ELEMENT_COLORS)color;
                free(anchors);
        }

        free(chip_map);
        circuit_rebuild_internal_state();
        datafile_destroy(&df);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_reset_internal_pin_states(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.internal_pins.start; i < global_circuit.internal_pins.end; ++i) {
                global_circuit.internal_pins.data[i].curr_state = false;
                global_circuit.internal_pins.data[i].next_state = false;
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_set_input_indicator_state(InputIndicatorIndex indicator, bool state) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);
        InputIndicator* input = &global_circuit.input_indicators.data[indicator];
        input -> state = state;
        InternalPinIndex internal = global_circuit.external_pins.data[input -> output_pin].internal;
        if (internal != global_circuit.internal_pins.end) {
                global_circuit.internal_pins.data[internal].curr_state = state;
                global_circuit.internal_pins.data[internal].next_state = state;
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_apply_input_indicator_states(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i)
                circuit_set_input_indicator_state(i, global_circuit.input_indicators.data[i].state);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_prepare_execute_mode(void) {
        DEBUG_TRACE();
        current_action = ENN_ACTION_NOTHING;
        vector_clear(global_circuit.selected_elements);
        vector_clear(selection_pane.move_states);
        vector_clear(selection_pane.original_anchors);
        selection_pane.has_collision = false;
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        circuit_rebuild_internal_state();
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i)
                global_circuit.input_indicators.data[i].state = false;
        circuit_reset_internal_pin_states();
        circuit_apply_input_indicator_states();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_prepare_edit_mode(void) {
        DEBUG_TRACE();
        current_action = ENN_ACTION_NOTHING;
        vector_clear(selection_pane.move_states);
        vector_clear(selection_pane.original_anchors);
        selection_pane.has_collision = false;
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        circuit_reset_internal_pin_states();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_update_tick(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.internal_pins.start; i < global_circuit.internal_pins.end; ++i)
                global_circuit.internal_pins.data[i].next_state = false;

        circuit_apply_input_indicator_states();

        for (i32 i = global_circuit.internal_wires.start; i < global_circuit.internal_wires.end; ++i) {
                InternalPinIndex from   = global_circuit.internal_wires.data[i].from;
                InternalPinIndex to     = global_circuit.internal_wires.data[i].to;
                global_circuit.internal_pins.data[to].next_state = global_circuit.internal_pins.data[from].curr_state;
        }
        
        for (i32 i = global_circuit.internal_gates.start; i < global_circuit.internal_gates.end; ++i) {
                InternalPinIndex in_a = global_circuit.internal_gates.data[i].input_a;
                InternalPinIndex in_b = global_circuit.internal_gates.data[i].input_b;
                InternalPinIndex out = global_circuit.internal_gates.data[i].output;
                bool a = global_circuit.internal_pins.data[in_a].curr_state;
                bool b = global_circuit.internal_pins.data[in_b].curr_state;
                global_circuit.internal_pins.data[out].next_state = !(a && b);
        }
        
        for (i32 i = global_circuit.internal_pins.start; i < global_circuit.internal_pins.end; ++i) {
                global_circuit.internal_pins.data[i].curr_state = global_circuit.internal_pins.data[i].next_state;
        }
        circuit_apply_input_indicator_states();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool circuit_toggle_input_indicator_at_pos(f32vec2 pos) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.input_indicators.end - 1; i >= global_circuit.input_indicators.start; --i) {
                if (is_inside_rectangle(pos, circuit_input_indicator_hitbox(i))) {
                        circuit_set_input_indicator_state(i, !global_circuit.input_indicators.data[i].state);
                        circuit_update_tick();
                        DEBUG_UNTRACE();
                        return true;
                }
        }
        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC void circuit_check_hovered_pin(f32vec2 pos) {
        DEBUG_TRACE();
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i)
                if (is_inside_rectangle(pos,
                        (f32vec4) {
                                .x = global_circuit.external_pins.data[i].pos.x,
                                .y = global_circuit.external_pins.data[i].pos.y,
                                .z = CIRCUIT_PIN_WIDTH,
                                .w = CIRCUIT_PIN_HEIGHT
                        })) {
                                global_circuit.hovered_pin = i;
                                break;
                        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_pins(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i) {
                render_rectangle_push(
                        global_circuit.external_pins.data[i].pos, 
                        (f32vec2) { global_circuit.external_pins.data[i].pos.x + CIRCUIT_PIN_WIDTH, global_circuit.external_pins.data[i].pos.y + CIRCUIT_PIN_HEIGHT },
                        CIRCUIT_PIN_COLOR
                );
        }
        if (global_circuit.hovered_pin != global_circuit.external_pins.end) {
                render_rectangle_push(
                        global_circuit.external_pins.data[global_circuit.hovered_pin].pos, 
                        (f32vec2) { global_circuit.external_pins.data[global_circuit.hovered_pin].pos.x + CIRCUIT_PIN_WIDTH, global_circuit.external_pins.data[global_circuit.hovered_pin].pos.y + CIRCUIT_PIN_HEIGHT },
                        CIRCUIT_PIN_HOVER_COLOR
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_wires_edit(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                render_multiline_push(
                        global_circuit.external_wires.data[i].anchors.data + global_circuit.external_wires.data[i].anchors.start,
                        vector_size(global_circuit.external_wires.data[i].anchors), 
                        CIRCUIT_WIRE_WIDTH,
                        color_dark_get_by_circuit_color(global_circuit.external_wires.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_wires_execute(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                const ExternalPin* pin = &global_circuit.external_pins.data[global_circuit.external_wires.data[i].from];
                bool state = global_circuit.internal_pins.data[pin -> internal].curr_state;
                render_multiline_push(
                        global_circuit.external_wires.data[i].anchors.data + global_circuit.external_wires.data[i].anchors.start,
                        vector_size(global_circuit.external_wires.data[i].anchors), 
                        CIRCUIT_WIRE_WIDTH,
                        state ? color_light_get_by_circuit_color(global_circuit.external_wires.data[i].color) : color_dark_get_by_circuit_color(global_circuit.external_wires.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_input_indicators_edit(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i) {
                render_rectangle_push(
                        global_circuit.input_indicators.data[i].pos,
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT },
                        CIRCUIT_INDICATOR_HARD_BORDER_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.input_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.input_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        CIRCUIT_INDICATOR_CONNECTOR_COLOR 
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        color_dark_dark_get_by_circuit_color(global_circuit.input_indicators.data[i].color)
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING - CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING -  CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        color_dark_get_by_circuit_color(global_circuit.input_indicators.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_input_indicators_execute(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i) {
                bool state = global_circuit.internal_pins.data[global_circuit.external_pins.data[global_circuit.input_indicators.data[i].output_pin].internal].curr_state;
                render_rectangle_push(
                        global_circuit.input_indicators.data[i].pos,
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT },
                        CIRCUIT_INDICATOR_HARD_BORDER_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.input_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.input_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        CIRCUIT_INDICATOR_CONNECTOR_COLOR 
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        state ? color_light_dark_get_by_circuit_color(global_circuit.input_indicators.data[i].color) : color_dark_dark_get_by_circuit_color(global_circuit.input_indicators.data[i].color)
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING - CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.input_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING -  CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        state ? color_light_get_by_circuit_color(global_circuit.input_indicators.data[i].color) : color_dark_get_by_circuit_color(global_circuit.input_indicators.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_output_indicators_edit(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i) {
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.output_indicators.data[i].pos.y },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT },
                        CIRCUIT_INDICATOR_HARD_BORDER_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x, global_circuit.output_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.output_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        CIRCUIT_INDICATOR_CONNECTOR_COLOR 
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        color_dark_dark_get_by_circuit_color(global_circuit.output_indicators.data[i].color)
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING - CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING -  CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        color_dark_get_by_circuit_color(global_circuit.output_indicators.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_output_indicators_execute(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i) {
                bool state = global_circuit.internal_pins.data[global_circuit.external_pins.data[global_circuit.output_indicators.data[i].input_pin].internal].curr_state;
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.output_indicators.data[i].pos.y },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT },
                        CIRCUIT_INDICATOR_HARD_BORDER_COLOR
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x, global_circuit.output_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.output_indicators.data[i].pos.y + (CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5 },
                        CIRCUIT_INDICATOR_CONNECTOR_COLOR 
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING },
                        state ? color_light_dark_get_by_circuit_color(global_circuit.output_indicators.data[i].color) : color_dark_dark_get_by_circuit_color(global_circuit.output_indicators.data[i].color)
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_HARD_BORDER_PADDING + CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH - CIRCUIT_INDICATOR_HARD_BORDER_PADDING - CIRCUIT_INDICATOR_SOFT_BORDER_PADDING, global_circuit.output_indicators.data[i].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT - CIRCUIT_INDICATOR_HARD_BORDER_PADDING -  CIRCUIT_INDICATOR_SOFT_BORDER_PADDING },
                        state ? color_light_get_by_circuit_color(global_circuit.output_indicators.data[i].color) : color_dark_get_by_circuit_color(global_circuit.output_indicators.data[i].color)
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_chip_body(BlueprintChipIndex blueprint, f32vec2 pos, f32vec2 dim, f32 border_padding, f32 name_padding, f32 text_height, f32 text_width) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        render_rectangle_push(
                pos,
                (f32vec2) { pos.x + dim.x, pos.y + dim.y },
                color_dark_get_by_circuit_color(bp -> color)
        );
        if (dim.x > border_padding * 2.0 && dim.y > border_padding * 2.0) {
                render_rectangle_push(
                        (f32vec2) { pos.x + border_padding, pos.y + border_padding },
                        (f32vec2) { pos.x + dim.x - border_padding, pos.y + dim.y - border_padding },
                        color_light_dark_get_by_circuit_color(bp -> color)
                );
        }

        if (text_height > 0.0 && text_width > 0.0 && dim.x > name_padding * 2.0 && dim.y > text_height) {
                i32 name_len = max((i32)strlen(bp -> name), 1);
                f32 available_text_width = dim.x - name_padding * 2.0;
                f32 render_text_width = min(text_width, available_text_width / name_len);
                render_text_push_width(
                        (f32vec2) { pos.x + name_padding, pos.y + (dim.y - text_height) * 0.5 },
                        (f32vec2) { pos.x + dim.x - name_padding, pos.y + (dim.y - text_height) * 0.5 },
                        bp -> name, CIRCUIT_CHIP_NAME_TEXT_COLOR, text_height, render_text_width, ENN_CENTER_ALIGN
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_blueprint_chip_preview(BlueprintChipIndex blueprint, f32vec2 top_left, f32vec2 bott_right) {
        DEBUG_TRACE();
        DEBUG_ASSERT(blueprint != global_circuit.blueprints.end);
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];
        f32vec2 natural_body = circuit_blueprint_chip_dim(blueprint);
        f32 natural_total_width = natural_body.x + CIRCUIT_PIN_WIDTH * 2.0;
        f32 natural_total_height = natural_body.y;
        f32 available_width = bott_right.x - top_left.x;
        f32 available_height = bott_right.y - top_left.y;
        if (available_width <= 0.0 || available_height <= 0.0) {
                DEBUG_UNTRACE();
                return;
        }

        f32 scale = min(available_width / natural_total_width, (available_height / ENN_FRAMEBUFF_ASPECT_RATIO) / natural_total_height);
        f32 total_width = natural_total_width * scale;
        f32 total_height = natural_total_height * scale * ENN_FRAMEBUFF_ASPECT_RATIO;
        f32 pin_width = CIRCUIT_PIN_WIDTH * scale;
        f32 pin_height = CIRCUIT_PIN_HEIGHT * scale * ENN_FRAMEBUFF_ASPECT_RATIO;
        f32vec2 body_dim = { natural_body.x * scale, natural_body.y * scale * ENN_FRAMEBUFF_ASPECT_RATIO };
        f32vec2 body_pos = {
                .x = (top_left.x + bott_right.x - total_width) * 0.5 + pin_width,
                .y = (top_left.y + bott_right.y - total_height) * 0.5
        };

        for (i32 i = 0; i < bp -> num_inputs; ++i) {
                f32 pin_y = body_pos.y + circuit_chip_pin_offset_y(natural_body.y, bp -> num_inputs, i) * scale * ENN_FRAMEBUFF_ASPECT_RATIO;
                render_rectangle_push(
                        (f32vec2) { body_pos.x - pin_width, pin_y },
                        (f32vec2) { body_pos.x, pin_y + pin_height },
                        CIRCUIT_PIN_COLOR
                );
        }

        for (i32 i = 0; i < bp -> num_outputs; ++i) {
                f32 pin_y = body_pos.y + circuit_chip_pin_offset_y(natural_body.y, bp -> num_outputs, i) * scale * ENN_FRAMEBUFF_ASPECT_RATIO;
                render_rectangle_push(
                        (f32vec2) { body_pos.x + body_dim.x, pin_y },
                        (f32vec2) { body_pos.x + body_dim.x + pin_width, pin_y + pin_height },
                        CIRCUIT_PIN_COLOR
                );
        }

        f32 text_height = CIRCUIT_CHIP_NAME_TEXT_HEIGHT * scale * ENN_FRAMEBUFF_ASPECT_RATIO;
        f32 text_width = CIRCUIT_CHIP_NAME_TEXT_WIDTH * scale;
        if (text_height < 0.012) text_height = 0.0;
        circuit_render_chip_body(blueprint, body_pos, body_dim, CIRCUIT_CHIP_BORDER_PADDING * scale, CIRCUIT_CHIP_NAME_PADDING * scale, text_height, text_width);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_chips(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                circuit_render_chip_body(
                        global_circuit.external_chips.data[i].blueprint,
                        global_circuit.external_chips.data[i].pos,
                        global_circuit.external_chips.data[i].dim,
                        CIRCUIT_CHIP_BORDER_PADDING,
                        CIRCUIT_CHIP_NAME_PADDING,
                        CIRCUIT_CHIP_NAME_TEXT_HEIGHT,
                        CIRCUIT_CHIP_NAME_TEXT_WIDTH
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool circuit_elements_equal(CircuitElement a, CircuitElement b) {
        return a.type == b.type && a.index == b.index;
}

ENNDEF_PUBLIC bool circuit_is_element_colliding(CircuitElement elem) {
        for (i32 i = selection_pane.move_states.start; i < selection_pane.move_states.end; ++i)
                if (circuit_elements_equal(selection_pane.move_states.data[i].elem, elem))
                        return selection_pane.move_states.data[i].colliding;

        return false;
}

ENNDEF_PUBLIC u32 circuit_selection_overlay_color(CircuitElement elem) {
        return circuit_is_element_colliding(elem) ? CIRCUIT_ELEMENT_OVERLAY_COLLISION_COLOR : CIRCUIT_ELEMENT_OVERLAY_COLOR;
}

ENNDEF_PUBLIC void circuit_render_selection_overlay(void) {
        DEBUG_TRACE();
        for (i32 idx = global_circuit.selected_elements.start; idx < global_circuit.selected_elements.end; ++idx) {
                CircuitElement elem = global_circuit.selected_elements.data[idx];
                u32 overlay_color = circuit_selection_overlay_color(elem);
                if (elem.type == ENN_INPUT_INDICATOR) {
                        f32vec4 hitbox = circuit_input_indicator_hitbox(elem.index);
                        render_rectangle_push(
                                (f32vec2) { hitbox.x, hitbox.y },
                                (f32vec2) { hitbox.x + hitbox.z, hitbox.y + hitbox.w },
                                overlay_color
                        );
                } else if (elem.type == ENN_OUTPUT_INDICATOR) {
                        f32vec4 hitbox = circuit_output_indicator_hitbox(elem.index);
                        render_rectangle_push(
                                (f32vec2) { hitbox.x, hitbox.y },
                                (f32vec2) { hitbox.x + hitbox.z, hitbox.y + hitbox.w },
                                overlay_color
                        );
                } else if (elem.type == ENN_CHIP) {
                        f32vec4 hitbox = circuit_chip_hitbox(elem.index);
                        render_rectangle_push(
                                (f32vec2) { hitbox.x, hitbox.y },
                                (f32vec2) { hitbox.x + hitbox.z, hitbox.y + hitbox.w },
                                overlay_color
                        );
                } else if (elem.type == ENN_EXTERNAL_WIRE) {
                        ExternalWire* wire = &global_circuit.external_wires.data[elem.index];
                        render_multiline_push(
                                wire -> anchors.data + wire -> anchors.start,
                                vector_size(wire -> anchors),
                                CIRCUIT_WIRE_WIDTH + CIRCUIT_INDICATOR_OVERLAY_PADDING,
                                overlay_color
                        );
                }
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_objects_edit(void) {
        DEBUG_TRACE();
        circuit_render_wires_edit();
        circuit_render_pins();
        circuit_render_chips();
        circuit_render_input_indicators_edit();
        circuit_render_output_indicators_edit();
        circuit_render_selection_overlay();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_objects_execute(void) {
        DEBUG_TRACE();
        circuit_render_wires_execute();
        circuit_render_pins();
        circuit_render_chips();
        circuit_render_input_indicators_execute();
        circuit_render_output_indicators_execute();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool circuit_is_element_selected(CircuitElement elem) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end; ++i) 
                if (circuit_elements_equal(elem, global_circuit.selected_elements.data[i])) {
                        DEBUG_UNTRACE();
                        return true;
                }
        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC void circuit_selection_add_element(CircuitElement elem) {
        DEBUG_TRACE();
        if (circuit_is_element_selected(elem)) {
                DEBUG_UNTRACE();
                return ;
        }

        vector_push_back(global_circuit.selected_elements, elem);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_add_connected_wires(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                CircuitElement from_parent = global_circuit.external_pins.data[global_circuit.external_wires.data[i].from].parent;
                CircuitElement to_parent = global_circuit.external_pins.data[global_circuit.external_wires.data[i].to].parent;

                if (circuit_is_element_selected(from_parent) && circuit_is_element_selected(to_parent))
                        circuit_selection_add_element((CircuitElement) { .index = i, .type = ENN_EXTERNAL_WIRE });
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_clear(void) {
        DEBUG_TRACE();
        vector_clear(global_circuit.selected_elements);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_pane_start(f32vec2 pos) {
        DEBUG_TRACE();
        selection_pane.start = pos;
        selection_pane.end = pos;
        selection_pane.last_move = pos;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_pane_extend(f32vec2 pos) {
        DEBUG_TRACE();
        selection_pane.end = pos;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_selection_pane(void) {
        DEBUG_TRACE();
        f32vec4 rect = circuit_rect_from_points(selection_pane.start, selection_pane.end);
        render_rectangle_push(
                (f32vec2) { rect.x, rect.y },
                (f32vec2) { rect.x + rect.z, rect.y + rect.w },
                CIRCUIT_SELECTION_BOX_COLOR
        );
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_add_intersections(f32vec4 rect) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i)
                if (is_intersect_rectangles(circuit_input_indicator_hitbox(i), rect))
                        circuit_selection_add_element((CircuitElement) { .index = i, .type = ENN_INPUT_INDICATOR });

        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i)
                if (is_intersect_rectangles(circuit_output_indicator_hitbox(i), rect))
                        circuit_selection_add_element((CircuitElement) { .index = i, .type = ENN_OUTPUT_INDICATOR });

        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i)
                if (is_intersect_rectangles(circuit_chip_hitbox(i), rect))
                        circuit_selection_add_element((CircuitElement) { .index = i, .type = ENN_CHIP });

        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i)
                if (circuit_wire_intersects_rect(i, rect))
                        circuit_selection_add_element((CircuitElement) { .index = i, .type = ENN_EXTERNAL_WIRE });

        circuit_selection_add_connected_wires();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC bool circuit_element_hitbox(CircuitElement elem, f32vec4* hitbox) {
        DEBUG_TRACE();
        DEBUG_ASSERT(hitbox != NULL);

        switch (elem.type) {
                case ENN_INPUT_INDICATOR:
                {
                        *hitbox = circuit_input_indicator_hitbox(elem.index);
                        DEBUG_UNTRACE();
                        return true;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        *hitbox = circuit_output_indicator_hitbox(elem.index);
                        DEBUG_UNTRACE();
                        return true;
                }
                case ENN_CHIP:
                {
                        *hitbox = circuit_chip_hitbox(elem.index);
                        DEBUG_UNTRACE();
                        return true;
                }
                default: break;
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC bool circuit_wire_is_connected_to_element(ExternalWireIndex wire, CircuitElement elem) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.external_wires.end);
        ExternalWire* external_wire = &global_circuit.external_wires.data[wire];
        CircuitElement from_parent = global_circuit.external_pins.data[external_wire -> from].parent;
        CircuitElement to_parent = global_circuit.external_pins.data[external_wire -> to].parent;
        bool is_connected = circuit_elements_equal(from_parent, elem) || circuit_elements_equal(to_parent, elem);
        DEBUG_UNTRACE();
        return is_connected;
}

ENNDEF_PUBLIC bool circuit_wires_share_pin(ExternalWireIndex a, ExternalWireIndex b) {
        DEBUG_TRACE();
        DEBUG_ASSERT(a != global_circuit.external_wires.end);
        DEBUG_ASSERT(b != global_circuit.external_wires.end);
        ExternalWire* wire_a = &global_circuit.external_wires.data[a];
        ExternalWire* wire_b = &global_circuit.external_wires.data[b];
        bool share_pin = wire_a -> from == wire_b -> from ||
                         wire_a -> from == wire_b -> to ||
                         wire_a -> to == wire_b -> from ||
                         wire_a -> to == wire_b -> to;
        DEBUG_UNTRACE();
        return share_pin;
}

ENNDEF_PUBLIC bool circuit_elements_intersect(CircuitElement a, CircuitElement b) {
        DEBUG_TRACE();
        if (circuit_elements_equal(a, b)) {
                DEBUG_UNTRACE();
                return false;
        }

        f32vec4 hitbox_a;
        f32vec4 hitbox_b;
        bool has_hitbox_a = circuit_element_hitbox(a, &hitbox_a);
        bool has_hitbox_b = circuit_element_hitbox(b, &hitbox_b);

        if (has_hitbox_a && has_hitbox_b) {
                bool intersects = is_intersect_rectangles(hitbox_a, hitbox_b);
                DEBUG_UNTRACE();
                return intersects;
        }

        if (has_hitbox_a && b.type == ENN_EXTERNAL_WIRE) {
                bool intersects = !circuit_wire_is_connected_to_element(b.index, a) &&
                                  circuit_wire_intersects_rect(b.index, hitbox_a);
                DEBUG_UNTRACE();
                return intersects;
        }

        if (a.type == ENN_EXTERNAL_WIRE && has_hitbox_b) {
                bool intersects = !circuit_wire_is_connected_to_element(a.index, b) &&
                                  circuit_wire_intersects_rect(a.index, hitbox_b);
                DEBUG_UNTRACE();
                return intersects;
        }

        if (a.type == ENN_EXTERNAL_WIRE && b.type == ENN_EXTERNAL_WIRE) {
                bool intersects = !circuit_wires_share_pin(a.index, b.index) &&
                                  circuit_wires_intersect(a.index, b.index);
                DEBUG_UNTRACE();
                return intersects;
        }

        DEBUG_UNTRACE();
        return false;
}

ENNDEF_PUBLIC void circuit_selection_check_collisions(void) {
        DEBUG_TRACE();
        selection_pane.has_collision = false;

        for (i32 i = selection_pane.move_states.start; i < selection_pane.move_states.end; ++i)
                selection_pane.move_states.data[i].colliding = false;

        for (i32 i = selection_pane.move_states.start; i < selection_pane.move_states.end; ++i) {
                CircuitElement elem = selection_pane.move_states.data[i].elem;

                for (i32 j = global_circuit.input_indicators.start; j < global_circuit.input_indicators.end; ++j) {
                        CircuitElement other = (CircuitElement) { .index = j, .type = ENN_INPUT_INDICATOR };
                        if (!circuit_is_element_selected(other) && circuit_elements_intersect(elem, other)) {
                                selection_pane.move_states.data[i].colliding = true;
                                selection_pane.has_collision = true;
                                break;
                        }
                }

                if (selection_pane.move_states.data[i].colliding) continue;
                for (i32 j = global_circuit.output_indicators.start; j < global_circuit.output_indicators.end; ++j) {
                        CircuitElement other = (CircuitElement) { .index = j, .type = ENN_OUTPUT_INDICATOR };
                        if (!circuit_is_element_selected(other) && circuit_elements_intersect(elem, other)) {
                                selection_pane.move_states.data[i].colliding = true;
                                selection_pane.has_collision = true;
                                break;
                        }
                }

                if (selection_pane.move_states.data[i].colliding) continue;
                for (i32 j = global_circuit.external_chips.start; j < global_circuit.external_chips.end; ++j) {
                        CircuitElement other = (CircuitElement) { .index = j, .type = ENN_CHIP };
                        if (!circuit_is_element_selected(other) && circuit_elements_intersect(elem, other)) {
                                selection_pane.move_states.data[i].colliding = true;
                                selection_pane.has_collision = true;
                                break;
                        }
                }

                if (selection_pane.move_states.data[i].colliding) continue;
                for (i32 j = global_circuit.external_wires.start; j < global_circuit.external_wires.end; ++j) {
                        CircuitElement other = (CircuitElement) { .index = j, .type = ENN_EXTERNAL_WIRE };
                        if (!circuit_is_element_selected(other) && circuit_elements_intersect(elem, other)) {
                                selection_pane.move_states.data[i].colliding = true;
                                selection_pane.has_collision = true;
                                break;
                        }
                }
        }

        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_update_wire_endpoint(ExternalWireIndex wire) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.external_wires.end);
        ExternalWire* external_wire = &global_circuit.external_wires.data[wire];
        if (vector_size(external_wire -> anchors) >= 2) {
                external_wire -> anchors.data[external_wire -> anchors.start] = circuit_external_pin_center(external_wire -> from);
                external_wire -> anchors.data[external_wire -> anchors.end - 1] = circuit_external_pin_center(external_wire -> to);
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_update_all_wire_endpoints(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i)
                circuit_update_wire_endpoint(i);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_set_input_indicator_pos(InputIndicatorIndex indicator, f32vec2 pos) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);
        InputIndicator* input = &global_circuit.input_indicators.data[indicator];
        input -> pos = pos;
        global_circuit.external_pins.data[input -> output_pin].pos = (f32vec2) {
                .x = input -> pos.x + CIRCUIT_INDICATOR_HITBOX_WIDTH - CIRCUIT_PIN_WIDTH,
                .y = input -> pos.y + (CIRCUIT_INDICATOR_HITBOX_HEIGHT - CIRCUIT_PIN_HEIGHT) * 0.5
        };
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_set_output_indicator_pos(OutputIndicatorIndex indicator, f32vec2 pos) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.output_indicators.end);
        OutputIndicator* output = &global_circuit.output_indicators.data[indicator];
        output -> pos = pos;
        global_circuit.external_pins.data[output -> input_pin].pos = (f32vec2) {
                .x = output -> pos.x - CIRCUIT_PIN_WIDTH,
                .y = output -> pos.y + (CIRCUIT_INDICATOR_HITBOX_HEIGHT - CIRCUIT_PIN_HEIGHT) * 0.5
        };
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_set_chip_pos(ExternalChipIndex chip, f32vec2 pos) {
        DEBUG_TRACE();
        DEBUG_ASSERT(chip != global_circuit.external_chips.end);
        ExternalChip* external_chip = &global_circuit.external_chips.data[chip];
        external_chip -> pos = pos;

        i32 input_count = vector_size(external_chip -> input_pins);
        for (i32 i = external_chip -> input_pins.start; i < external_chip -> input_pins.end; ++i) {
                i32 slot = i - external_chip -> input_pins.start;
                global_circuit.external_pins.data[external_chip -> input_pins.data[i]].pos = (f32vec2) {
                        .x = external_chip -> pos.x - CIRCUIT_PIN_WIDTH,
                        .y = external_chip -> pos.y + circuit_chip_pin_offset_y(external_chip -> dim.y, input_count, slot)
                };
        }

        i32 output_count = vector_size(external_chip -> output_pins);
        for (i32 i = external_chip -> output_pins.start; i < external_chip -> output_pins.end; ++i) {
                i32 slot = i - external_chip -> output_pins.start;
                global_circuit.external_pins.data[external_chip -> output_pins.data[i]].pos = (f32vec2) {
                        .x = external_chip -> pos.x + external_chip -> dim.x,
                        .y = external_chip -> pos.y + circuit_chip_pin_offset_y(external_chip -> dim.y, output_count, slot)
                };
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_move_input_indicator(InputIndicatorIndex indicator, f32vec2 delta) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);
        InputIndicator* input = &global_circuit.input_indicators.data[indicator];
        circuit_set_input_indicator_pos(indicator, (f32vec2) { input -> pos.x + delta.x, input -> pos.y + delta.y });
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_move_output_indicator(OutputIndicatorIndex indicator, f32vec2 delta) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.output_indicators.end);
        OutputIndicator* output = &global_circuit.output_indicators.data[indicator];
        circuit_set_output_indicator_pos(indicator, (f32vec2) { output -> pos.x + delta.x, output -> pos.y + delta.y });
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_move_chip(ExternalChipIndex chip, f32vec2 delta) {
        DEBUG_TRACE();
        DEBUG_ASSERT(chip != global_circuit.external_chips.end);
        ExternalChip* external_chip = &global_circuit.external_chips.data[chip];
        circuit_set_chip_pos(chip, (f32vec2) { external_chip -> pos.x + delta.x, external_chip -> pos.y + delta.y });
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_move_wire(ExternalWireIndex wire, f32vec2 delta) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.external_wires.end);
        ExternalWire* external_wire = &global_circuit.external_wires.data[wire];
        for (i32 i = external_wire -> anchors.start + 1; i < external_wire -> anchors.end - 1; ++i) {
                external_wire -> anchors.data[i].x += delta.x;
                external_wire -> anchors.data[i].y += delta.y;
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_move_selection(f32vec2 delta) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end; ++i) {
                CircuitElement elem = global_circuit.selected_elements.data[i];
                switch (elem.type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                circuit_move_input_indicator(elem.index, delta);
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                circuit_move_output_indicator(elem.index, delta);
                                break;
                        }
                        case ENN_CHIP:
                        {
                                circuit_move_chip(elem.index, delta);
                                break;
                        }
                        default: break;
                }
        }

        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end; ++i)
                if (global_circuit.selected_elements.data[i].type == ENN_EXTERNAL_WIRE)
                        circuit_move_wire(global_circuit.selected_elements.data[i].index, delta);

        circuit_update_all_wire_endpoints();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_move_end(void) {
        DEBUG_TRACE();
        vector_clear(selection_pane.move_states);
        vector_clear(selection_pane.original_anchors);
        selection_pane.has_collision = false;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_move_begin(f32vec2 pos) {
        DEBUG_TRACE();
        circuit_selection_move_end();
        selection_pane.last_move = pos;
        global_circuit.hovered_pin = global_circuit.external_pins.end;

        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end; ++i) {
                CircuitElement elem = global_circuit.selected_elements.data[i];
                CircuitSelectionMoveState state;
                memset(&state, 0x0, (sizeof (CircuitSelectionMoveState)));
                state.elem = elem;
                state.anchor_start = selection_pane.original_anchors.end;

                switch (elem.type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                state.pos = global_circuit.input_indicators.data[elem.index].pos;
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                state.pos = global_circuit.output_indicators.data[elem.index].pos;
                                break;
                        }
                        case ENN_CHIP:
                        {
                                state.pos = global_circuit.external_chips.data[elem.index].pos;
                                break;
                        }
                        case ENN_EXTERNAL_WIRE:
                        {
                                ExternalWire* wire = &global_circuit.external_wires.data[elem.index];
                                state.anchor_count = vector_size(wire -> anchors);
                                for (i32 j = wire -> anchors.start; j < wire -> anchors.end; ++j)
                                        vector_push_back(selection_pane.original_anchors, wire -> anchors.data[j]);
                                break;
                        }
                        default:
                        {
                                continue;
                        }
                }

                vector_push_back(selection_pane.move_states, state);
        }

        circuit_selection_check_collisions();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_move_revert(void) {
        DEBUG_TRACE();
        for (i32 i = selection_pane.move_states.start; i < selection_pane.move_states.end; ++i) {
                CircuitSelectionMoveState* state = &selection_pane.move_states.data[i];
                switch (state -> elem.type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                circuit_set_input_indicator_pos(state -> elem.index, state -> pos);
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                circuit_set_output_indicator_pos(state -> elem.index, state -> pos);
                                break;
                        }
                        case ENN_CHIP:
                        {
                                circuit_set_chip_pos(state -> elem.index, state -> pos);
                                break;
                        }
                        case ENN_EXTERNAL_WIRE:
                        {
                                ExternalWire* wire = &global_circuit.external_wires.data[state -> elem.index];
                                vector_clear(wire -> anchors);
                                for (i32 j = 0; j < state -> anchor_count; ++j)
                                        vector_push_back(wire -> anchors, selection_pane.original_anchors.data[state -> anchor_start + j]);
                                break;
                        }
                        default: break;
                }
        }

        circuit_update_all_wire_endpoints();
        circuit_selection_move_end();
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_destroy(void) {
        DEBUG_TRACE();
        circuit_selection_move_end();
        while (vector_size(global_circuit.selected_elements) > 0) {
                CircuitElement elem = global_circuit.selected_elements.data[global_circuit.selected_elements.end - 1];
                vector_pop_back(global_circuit.selected_elements);
                switch (elem.type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                circuit_destroy_input_indicator(elem.index);
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                circuit_destroy_output_indicator(elem.index);
                                break;
                        }
                        case ENN_CHIP:
                        {
                                circuit_destroy_chip(elem.index);
                                break;
                        }
                        case ENN_EXTERNAL_WIRE:
                        {
                                circuit_destroy_external_wire(elem.index);
                                break;
                        }
                        default: break;
                }
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC f32vec2 circuit_magnetize_line(f32vec2 p1, f32vec2 p2, f32 threshold) {
        f32 dx = p2.x - p1.x;
        f32 dy = p2.y - p1.y;
        f32 len = sqrtf(dx * dx + dy * dy);

        if (len == 0.0) return p2;

        f32 angle = atan2f(dy, dx);
        const f32 snap_interval = 0.785398163;
        f32 snapped_angle = roundf(angle / snap_interval) * snap_interval;

        if (fabsf(angle - snapped_angle) > threshold * 0.392699082) return p2;

        return (f32vec2) {
                .x = p1.x + len * cosf(snapped_angle),
                .y = p1.y + len * sinf(snapped_angle)
        };
}

#endif
