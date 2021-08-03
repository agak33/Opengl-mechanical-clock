#version 330

// texture, specular map
uniform sampler2D tex;
uniform sampler2D spec;

// pixel color
out vec4 pixelColor;

// vertex coordinates on the texture and specular map
in vec2 texCoord;

// normal vector
in vec4 n;

// array with lights positions
in vec4 l[2];

// vectex coordinates
in vec4 v;

void main(void) {
	// normalized, interpolated vectors
	vec4 ml_1 = normalize(l[0]);
	vec4 ml_2 = normalize(l[1]);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	// Reflected vector
	vec4 mr_1 = reflect(-ml_1, mn);
	vec4 mr_2 = reflect(-ml_2, mn);

	// Surface parameters
	vec4 kd = texture(tex , texCoord);  // texture color
	vec4 ks = texture(spec, texCoord);  // reflection color

	// Calculation of the lighting model
	float nl_1 = clamp(dot(mn, ml_1), 0, 1);
	float nl_2 = clamp(dot(mn, ml_2), 0, 1);

	float rv_1 = pow(clamp(dot(mr_1, mv), 0, 1), 30);
	float rv_2 = pow(clamp(dot(mr_2, mv), 0, 1), 30);

	// final pixel color
	pixelColor = vec4(kd.rgb * nl_1, kd.a) + vec4(ks.rgb * rv_1, 0) +
				 vec4(kd.rgb * nl_2, kd.a) + vec4(ks.rgb * rv_2, 0);
}
