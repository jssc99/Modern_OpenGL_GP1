#version 410 core

out vec4 fragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;   

    float shininess;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;

uniform vec3 viewPos;
uniform Material material;

#define MAXLIGHTS 5

uniform int nbDirLight;
uniform int nbPointLight;
uniform int nbSpotLight;

uniform DirLight dirLights[MAXLIGHTS];
uniform PointLight pointLights[MAXLIGHTS];
uniform SpotLight spotLights[MAXLIGHTS];

vec3 getDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = vec3(0.f, 0.f, 0.f);
    
    for (int i = 0; i < nbDirLight; ++i)
        result += getDirLight(dirLights[i], norm, viewDir);

    for (int i = 0; i < nbPointLight; ++i)
        result += getPointLight(pointLights[i], norm, fragPos, viewDir);  
        
    for (int i = 0; i < nbSpotLight; ++i)
        result += getSpotLight(spotLights[i], norm, fragPos, viewDir);    

    fragColor = vec4(result, 1.f);
}

vec3 getDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.f);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    return (ambient + diffuse + specular);
}

vec3 getPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.f);
    
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
    
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 getSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.f);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.f, 1.f);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}