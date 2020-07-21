#include "sepch.h"
#include "FileReader.h"


#include <filesystem>
#include <fstream>

namespace Shake
{
    std::string FileReader::m_AdditionalDirectoryPath = "Content/"; 
    
    std::string FileReader::ReadFile(std::string fileName)
    {
        WCHAR rawPathData[MAX_PATH];
        GetModuleFileNameW(NULL, rawPathData, MAX_PATH);

        char charPath[MAX_PATH];
        char defaultChar = ' ';
        WideCharToMultiByte(CP_ACP, 0, rawPathData, -1, charPath, MAX_PATH, &defaultChar, NULL);
        
        std::string filePath = charPath;
        // Hardcoded until content copy step works
        filePath = "E:/Documents/github/Shake_Engine_CPP/Shake_Engine/";
        const std::string completeFilePath = filePath + m_AdditionalDirectoryPath + fileName;
        std::ifstream file (completeFilePath);
        
        std::string outString;
        
        std::string outLine;
        while(getline(file, outLine))
        {
            outString += outLine + '\n';  
        }
        file.close();
        
        return outString;
    }
}
