#include <string>
#include <fstream>
#include <iostream>

#include "../include/nlohmann/json.hpp"
using nlohmann::json;

int init_data (const std::string& data_path)
{
    auto basic_json = json::parse("{\"package_list\" :[],\"packages\" : 0}");
    std::cout << basic_json.dump(4) << std::endl;
    //write the json to data_path
    std::ofstream file_spm((data_path).c_str(), std::ios::out);
    file_spm << basic_json.dump(4);
    file_spm.close();

    return 0;
}
int add_pkg_data (const std::string& data_path, const std::string& pkg_name, const std::string& pkg_version)
{
    std::ifstream file_spm((data_path).c_str(), std::ios::in);
    std::stringstream buffer;
    buffer << file_spm.rdbuf();
    file_spm.close();
    //parsing json data
    auto pkg_info = json::parse(buffer.str());
    json o;
    o["name"] = pkg_name;
    o["version"] = pkg_version;
    pkg_info["package_list"].push_back(o);
    pkg_info["packages"] = int(pkg_info["packages"]) + 1;
    std::ofstream file_data_new((data_path).c_str(), std::ios::out);
    file_data_new << pkg_info.dump(4);
    file_data_new.close();
    return 0;
}
int rm_pkg_data (const std::string& data_path, const std::string& pkg_name)
{
    std::ifstream file_spm((data_path).c_str(), std::ios::in);
    std::stringstream buffer;
    buffer << file_spm.rdbuf();
    file_spm.close();
    //parsing json data
    auto pkg_info = json::parse(buffer.str());
    for (int i = 0; i < pkg_info["package_list"].size(); i++)
    {
        std::string name = pkg_info["package_list"][i]["name"];
        if (name == pkg_name)
        {
            pkg_info["package_list"].erase(pkg_info["package_list"].begin() + i);
            pkg_info["packages"] = int(pkg_info["packages"]) - 1;
            break;
        }
    }
    std::ofstream file_data_new((data_path).c_str(), std::ios::out);
    file_data_new << pkg_info.dump(4);
    file_data_new.close();
    return 0;
}