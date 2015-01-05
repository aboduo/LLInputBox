attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying lowp vec4 v_color;
varying mediump vec2 v_texCoord;
#else
varying vec2 v_texCoord;
varying vec4 v_color;
#endif

void main()
{
//    vec4 pos=vec4(a_position.xy,0,1);
//    gl_Position = CC_MVPMatrix * pos;
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = a_texCoord;
    v_color = a_color;
    
}