/*uniform sampler2D texture;
//uniform float blur_radius;
uniform float min;
uniform float mult;
void main()
{

    //float xxx = min*mult;

    //vec2 offx = vec2(blur_radius, 0.0);
    //vec2 offy = vec2(0.0, blur_radius);
    */
/*
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * 4.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        * 2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx + offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * 1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx + offy) * 1.0;

    gl_FragColor =  gl_Color * (pixel / 16.0);
    */
    /*
    //vec4 pixel
    //gl_FragColor = vec4(texture2D(texture, gl_TexCoord[0].xy).xyz *(1-(gl_TexCoord[0].y)), 1);
    gl_FragColor = vec4(texture2D(texture, gl_TexCoord[0].xy));
    //gl_FragColor = vec4(vec3(1,1,1)*((gl_TexCoord[0].y+1)/2), 1);
    //gl_FragColor = vec4(vec3((uv.y-min)*mult),1.0);
}
*/
uniform vec4 color;
uniform float expand;
uniform vec2 center;
uniform float radius;
uniform float windowHeight;
uniform sampler2D texture;
void main(void)
{

    vec2 centerFromSfml = vec2(center.x, windowHeight - center.y);
    vec2 p = (gl_FragCoord.xy - centerFromSfml) / radius;
    float r = sqrt(dot(p, p));
    float res = float(r - expand)/float(1.0-expand);
    if(gl_Color == vec4(0,0,0,1)) gl_FragColor= gl_Color;
    else if (r >= 1.0)
    {
        gl_FragColor = mix(color, vec4(texture2D(texture, gl_TexCoord[0].xy)), res);
    }
    else
    {
        gl_FragColor = vec4(texture2D(texture, gl_TexCoord[0].xy));
    }
}