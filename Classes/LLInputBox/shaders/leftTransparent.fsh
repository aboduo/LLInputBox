

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
varying vec4 v_color;

uniform sampler2D CC_Texture0;
uniform float u_left;
uniform float u_transDis;

void main()
{

    vec4 ttColor= v_color*texture2D(CC_Texture0, v_texCoord);
    
    float px = gl_FragCoord.x - u_left;
    px = max(px, 0.0);
    
    ttColor.a = min(ttColor.a, px/u_transDis);
    
    gl_FragColor=ttColor;
}

