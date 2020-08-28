#include "sepch.h"
#include "SubTexture2D.h"

namespace Shake
{
    Ref<SubTexture2D> SubTexture2D::CreateSubTexture(Ref<Texture2D> inTexture,
                                                const SubTextureData& subTextureData)
    {
        const int32_t textureWidth = inTexture->GetWidth();
        const int32_t textureHeight = inTexture->GetHeight();
        
        const float normalizedCellWidth = static_cast<float>(subTextureData.cellWidthInPixels) / static_cast<float>(textureWidth);
        const float normalizedCellHeight = static_cast<float>(subTextureData.cellHeightInPixels) / static_cast<float>(textureHeight);
        const float xCoord = subTextureData.cellXIndex * normalizedCellWidth;
        const float yCoord = subTextureData.cellYIndex * normalizedCellHeight;
        
        return std::make_shared<SubTexture2D>(SubTexture2D(inTexture, xCoord, yCoord, normalizedCellWidth, normalizedCellHeight));
    }

    SubTexture2D::SubTexture2D(Ref<Texture2D> inTexture, float xCoord, float yCoord, float width, float height)
    {
        m_texture = inTexture;
        m_normalizedXCoord = xCoord;
        m_normalizedYCoord = yCoord;
        m_normalizedCellWidth = width;
        m_normalizedCellHeight = height;
    }

    void SubTexture2D::IncrementCellIndex(int xIncrement, int yIncrement)
    {
        m_normalizedXCoord += xIncrement * m_normalizedCellWidth;
        m_normalizedYCoord += yIncrement * m_normalizedCellHeight;
    }
}
