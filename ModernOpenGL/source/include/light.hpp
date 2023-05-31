#pragma once

#include "basicMath.hpp"

namespace LowRenderer
{
    struct BaseLight
    {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };

    struct DirLight {
        vec3 direction;

        BaseLight base;
    };

    struct PointLight {
        vec3 position;

        float constant;
        float linear;
        float quadratic;

        BaseLight base;
    };

    struct SpotLight {
        vec3 position;
        vec3 direction;
        float cutOff;
        float outerCutOff;

        float constant;
        float linear;
        float quadratic;

        BaseLight base;
    };

    inline BaseLight makeBaseLight(vec3 amb, vec3 dif, vec3 spe) {
        return { amb, dif, spe };
    }

    inline DirLight makeDirLight(vec3 pos, BaseLight baseLight) {
        return { pos, baseLight };
    }
    inline DirLight makeDirLight(vec3 pos, vec3 amb, vec3 dif, vec3 spe) {
        return { pos, amb, dif, spe };
    }

    inline PointLight makePointLight(vec3 pos, float constant, float linear, float quadratic, BaseLight baseLight) {
        return { pos, constant, linear, quadratic, baseLight };
    }
    inline PointLight makePointLight(vec3 pos, float constant, float linear, float quadratic, vec3 amb, vec3 dif, vec3 spe) {
        return { pos, constant, linear, quadratic, amb, dif, spe };
    }

    inline SpotLight makeSpotLight(vec3 pos, vec3 dir, float cutOff, float outerCutOff, float constant, float linear, float quadratic, BaseLight baseLight) {
        return { pos, dir, cutOff, outerCutOff, constant, linear, quadratic, baseLight };
    }
    inline SpotLight makeSpotLight(vec3 pos, vec3 dir, float cutOff, float outerCutOff, float constant, float linear, float quadratic, vec3 amb, vec3 dif, vec3 spe) {
        return { pos, dir, cutOff, outerCutOff, constant, linear, quadratic, amb, dif, spe };
    }
}