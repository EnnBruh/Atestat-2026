#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "layer.h"

#define CIRCUIT_PIN_WIDTH                               2
#define CIRCUIT_PIN_HEIGHT                              3
#define CIRCUIT_PIN_COLOR                               0x202020FF
#define CIRCUIT_PIN_HOVER_COLOR                         0xFFFFFFFF

#define CIRCUIT_WIRE_WIDTH                              1.5

#define CIRCUIT_INDICATOR_BODY_WIDTH                    10
#define CIRCUIT_INDICATOR_BODY_HEIGHT                   10
#define CIRCUIT_INDICATOR_CONNECTOR_WIDTH               4
#define CIRCUIT_INDICATOR_CONNECTOR_HEIGHT              1.25
#define CIRCUIT_INDICATOR_CONNECTOR_COLOR               CIRCUIT_PIN_COLOR
#define CIRCUIT_INDICATOR_HARD_BORDER_PADDING           0.75
#define CIRCUIT_INDICATOR_SOFT_BORDER_PADDING           0.75
#define CIRCUIT_INDICATOR_HARD_BORDER_COLOR             CIRCUIT_PIN_COLOR
#define CIRCUIT_INDICATOR_OVERLAY_COLOR                 0xFFFFFF80
#define CIRCUIT_INDICATOR_OVERLAY_PADDING               2

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
#define CIRCUIT_CHIP_NAME_PADDING                       3
#define CIRCUIT_CHIP_NAME_TEXT_HEIGHT                   3
#define CIRCUIT_CHIP_NAME_TEXT_COLOR                    0xFFFFFFFF
#define CIRCUIT_CHIP_PIN_PADDING                        2
#define CIRCUIT_CHIP_MAX_NAME_LEN                       128
#define CIRCUIT_CHIP_OVERLAY_COLOR                      0xFFFFFF80
#define CIRCUIT_CHIP_OVERLAY_PADDING                    2

#define CIRCUIT_SELECTION_BOX_COLOR                     0xFFFFFF50

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
        bool    curr_state : 1;
        bool    next_state : 1;
} InternalPin;

typedef struct InternalWire {
        InternalPinIndex from;
        InternalPinIndex to;
} InternalWire;

typedef struct InternalNANDGate {
        InternalPinIndex input_a;
        InternalPinIndex input_b;
        InternalPinIndex output;
} InternalNANDGate;

typedef struct ExternalPin {
        InternalPinIndex        internal;
        f32vec2                 pos;
        CircuitElement          parent;
} ExternalPin;

typedef struct ExternalWire {
        InternalWireIndex       internal;
        ExternalPinIndex        from;
        ExternalPinIndex        to;
        vector(f32vec2)         anchors;
} ExternalWire;

typedef struct BlueprintSubChip {
        BlueprintChipIndex      blueprint_id;
} BlueprintSubChip;

typedef struct BlueprintWire {
        i32                     from_sub_chip;
        i32                     from_pin;
        i32                     to_sub_chip;
        i32                     to_pin;
} BlueprintWire;

typedef struct BlueprintChip {
        char                            name[CIRCUIT_CHIP_MAX_NAME_LEN];
        ENN_CIRCUIT_ELEMENT_COLORS      color;
        i32                             num_inputs;
        i32                             num_outputs; 

        vector(BlueprintSubChip)        sub_chips;
        vector(BlueprintWire)           wires;
} BlueprintChip;

typedef struct ExternalChip {
        BlueprintChipIndex              blueprint;
        f32vec2                         pos;
        f32vec2                         dim;
} ExternalChip;

typedef struct InputIndicator {
        f32vec2                         pos;
        ExternalPinIndex                output_pin;
        ENN_CIRCUIT_ELEMENT_COLORS      color;
} InputIndicator;

typedef struct OutputIndicator {
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

ENNDEF_PUBLIC void circuit_render_pins(void) {
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i) {
                render_rectangle_push(
                        global_circuit.external_pins.data[i].pos,
                        (f32vec2) { global_circuit.external_pins.data[i].pos.x + CIRCUIT_PIN_WIDTH, global_circuit.external_pins.data[i].pos.y + CIRCUIT_PIN_HEIGHT },
                        CIRCUIT_PIN_COLOR
                );
        }

        if (global_circuit.hovered_pin != global_circuit.external_pins.end) 
                render_rectangle_push(
                        global_circuit.external_pins.data[global_circuit.hovered_pin].pos,
                        (f32vec2) { global_circuit.external_pins.data[global_circuit.hovered_pin].pos.x + CIRCUIT_PIN_WIDTH, global_circuit.external_pins.data[global_circuit.hovered_pin].pos.y + CIRCUIT_PIN_HEIGHT },
                        CIRCUIT_PIN_HOVER_COLOR
                );
}

ENNDEF_PUBLIC void circuit_render_wires(void) {
        for (i32 i = global_circuit.external_wires.start; i < global_circuit.external_wires.end; ++i) {
                u32 color = 0xFFFFFFFF;
                const ExternalPin* pin = &global_circuit.external_pins.data[global_circuit.external_wires.data[i].from];
                switch (pin -> parent.type) {
                        case ENN_INPUT_INDICATOR:
                        {
                                if (global_circuit.internal_pins.data[pin -> internal].curr_state)
                                        color = color_light_get_by_circuit_color(global_circuit.input_indicators.data[pin -> parent.index].color);
                                else 
                                        color = color_dark_get_by_circuit_color(global_circuit.input_indicators.data[pin -> parent.index].color);
                                break;
                        }
                        case ENN_OUTPUT_INDICATOR:
                        {
                                if (global_circuit.internal_pins.data[pin -> internal].curr_state)
                                        color = color_light_get_by_circuit_color(global_circuit.output_indicators.data[pin -> parent.index].color);
                                else 
                                        color = color_dark_get_by_circuit_color(global_circuit.output_indicators.data[pin -> parent.index].color);
                                break;
                        }
                        case ENN_CHIP:
                        {
                                if (global_circuit.internal_pins.data[pin -> internal].curr_state)
                                        color = color_light_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[pin -> parent.index].blueprint].color);
                                else 
                                        color = color_dark_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[pin -> parent.index].blueprint].color);
                                break;
                        }
                        default: break;
                }
                render_multiline_push(
                        global_circuit.external_wires.data[i].anchors.data + global_circuit.external_wires.data[i].anchors.start,
                        vector_size(global_circuit.external_wires.data[i].anchors), 
                        CIRCUIT_PIN_WIDTH,
                        color
                );
        }
}

ENNDEF_PUBLIC void circuit_render_input_indicators(void) {
        for (i32 i = global_circuit.input_indicators.start; i < global_circuit.input_indicators.end; ++i) {
                // render_sprite_push(
                //         global_circuit.input_indicators.data[i].pos,
                //         (f32vec2) { global_circuit.input_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.input_indicators.data[i].pos.y + max(CIRCUIT_INDICATOR_BODY_HEIGHT, CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) },
                //         &indicator_sprites[global_circuit.input_indicators.data[i].color]
                // );

                
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
}

ENNDEF_PUBLIC void circuit_render_output_indicators(void) {
        for (i32 i = global_circuit.output_indicators.start; i < global_circuit.output_indicators.end; ++i) {
                // render_sprite_push(
                //         global_circuit.output_indicators.data[i].pos,
                //         (f32vec2) { global_circuit.output_indicators.data[i].pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH, global_circuit.output_indicators.data[i].pos.y + max(CIRCUIT_INDICATOR_BODY_HEIGHT, CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) },
                //         &indicator_sprites[global_circuit.output_indicators.data[i].color]
                // );

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
}

ENNDEF_PUBLIC void circuit_render_chips(void) {
        for (i32 i = global_circuit.external_chips.start; i < global_circuit.external_chips.end; ++i) {
                render_rectangle_push(
                        global_circuit.external_chips.data[i].pos,
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x, global_circuit.external_chips.data[i].pos.y + global_circuit.external_chips.data[i].dim.y },
                        color_dark_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].color)
                );

                render_rectangle_push(
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + CIRCUIT_CHIP_BORDER_PADDING, global_circuit.external_chips.data[i].pos.y + CIRCUIT_CHIP_BORDER_PADDING },
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x - CIRCUIT_CHIP_BORDER_PADDING, global_circuit.external_chips.data[i].pos.y + global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_BORDER_PADDING },
                        color_light_get_by_circuit_color(global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].color)
                );

                render_text_push(
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + CIRCUIT_CHIP_NAME_PADDING, global_circuit.external_chips.data[i].pos.y + (global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_NAME_TEXT_HEIGHT) * 0.5 },
                        (f32vec2) { global_circuit.external_chips.data[i].pos.x + global_circuit.external_chips.data[i].dim.x - CIRCUIT_CHIP_NAME_PADDING, global_circuit.external_chips.data[i].pos.y + (global_circuit.external_chips.data[i].dim.y - CIRCUIT_CHIP_NAME_TEXT_HEIGHT) * 0.5 },
                        global_circuit.blueprints.data[global_circuit.external_chips.data[i].blueprint].name, CIRCUIT_CHIP_NAME_TEXT_COLOR, CIRCUIT_CHIP_NAME_TEXT_HEIGHT, ENN_CENTER_ALIGN
                );
        }
}

ENNDEF_PUBLIC void circuit_render_objects(void) {
        circuit_render_wires();
        circuit_render_pins();
        circuit_render_chips();
        circuit_render_input_indicators();
        circuit_render_output_indicators();
}

ENNDEF_PUBLIC InputIndicatorIndex circuit_summon_input_indicator(f32vec2 pos, ENN_CIRCUIT_ELEMENT_COLORS color) {
        InputIndicator indicator;
        indicator.pos = pos;
        indicator.color = color;

        InternalPin internal_pin;
        internal_pin.curr_state = false;
        internal_pin.next_state = false;

        vector_push_back(global_circuit.internal_pins, internal_pin);
        InternalPinIndex internal_idx = vector_size(global_circuit.internal_pins) - 1;

        InputIndicatorIndex indicator_idx = vector_size(global_circuit.input_indicators);

        ExternalPin ext_pin;
        ext_pin.internal = internal_idx;
        ext_pin.pos = (f32vec2){
                pos.x + CIRCUIT_INDICATOR_BODY_WIDTH + CIRCUIT_INDICATOR_CONNECTOR_WIDTH,
                pos.y + max(CIRCUIT_INDICATOR_BODY_HEIGHT, CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5f - CIRCUIT_PIN_HEIGHT * 0.5f
        };
        ext_pin.parent.index = indicator_idx;
        ext_pin.parent.type = ENN_INPUT_INDICATOR;

        vector_push_back(global_circuit.external_pins, ext_pin);
        indicator.output_pin = vector_size(global_circuit.external_pins) - 1;

        vector_push_back(global_circuit.input_indicators, indicator);
        
        return indicator_idx;
}

ENNDEF_PUBLIC OutputIndicatorIndex circuit_summon_output_indicator(f32vec2 pos, ENN_CIRCUIT_ELEMENT_COLORS color) {
        OutputIndicator indicator;
        indicator.pos = pos;
        indicator.color = color;

        InternalPin internal_pin;
        internal_pin.curr_state = false;
        internal_pin.next_state = false;

        vector_push_back(global_circuit.internal_pins, internal_pin);
        InternalPinIndex internal_idx = vector_size(global_circuit.internal_pins) - 1;

        OutputIndicatorIndex indicator_idx = vector_size(global_circuit.output_indicators);

        ExternalPin ext_pin;
        ext_pin.internal = internal_idx;
        ext_pin.pos = (f32vec2){
                pos.x - CIRCUIT_PIN_WIDTH,
                pos.y + max(CIRCUIT_INDICATOR_BODY_HEIGHT, CIRCUIT_INDICATOR_CONNECTOR_HEIGHT) * 0.5f - CIRCUIT_PIN_HEIGHT * 0.5f
        };
        ext_pin.parent.index = indicator_idx;
        ext_pin.parent.type = ENN_OUTPUT_INDICATOR;

        vector_push_back(global_circuit.external_pins, ext_pin);
        indicator.input_pin = vector_size(global_circuit.external_pins) - 1;

        vector_push_back(global_circuit.output_indicators, indicator);
        
        return indicator_idx;
}

ENNDEF_PUBLIC ExternalChipIndex circuit_summon_chip(f32vec2 pos, BlueprintChipIndex blueprint) {
        ExternalChip chip;
        chip.blueprint = blueprint;
        chip.pos = pos;
        
        BlueprintChip* bp = &global_circuit.blueprints.data[blueprint];

        f32 max_pins = max(bp -> num_inputs, bp -> num_outputs);
        chip.dim = (f32vec2){ 40.0f, max_pins * (CIRCUIT_PIN_HEIGHT + CIRCUIT_CHIP_PIN_PADDING) + CIRCUIT_CHIP_PIN_PADDING };

        ExternalChipIndex chip_idx = vector_size(global_circuit.external_chips);

        for (i32 i = 0; i < bp -> num_inputs; ++i) {
                InternalPin internal_pin;
                internal_pin.curr_state = false;
                internal_pin.next_state = false;
                vector_push_back(global_circuit.internal_pins, internal_pin);
                InternalPinIndex internal_idx = vector_size(global_circuit.internal_pins) - 1;

                ExternalPin ext_pin;
                ext_pin.internal = internal_idx;
                ext_pin.pos = (f32vec2){
                        pos.x - CIRCUIT_PIN_WIDTH,
                        pos.y + CIRCUIT_CHIP_PIN_PADDING + i * (CIRCUIT_PIN_HEIGHT + CIRCUIT_CHIP_PIN_PADDING)
                };
                ext_pin.parent.index = chip_idx;
                ext_pin.parent.type = ENN_CHIP;
                vector_push_back(global_circuit.external_pins, ext_pin);
        }

        for (i32 i = 0; i < bp -> num_outputs; ++i) {
                InternalPin internal_pin;
                internal_pin.curr_state = false;
                internal_pin.next_state = false;
                vector_push_back(global_circuit.internal_pins, internal_pin);
                InternalPinIndex internal_idx = vector_size(global_circuit.internal_pins) - 1;

                ExternalPin ext_pin;
                ext_pin.internal = internal_idx;
                ext_pin.pos = (f32vec2){
                        pos.x + chip.dim.x,
                        pos.y + CIRCUIT_CHIP_PIN_PADDING + i * (CIRCUIT_PIN_HEIGHT + CIRCUIT_CHIP_PIN_PADDING)
                };
                ext_pin.parent.index = chip_idx;
                ext_pin.parent.type = ENN_CHIP;
                vector_push_back(global_circuit.external_pins, ext_pin);
        }

        vector_push_back(global_circuit.external_chips, chip);

        return chip_idx;
}

ENNDEF_PUBLIC ExternalWireIndex circuit_summon_wire(ExternalPinIndex from, ExternalPinIndex to) {
        ExternalWire wire;
        wire.from = from;
        wire.to = to;
        wire.anchors.data = NULL;
        wire.anchors.capacity = 0;
        wire.anchors.start = 0;
        wire.anchors.end = 0;

        InternalWire internal_wire;
        internal_wire.from = global_circuit.external_pins.data[from].internal;
        internal_wire.to = global_circuit.external_pins.data[to].internal;

        vector_push_back(global_circuit.internal_wires, internal_wire);
        wire.internal = vector_size(global_circuit.internal_wires) - 1;

        vector_push_back(global_circuit.external_wires, wire);
        
        return vector_size(global_circuit.external_wires) - 1;
}

ENNDEF_PUBLIC void circuit_destroy_wire(ExternalWireIndex index) {
        InternalWireIndex internal_idx = global_circuit.external_wires.data[index].internal;
        
        if (global_circuit.external_wires.data[index].anchors.capacity > 0) {
                free(global_circuit.external_wires.data[index].anchors.data);
        }

        InternalWireIndex last_iw = global_circuit.internal_wires.end - 1;
        vector_remove_at_index(global_circuit.internal_wires, internal_idx);
        if (internal_idx != last_iw) {
                for (i32 j = global_circuit.external_wires.start; j < global_circuit.external_wires.end; ++j) {
                        if (global_circuit.external_wires.data[j].internal == last_iw) {
                                global_circuit.external_wires.data[j].internal = internal_idx;
                                break;
                        }
                }
        }

        vector_remove_at_index(global_circuit.external_wires, index);
}

ENNDEF_PUBLIC void circuit_destroy_input_indicator(InputIndicatorIndex index) {
        ExternalPinIndex ext_pin = global_circuit.input_indicators.data[index].output_pin;
        InternalPinIndex int_pin = global_circuit.external_pins.data[ext_pin].internal;

        for (i32 j = global_circuit.external_wires.end - 1; j >= global_circuit.external_wires.start; --j) {
                if (global_circuit.external_wires.data[j].from == ext_pin || global_circuit.external_wires.data[j].to == ext_pin) {
                        circuit_destroy_wire(j);
                }
        }

        InternalPinIndex last_ip = global_circuit.internal_pins.end - 1;
        vector_remove_at_index(global_circuit.internal_pins, int_pin);
        if (int_pin != last_ip) {
                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                        if (global_circuit.external_pins.data[k].internal == last_ip) {
                                global_circuit.external_pins.data[k].internal = int_pin;
                                break;
                        }
                }
                for (i32 k = global_circuit.internal_wires.start; k < global_circuit.internal_wires.end; ++k) {
                        if (global_circuit.internal_wires.data[k].from == last_ip) global_circuit.internal_wires.data[k].from = int_pin;
                        if (global_circuit.internal_wires.data[k].to == last_ip) global_circuit.internal_wires.data[k].to = int_pin;
                }
                for (i32 k = global_circuit.internal_gates.start; k < global_circuit.internal_gates.end; ++k) {
                        if (global_circuit.internal_gates.data[k].input_a == last_ip) global_circuit.internal_gates.data[k].input_a = int_pin;
                        if (global_circuit.internal_gates.data[k].input_b == last_ip) global_circuit.internal_gates.data[k].input_b = int_pin;
                        if (global_circuit.internal_gates.data[k].output == last_ip) global_circuit.internal_gates.data[k].output = int_pin;
                }
        }

        ExternalPinIndex last_ep = global_circuit.external_pins.end - 1;
        vector_remove_at_index(global_circuit.external_pins, ext_pin);
        if (ext_pin != last_ep) {
                for (i32 k = global_circuit.external_wires.start; k < global_circuit.external_wires.end; ++k) {
                        if (global_circuit.external_wires.data[k].from == last_ep) global_circuit.external_wires.data[k].from = ext_pin;
                        if (global_circuit.external_wires.data[k].to == last_ep) global_circuit.external_wires.data[k].to = ext_pin;
                }
                for (i32 k = global_circuit.input_indicators.start; k < global_circuit.input_indicators.end; ++k) {
                        if (global_circuit.input_indicators.data[k].output_pin == last_ep) {
                                global_circuit.input_indicators.data[k].output_pin = ext_pin;
                                break;
                        }
                }
                for (i32 k = global_circuit.output_indicators.start; k < global_circuit.output_indicators.end; ++k) {
                        if (global_circuit.output_indicators.data[k].input_pin == last_ep) {
                                global_circuit.output_indicators.data[k].input_pin = ext_pin;
                                break;
                        }
                }
        }

        InputIndicatorIndex last_ind = global_circuit.input_indicators.end - 1;
        vector_remove_at_index(global_circuit.input_indicators, index);
        if (index != last_ind) {
                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                        if (global_circuit.external_pins.data[k].parent.type == ENN_INPUT_INDICATOR && global_circuit.external_pins.data[k].parent.index == last_ind) {
                                global_circuit.external_pins.data[k].parent.index = index;
                                break;
                        }
                }
        }
}

ENNDEF_PUBLIC void circuit_destroy_output_indicator(OutputIndicatorIndex index) {
        ExternalPinIndex ext_pin = global_circuit.output_indicators.data[index].input_pin;
        InternalPinIndex int_pin = global_circuit.external_pins.data[ext_pin].internal;

        for (i32 j = global_circuit.external_wires.end - 1; j >= global_circuit.external_wires.start; --j) {
                if (global_circuit.external_wires.data[j].from == ext_pin || global_circuit.external_wires.data[j].to == ext_pin) {
                        circuit_destroy_wire(j);
                }
        }

        InternalPinIndex last_ip = global_circuit.internal_pins.end - 1;
        vector_remove_at_index(global_circuit.internal_pins, int_pin);
        if (int_pin != last_ip) {
                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                        if (global_circuit.external_pins.data[k].internal == last_ip) {
                                global_circuit.external_pins.data[k].internal = int_pin;
                                break;
                        }
                }
                for (i32 k = global_circuit.internal_wires.start; k < global_circuit.internal_wires.end; ++k) {
                        if (global_circuit.internal_wires.data[k].from == last_ip) global_circuit.internal_wires.data[k].from = int_pin;
                        if (global_circuit.internal_wires.data[k].to == last_ip) global_circuit.internal_wires.data[k].to = int_pin;
                }
                for (i32 k = global_circuit.internal_gates.start; k < global_circuit.internal_gates.end; ++k) {
                        if (global_circuit.internal_gates.data[k].input_a == last_ip) global_circuit.internal_gates.data[k].input_a = int_pin;
                        if (global_circuit.internal_gates.data[k].input_b == last_ip) global_circuit.internal_gates.data[k].input_b = int_pin;
                        if (global_circuit.internal_gates.data[k].output == last_ip) global_circuit.internal_gates.data[k].output = int_pin;
                }
        }

        ExternalPinIndex last_ep = global_circuit.external_pins.end - 1;
        vector_remove_at_index(global_circuit.external_pins, ext_pin);
        if (ext_pin != last_ep) {
                for (i32 k = global_circuit.external_wires.start; k < global_circuit.external_wires.end; ++k) {
                        if (global_circuit.external_wires.data[k].from == last_ep) global_circuit.external_wires.data[k].from = ext_pin;
                        if (global_circuit.external_wires.data[k].to == last_ep) global_circuit.external_wires.data[k].to = ext_pin;
                }
                for (i32 k = global_circuit.input_indicators.start; k < global_circuit.input_indicators.end; ++k) {
                        if (global_circuit.input_indicators.data[k].output_pin == last_ep) {
                                global_circuit.input_indicators.data[k].output_pin = ext_pin;
                                break;
                        }
                }
                for (i32 k = global_circuit.output_indicators.start; k < global_circuit.output_indicators.end; ++k) {
                        if (global_circuit.output_indicators.data[k].input_pin == last_ep) {
                                global_circuit.output_indicators.data[k].input_pin = ext_pin;
                                break;
                        }
                }
        }

        OutputIndicatorIndex last_ind = global_circuit.output_indicators.end - 1;
        vector_remove_at_index(global_circuit.output_indicators, index);
        if (index != last_ind) {
                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                        if (global_circuit.external_pins.data[k].parent.type == ENN_OUTPUT_INDICATOR && global_circuit.external_pins.data[k].parent.index == last_ind) {
                                global_circuit.external_pins.data[k].parent.index = index;
                                break;
                        }
                }
        }
}

ENNDEF_PUBLIC void circuit_destroy_chip(ExternalChipIndex index) {
        for (i32 i = global_circuit.external_pins.end - 1; i >= global_circuit.external_pins.start; --i) {
                if (global_circuit.external_pins.data[i].parent.type == ENN_CHIP && global_circuit.external_pins.data[i].parent.index == index) {
                        ExternalPinIndex ext_pin = i;
                        InternalPinIndex int_pin = global_circuit.external_pins.data[i].internal;

                        for (i32 j = global_circuit.external_wires.end - 1; j >= global_circuit.external_wires.start; --j) {
                                if (global_circuit.external_wires.data[j].from == ext_pin || global_circuit.external_wires.data[j].to == ext_pin) {
                                        circuit_destroy_wire(j);
                                }
                        }

                        InternalPinIndex last_ip = global_circuit.internal_pins.end - 1;
                        vector_remove_at_index(global_circuit.internal_pins, int_pin);
                        if (int_pin != last_ip) {
                                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                                        if (global_circuit.external_pins.data[k].internal == last_ip) {
                                                global_circuit.external_pins.data[k].internal = int_pin;
                                                break;
                                        }
                                }
                                for (i32 k = global_circuit.internal_wires.start; k < global_circuit.internal_wires.end; ++k) {
                                        if (global_circuit.internal_wires.data[k].from == last_ip) global_circuit.internal_wires.data[k].from = int_pin;
                                        if (global_circuit.internal_wires.data[k].to == last_ip) global_circuit.internal_wires.data[k].to = int_pin;
                                }
                                for (i32 k = global_circuit.internal_gates.start; k < global_circuit.internal_gates.end; ++k) {
                                        if (global_circuit.internal_gates.data[k].input_a == last_ip) global_circuit.internal_gates.data[k].input_a = int_pin;
                                        if (global_circuit.internal_gates.data[k].input_b == last_ip) global_circuit.internal_gates.data[k].input_b = int_pin;
                                        if (global_circuit.internal_gates.data[k].output == last_ip) global_circuit.internal_gates.data[k].output = int_pin;
                                }
                        }

                        ExternalPinIndex last_ep = global_circuit.external_pins.end - 1;
                        vector_remove_at_index(global_circuit.external_pins, ext_pin);
                        if (ext_pin != last_ep) {
                                for (i32 k = global_circuit.external_wires.start; k < global_circuit.external_wires.end; ++k) {
                                        if (global_circuit.external_wires.data[k].from == last_ep) global_circuit.external_wires.data[k].from = ext_pin;
                                        if (global_circuit.external_wires.data[k].to == last_ep) global_circuit.external_wires.data[k].to = ext_pin;
                                }
                                for (i32 k = global_circuit.input_indicators.start; k < global_circuit.input_indicators.end; ++k) {
                                        if (global_circuit.input_indicators.data[k].output_pin == last_ep) {
                                                global_circuit.input_indicators.data[k].output_pin = ext_pin;
                                                break;
                                        }
                                }
                                for (i32 k = global_circuit.output_indicators.start; k < global_circuit.output_indicators.end; ++k) {
                                        if (global_circuit.output_indicators.data[k].input_pin == last_ep) {
                                                global_circuit.output_indicators.data[k].input_pin = ext_pin;
                                                break;
                                        }
                                }
                        }
                }
        }

        ExternalChipIndex last_chip = global_circuit.external_chips.end - 1;
        vector_remove_at_index(global_circuit.external_chips, index);
        if (index != last_chip) {
                for (i32 k = global_circuit.external_pins.start; k < global_circuit.external_pins.end; ++k) {
                        if (global_circuit.external_pins.data[k].parent.type == ENN_CHIP && global_circuit.external_pins.data[k].parent.index == last_chip) {
                                global_circuit.external_pins.data[k].parent.index = index;
                        }
                }
        }
}

ENNDEF_PUBLIC void circuit_move_input_indicator(InputIndicatorIndex index, f32vec2 new_pos) {
        f32vec2 delta = {
                new_pos.x - global_circuit.input_indicators.data[index].pos.x,
                new_pos.y - global_circuit.input_indicators.data[index].pos.y
        };
        
        global_circuit.input_indicators.data[index].pos = new_pos;
        
        ExternalPinIndex pin_idx = global_circuit.input_indicators.data[index].output_pin;
        global_circuit.external_pins.data[pin_idx].pos.x += delta.x;
        global_circuit.external_pins.data[pin_idx].pos.y += delta.y;
}

ENNDEF_PUBLIC void circuit_move_output_indicator(OutputIndicatorIndex index, f32vec2 new_pos) {
        f32vec2 delta = {
                new_pos.x - global_circuit.output_indicators.data[index].pos.x,
                new_pos.y - global_circuit.output_indicators.data[index].pos.y
        };
        
        global_circuit.output_indicators.data[index].pos = new_pos;
        
        ExternalPinIndex pin_idx = global_circuit.output_indicators.data[index].input_pin;
        global_circuit.external_pins.data[pin_idx].pos.x += delta.x;
        global_circuit.external_pins.data[pin_idx].pos.y += delta.y;
}

ENNDEF_PUBLIC void circuit_move_chip(ExternalChipIndex index, f32vec2 new_pos) {
        f32vec2 delta = {
                new_pos.x - global_circuit.external_chips.data[index].pos.x,
                new_pos.y - global_circuit.external_chips.data[index].pos.y
        };
        
        global_circuit.external_chips.data[index].pos = new_pos;
        
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i) {
                if (global_circuit.external_pins.data[i].parent.type == ENN_CHIP && global_circuit.external_pins.data[i].parent.index == index) {
                        global_circuit.external_pins.data[i].pos.x += delta.x;
                        global_circuit.external_pins.data[i].pos.y += delta.y;
                }
        }
}

ENNDEF_PUBLIC void circuit_check_hovered_pin(f32vec2 pos) {
        global_circuit.hovered_pin = global_circuit.external_pins.end;
        for (i32 i = global_circuit.external_pins.start; i < global_circuit.external_pins.end; ++i) {
                f32vec2 pin_pos = global_circuit.external_pins.data[i].pos;
                if (pos.x >= pin_pos.x && pos.x <= pin_pos.x + CIRCUIT_PIN_WIDTH &&
                    pos.y >= pin_pos.y && pos.y <= pin_pos.y + CIRCUIT_PIN_HEIGHT) {
                        global_circuit.hovered_pin = i;
                        break;
                }
        }
}

#endif