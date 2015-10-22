#include "OpenGLProgramFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"
#include "OpenGL/Resource/OpenGLGraphicsResourceManager.h"

namespace SamEngine
{
    ResourceStatus OpenGLProgramFactory::Create(OpenGLProgram &resource, DataPtr data)
    {
        auto vertex = OpenGLGraphicsResourceManager::Get().GetShader(resource.Config.VertexShader);
        auto fragment = OpenGLGraphicsResourceManager::Get().GetShader(resource.Config.FragmentShader);

        s_assert(vertex != nullptr);
        s_assert(fragment != nullptr);

        auto program = glCreateProgram();
        
        glAttachShader(program, vertex->ShaderID);
        glAttachShader(program, fragment->ShaderID);

        for (auto i = 0; i < GraphicsConfig::MaxVertexNodeCount; ++i)
        {
            glBindAttribLocation(program, i, VertexAttributeNameFromType(static_cast<VertexAttributeType>(i)));
        }

        glLinkProgram(program);

        auto status = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        #if SAM_DEBUG
        auto log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        if (status == GL_FALSE && log_length > 0)
        {
            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetProgramInfoLog(program, log_length, &log_length, log);
            GetLog().Debug("[link log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteProgram(program);
            program = 0;
        }

        resource.ProgramID = program;

        return ResourceStatus::COMPLETED;
    }

    void OpenGLProgramFactory::Destroy(OpenGLProgram &resource)
    {
        OpenGLRenderer::Get().ResetProgram();
        glDeleteProgram(resource.ProgramID);
    }
}