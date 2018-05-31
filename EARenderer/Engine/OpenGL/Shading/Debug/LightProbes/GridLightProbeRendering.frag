#version 400 core

// Constants

// Spherical harmonics
const float kC1 = 0.429043;
const float kC2 = 0.511664;
const float kC3 = 0.743125;
const float kC4 = 0.886227;
const float kC5 = 0.247708;

// Input

in vec3 vCurrentPosition;
in vec3 vTexCoords;
in mat3 vNormalMatrix;

// Output

out vec4 oFragColor;

// Uniforms

uniform float uRadius;
uniform ivec3 uProbesGridResolution;

uniform sampler3D uGridSHMap0;
uniform sampler3D uGridSHMap1;
uniform sampler3D uGridSHMap2;
uniform sampler3D uGridSHMap3;
uniform sampler3D uGridSHMap4;
uniform sampler3D uGridSHMap5;
uniform sampler3D uGridSHMap6;

// Types

struct SH {
    vec3 L00;
    vec3 L11;
    vec3 L10;
    vec3 L1_1;
    vec3 L21;
    vec3 L2_1;
    vec3 L2_2;
    vec3 L20;
    vec3 L22;
};

// Functions

// Shrink tex coords by the size of 1 texel, which will result in a (0; 0; 0)
// coordinate to become (0.5; 0.5; 0.5) coordinate (in texel space)
vec3 AlignWithTexelCenters(vec3 texCoords) {
    vec3 halfTexel = 1.0 / vec3(uProbesGridResolution) / 2.0;
    vec3 reductionFactor = vec3(uProbesGridResolution - 1) / vec3(uProbesGridResolution);
    return texCoords * reductionFactor + halfTexel;
}

SH UnpackSH() {
    SH sh;

    vec3 shMapCoords = AlignWithTexelCenters(vTexCoords);

    vec4 shMap0Data = texture(uGridSHMap0, shMapCoords);
    vec4 shMap1Data = texture(uGridSHMap1, shMapCoords);
    vec4 shMap2Data = texture(uGridSHMap2, shMapCoords);
    vec4 shMap3Data = texture(uGridSHMap3, shMapCoords);
    vec4 shMap4Data = texture(uGridSHMap4, shMapCoords);
    vec4 shMap5Data = texture(uGridSHMap5, shMapCoords);
    vec4 shMap6Data = texture(uGridSHMap6, shMapCoords);

    sh.L00  = vec3(shMap0Data.rgb);
    sh.L11  = vec3(shMap0Data.a, shMap1Data.rg);
    sh.L10  = vec3(shMap1Data.ba, shMap2Data.r);
    sh.L1_1 = vec3(shMap2Data.gba);
    sh.L21  = vec3(shMap3Data.rgb);
    sh.L2_1 = vec3(shMap3Data.a, shMap4Data.rg);
    sh.L2_2 = vec3(shMap4Data.ba, shMap5Data.r);
    sh.L20  = vec3(shMap5Data.gba);
    sh.L22  = vec3(shMap6Data.rgb);

//    // White and green
//    sh.L00  = vec3(1.77245402, 3.54490805, 1.77245402);
//    sh.L11  = vec3(3.06998014, 0.0, 3.06998014);
//    sh.L10  = vec3(0.0);
//    sh.L1_1 = vec3(0.0);
//    sh.L21  = vec3(0.0);
//    sh.L2_1 = vec3(0.0);
//    sh.L2_2 = vec3(0.0);
//    sh.L20  = vec3(-1.9816637, -3.96332741, -1.9816637);
//    sh.L22  = vec3(3.43234229, 6.86468458, 3.43234229);

    return sh;
}

float SHRadiance(SH sh, vec3 direction, int component) {
    int c = component;

    return  kC1 * sh.L22[c] * (direction.x * direction.x - direction.y * direction.y) +
            kC3 * sh.L20[c] * (direction.z * direction.z) +
            kC4 * sh.L00[c] -
            kC5 * sh.L20[c] +
            2.0 * kC1 * (sh.L2_2[c] * direction.x * direction.y + sh.L21[c] * direction.x * direction.z + sh.L2_1[c] * direction.y * direction.z) +
            2.0 * kC2 * (sh.L11[c] * direction.x + sh.L1_1[c] * direction.y + sh.L10[c] * direction.z);
}

vec3 EvaluateSphericalHarmonics(vec3 direction) {
    SH sh = UnpackSH();
    return vec3(SHRadiance(sh, direction, 0), SHRadiance(sh, direction, 1), SHRadiance(sh, direction, 2));
}

vec3 ReinhardToneMap(vec3 color) {
    return color / (color + vec3(1.0));
}

// Drawing a sphere using billboard
void main() {
    vec2 normPosition = vCurrentPosition.xy / uRadius;
    float normDistanceFromCenter = length(normPosition);

    if (normDistanceFromCenter > 1.0) {
        discard;
    }

    // Knowing that our billboard represents a sphere we can reconstruct the z coordinate
    // Also negate Z because the equation gives positive values for Z pointing "from the screen to the viewer"
    // which is the opposite of the positive Z direction in NDC space
    float z = -sqrt(1.0 - normDistanceFromCenter * normDistanceFromCenter);

    // Calculate the normal for the sphere
    vec3 normal = normalize(vec3(normPosition, z));

    // Rotate
    normal = vNormalMatrix * normal;

    vec3 color = EvaluateSphericalHarmonics(normal);
    color = ReinhardToneMap(color);

    oFragColor = vec4(color, 1.0);
}
