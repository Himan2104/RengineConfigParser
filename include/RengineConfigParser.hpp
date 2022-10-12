#pragma once

#include<memory>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<fstream>
#include<variant>

namespace ren
{
    using ConfigVariant = std::variant<std::string, int, float, bool>;

    class Section
    {
    private:
        
        std::map<std::string, ConfigVariant> _config_values;

    public:
        //Gets the value of variant 
        //Specified type and key must be correct or it will throw
        //Be prepared to catch XD
        template<typename value_type>
        value_type GetValue(const std::string& key)
        {
            //static assert key
            return std::get<value_type>(_config_values[key]);
        }
        friend class ConfigurationParser;
    };

    class Configuration
    {
    private:
        
        std::map<std::string, std::unique_ptr<Section>> _sections;

    public:
        //Pretty self explanatory -_-
        //Hint: Shits out the raw pointer to section
        Section* operator[](const std::string& section)
        {
            //static assert section name
            return _sections[section].get();
        }

        friend class ConfigurationParser;
    };

    //Class to load configs
    //Will probably add a way to save as well later on... We'll see.
    class ConfigurationParser
    {
    public:
        //Loads a config file from given filename (must also include relative path)
        static Configuration LoadConfig(const std::string& filename)
        {
            Configuration config;
            std::ifstream file;
            file.open(filename);
            if (!file.is_open())
            {
                return config;
            }
            std::string line;
            std::string currentSection;
            while (std::getline(file, line))
            {
                if (line[0] == '#' || line.empty()) continue;
                line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // remove whitespaces
                if (line[0] == '[')
                {
                    std::string sectionName = line.substr(1, line.find(']') - 1);
                    config._sections.insert(std::make_pair(sectionName, new Section));
                    currentSection = sectionName;
                    continue;
                }
                std::string key, value, type;
                size_t type_index = line.find(':');
                size_t value_index = line.find('=');
                type = line.substr(0, type_index);
                key = line.substr(type_index + 1, value_index - type_index - 1);
                value = line.substr(value_index + 1);

                ValueType vt = ValueHashMap.find(type) != ValueHashMap.end() ? ValueHashMap.at(type) : ValueType::ERROR;

                switch (vt)
                {
                case ValueType::ERROR:
                    //log type error, yet pass value as a string
                    config._sections[currentSection]->_config_values.insert(std::make_pair(key, value));
                    break;
                case ValueType::STRING:
                    config._sections[currentSection]->_config_values.insert(std::make_pair(key, value));
                    break;
                case ValueType::INTEGER:
                    config._sections[currentSection]->_config_values.insert(std::make_pair(key, std::stoi(value)));
                    break;
                case ValueType::FLOAT:
                    config._sections[currentSection]->_config_values.insert(std::make_pair(key, std::stof(value)));
                    break;
                case ValueType::BOOLEAN:
                    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return std::tolower(c); });
                    config._sections[currentSection]->_config_values.insert(std::make_pair(key, value == "true"));
                    break;
                default:
                    //unknown error
                    break;
                }
            }
            return config;
        }



    private:

        //this is the beginning of dog water code cringe fest
        //couldn't find a better apporoach you might ask
        //no time I'd argue

        enum class ValueType
        {
            STRING = 0,
            INTEGER = 1,
            FLOAT = 2,
            BOOLEAN = 3,
            ERROR = 4
        };

        static const std::unordered_map<std::string, ValueType> ValueHashMap;
    };

    const std::unordered_map<std::string, ConfigurationParser::ValueType> ConfigurationParser::ValueHashMap
    {
        std::make_pair("str", ValueType::STRING),
        std::make_pair("int", ValueType::INTEGER),
        std::make_pair("dec", ValueType::FLOAT),
        std::make_pair("bit", ValueType::BOOLEAN)
    };

    //this is the end of dog water code cringe fest

}