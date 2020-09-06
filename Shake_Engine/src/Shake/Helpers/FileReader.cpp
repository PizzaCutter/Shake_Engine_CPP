#include "sepch.h"
#include "FileReader.h"


#include <filesystem>
#include <fstream>

namespace Shake
{
    SString FileReader::m_AdditionalDirectoryPath = "Content/"; 
    
    SString FileReader::ReadFile(SString fileName)
    {
        WCHAR rawPathData[MAX_PATH];
        GetModuleFileNameW(NULL, rawPathData, MAX_PATH);

        char charPath[MAX_PATH];
        char defaultChar = ' ';
        WideCharToMultiByte(CP_ACP, 0, rawPathData, -1, charPath, MAX_PATH, &defaultChar, NULL);
        
        SString filePath = charPath;
        // Hardcoded until content copy step works
        filePath = "E:/Documents/github/Shake_Engine_CPP/Shake_Engine/";
        const SString completeFilePath = filePath + m_AdditionalDirectoryPath + fileName;
        std::ifstream file (completeFilePath);
        
        SString outString;
        
        SString outLine;
        while(getline(file, outLine))
        {
            outString += outLine + '\n';  
        }
        file.close();
        
        return outString;
    }
}
