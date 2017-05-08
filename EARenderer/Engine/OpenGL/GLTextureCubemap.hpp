//
//  GLTextureCubemap.hpp
//  EARenderer
//
//  Created by Pavlo Muratov on 21.04.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#ifndef GLTextureCubemap_hpp
#define GLTextureCubemap_hpp

#include "GLNamedObject.hpp"
#include "GLBindable.hpp"

namespace EARenderer {
    
    class GLTextureCubemap: public GLNamedObject, public GLBindable {
    public:
        using GLNamedObject::GLNamedObject;
        
        GLTextureCubemap(const std::string& rightImagePath,
                         const std::string& leftImagePath,
                         const std::string& topImagePath,
                         const std::string& bottomImagePath,
                         const std::string& frontImagePath,
                         const std::string& backImagePath);
        
        GLTextureCubemap(GLTextureCubemap&& that) = default;
        GLTextureCubemap& operator=(GLTextureCubemap&& rhs) = default;
        ~GLTextureCubemap() override;
        
        void bind() const override;
    };
    
}

#endif /* GLTextureCubemap_hpp */