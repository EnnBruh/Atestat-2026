#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "layer.h"

#define CIRCUIT_PIN_WIDTH               2
#define CIRCUIT_PIN_HEIGHT              3
#define CIRCUIT_PIN_COLOR               0x202020FF

#define CIRCUIT_INDICATOR_WIDTH                         10
#define CIRCUIT_INDICATOR_HEIGHT                        10
#define CIRCUIT_INDICATOR_BORDER_PADDING                1
#define CIRCUIT_INDICATOR_BORDER_COLOR                  CIRCUIT_PIN_COLOR

#define CIRCUIT_INDICATOR_COLOR_RED             0xcc241dFF
#define CIRCUIT_INDICATOR_COLOR_ORANGE          0xfe8109FF
#define CIRCUIT_INDICATOR_COLOR_YELLOW          0xd79921FF
#define CIRCUIT_INDICATOR_COLOR_GREEN           0x98971aFF
#define CIRCUIT_INDICATOR_COLOR_BLUE            0x458588FF
#define CIRCUIT_INDICATOR_COLOR_PURPLE          0xb16286FF


#define CIRCUIT_CHIP_MAX_NAME_LEN       64
#define CIRCUIT_CHIP_NAME_PADDING       3
#define CIRCUIT_CHIP_PIN_PADDING        2
#define CIRCUIT_CHIP_OPERATION_ID_LEN   13

#define CIRCUIT_CHIP_OPERATION_NAND     "0000000000000"

typedef i32     PinID;
typedef i32     IndicatorID;
typedef i32     WireID;
typedef i32     ChipID;
typedef char    ChipOperationID[CIRCUIT_CHIP_OPERATION_ID_LEN];

typedef enum ENN_CIRCUIT_ELEMENT_TYPE {
        ENN_PIN,
        ENN_INPUT_INDICATOR,
        ENN_OUTPUT_INDICATOR,
        ENN_WIRE,
        ENN_CHIP
} ENN_CIRCUIT_ELEMENT_TYPE;

typedef struct CircuitElement {
        void*                           element;
        ENN_CIRCUIT_ELEMENT_TYPE        type;
} CircuitElement;

typedef struct InternalPin {
        PinID   id;
        bool    curr_state : 1;
        bool    prev_state : 1;
} InternalPin;

typedef struct InternalWire {
        InternalPin* from;
        InternalPin* to;
} InternalWire;

typedef struct InternalChip {
        ChipOperationID                 oper;
        vector(InternalPin*)            input_pins;
        vector(InternalPin*)            output_pins;

        struct {
                vector(InternalPin)             pins;
                vector(InternalWire)            wires;
                vector(struct InternalChip)     chips;
        }                               internal_circuit;
} InternalChip;

typedef struct Pin {
        PinID           id;
        f32vec2         pos;

        InternalPin     internal;
} Pin;

typedef struct InputIndicator {                 
        IndicatorID     id;
        f32vec2         pos;

        bool            state;
        Pin*            pin;
        u32             color;
} InputIndicator;

typedef struct OutputIndicator {
        IndicatorID     id;
        f32vec2         pos;

        bool            state;
        Pin*            pin;
        u32             color;
} OutputIndicator;

typedef struct Chip {
        ChipID          id;
        f32vec2         pos;

        char            name[CIRCUIT_CHIP_MAX_NAME_LEN];
        u32             color;

        InternalChip    internal;
} Chip;

typedef struct Wire {
        WireID          id;
        InternalWire    internal;
        vector(f32vec2) anchors;
} Wire;

typedef i32 CircuitID;
typedef struct Circuit {
        CircuitID               id;
        vector(Pin)             pins;
        vector(Wire)            wires;
        vector(InputIndicator)  input_indicators;
        vector(OutputIndicator) output_indicators;
        vector(Chip)            chips;
} Circuit;



#endif