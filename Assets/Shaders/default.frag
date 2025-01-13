#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;
in vec4 shadowFragPos;

uniform sampler2DArray shadowPass;
uniform sampler2D albedo;

uniform mat4 view;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 viewPos;

const float farPlane = 100000.0f;

layout (std140) uniform LightSpaceMatrices
{
    mat4 lightSpaceMatrices[16];
};

uniform float cascadePlaneDistances[16];
uniform int cascadeCount;   // number of frusta - 1


vec2 ShadowCalculation(vec3 fragPosWorldSpace)
{

    vec4 fragPosViewSpace = view * vec4(fragPosWorldSpace, 1.0);
    float depthValue = abs(fragPosViewSpace.z);

    int layer = -1;
    for (int i = 0; i < cascadeCount; ++i)
    {
        if (depthValue < cascadePlaneDistances[i])
        {
            layer = i;
            break;
        }
    }
    if (layer == -1)
    {
        layer = cascadeCount;
    }

    vec4 shadowFragView = lightSpaceMatrices[layer] * vec4(fragPosWorldSpace, 1.0);

    vec3 projCoords = shadowFragView.xyz / shadowFragView.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = texture(shadowPass, vec3(projCoords.xy, layer)).r * 200.0f;

    float currentDepth = projCoords.z * 200.0f;

    float bias = 0.005;
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(shadowPass, layer));

       for(int x = -1; x <= 1; ++x)
       {
           for(int y = -1; y <= 1; ++y)
           {
               float pcfDepth = texture(shadowPass, vec3(projCoords.xy + vec2(x, y) * texelSize, layer)).r * 200.0f;
               shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
           }
       }

    if (projCoords.x < 0.3 || projCoords.y < 0.3 || projCoords.z * 200 > 0.7)
        return vec2(0.0, layer);

    shadow /= 9.0;

    return vec2(shadow, layer);
}

void main()
{
    vec3 objectColor = texture(albedo, TexCoord).rgb;
    float ambientStrength = 0.7;
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

    objectColor = vec3(0.6, 0.6, 0.6);

    vec2 shadow = ShadowCalculation(FragPos);

    vec3 result = (ambient + (1.0f - shadow.x) * (diffuse + specular)) * objectColor;
    FragColor = vec4(result.x, result.y + (shadow.y / 10), result.z, 1.0);
}