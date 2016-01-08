
#include "Config.h"

#include <fstream>
#include <compose.h>

#include "ConfigParser.h"

namespace pkzo
{
    bool is_identifier(const std::string& str)
    {
        static const char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
        return str.find_first_not_of(valid_chars) == std::string::npos;
    }

    Config::Config() {}

    Config::~Config() {}

    void Config::load(const std::string & file)
    {
        std::string section;
        std::map<std::string, std::map<std::string, std::string>> tmp;
        
        ConfigParser parser;

        parser.on_section_begin([&] (const std::string& name) {
            section = name;        
        });
        parser.on_key_value_pair([&] (const std::string& key, const std::string& value) {
            tmp[section][key] = value;
        });

        parser.parse(file);

        values = tmp;
    }

    void Config::save(const std::string & file)
    {
        std::ofstream out(file);        
        if (! out.is_open())
        {
            throw std::logic_error(compose("Failed to open %0 for writing.", file));
        }

        for (auto section : values)
        {
            out << "[" << section.first << "]" << std::endl;
            for (auto key_value : section.second)
            {
                if (is_identifier(key_value.second))
                {
                    out << "  " << key_value.first << " = " << key_value.second << std::endl;
                }
                else
                {
                    out << "  " << key_value.first << " = \"" << key_value.second << "\"" << std::endl;
                }
            }
            out << std::endl; // for readability
        }
    }
    
    bool Config::has_value(const std::string& section, const std::string& key)
    {
        auto si = values.find(section);
        if (si == values.end())
        {
            return false;
        }

        auto vi = si->second.find(key);
        if (vi == si->second.end())
        {
            return false;
        }

        return true;
    }

    std::string Config::get_value(const std::string & section, const std::string & key)
    {
        auto si = values.find(section);
        if (si == values.end())
        {
            throw std::logic_error(compose("Section %0 not in config.", section));
        }

        auto vi = si->second.find(key);
        if (vi == si->second.end())
        {
            throw std::logic_error(compose("Section %0 has no key %1 in config.", section, key));
        }

        return vi->second;
    }

    std::string Config::get_value(const std::string& section, const std::string& key, const std::string& fallback)
    {
        if (has_value(section, key)) 
        {
            return get_value(section, key);
        }
        else
        {
            return fallback;
        }
    }

    void Config::set_value(const std::string & section, const std::string & key, const std::string & value)
    {
        if (! is_identifier(section))
        {
            throw std::logic_error(compose("'%0' is not a valid identifier.", section));
        }
        
        if (! is_identifier(key))
        {
            throw std::logic_error(compose("'%0' is not a valid identifier.", key));
        }

        values[section][key] = value;
    }
}
