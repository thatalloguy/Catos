#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;
in vec4 shadowFragPos;

uniform sampler2D shadowPass;
uniform sampler2D albedo;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

float shadowCalc(vec4 shadowFragSpace) {

    vec3 projCoords = shadowFragSpace.xyz / shadowFragSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowPass, projCoords.xy).r;

    float currentDepth = projCoords.z;

    vec3 lightDir = vec3(0.7, 1.0, 0);

    float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowPass, 0);

    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowPass, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

        if (projCoords.x > 0.6 || projCoords.y > 0.6 || projCoords.z > 0.6 ||
            projCoords.x < 0.3 || projCoords.y < 0.3)
            return 0.0;


    return shadow;
}

void main()
{
    vec3 objectColor = texture(albedo, TexCoord).rgb;
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),  16);
    vec3 specular = specularStrength * spec * lightColor;

    float shadow = shadowCalc(shadowFragPos);

    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * objectColor;
    FragColor = vec4(texture(albedo, TexCoord).rgb, 1.0);
}