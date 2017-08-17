//
//  GLTexture.cpp
//  EARenderer
//
//  Created by Pavlo Muratov on 06.08.17.
//  Copyright © 2017 MPO. All rights reserved.
//

#include "GLTexture.hpp"

namespace EARenderer {
    
#pragma mark - Lifecycle
    
    GLTexture::GLTexture(GLenum bindingPoint, GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT)
    :
    GLTexture(Size2D::zero(), bindingPoint, minFilter, magFilter, wrapModeS, wrapModeT)
    { }
    
    GLTexture::GLTexture(const Size2D& size, GLenum bindingPoint, GLint minFilter, GLint magFilter, GLint wrapModeS, GLint wrapModeT)
    :
    mSize(size),
    mBindingPoint(bindingPoint)
    {
        glGenTextures(1, &mName);
        bind();
        glTexParameteri(mBindingPoint, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(mBindingPoint, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(mBindingPoint, GL_TEXTURE_WRAP_S, wrapModeS);
        glTexParameteri(mBindingPoint, GL_TEXTURE_WRAP_T, wrapModeT);
    }
    
    GLTexture::~GLTexture() {
        glDeleteTextures(1, &mName);
    }
    
#pragma mark - Getters
    
    const Size2D& GLTexture::size() const {
        return mSize;
    }
    
#pragma mark - Binding
    
    void GLTexture::bind() const {
        glBindTexture(mBindingPoint, mName);
    }
    
}
