#include<iostream>
#include"../include/RengineConfigParser.hpp"

int main()
{
    ren::Configuration config = ren::ConfigurationParser::LoadConfig("test/test.ini"); //.ini file type suffix seems misleading. Might just name it .rencfg or something later on.
    //correct vals
    std::cout << config["Alpha"]->GetValue<std::string>("state_name") << std::endl
              << config["Alpha"]->GetValue<int>("chunk_size") << std::endl
              << config["Omega"]->GetValue<std::string>("user_name") << std::endl
              << config["Omega"]->GetValue<int>("inches") << std::endl
              << config["Omega"]->GetValue<float>("twin_towers") << std::endl
              << config["Omega"]->GetValue<bool>("is_cringe") << std::endl
              << config["Omega"]->GetValue<bool>("is_friendly") << std::endl;

    //incorrect vals [comment this out to run without problems]
    std::cout << config["LMAO"]->GetValue<bool>("cheeese") << std::endl;        // "LMAO" section doesn't exist so this will throw [Read access violation or some shit]
    std::cout << config["Alpha"]->GetValue<std::string>("chonk") << std::endl;  // "chonk" not a valid key, will throw bad variant access
    std::cout << config["Alpha"]->GetValue<int>("state_name") << std::endl;     // "state_name" is std::string not int, will throw bad variant access
    //might write some in-built code to catch and log this
    //rengine version of this already does it
    //I'm just lazy to bring it here.

    return EXIT_SUCCESS;
}