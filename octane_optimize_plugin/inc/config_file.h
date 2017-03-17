#pragma once

#include <tuple>
#include <string>

#include "config_file_parser.h"

namespace config_file {

    class ConfigFile {
    public:
        // ����Ĭ�ϵ�copy�����븴�ƹ���
        // ����Ĭ�ϵ��ƶ�copy�������ƶ����ƹ���
        ConfigFile(const ConfigFile&) = delete;
        ConfigFile& operator =(const ConfigFile&) = delete;
        ConfigFile(const ConfigFile&&) = delete;
        ConfigFile& operator =(const ConfigFile&&) = delete;

        static ConfigFile& Get();
        ~ConfigFile();

        void Setup(const std::string& configFileName);
        std::tuple<std::string, bool> Read(const std::string& key);
        void Write(const std::string& key, const std::string& value) const;
        bool IsReadable() const;

    private:
        // ���캯������˽��������,��ֹ���������ʷ����������ʵ��
        ConfigFile();
        
    private:
        std::string config_file_name_;
        config_file_parser::ConfigFileParser* config_file_parser_ = nullptr;
    };
}
