#pragma once

#include <glad/glad.h>
#include <stdexcept>

namespace los
{

class Image
{
private:
    unsigned int mImageId;
    int mWidth, mHeight;
    int mNbChannels;

public:
    Image(const unsigned char *data, int width, int height, int nb_channels)
    : mWidth(width)
    , mHeight(height)
    , mNbChannels(nb_channels)
    {
        if(mNbChannels > 4 && mNbChannels < 3) {
            throw std::runtime_error("Unsupported number of channel in image");
        }
        glGenTextures(1, &mImageId);  
        glBindTexture(GL_TEXTURE_2D, mImageId); 

        if (data) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            unsigned int format = mNbChannels == 4 ? GL_RGBA : GL_RGB;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            throw std::runtime_error("Failed to load texture");
        }
        
    }

    inline unsigned int getImage() const noexcept {
        return mImageId;
    }

    inline int getWidth() const noexcept {
        return mWidth;
    }

    inline int getHeight() const noexcept {
        return mHeight;
    }

    ~Image() {
        glDeleteTextures(1, &mImageId);
    }
};


} // namespace los
