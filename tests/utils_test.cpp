// Add this test code to your main.cpp or create a separate test function
// This will help debug your file reading issues

#include <iostream>
#include <filesystem>
#include "http_utils.h"

void testFileReading() {
    std::cout << "=== File Reading Test ===" << std::endl;
    
    // Test 1: Check current working directory
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    
    // Test 2: List files in current directory
    std::cout << "\nFiles in current directory:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::cout << "  " << entry.path() << std::endl;
    }
    
    // Test 3: Check if public folder exists
    if (std::filesystem::exists("public")) {
        std::cout << "\n✅ 'public' folder exists" << std::endl;
        
        // List files in public folder
        std::cout << "Files in public folder:" << std::endl;
        for (const auto& entry : std::filesystem::directory_iterator("public")) {
            std::cout << "  " << entry.path() << std::endl;
        }
    } else {
        std::cout << "\n❌ 'public' folder does NOT exist" << std::endl;
    }
    
    // Test 4: Try to read specific files
    std::vector<std::string> testPaths = {
        "public/index.html",
        "public/about.html", 
        "public/style.css",
        "./public/index.html",    // Alternative path format
        "src/../public/index.html" // Another alternative
    };
    
    std::cout << "\n=== Testing File Reading ===" << std::endl;
    for (const auto& path : testPaths) {
        std::cout << "\nTrying to read: " << path << std::endl;
        
        // Check if file exists first
        if (std::filesystem::exists(path)) {
            std::cout << "  ✅ File exists" << std::endl;
            
            // Try your readFileContents function
            std::string content = readFileContents(path);
            if (content != "Error loading file") {
                std::cout << "  ✅ Successfully read " << content.length() << " bytes" << std::endl;
                std::cout << "  First 100 chars: " << content.substr(0, 100) << "..." << std::endl;
            } else {
                std::cout << "  ❌ readFileContents failed" << std::endl;
            }
        } else {
            std::cout << "  ❌ File does not exist" << std::endl;
        }
    }
    
    // Test 5: Create a simple test file to ensure function works
    std::cout << "\n=== Creating Test File ===" << std::endl;
    std::ofstream testFile("test.html");
    testFile << "<html><body><h1>Test File</h1></body></html>";
    testFile.close();
    
    std::string testContent = readFileContents("test.html");
    if (testContent != "Error loading file") {
        std::cout << "✅ Test file read successfully: " << testContent << std::endl;
    } else {
        std::cout << "❌ Even simple test file failed" << std::endl;
    }
}