# A Simple Dependency-Free C++ JSON Library

The goal of this library is to provide a C++ JSON interface that's simple to use and doesn't require any dependencies. 
This library provides all necessary operations required for working with JSON documents (see [examples](#expamles_section)). 

**Note:** The library only works with C++ 11 and newer.

- [C++ Representation of JSON](#cpp_representation_section)
- [Integration](#integration_section)
- [Documentation](#doc_section)
- [Tests](#tests_section)
- [Examples](#expamles_section)
    - [Converting a string into a json_variant](#convert_a_string_to_json_section)
    - [Converting a json_variant into a string](#convert_a_json_to_string_section)
    - [Opening, changing and saving a JSON file](#opening_changing_section)
    - [Working with simple json_variant values](#working_with_simple_section)
    - [Working with json_array](#working_with_json_array_section)
    - [Working with json_object](#working_with_json_object_section)
    - [Typecast exceptions](#typecast_exceptions_section)
        - [Handling typecast a exception](#handling_typecast_expception_section)
        - [Avoid typecast a exception](#avoid_typecast_exception_section)
    - [JSON and string escapes](#json_and_string_escapes_section)
- [Customization](#customization_section)
- [Troubleshooting](#troubleshooting_section)

### <a name="cpp_representation_section"></a>C++ Representation of JSON

All possible JSON values are represenented in the class `json_variant`. 
The datatypes are:
- int value: `json_int` (typedef of `std::int64_t`)
- double value: `double`
- bool value: `bool`
- string value: `std::string`
- array value: `json_array` (typedef of `std::vector<json_variant>`)
- object value: `json_object` (typedef of `std::map<std::string, json_variant>`)

### <a name="integration_section"></a>Integration

Since the library consists only of the two files [json_library.h](https://github.com/n0dex/cppjsonlib/blob/master/json_library.h) and [json_library.cpp](https://github.com/n0dex/cppjsonlib/blob/master/json_library.cpp) you can just download them and add them into your project.  
To use the library, add:
```cpp
// include library
#include "json_library.h"

// for convenience
using namespace json;

int main(int, char *[]) {
    ...
}
```

If you prefer to add the files seperated by classes you can download the [json_library](https://github.com/n0dex/cppjsonlib/tree/master/json_library_source) directory and include the directory into your project.   
In this case the following include should be used:
```cpp
#include "json_library_source/json_library.h"
```
### <a name="doc_section"></a>Documentation

The library is documented with doxygen. The documentation can be found [here](https://github.com/n0dex/cppjsonlib/tree/master/json_library_documentation).  
To use the documentation open [html/index.html](https://github.com/n0dex/cppjsonlib/blob/master/json_library_documentation/html/index.html) in a browser.

### <a name="tests_section"></a>Tests

The library was thoroughly tested. The test cases are written with the Qt Test Library and can be found [here](https://github.com/n0dex/cppjsonlib/tree/master/json_library_tests).

### <a name="expamles_section"></a>Examples

The following examples will show how to work with the library.

#### <a name="convert_a_string_to_json_section"></a>Converting a string into a json_variant

```cpp
json_variant json;

// intializing a json_variant from a string
json = json_variant::parse("{" 
    "\"name\": \"user\", "
    "\"age\": 22, "
    "\"favourite_values\": ["
        "2,"
        "null,"
        "false,"
        "{}"
    "] "
"}");

// intializing a json_variant from a string with more convenient writing
json = json_variant::parse(R"({
    "name": "user",
    "age": 22,
    "favourite_values": [
        2,
        null,
        false,
        {}
    ]
})");

if (json.is_valid_json()) {
    // do something with json
}
else {        
    std::cout << "The string isn't in valid JSON syntax.";
}
```

#### <a name="convert_a_json_to_string_section"></a>Converting a json_variant into a string

```cpp
json_variant json = json_variant::parse(...);
std::string str;

// convert the json_variant into a string with the default indent of 4 spaces
str = json.dump();
// convert the json_variant into a string with a indent of 2 spaces
str = json.dump(2);
// convert the json_variant into a string with no indent and no new lines
str = json.dump(0);

// converting and writing the json_variant into std::ostream directly is also possible
std::cout << json << std::endl;
```

#### <a name="opening_changing_section"></a>Opening, changing and saving a JSON file
This example assumes that there is a file called `values.json` saved on the hard drive with the following content:
```json 
{
    "age": 22,
    "favourite_values": [
        2,
        null,
        false,
        {

        }
    ],
    "name": "user"
}
```
`json_document` provides simple JSON I/O access:
```cpp
// define json document used for I/O operations
json_document doc("values.json");

// read and parse the file content
bool ok = doc.open();

// only successfull if document contains valid 
// json syntax and the file was found
if (ok) {
    // print the content
    std::cout << doc.json() << std::endl;

    // add a new subvalue in "favourite_values" and change the "age":

    // note that the reference symbol is important if 
    // you want to change the document source.
    json_variant &var = doc.json();
    json_object &obj = var.to_object();

    // change the value of age
    obj.at("age") = 44;

    // add a new value in "favourite_values" 
    json_array &arr = obj["favourite_values"].to_array();
    json_object &obj2 = arr[3].to_object();
    obj2.insert({"favourite sub value", -11});

    // save the changes into the file
    ok = doc.save();

    // only successfull if document only contains valid json_variants
    // (variants with values) and the filename is valid
    if (ok) { 
        std::cout << "document successfully saved." << std::endl;
    }

    // optional
    doc.close(); 
}
```
  
After running the code the file content will look like this:
```json 
{
    "age": 44,
    "favourite_values": [
        2,
        null,
        false,
        {
            "favourite sub value": -11
        }
    ],
    "name": "user"
}
```

#### <a name="working_with_simple_section"></a>Working with simple json_variant values        

```cpp
// the json variant currently holds no value and is invalid
json_variant var;

// will print "1"
std::cout << var.is_invalid_json() << std::endl;    

// setting the json_variant to null
var = json_variant::null;
// NOTE: to initalize a json_variant with null you 
// have to use json_variant::null, using for expample 
// nullptr will not work

// will print "0"
std::cout << var.is_invalid_json() << std::endl;

// will print "1"
std::cout << var.is_null() << std::endl;

// setting the json_variant to json_int
var = 234;

// setting the json_variant to double
var = 0.345;

// setting the json_variant to double in scientific notation
var = 2E-2;

// setting the json_variant to bool
var = true;

// setting the json_variant to std::string
var = "string value";       
```

#### <a name="working_with_json_array_section"></a>Working with json_array

Keep in mind that a `json_array` is just a `typedef` of `std::vector<json_variant>` so all `std::vector` functions work on `json_array` as well.

```cpp
// the json variant currently holds no value and is invalid
json_variant var;

// setting the json_variant to json_array
var = json_array();
// the json_array holds json_variants so this is valid syntax
var = json_array({234, 0.345, "string value"});

// add array values:

// add json_variant element "new value"
var.to_array().push_back("new value");
// adds json_variant element "false"
var.to_array().push_back(false);                

// overwrites "string value" with "string value 2"
var.to_array()[2] = "string value 2";           

// using a array reference:

// The reference symbol is important, otherwise 
// you'll get a copy and won't modify the source array
json_array &arr = var.to_array();

// add json_variant element "456"
arr.push_back(456);
 // overwrites "234" with "567"
arr[0] = 567;     
```

#### <a name="working_with_json_object_section"></a>Working with json_object

Keep in mind that a `json_object` is just a `typedef` of `std::map<std::string, json_variant>` so all `std::map` functions work on `json_object` as well.

```cpp
// the json variant currently holds no value and is invalid
json_variant var; 

// initalizing with empty json object
var = json_object();
// using the c++ 11 way to initialize
var = json_object({ {"property 1", true }, { "property 2", json_array({1, 2}) } }); 

// adding new properties with std::pair
var.to_object().insert(std::pair<std::string, json_variant>("new property 3", -2 ));

// prints "-2"
std::cout << var.to_object().at("new property 3").to_int() << std::endl; 

// adding new properties with c++ 11
var.to_object().insert({"new property", "new value"});
var.to_object().insert({"new property 2", json_variant::null });

// changing a value
var.to_object().at("property 1") = false;

// prints "0" (false)
std::cout << var.to_object().at("property 1").to_bool() << std::endl; 

// using a object reference
json_object &obj = var.to_object();
obj.at("property 2") = 100;
obj.insert({"property 5", -100});
```

#### <a name="typecast_exceptions_section"></a>Typecast exceptions

Everytime a `json_variant::to_*type*()` (`to_int()`, `to_string()`, ...) gets called the `json_variant` will try to cast the underlying value to the requested value. If the actuall value isn't the requested value a `std::runtime_error` will be thrown. To avoid handling exceptions you have to check whether the underlying value is actually the requested type. You can do so by using `is_*type*()` (`is_int()`, `is_string()`, ...)

##### <a name="handling_typecast_expception_section"></a>Handling typecast a exception

```cpp
json_variant var = 234;

try {
    // won't work since var is int
    double d = var.to_double();  
    // ...
}
catch (const std::runtime_error &e) {
    std::cout << "runtime_error: " << e.what() << std::endl;   
} 
```

##### <a name="avoid_typecast_exception_section"></a>Avoid typecast a exception

```cpp
json_variant var = 234;

// returns false
if (var.is_double()) {
    double d = var.to_double();   
    // ...
}
else {
    std::cout << "var is not double" << std::endl;   
}
```

#### <a name="json_and_string_escapes_section"></a>JSON and string escapes

All strings in a `json_variant` and its children will be unicode escaped before being converted to a string (for example when calling `json_variant::dump()`). However only the characters " and \\ will be escaped since those are the only illegal characters in a JSON string. `json_variant::unescape_string()` is able unescape ASCII-characters (other escaped characters will stay escaped). 

```cpp
// same string content
std::string unescaped = R"("name",\t user\u3093\n)";
std::string escaped   = R"("\u0022name\u0022,\u005ct user\u005cu3093\u005cn")";

// initializes json_variant with string that contains illegal json characters
json_variant var = unescaped;

std::cout << var << std::endl;
// prints: '\u0022name\u0022,\u005ct user\u005cu3093\u005cn'

std::cout << json_variant::unescape_string(escaped) << std::endl;
// prints: '"name",\t user\u3093\n'
```

### <a name="customization_section"></a>Customization

The behaviour of the library can be changed by changing defines in the header. The header will be either called [json_library.h](https://github.com/n0dex/cppjsonlib/blob/master/json_library.h) or [json_library/json_defines.h](https://github.com/n0dex/cppjsonlib/blob/master/json_library_source/json_defines.h) if you've added the complete directory.

- Defining `JSONLIB_VERBOSE_DEBUG` will enable writing debug messagess into `std::cout` and `std::cerr` that may be helpfull to you, but those messages mostly report internal library errors. 
- Changing the datatype in `JSONLIB_INT_TYPE` is possible and may be helpfull if you for expample already know that youre only working with short ints and want to reduce the memory usage. The datatype must be a *signed* int.
 

### <a name="troubleshooting_section"></a>Troubleshooting

- The libraries standard namespace is called `json`. If there are conflicting naming issues in your project you can change the namespace by changing the define `JSONLIB_NAMESPACE` in the header (where to find the header is explained in [Customization](#customization_section)). 
