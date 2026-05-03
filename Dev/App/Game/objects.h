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
#define CIRCUIT_INDICATOR_OVERLAY_COLOR                 0xFFFFFF80
#define CIRCUIT_INDICATOR_OVERLAY_COLLISION_COLOR       0xcc241d80
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
#define CIRCUIT_CHIP_OVERLAY_COLOR                      0xFFFFFF80
#define CIRCUIT_CHIP_OVERLAY_COLLISION_COLOR       0xcc241d80
#define CIRCUIT_CHIP_OVERLAY_PADDING                    2

#define CIRCUIT_SELECTION_BOX_COLOR                     0xFFFFFF50

#define CIRCUIT_ELEMENT_OVERLAY_COLOR                   0xFFFFFF80

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
} Circuit;

extern Circuit global_circuit;

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
                return global_circuit.external_pins.end;
        }

        ExternalWire new_wire; memset(&new_wire, 0x0, (sizeof (ExternalWire)));
        new_wire.color = circuit_get_pin_color(from);
        if (global_circuit.external_pins.data[from].type == ENN_INPUT_PIN) swap(from, to);

        new_wire.id = global_circuit.external_wires.end;
        new_wire.internal = circuit_summon_internal_wire(global_circuit.external_pins.data[from].internal, global_circuit.external_pins.data[to].internal);
        new_wire.from = from;
        new_wire.to = to;
        if (anchor_count > 0 && anchors != NULL) {
                vector_reserve(new_wire.anchors, anchor_count);
                memcpy(new_wire.anchors.data + new_wire.anchors.start, anchors, (sizeof (f32vec2)) * anchor_count);
                new_wire.anchors.end += anchor_count;
        }
        vector_push_back(global_circuit.external_wires, new_wire);
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
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_internal_pin(InternalPinIndex pin) {
        DEBUG_TRACE();
        DEBUG_ASSERT(pin != global_circuit.internal_pins.end);
        vector_destroy(global_circuit.internal_pins.data[pin].connections);
        memset(&global_circuit.internal_pins.data[pin], 0x0, (sizeof (InternalPin)));
        vector_remove_at_index(global_circuit.internal_pins, pin);

        switch (global_circuit.internal_pins.data[pin].parent.type) {
                case ENN_EXTERNAL_PIN:
                {
                        global_circuit.external_pins.data[global_circuit.internal_pins.data[pin].parent.index].internal = pin; 
                        break;
                }
                default: break;
        }
        
        for (i32 i = global_circuit.internal_pins.data[pin].connections.start; i < global_circuit.internal_pins.data[pin].connections.start; ++i) {
                InternalWire* wire = &global_circuit.internal_wires.data[global_circuit.internal_pins.data[pin].connections.data[i]];
                if (wire -> from == global_circuit.internal_pins.data[pin].id) wire -> from = pin;
                else wire -> to = pin;
                
        }

        global_circuit.internal_pins.data[pin].id = pin;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_internal_wire(InternalWireIndex wire) {
        DEBUG_TRACE();
        DEBUG_ASSERT(wire != global_circuit.internal_wires.end);
        
        InternalPin* from = &global_circuit.internal_pins.data[global_circuit.internal_wires.data[wire].from];
        for (i32 i = from -> connections.start; i < from -> connections.end; ++i) {
                if (from -> connections.data[i] == wire) {
                        vector_remove_at_index(from -> connections, i);
                        break;
                }
        }

        InternalPin* to = &global_circuit.internal_pins.data[global_circuit.internal_wires.data[wire].to];
        for (i32 i = to -> connections.start; i < to -> connections.end; ++i) {
                if (to -> connections.data[i] == wire) {
                        vector_remove_at_index(to -> connections, i);
                        break;
                }
        }

        memset(&global_circuit.internal_wires.data[wire], 0x0, (sizeof (InternalWire)));
        vector_remove_at_index(global_circuit.internal_wires, wire);

        from = &global_circuit.internal_pins.data[global_circuit.internal_wires.data[wire].from];
        to = &global_circuit.internal_pins.data[global_circuit.internal_wires.data[wire].to];
        for (i32 i = from -> connections.start; i < from -> connections.end; ++i)
                if (from -> connections.data[i] == global_circuit.internal_wires.data[wire].id) {
                        from -> connections.data[i] = wire;
                        break;
                }

        for (i32 i = to -> connections.start; i < to -> connections.end; ++i)
                if (to -> connections.data[i] == global_circuit.internal_wires.data[wire].id) {
                        to -> connections.data[i] = wire;
                        break;
                }

        global_circuit.internal_wires.data[wire].id = wire;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_external_pin(ExternalPinIndex pin) {
        DEBUG_TRACE();
        DEBUG_ASSERT(pin != global_circuit.external_pins.end);
        vector_destroy(global_circuit.external_pins.data[pin].connections);
        circuit_destroy_internal_pin(global_circuit.external_pins.data[pin].internal);
        memset(&global_circuit.external_pins.data[pin], 0x0, (sizeof (InternalPin)));
        vector_remove_at_index(global_circuit.external_pins, pin);

        switch (global_circuit.external_pins.data[pin].parent.type) {
                case ENN_INPUT_INDICATOR:
                {
                        global_circuit.input_indicators.data[global_circuit.external_pins.data[pin].parent.index].output_pin = pin; 
                        break;
                }
                case ENN_OUTPUT_INDICATOR:
                {
                        global_circuit.output_indicators.data[global_circuit.external_pins.data[pin].parent.index].input_pin = pin; 
                        break;
                }
                case ENN_CHIP:
                {
                        switch (global_circuit.external_pins.data[pin].type) {
                                case ENN_INPUT_PIN:
                                {
                                        ExternalChip* chip = &global_circuit.external_chips.data[global_circuit.external_pins.data[pin].parent.index];
                                        for (i32 i = chip -> input_pins.start; i < chip -> input_pins.end; ++i)
                                                if (chip -> input_pins.data[i] == global_circuit.external_pins.data[pin].id) {
                                                        chip -> input_pins.data[i] = pin;
                                                        break;
                                                }
                                        break;
                                }
                                case ENN_OUTPUT_PIN:
                                {
                                        ExternalChip* chip = &global_circuit.external_chips.data[global_circuit.external_pins.data[pin].parent.index];
                                        for (i32 i = chip -> output_pins.start; i < chip -> output_pins.end; ++i)
                                                if (chip -> output_pins.data[i] == global_circuit.external_pins.data[pin].id) {
                                                        chip -> output_pins.data[i] = pin;
                                                        break;
                                                }
                                        break;
                                }
                                default: break;
                        }
                        break;
                }
                default: break;
        }
        
        for (i32 i = global_circuit.external_pins.data[pin].connections.start; i < global_circuit.external_pins.data[pin].connections.start; ++i) {
                InternalWire* wire = &global_circuit.internal_wires.data[global_circuit.external_pins.data[pin].connections.data[i]];
                if (wire -> from == global_circuit.external_pins.data[pin].id) wire -> from = pin;
                else wire -> to = pin;
                
        }

        global_circuit.external_pins.data[pin].id = pin;
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_input_indicator(InputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.input_indicators.end);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_output_indicator(OutputIndicatorIndex indicator) {
        DEBUG_TRACE();
        DEBUG_ASSERT(indicator != global_circuit.output_indicators.end);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_destroy_chip(ExternalChipIndex chip) {
        DEBUG_TRACE();
        DEBUG_ASSERT(chip != global_circuit.external_chips.end);
        DEBUG_UNTRACE();
}


ENNDEF_PUBLIC void circuit_update_tick(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.internal_wires.start; i < global_circuit.internal_wires.end; ++i) {
                InternalPinIndex from   = global_circuit.external_wires.data[i].from;
                InternalPinIndex to     = global_circuit.external_wires.data[i].to;
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
        DEBUG_UNTRACE();
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

ENNDEF_PUBLIC void circuit_render_chips(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                render_rectangle_push(
                        global_circuit.external_chips.data[i].pos,
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x, global_circuit.external_chips.data[i].pos.y + global_circuit.external_chips.data[i].dim.y },
                        color_dark_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].color)
                );
                render_rectangle_push(
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + CIRCUIT_CHIP_BORDER_PADDING, global_circuit.external_chips.data[i].pos.y + CIRCUIT_CHIP_BORDER_PADDING },
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x - CIRCUIT_CHIP_BORDER_PADDING, global_circuit.external_chips.data[i].pos.y + global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_BORDER_PADDING },
                        color_light_dark_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].color)
                );
                render_text_push_width(
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + CIRCUIT_CHIP_NAME_PADDING, global_circuit.external_chips.data[i].pos.y + (global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_NAME_TEXT_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x - CIRCUIT_CHIP_NAME_PADDING, global_circuit.external_chips.data[i].pos.y + (global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_NAME_TEXT_HEIGHT) * 0.5 },
                        global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].name, CIRCUIT_CHIP_NAME_TEXT_COLOR, CIRCUIT_CHIP_NAME_TEXT_HEIGHT, CIRCUIT_CHIP_NAME_TEXT_WIDTH, ENN_CENTER_ALIGN
                );
        }
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_render_selection_overlay(void) {
        DEBUG_TRACE();
        for (i32 idx = global_circuit.selected_elements.start; idx < global_circuit.selected_elements.end; ++idx) {
                CircuitElement elem = global_circuit.selected_elements.data[idx];
                if (elem.type == ENN_INPUT_INDICATOR) {
                        render_rectangle_push(
                                (f32vec2) { global_circuit.input_indicators.data[elem.index].pos.x - CIRCUIT_INDICATOR_OVERLAY_PADDING, global_circuit.input_indicators.data[elem.index].pos.y - CIRCUIT_INDICATOR_OVERLAY_PADDING },
                                (f32vec2) { global_circuit.input_indicators.data[elem.index].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_PIN_WIDTH + CIRCUIT_INDICATOR_OVERLAY_PADDING, global_circuit.input_indicators.data[elem.index].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_OVERLAY_PADDING },
                                CIRCUIT_ELEMENT_OVERLAY_COLOR
                        );
                } else if (elem.type == ENN_OUTPUT_INDICATOR) {
                        render_rectangle_push(
                                (f32vec2) { global_circuit.output_indicators.data[elem.index].pos.x - CIRCUIT_PIN_WIDTH - CIRCUIT_INDICATOR_OVERLAY_PADDING, global_circuit.output_indicators.data[elem.index].pos.y - CIRCUIT_INDICATOR_OVERLAY_PADDING },
                                (f32vec2) { global_circuit.output_indicators.data[elem.index].pos.x + CIRCUIT_INDICATOR_CONNECTOR_WIDTH + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_OVERLAY_PADDING, global_circuit.output_indicators.data[elem.index].pos.y + CIRCUIT_INDICATOR_BODY_HEIGHT + CIRCUIT_INDICATOR_OVERLAY_PADDING },
                                CIRCUIT_ELEMENT_OVERLAY_COLOR
                        );
                } else if (elem.type == ENN_CHIP) {
                        render_rectangle_push(
                                (f32vec2) { global_circuit.external_chips.data[elem.index].pos.x - CIRCUIT_PIN_WIDTH - CIRCUIT_CHIP_OVERLAY_PADDING, global_circuit.external_chips.data[elem.index].pos.y - CIRCUIT_CHIP_OVERLAY_PADDING },
                                (f32vec2) { global_circuit.external_chips.data[elem.index].pos.x + global_circuit.external_chips.data[elem.index].dim.x + CIRCUIT_PIN_WIDTH + CIRCUIT_CHIP_OVERLAY_PADDING, global_circuit.external_chips.data[elem.index].pos.y + global_circuit.external_chips.data[elem.index].dim.y + CIRCUIT_CHIP_OVERLAY_PADDING },
                                CIRCUIT_ELEMENT_OVERLAY_COLOR
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
                if (elem.type == global_circuit.selected_elements.data[i].type && elem.index == global_circuit.selected_elements.data[i].index) {
                        DEBUG_UNTRACE();
                        return true;
                }
        return false;
        DEBUG_UNTRACE();
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

ENNDEF_PUBLIC void circuit_selection_clear(void) {
        DEBUG_TRACE();
        vector_clear(global_circuit.selected_elements);
        DEBUG_UNTRACE();
}

ENNDEF_PUBLIC void circuit_selection_destroy(void) {
        DEBUG_TRACE();
        for (i32 i = global_circuit.selected_elements.start; i < global_circuit.selected_elements.end; ++i) {
                switch (global_circuit.selected_elements.data[i].type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                break;
                        }
                        case ENN_CHIP:
                        {
                                break;
                        }
                        case ENN_EXTERNAL_WIRE:
                        {
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