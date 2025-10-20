#include <iostream>
#include <fstream>
#include <string>

class Crypto {
public:
    static std::string caesarEncrypt(const std::string& text,int key) {
        std::string result = text;
        for (char& c : result) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                int offset = (c - base + key) % 26;
                if (offset < 0) {
                    offset += 26;
                }
                c = offset + base;
            }
        }
        return result;
    }

    static std::string caesarDecrypt(const std::string& cipherText,int key) {
        Crypto decryptor;
        return decryptor.caesarEncrypt(cipherText,-key);
    }
};


class FileHandler {
public:
    static std::string readFromFile(const std::string& filePath) {
        std::ifstream file(filePath); 
        if (!file.is_open()) { 
            std::cerr << "未能成功打开读取文件 " << filePath << std::endl;
            return ""; 
        }

        std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
        file.close(); 
        return content;
    }

    static bool writeToFile(const std::string& content, const std::string& filePath) {
        std::ofstream file(filePath); 
        if (!file.is_open()) { 
            std::cerr << "未能成功打开保存文件" << filePath << std::endl;
            return false; 
        }
        file << content; 
        file.close(); 
        return true; 
    }
};


class Menu {
public:
    void showMainMenu() {
        int choice;
        while (true) {
            std::cout << "\n=====凯撒加密=====" << std::endl;
            std::cout << "1. 加密文本" << std::endl;
            std::cout << "2. 解密密文" << std::endl;
            std::cout << "3. 加密文件" << std::endl;
            std::cout << "4. 解密文件" << std::endl;
            std::cout << "0. 退出程序" << std::endl;
            std::cout << "请输入选项: ";
            std::cin >> choice;
            std::cin.ignore();
            switch (choice) {
                case 1:
                    encryptText();
                    break;
                case 2:
                    decryptText();
                    break;
                case 3:
                    encryptFile();
                    break;
                case 4:
                    decryptFile();
                    break;
                case 0:
                    std::cout << "已退出程序" << std::endl;
                    return;
                default:
                    std::cout << "无效选项，请重新输入" << std::endl;
            }
        }
    }

    void encryptText() {
        std::string text;
        std::cout << "请输入要加密的文本: ";
        std::getline(std::cin, text); 
        std::cout<<"请输入密钥：";
        int key;
        std::cin>>key;
        std::string cipherText = Crypto::caesarEncrypt(text,key); 
        std::cout << "加密后的文本: " << cipherText << std::endl; 
    }

    void decryptText() {
        std::string cipherText;
        std::cout << "请输入要解密的密文: ";
        std::getline(std::cin, cipherText); 
        std::cout<<"请输入密钥：";
        int key;
        std::cin>>key;
        std::string text = Crypto::caesarDecrypt(cipherText,key); 
        std::cout << "解密后的文本: " << text << std::endl; 
    }

    void encryptFile() {
        std::string inputPath, outputPath;
        std::cout << "请输入源文件路径: ";
        std::getline(std::cin, inputPath); 
        std::cout << "请输入加密后文件路径: ";
        std::getline(std::cin, outputPath); 
        std::cout<<"请输入密钥：";
        int key;
        std::cin>>key;
        std::string content = FileHandler::readFromFile(inputPath); 
        if (content.empty()) { 
            return;
        }
        std::string cipherText = Crypto::caesarEncrypt(content,key); 
        if (FileHandler::writeToFile(cipherText, outputPath)) { 
            std::cout << "文件加密成功，已保存到: " << outputPath << std::endl;
        }
    }

    void decryptFile() {
        std::string inputPath, outputPath;
        std::cout << "请输入加密文件路径: ";
        std::getline(std::cin, inputPath); 
        std::cout << "请输入解密后文件路径: ";
        std::getline(std::cin, outputPath); 
        std::cout<<"请输入密钥：";
        int key;
        std::cin>>key;
        std::string cipherText = FileHandler::readFromFile(inputPath);
        if (cipherText.empty()) { 
            return;
        }
        std::string text = Crypto::caesarDecrypt(cipherText,key); 
        if (FileHandler::writeToFile(text, outputPath)) { 
            std::cout << "文件解密成功，已保存到: " << outputPath << std::endl;
        }
    }
};


int main(){
        Menu menu; 
        menu.showMainMenu(); 
}