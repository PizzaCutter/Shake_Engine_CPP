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
      SubTexture2D(Ref<Texture2D> inTexture, float xCoord, float yCoord, float width, float height);

      void IncrementCellIndex(int xIncrement, int yIncrement);

      Ref<Texture2D> GetTexture() const { return m_texture; }

      float GetNormalizedXCoord() const { return m_normalizedXCoord; }
      float GetNormalizedYCoord() const { return m_normalizedYCoord; }
      float GetNormalizedCellWidth() const { return m_normalizedCellWidth; }
      float GetNormalizedCellHeight() const { return m_normalizedCellHeight; }

      static Ref<SubTexture2D> CreateSubTexture(Ref<Texture2D> inTexture, const SubTextureData& subTextureData);

   private:
      float m_normalizedXCoord = 0.0f;
      float m_normalizedYCoord = 0.0f;
      float m_normalizedCellWidth = 0.0f;
      float m_normalizedCellHeight = 0.0f;

      Ref<Texture2D> m_texture;
   };
}
