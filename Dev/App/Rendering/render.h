#ifndef ENN_CUSTOM_RENDER_H
#define ENN_CUSTOM_RENDER_H

#include "core.h"

typedef struct Vertex {
        f32vec2         pos;
        u32             color;
        f32vec2         texture_pos;
} Vertex;


#define ENN_RENDER_VERTEX_BUFF_SIZE 16384

typedef GLint UniformLocation;

#define ENN_FONT_ATLAS_FIRST_CHAR ' '
#define ENN_FONT_ATLAS_LAST_CHAR '~'
extern struct Renderer {
        Vertex          buff[ENN_RENDER_VERTEX_BUFF_SIZE];
        i32             buff_size;

        VAOID           vao;
        VBOID           vbo;
        ShaderID        shader;

        UniformLocation proj_matrix_location;
        f32mat4         proj_matrix;

        TextureID       sprite_sheet_id;
        Image           sprite_sheet;

        struct {
                i32vec2 font_offset;
                i32vec2 char_dim;
                i32vec2 font_dim;
                i32     char_per_col;
                f32vec4 char_sprite[(i32)(ENN_FONT_ATLAS_LAST_CHAR - ENN_FONT_ATLAS_FIRST_CHAR) + 10];
        } font_atlas;
} global_render;

typedef struct Sprite {
        Image*  img;
        f32vec2 texture_top_left;
        f32vec2 texture_bott_right;
} Sprite;

ENNDEF_PRIVATE void render_init(void);
ENNDEF_PRIVATE void render_term(void);
ENNDEF_PRIVATE void render_buff_draw(void);

ENNDEF_PRIVATE Sprite render_sprite_create(Image* texture, i32vec2 texture_top_left, i32vec2 texture_bott_right);

ENNDEF_PRIVATE void render_proj_set(f32mat4 proj_matrix);

ENNDEF_PRIVATE void render_rectangle_push(f32vec2 top_left, f32vec2 bott_right, u32 color);
ENNDEF_PRIVATE void render_line_push(f32vec2 pos1, f32vec2 pos2, f32 width, u32 color);
ENNDEF_PRIVATE void render_sprite_push_color(f32vec2 top_left, f32vec2 bott_right, Sprite* sprite, u32 color);
ENNDEF_PRIVATE void render_sprite_push(f32vec2 top_left, f32vec2 bott_right, Sprite* sprite);
ENNDEF_PRIVATE void render_sprite_flip_horizontal(Sprite* sprite);
ENNDEF_PRIVATE void render_sprite_flip_vertical(Sprite* sprite);

typedef enum ENN_TEXT_ALIGN {
        ENN_LEFT_ALIGN,
        ENN_RIGHT_ALIGN,
        ENN_CENTER_ALIGN
} ENN_TEXT_ALIGN;

ENNDEF_PRIVATE void render_text_push(f32vec2 top_left, f32vec2 bott_right, const char* text, u32 color, f32 text_height, ENN_TEXT_ALIGN align);


#endif