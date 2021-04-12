#ifndef CG_SCRATCH_LIGHT_H
#define CG_SCRATCH_LIGHT_H

enum LightType {AMBIENT = 0, POINT, DIRECTIONAL};

class Light
{
public:
    cgm::vec3f position;
    cgm::vec3f direction;
    float intensity;
    LightType Type;

    Light() {};
    Light(const cgm::vec3f &lPos, const cgm::vec3f &lDir, const float &lIntensity, LightType lType)
    : position(lPos), direction(lDir), intensity(lIntensity), Type(lType){};
};

#endif //CG_SCRATCH_LIGHT_H
