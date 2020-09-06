#pragma once
#include "Shake/Core/Core.h"

namespace Shake
{
    enum class ShaderDataType
    {
        None = 0,
        Float = 1,
        Float2 = 2,
        Float3 = 3,
        Float4 = 4,
        Mat3 = 5,
        Mat4 = 6,
        Int = 7,
        Int2 = 8,
        Int3 = 9,
        Int4 = 10,
        Bool = 11
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
        case ShaderDataType::None:
            // TODO[rsmekens]: add dev exception here 
            return 0;
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 4 * 2;
        case ShaderDataType::Int3: return 4 * 3;
        case ShaderDataType::Int4: return 4 * 4;
        case ShaderDataType::Bool: return 1;
        default:
            // TODO[rsmekens]: add dev exception here
            return 0;
        }
    }

    struct BufferElement
    {
        std::string m_name;
        ShaderDataType m_type;
        uint32_t m_size;
        uint32_t m_offset;
        bool m_normalized;

        BufferElement(const std::string& name, ShaderDataType type, bool normalized = false)
            : m_name(name), m_type(type), m_size(ShaderDataTypeSize(type)), m_offset(0), m_normalized(normalized)
        {
            
        }

        uint32_t GetComponentCount() const
        {
            // ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
            // ReSharper disable once CppIncompleteSwitchStatement
            switch(m_type)
            {
            case ShaderDataType::Float: return 1;
            case ShaderDataType::Float2: return 2;
            case ShaderDataType::Float3: return 3;
            case ShaderDataType::Float4: return 4;
            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;
            case ShaderDataType::Int: return 1;
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;
            case ShaderDataType::Bool: return 1;
            }
            
            // TODO[rsmekens]: add dev exception
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {};
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_elements(elements)
        {
            CalculateOffsetsAndStride(); 
        };

        inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
        inline const int32_t GetStride() const { return m_stride; }

        
        // TODO[rsmekens]: remove iterators
        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
        
    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;

        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_stride = 0;
            for (int i = 0; i < m_elements.size(); ++i)
            {
                BufferElement& element = m_elements[i];
                element.m_offset = offset;
                offset += element.m_size;
                m_stride += element.m_size;
            } 
        }
    };

    class VertexBuffer 
    {
    public:
        virtual ~VertexBuffer() {};

        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetBufferLayout() const = 0;

        virtual void SetData(const void* data, uint32_t dataSize) = 0;

        static Ref<VertexBuffer> Create(uint32_t size);
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };


    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {};

        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}
