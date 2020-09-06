#pragma once
#include "Texture.h"

namespace Shake
{
   struct SubTextureData
   {
      SubTextureData(int inCellXIndex, int inCellYIndex, int inCellWidthInPixels, int inCellHeightInPixels)
      {
         cellXIndex = inCellXIndex;
         cellYIndex = inCellYIndex;
         cellWidthInPixels = inCellWidthInPixels;
         cellHeightInPixels = inCellHeightInPixels;
      }
      
      int cellXIndex = 0;
      int cellYIndex = 0;
      int cellWidthInPixels = 0;
      int cellHeightInPixels = 0;
   };
   
   class SubTexture2D
   {
   public:
      SubTexture2D(SharedPtr<Texture2D> inTexture, float xCoord, float yCoord, float width, float height);

      SharedPtr<Texture2D> GetTexture() const { return m_texture; }

      float GetNormalizedXCoord() const { return m_normalizedXCoord; }
      float GetNormalizedYCoord() const { return m_normalizedYCoord; }
      float GetNormalizedCellWidth() const { return m_normalizedCellWidth; }
      float GetNormalizedCellHeight() const { return m_normalizedCellHeight; }

      static SharedPtr<SubTexture2D> CreateSubTexture(SharedPtr<Texture2D> inTexture, const SubTextureData& subTextureData);

   private:
      // TODO[rsmekens]: move to vector2 instead of individual floats 
      float m_normalizedXCoord = 0.0f;
      float m_normalizedYCoord = 0.0f;
      float m_normalizedCellWidth = 0.0f;
      float m_normalizedCellHeight = 0.0f;

      SharedPtr<Texture2D> m_texture;
   };
}
