#ifndef RENDER_H
#define RENDER_H

#include "core.h"

#define ENN_FONT_ATLAS_FIRST_CHAR ' '
#define ENN_FONT_ATLAS_LAST_CHAR '~'
#define ENN_RENDER_VERTEX_BUFF_SIZE 16384

typedef GLint UniformLocation;
typedef struct Vertex {
        f32vec2         pos;
        u32             color;
        f32vec2         texture_pos;
} Vertex;

extern struct Renderer {
        vector(Vertex)  buff;

        VAOID           vao;
        VBOID           vbo;
        ShaderID        shader;

        UniformLocation proj_matrix_location;

        TextureID       sprite_sheet_id;
        Image           sprite_sheet;

        f32vec4 char_sprite[ENN_FONT_ATLAS_LAST_CHAR - ENN_FONT_ATLAS_FIRST_CHAR];
} global_render;

ENNDEF_PRIVATE void render_init(void);
ENNDEF_PRIVATE void render_term(void);
ENNDEF_PRIVATE void render_buff_flush(void);

typedef struct BitmapFontSpecification {
        char*   file_path;
        i32     char_width;
        i32     char_height;
        i32     char_per_col;
} BitmapFontSpecification;
ENNDEF_PRIVATE void render_font_bitmap_load(BitmapFontSpecification* spec);

#endif