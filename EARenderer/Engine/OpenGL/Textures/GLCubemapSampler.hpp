//
//  CubemapSampler.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 18.11.2017.
//  Copyright © 2017 MPO. All rights reserved.
//

#ifndef CubemapSampler_hpp
#define CubemapSampler_hpp

#include "Color.hpp"
#include "GLCubemapFace.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace EARenderer {
    
    class GLCubemapSampler {
    protected:
        void computeTexCoords(const glm::vec3& sampleVector, GLCubemapFace& face, glm::vec2& texCoords) const;
        
    public:        
        virtual Color sample(const glm::vec3& direction) const = 0;
        virtual Color sample(GLCubemapFace face, int32_t x, int32_t y) const = 0;
    };
    
}

#endif /* CubemapSampler_hpp */