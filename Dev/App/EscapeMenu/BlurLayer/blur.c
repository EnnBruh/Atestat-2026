#include "layer.h"

LayerID blur_layer_id;

static VAOID blur_vao;
static VBOID blur_vbo;
static ShaderID blur_shader;
static TextureID blur_texture;
static UniformLocation offset_loc;

static i32 current_width;
static i32 current_height;

void blur_layer_update_texture(void) {
        DEBUG_TRACE();
        glBindTexture(GL_TEXTURE_2D, blur_texture);
        
        if (window_viewport.z != current_width || window_viewport.w != current_height) {
                glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, window_viewport.x, window_viewport.y, window_viewport.z, window_viewport.w, 0);
                current_width = window_viewport.z;
                current_height = window_viewport.w;
        } else {
                glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, window_viewport.x, window_viewport.y, window_viewport.z, window_viewport.w);
        }
        DEBUG_UNTRACE();
}

void blur_layer_init(void) {
        DEBUG_TRACE();
        blur_shader = render_shader_compile("Blur/vertex.glsl", "Blur/fragment.glsl");
        offset_loc = glGetUniformLocation(blur_shader, "texture_offset");

        f32 quad_vertices[] = {
                -1.0,  1.0,  0.0, 1.0,
                -1.0, -1.0,  0.0, 0.0,
                 1.0, -1.0,  1.0, 0.0,

                -1.0,  1.0,  0.0, 1.0,
                 1.0, -1.0,  1.0, 0.0,
                 1.0,  1.0,  1.0, 1.0
        };

        glGenVertexArrays(1, &blur_vao);
        glGenBuffers(1, &blur_vbo);

        glBindVertexArray(blur_vao);

        glBindBuffer(GL_ARRAY_BUFFER, blur_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(f32)));

        glGenTextures(1, &blur_texture);
        glBindTexture(GL_TEXTURE_2D, blur_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        current_width = 0;
        current_height = 0;
        DEBUG_UNTRACE();
}

void blur_layer_term(void) {
        DEBUG_TRACE();
        glDeleteVertexArrays(1, &blur_vao);
        glDeleteBuffers(1, &blur_vbo);
        glDeleteTextures(1, &blur_texture);
        glDeleteProgram(blur_shader);
        DEBUG_UNTRACE();
}

void blur_layer_on_render(void) {
        DEBUG_TRACE();
        glUseProgram(blur_shader);

        if (current_width > 0 && current_height > 0) {
                glUniform2f(offset_loc, 1.0 / (f32)current_width, 1.0 / (f32)current_height);
        } else {
                glUniform2f(offset_loc, 0.0, 0.0);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, blur_texture);

        glBindVertexArray(blur_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        DEBUG_UNTRACE();
}

void blur_layer_on_update(f64 dt) {
}

void blur_layer_on_event(Event* event) {
}