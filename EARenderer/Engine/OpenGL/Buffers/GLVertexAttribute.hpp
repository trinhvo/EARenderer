//
//  GLVertexAttribute.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 18.02.2018.
//  Copyright © 2018 MPO. All rights reserved.
//

#ifndef GLVertexAttribute_hpp
#define GLVertexAttribute_hpp

#include <OpenGL/gltypes.h>

namespace EARenderer {

    struct GLVertexAttribute {
        GLint bytes;
        GLint components;
        GLint divisor;

        GLVertexAttribute(GLint sizeInBytes, GLint componentCount);
        GLVertexAttribute(GLint sizeInBytes, GLint componentCount, GLint divisor);

        /**
         Factory function providing attribute unique for every vertex (default OpenGL behaviour)

         @param sizeInBytes attribute's size in bytes
         @param componentCount number of attribute's components
         @return attribute with divisor parameter set to 0
         */
        static GLVertexAttribute UniqueAttribute(GLint sizeInBytes, GLint componentCount);

        /**
         Factory function providing attribute which will be shared between vertices of the same instance in instanced rendering mode

         @param sizeInBytes attribute's size in bytes
         @param componentCount number of attribute's components
         @return attribute with divisor parameter set to 1
         */
        static GLVertexAttribute SharedAttribute(GLint sizeInBytes, GLint componentCount);
    };

}

#endif /* GLVertexAttribute_hpp */