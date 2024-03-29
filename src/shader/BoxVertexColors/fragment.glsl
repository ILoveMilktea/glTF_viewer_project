﻿#version 120                  // GLSL 1.20

uniform sampler2D u_diffuse_texture;

uniform vec3 u_view_position_wc;
uniform vec3 u_light_position_wc;

uniform vec4 u_light_diffuse;
uniform vec4 u_light_specular;

uniform vec4 u_material_diffuse;
uniform vec4 u_material_specular;
uniform float u_material_shininess;

varying vec3 v_position_wc;
varying vec3 v_normal_wc;
varying vec3 v_color;
//varying vec2 v_texcoord;

void main()
{
    gl_FragColor = vec4(v_color, 1.0f);
}