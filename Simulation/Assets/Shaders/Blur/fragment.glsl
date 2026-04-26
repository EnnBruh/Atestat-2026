#version 330 core

out vec4 f_color;

in vec2 m_texture_pos;

uniform sampler2D framebuff_texture;
uniform vec2 texture_offset;

uniform float strength = 2.25;

void main() {
    float kernel[25] = float[](
        1.0, 4.0, 6.0, 4.0, 1.0,
        4.0, 16.0, 24.0, 16.0, 4.0,
        6.0, 24.0, 36.0, 24.0, 6.0,
        4.0, 16.0, 24.0, 16.0, 4.0,
        1.0, 4.0, 6.0, 4.0, 1.0
    );
    
    vec3 color = vec3(0.0);
    int k = 0;
    
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            vec2 coord = m_texture_pos + vec2(float(i), float(j)) * texture_offset * strength;
            color += texture(framebuff_texture, coord).rgb * (kernel[k] / 256.0);
            k++;
        }
    }
    
    f_color = vec4(color, 1.0);
}