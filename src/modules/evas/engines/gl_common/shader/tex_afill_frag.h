"#ifdef GL_ES\n"
"#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
"precision highp float;\n"
"#else\n"
"precision mediump float;\n"
"#endif\n"
"#endif\n"
"uniform sampler2D tex;\n"
"varying vec4 col;\n"
"varying vec2 tex_c;\n"
"void main()\n"
"{\n"
"   vec4 c = texture2D(tex, tex_c.xy);\n"
"   gl_FragColor = vec4(c.r, c.g, c.b, 1) * col;\n"
"}\n"
