#pragma once

namespace Shake
{
    // Should probably become single ton of somme sort so we can multi thread this and pool some data instead of re-reading multiple times since IO is slow :D  
    class FileReader
    {
    public:
        static std::string ReadFile(std::string filePath);

    private:
        static std::string m_AdditionalDirectoryPath;
    };
}
