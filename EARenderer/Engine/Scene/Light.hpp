//
//  Light.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 25.03.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace EARenderer {
    
    class Light {
    protected:
        glm::vec3 mPosition;
        glm::vec3 mColor;
        
    public:
        Light();
        Light(const glm::vec3& position, const glm::vec3& color);
        
        const glm::vec3& position() const;
        const glm::vec3& color() const;
        
        void setPosition(const glm::vec3& position);
        void setColor(const glm::vec3& color);
    };
    
}

#endif /* Light_hpp */