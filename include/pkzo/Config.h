
#ifndef _PKZO_CONFIG_H_
#define _PKZO_CONFIG_H_

#include <string>
#include <map>
#include <ostream>
#include <sstream>

namespace pkzo
{
    class Config
    {
    public:
        
        Config();

        ~Config();

        void load(const std::string& file);

        void save(const std::string& file);

        bool has_value(const std::string& section, const std::string& key);

        std::string get_value(const std::string& section, const std::string& key);

        std::string get_value(const std::string& section, const std::string& key, const std::string& fallback);

        template <typename Type>
        Type get_value(const std::string& section, const std::string& key);

        template <typename Type>
        Type get_value(const std::string& section, const std::string& key, Type fallback);

        void set_value(const std::string& section, const std::string& key, const std::string& value);

        template <typename Type>
        void set_value(const std::string& section, const std::string& key, Type value);

    private:
        std::map<std::string, std::map<std::string, std::string>> values;
    };

    template <typename Type>
    void Config::set_value(const std::string& section, const std::string& key, Type value)
    {
        std::stringstream buff;
        buff << value;

        set_value(section, key, buff.str());
    }
    
    template <> inline
    void Config::set_value<bool>(const std::string& section, const std::string& key, bool value)
    {
        set_value(section, key, value ? "true" : "false");
    }

    template <typename Type>
    Type Config::get_value(const std::string& section, const std::string& key)
    {
        std::string svalue = get_value(section, key);
        Type value;

        std::stringstream buff(svalue);
        buff >> value;

        return value;
    }

    template <typename Type>
    Type Config::get_value(const std::string& section, const std::string& key, Type fallback)
    {
        if (has_value(section, key)) 
        {
            return get_value<Type>(section, key);
        }
        else
        {
            return fallback;
        }
    }

    inline
    bool iequals(const std::string& a, const std::string& b)
    {
        unsigned int sz = a.size();
        if (b.size() != sz)
            return false;
        for (unsigned int i = 0; i < sz; ++i)
            if (tolower(a[i]) != tolower(b[i]))
                return false;
        return true;
    }

    template <> inline
    bool Config::get_value<bool>(const std::string& section, const std::string& key)
    {
        std::string svalue = get_value(section, key);
        
        if (iequals(svalue, "true"))
        {
            return true;
        }
        else if (iequals(svalue, "false"))
        {
            return false;
        }
        else
        {
            throw std::runtime_error("Not a boolean value.");
        }
    }
}

#endif
