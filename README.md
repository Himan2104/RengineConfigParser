# RENGINE CONFIG PARSER
Header only configuration file parser for [Rengine](https://himan2104.github.io/Rengine)

---
To be used internally in rengine for loading assets, settings, etc. It only supports strings, 32 bit signed integers, floats, and booleans. Not the most memory friendly or fast implementation, I know. I do not plan on fixing that, it works for now as I work on my physics engine and improve the renderer. I'll design a better system when I have time.

---

## USAGE
- Use the (static) function LoadConfig to load a config by giving its realtive path + filename.
- Syntax:
 
``` C++
std::string string_value = cfg[section_name]->GetValue<std::string>(key); //for string values [no whitespaces]
int integer_value = cfg[section_name]->GetValue<int>(key); //for 32 bit integer values
float float_value = cfg[section_name]->GetValue<float>(key); //for floating point values
bool bool_value = cfg[section_name]->GetValue<bool>(key); //for boolean values
```
- Example of a config  file

```
[SectionName]

# this is a multiline comment. inline comments are not supported.
# syntax for entries is 
# type:key=value
# avaiable types are str, int, dec and bit [stands for string, integer, decimal(float) and boolean, respectively]
# example below

str : user_name = capybara_enjoyer

[NewSection]
int : page_count = 32
dec : density = 1.52f
bit : is_viable = false
```
NOTE:
- Whitespaces not allowed in strings cause I'm a lazy fuck.
- Integers and floats will are parsed using std::stoi() and std::stof(), respectively, so all their mechanics apply.
- For booleans, true is true anything else is false i.e. 
```
bit : boolean_value_a = true            //this is true
bit : boolean_value_b = tru             //this is false
bit : boolean_value_c = false           //this is false as well
bit : boolean_value_c = ok i pull up    //and this too

you get the idea...
```
- Incorrect inputs WILL THROW EXCEPTIONS. Be ready to catch XD.
```
std::cout << config["LMAO"]->GetValue<bool>("cheeese") << std::endl;        // "LMAO" section doesn't exist so this will throw [Read access violation or some shit]
std::cout << config["Alpha"]->GetValue<std::string>("chonk") << std::endl;  // "chonk" not a valid key, will throw bad variant access
std::cout << config["Alpha"]->GetValue<int>("state_name") << std::endl;     // "state_name" is std::string not int, will throw bad variant access
```
- If you want to use this for your projects do write some code to catch exceptions and assert keys.
