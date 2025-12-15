/**
 * @name Json
 * @author Sunny
 * @date 15-12-2025
 */
#pragma once
#include <Arduino.h>
class Json
{
private:
    String content;  // String content
    bool firstField; // for adding comma

    /**
     * @name addComma
     * @author Sunny
     * @date 15-12-2025
     */
    void addComma()
    {
        if (firstField)
        {
            firstField = false;
        }
        else
        {
            content += ",";
        }
    }

public:
    /**
     * @name Json
     * @author Sunny
     * @date 15-12-2025
     * @details construct function
     */
    Json()
    {
        content = "{";
        firstField = true;
    }

    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append String value
     * @param key key name
     * @param value key's value
     */
    void add(const String &key, const char* value)
    {
        addComma();
        content += "\"" + key + "\":\"" + value + "\"";
    }

    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append int value
     * @param key key name
     * @param value key's value
     */
    void add(const String &key, int value)
    {
        addComma();
        content += "\"" + key + "\":" + String(value);
    }

    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append float value
     * @param key key name
     * @param value key's value
     */
    void add(const String &key, float value, int precision = 2)
    {
        addComma();
        content += "\"" + key + "\":" + String(value, precision);
    }
    
    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append boolean value
     * @param key key name
     * @param value key's value
     */
    void add(const String& key, bool value) {
        addComma();
        content += "\"" + key + "\":" + (value ? "true" : "false");
    }

    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append Json
     * @param key key name
     * @param value key's value
     */
    void add(const String& key, Json& nested) {
        addComma();
        content += "\"" + key + "\":" + nested.toString();
    }

    /**
     * @name add
     * @author Sunny
     * @date 15-12-2025
     * @details append Json array
     * @param key key name
     * @param value key's value
     * @param len length of array
     */
    void addArray(const String& key, Json* arr[], int len) {
        addComma();
        content += "\"" + key + "\":[";
        for(int i = 0; i < len; i++){
            content += arr[i]->toString();
            if(i < len-1) content += ",";
        }
        content += "]";
    }

     /**
     * @name toString
     * @author Sunny
     * @date 15-12-2025
     * @details show json String
     */
    String toString() {
        return content + "}";
    }
};