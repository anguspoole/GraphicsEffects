#version 420
in vec4 finalOutputColour; //get this from the regular fragment shader (finalOutputColour)

out vec4 BrightColor; 

void main()
{            
    // check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(finalOutputColour.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(finalOutputColour.rgb, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
		
	return;
}