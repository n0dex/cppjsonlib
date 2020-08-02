#include "json_variant.h"
#include "json_parser.h"

namespace JSONLIB_NAMESPACE {

json_variant::json_variant(int value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(json_int value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(double value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(bool value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(const char *value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(const std::string &value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(const json_array &value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(const json_object &value) : json_variant() {
    set_value(value);
}

json_variant::json_variant(const json_array *value) {
    set_value(*value);
}

json_variant::json_variant(const json_object *value) {
    set_value(*value);
}

json_variant::json_variant(json_variant::json_null_type) : json_variant() {
    set_value(null);
}

json_variant::json_variant(const json_variant &other) : json_variant() {
    set_value(other);
}

json_variant::json_variant() {
    this->type = json_invalid_variant;
    this->value = nullptr;
}

json_variant::~json_variant() {
    free_memory();
}

void json_variant::set_value(int value) {
    free_memory();
    type = json_int_variant;
    this->value = static_cast<void*>(new json_int(value));
}

void json_variant::set_value(json_int value) {
    free_memory();
    type = json_int_variant;
    this->value = static_cast<void*>(new json_int(value));
}

void json_variant::set_value(double value) {
    free_memory();
    type = json_double_variant;
    this->value = static_cast<void*>(new double(value));
}

void json_variant::set_value(bool value) {
    free_memory();
    type = json_bool_variant;
    this->value = static_cast<void*>(new bool(value));
}

void json_variant::set_value(const char *value) {
    free_memory();
    type = json_string_variant;
    this->value = static_cast<void*>(new std::string(value));
}

void json_variant::set_value(const std::string &value) {
    free_memory();
    type = json_string_variant;
    this->value = static_cast<void*>(new std::string(value));
}

void json_variant::set_value(const json_array &value){
    free_memory();
    type = json_array_variant;
    this->value = static_cast<void*>(new json_array(value));
}

void json_variant::set_value(const json_object &value){
    free_memory();
    type = json_object_variant;
    this->value = static_cast<void*>(new json_object(value));
}

void json_variant::set_value(json_variant::json_null_type){
    free_memory();
    type = json_null_variant;
    this->value = nullptr;
}

void json_variant::set_value(const json_variant &other) {
    free_memory();

    this->type = other.type;
    switch (other.type) {
    case json_int_variant:
        this->value = new int(other.to_int());
        break;
    case json_double_variant:
        this->value = new double(other.to_double());
        break;
    case json_bool_variant:
        this->value = new bool(other.to_bool());
        break;
    case json_array_variant:
        this->value = new json_array(other.to_array());
        break;
    case json_object_variant:
        this->value = new json_object(other.to_object());
        break;
    case json_string_variant:
        this->value = new std::string(other.to_string());
        break;
    case json_null_variant:
        this->value = nullptr;
        break;
    case json_invalid_variant:
        this->value = nullptr;
        break;
    default:
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_variant::set_value: ERROR: unknown json_variant_type: " << type << std::endl;
#endif
        break;
    }
}

bool json_variant::is_int() const {
    return (json_variant_type::json_int_variant == this->type);
}

bool json_variant::is_double() const {
    return (json_variant_type::json_double_variant == this->type);
}

bool json_variant::is_bool() const {
    return (json_variant_type::json_bool_variant == this->type);
}

bool json_variant::is_string() const {
    return (json_variant_type::json_string_variant == this->type);
}

bool json_variant::is_array() const {
    return (json_variant_type::json_array_variant == this->type);
}

bool json_variant::is_object() const {
    return (json_variant_type::json_object_variant == this->type);
}

bool json_variant::is_null() const {
    return (json_variant_type::json_null_variant == this->type);
}

bool json_variant::is_valid_value() const {
    return (json_variant_type::json_invalid_variant != this->type);
}

bool json_variant::is_invalid_value() const {
    return (json_variant_type::json_invalid_variant == this->type);
}

bool json_variant::is_invalid_json() const {
    if (this->is_invalid_value()) return true;

    if (this->is_object()) {
        json_object json_obj = this->to_object();
        for (auto iter = json_obj.begin(); iter != json_obj.end(); ++iter) {
            if (iter->second.is_invalid_json()) return true;
        }
    }
    else if (this->is_array()) {
        json_array json_arr = this->to_array();
        for (auto& obj : json_arr) {
            if (obj.is_invalid_json()) return true;
        }
    }

    return false;
}

bool json_variant::is_valid_json() const {
    return !is_invalid_json();
}

json_int json_variant::to_int() const {
    if (!is_int() || !value) throw std::runtime_error("json_variant::to_int: bad cast");
    return *(static_cast<int*>(value));
}

double json_variant::to_double() const {
    if (!is_double() || !value) throw std::runtime_error("json_variant::to_double: bad cast");
    return *(static_cast<double*>(value));
}

bool json_variant::to_bool() const {
    if (!is_bool() || !value) throw std::runtime_error("json_variant::to_bool: bad cast");
    return *(static_cast<bool*>(value));
}

std::string json_variant::to_string() const {
    if (!is_string() || !value) throw std::runtime_error("json_variant::to_string: bad cast");
    return *(static_cast<std::string*>(value));
}

json_array json_variant::to_array() const {
    if (!is_array() || !value) throw std::runtime_error("json_variant::to_array: bad cast");
    return *(static_cast<json_array*>(value));
}

json_array &json_variant::to_array() {
    if (!is_array() || !value) throw std::runtime_error("json_variant::to_array: bad cast");
    return *(static_cast<json_array*>(value));
}

json_object json_variant::to_object() const {
    if (!is_object() || !value) throw std::runtime_error("json_variant::to_object: bad cast");
    return *(static_cast<json_object*>(value));
}

json_object &json_variant::to_object() {
    if (!is_object() || !value) throw std::runtime_error("json_variant::to_object: bad cast");
    return *(static_cast<json_object*>(value));
}

bool json_variant::equals(const json_variant &other) const {
    if (this->type != other.type) {
        return false;
    }

    switch (type) {
    case json_int_variant:
        return (this->to_int() == other.to_int());
    case json_double_variant:
        return (std::abs(this->to_double() - other.to_double()) < std::numeric_limits<double>::epsilon());
    case json_bool_variant:
        return (this->to_bool() == other.to_bool());
    case json_array_variant:
        return (this->to_array() == other.to_array());
    case json_object_variant:
        return (this->to_object() == other.to_object());
    case json_string_variant:
        return  (this->to_string() == other.to_string());
    case json_null_variant:
        return true;
        break;
    case json_invalid_variant:
        return true;
        break;
    default:
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_variant::free_memory: ERROR: unknown json_variant_type: " << type << std::endl;
#endif
        break;
    }

    return false;
}

std::string json_variant::dump(int indent) const {
    std::stringstream stream;
    dump(*this, stream, 0, indent);
    return stream.str();
}

json_variant json_variant::parse(const std::string& json_string) {
    return json_parser::parse(json_string);
}

std::string json_variant::escape_string(const std::string &str) {
    std::ostringstream stream;
    for (const char &c : str) {
        if (c == '"' || c == '\\') {
            stream << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
        }
        else {
            stream << c;
        }
    }
    return stream.str();
}

std::string json_variant::unescape_string(std::string str) {
    std::ostringstream stream;

    for(std::string::iterator it = str.begin(); it != str.end(); it++) {
        char hex[5];
        if (std::next(it, 5) <= str.end() && *it == '\\' && *(std::next(it, 1)) == 'u') {
            hex[0] = *std::next(it, 2);
            hex[1] = *std::next(it, 3);
            hex[2] = *std::next(it, 4);
            hex[3] = *std::next(it, 5);
            hex[4] = '\0';

            long char_val = strtol(hex, nullptr, 16);

            if (char_val < 127) {
                std::advance(it, 5);
                stream << static_cast<char>(char_val);
            }
            else {
                stream << *it;
            }
        }
        else {
            stream << *it;
        }
    }

    return stream.str();
}

void json_variant::dump(const json_variant &variant, std::stringstream &stream, int current_indent, int indent_increase) const {
    switch (variant.type) {
    case json_int_variant: {
        stream << variant.to_int();
        break;
    }
    case json_double_variant: {
        stream << variant.to_double();
        break;
    }
    case json_bool_variant: {
        if (variant.to_bool()) {
            stream << "true";
        }
        else {
            stream << "false";
        }
        break;
    }
    case json_string_variant: {
        stream << "\"" << escape_string(variant.to_string()) << "\"";
        break;
    }
    case json_array_variant: {
        json_array json_arr = variant.to_array();
        stream << "[";
        if (indent_increase > 0) {
            stream << std::endl;
        }

        for (auto& obj : json_arr) {
            stream << fill_indent(current_indent+indent_increase);
            dump(obj, stream, current_indent+indent_increase, indent_increase);

            if (&obj != &json_arr.back()) {
                stream << ",";
            }
            if (indent_increase > 0) {
                stream << std::endl;
            }

        }

        if (indent_increase > 0) {
            stream << fill_indent(current_indent);
        }

        stream << "]";
        break;
    }
    case json_object_variant: {
        json_object json_obj = variant.to_object();
        stream << "{";
        if (indent_increase > 0) {
            stream << std::endl;
        }

        for (auto iter = json_obj.begin(); iter != json_obj.end();) {
            stream << fill_indent(current_indent+indent_increase) << "\"" << iter->first;

            if (indent_increase > 0) {
                stream << "\": ";
            }
            else {
                stream << "\":";
            }

            dump(iter->second, stream, current_indent+indent_increase, indent_increase);

            if (++iter != json_obj.end()) {
                stream << ",";
                if (indent_increase > 0) {
                    stream << std::endl;
                }
            }
        }

        if (indent_increase > 0) {
            stream << std::endl << fill_indent(current_indent);
        }
        stream << "}";
        break;
    }
    case json_null_variant: {
        stream << "null";
        break;
    }
    case json_invalid_variant: {
        stream << "(invalid json variant)";
        break;
    }
    default:{
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_variant::dump: ERROR: unknown json_variant_type: " << type << std::endl;
#endif
        break;
    }
    }
}

std::string json_variant::fill_indent(int indent) const {
    return std::string(indent, ' ');
}

void json_variant::free_memory() {
    if (!value) {
        return;
    }

    switch (type) {
    case json_int_variant:
        delete static_cast<json_int*>(value);
        break;
    case json_double_variant:
        delete static_cast<double*>(value);
        break;
    case json_bool_variant:
        delete static_cast<bool*>(value);
        break;
    case json_array_variant:
        delete static_cast<json_array*>(value);
        break;
    case json_object_variant:
        delete static_cast<json_object*>(value);
        break;
    case json_string_variant:
        delete static_cast<std::string*>(value);
        break;
    case json_null_variant:
        break;
    case json_invalid_variant:
        break;
    default:
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_variant::free_memory: ERROR: unknown json_variant_type: " << type << std::endl;
#endif
        break;
    }

    value = nullptr;
}

} // namespace
