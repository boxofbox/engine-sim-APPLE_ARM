#version 410 core

uniform sampler2D diffuseTex;

in vec4 ex_Pos;
in vec2 ex_Tex;
in vec4 ex_Col;

out vec4 out_Color;

uniform ObjectVariables {
	vec4 MulCol;
	vec2 TexOffset;
	vec2 TexScale;
};

void main(void) {
	float a = texture(diffuseTex, ex_Tex).r;
	//out_Color = vec4(1.0, 1.0, 1.0, a) * MulCol * ex_Col;
    out_Color = vec4(1.0, 1.0, 1.0, 1.0);
}
