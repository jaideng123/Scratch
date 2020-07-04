#pragma once

#include <string>
#include <vector>
#include <glad/glad.h> // holds all OpenGL type declarations

namespace scratch
{
    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Material
    {
    public:
        Material(std::vector<Texture> textures)
        {
            _textures = textures;
        }
        Material() = default;

        void activate(Shader *shader)
        {
            setupTextures(shader);
        }

    private:
        std::vector<Texture> _textures;
        void setupTextures(Shader *shader)
        {
            // bind appropriate textures
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            for (unsigned int i = 0; i < _textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                std::string number;
                std::string name = _textures[i].type;
                if (name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (name == "texture_specular")
                    number = std::to_string(specularNr++); // transfer unsigned int to stream
                else if (name == "texture_normal")
                    number = std::to_string(normalNr++); // transfer unsigned int to stream
                else if (name == "texture_height")
                    number = std::to_string(heightNr++); // transfer unsigned int to stream

                // now set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(shader->ID, ("material." + name + number).c_str()), i);
                // and finally bind the texture
                glBindTexture(GL_TEXTURE_2D, _textures[i].id);
            }
        }
    };
} // namespace scratch