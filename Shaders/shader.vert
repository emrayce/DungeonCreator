#version 450
in highp vec4 posAttr;
in lowp vec4 colAttr;
out lowp vec4 col;
uniform highp mat4 projection;
uniform highp mat4 view;
uniform highp mat4 model;
void main() {
   col = colAttr;
   gl_Position = projection * view *model * posAttr;
}