#include "json_library.h"

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

json_variant json_parser::parse(const std::string &json_string) {
    std::size_t len = json_string.size();

    // Index 0 won't be used to store values since the position is
    // reserved to indicate invalid routes in the grammar.
    char chars[len+1];
    strcpy((chars+1), json_string.c_str());

    tokens toks(chars, len+1);

    return match_json(&toks);
}

json_parser::json_parser() {}

json_variant json_parser::match_json(tokens *toks) {
    try {
        token_index result = match_element(1, toks);

        std::size_t last_token_pos = result.first;
        json_variant node = result.second;

        if (node.is_valid_value() && last_token_pos != 0 && last_token_pos == toks->size) {
            return node;
        }
        else {
            return json_variant();
        }
    }
    catch(const std::runtime_error& e) {
        return json_variant();
    }
}

std::string json_parser::combine_tokens_to_string(std::size_t start_token, std::size_t end_token, tokens *toks) {
#ifdef JSONLIB_VERBOSE_DEBUG
    if (!toks->valid_pos(start_token)) {
        std::cerr << "json_parser::merge_tokens_to_string: ERROR: invalid startToken" << std::endl;
    }
    if (!toks->valid_pos(end_token)) {
        std::cerr << "json_parser::merge_tokens_to_string: ERROR: invalid endToken" << std::endl;
    }
#endif

    std::string res;
    for (std::size_t i=start_token; i<=end_token; i++) {
        res += toks->at(i);
    }
    return res;
}

bool json_parser::is_int(const std::string &number) {
    char* p;
    strtol(number.c_str(), &p, 10);
    return (*p == 0);
}

json_int json_parser::string_to_int(const std::string &number) {
    try {
        return std::stoll(number.c_str());
    }
    catch (std::invalid_argument) {
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_parser::string_to_int: ERROR: a number conversion exception occurred" << std::endl;
#endif
        return -1;
    }
}

double json_parser::string_to_double(const std::string &number) {
    try {
        return std::stod(number.c_str());
    }
    catch (std::invalid_argument) {
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cerr << "json_parser::string_to_double: ERROR: a number conversion exception occurred" << std::endl;
#endif
        return -1;
    }
}

json_parser::token_index json_parser::match_ws(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {pos, json_variant()};

    auto token = toks->at(pos);
    if (token == ' ' || token == '\n' || token == '\r' || token == '\\') {
        return match_ws(pos+1, toks);
    }

    return {pos, json_variant()};
}

json_parser::token_index json_parser::match_sign(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {pos, json_variant()};

    auto token = toks->at(pos);
    if (token == '+' || token == '-') {
        return {pos+1, json_variant()};
    }

    return {pos, json_variant()};
}

json_parser::token_index json_parser::match_exponent(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {pos, json_variant()};;

    auto token = toks->at(pos);
    if (token == 'e' || token == 'E') {
        auto res = match_sign(pos+1, toks);
        if (res.first != 0) {
            return match_digits(res.first, toks);

        }
        return {0, json_variant()};
    }

    return {pos, json_variant()};
}

json_parser::token_index json_parser::match_onenine(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token >= '1' && token <= '9') {
        return {pos+1, json_variant()};
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_digit(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '0') {
        return {pos+1, json_variant()};
    }

    return match_onenine(pos, toks);
}

json_parser::token_index json_parser::match_digits(std::size_t pos, tokens *toks) {
    std::size_t initial_pos = pos;
    while (toks->valid_pos(pos)) {
         std::size_t new_pos = match_digit(pos, toks).first;
         if (new_pos == 0) {
             break;
         }
         pos = new_pos;
    }
    return {(pos == initial_pos ? 0 : pos), json_variant()};
}

json_parser::token_index json_parser::match_integer(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '-') {
        std::size_t pos2 = match_onenine(pos+1, toks).first;
        if (pos2 != 0) {
            pos2 = match_digits(pos2, toks).first;
            if (pos2 != 0) {
                return {pos2, json_variant()};
            }
        }

        return match_digit(pos+1, toks);
    }

    std::size_t pos2 = match_onenine(pos, toks).first;
    if (pos2 != 0) {
        pos2 = match_digits(pos2, toks).first;
        if (pos2 != 0) {
            return {pos2, json_variant()};
        }
    }

    return match_digit(pos, toks);
}

json_parser::token_index json_parser::match_fraction(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {pos, json_variant()};

    auto token = toks->at(pos);
    if (token == '.') {
        return match_digits(pos+1, toks);
    }

    return {pos, json_variant()};
}

json_parser::token_index json_parser::match_number(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    std::size_t pos2 = match_integer(pos, toks).first;
    if (pos2 != 0) {
        pos2 = match_fraction(pos2, toks).first;
        if (pos2 != 0) {
            pos2 = match_exponent(pos2, toks).first;
            if (pos2 != 0) {
                std::string number = combine_tokens_to_string(pos, pos2-1, toks);
                if (is_int(number)) {
                    return {pos2, string_to_int(number)};
                }
                else {
                    return {pos2, string_to_double(number)};
                }
            }
        }
    }
    return {0, json_variant()};
}

json_parser::token_index json_parser::match_hex(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    std::size_t pos2 = match_digit(pos, toks).first;
    if (pos2 != 0) {
        return {pos2, json_variant()};
    }

    auto token = toks->at(pos);
    if ((token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
        return {pos+1, json_variant()};
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_escape(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '"' || token == '\\' || token == '/' || token == 'b' || token == 'f' || token == 'n' || token == 'r' || token == 't') {
        return {pos+1, json_variant()};
    }

    if (token == 'u') {
        pos = match_hex(pos+1, toks).first;
        if (pos != 0) {
            pos = match_hex(pos, toks).first;
            if (pos != 0) {
                pos = match_hex(pos, toks).first;
                if (pos != 0) {
                    return match_hex(pos, toks);
                }
            }
        }
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_character(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token != '"' && token != '\\') {
        return {pos+1, json_variant()};
    }

    if (token == '\\') {
        return match_escape(pos+1, toks);
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_characters(std::size_t pos, tokens *toks) {
    while (toks->valid_pos(pos)) {
         std::size_t new_pos = match_character(pos, toks).first;
         if (new_pos == 0) {
             break;
         }
         pos = new_pos;
    }
    return {pos, json_variant()};
}

json_parser::token_index json_parser::match_string(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '"') {
        std::size_t pos2 = match_characters(pos+1, toks).first;

        if (pos2 != 0 && toks->valid_pos(pos2)) {
            token = toks->at(pos2);
            if (token == '"') {
                return {pos2+1, combine_tokens_to_string(pos+1, pos2-1, toks)};
            }
        }
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_true(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos+3)) return {0, json_variant()};

    auto t = toks->at(pos);
    auto r = toks->at(pos+1);
    auto u = toks->at(pos+2);
    auto e = toks->at(pos+3);

    if (t == 't' && r == 'r' && u == 'u' && e == 'e') {
        return {pos+4, true};
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_false(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos+4)) return {0, json_variant()};

    auto f = toks->at(pos);
    auto a = toks->at(pos+1);
    auto l = toks->at(pos+2);
    auto s = toks->at(pos+3);
    auto e = toks->at(pos+4);

    if (f == 'f' && a == 'a' && l == 'l' && s == 's' && e == 'e') {
        return {pos+5, false};
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_null(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos+3)) return {0, json_variant()};

    auto n = toks->at(pos);
    auto u = toks->at(pos+1);
    auto l1 = toks->at(pos+2);
    auto l2 = toks->at(pos+3);

    if (n == 'n' && u == 'u' && l1 == 'l' && l2 == 'l') {
        return {pos+4, json_variant::null};
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_value(std::size_t pos, tokens *toks) {
    auto res = match_true(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_false(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_null(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_string(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_number(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_object(pos, toks);
    if (res.first != 0) {
        return res;
    }
    res = match_array(pos, toks);
    if (res.first != 0) {
        return res;
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_element(std::size_t pos, tokens *toks) {
    pos = match_ws(pos, toks).first;
    if (pos != 0) {
        auto res = match_value(pos, toks);
        pos = res.first;
        if (pos != 0) {
            pos = match_ws(pos, toks).first;
            return {pos, res.second};
        }
        else {
            return {0, json_variant()};
        }
    }
    else {
        return {0, json_variant()};
    }
}

json_parser::token_index json_parser::match_elements(std::size_t pos, tokens *toks) {
    auto res = match_element(pos, toks);
    std::size_t pos2 = res.first;
    if (pos2 != 0 && toks->valid_pos(pos2)) {
        json_variant obj = res.second;

        auto token = toks->at(pos2);
        if (token == ',') {
            res = match_elements(pos2+1, toks);
            res.second.to_array().insert(res.second.to_array().begin(), obj);
            return res;
        }
        else {
            return {pos2, json_array({obj})};
        }
    }
    return {0, json_variant()};
}

json_parser::token_index json_parser::match_member(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    pos = match_ws(pos, toks).first;
    if (pos != 0) {
        auto res = match_string(pos, toks); // FIXME: what if return 0
        pos = res.first;
        json_variant string_property = res.second;
        if (pos != 0) {
            pos = match_ws(pos, toks).first;
            if (pos != 0 && toks->valid_pos(pos)) {
                auto token = toks->at(pos);
                if (token == ':') {
                    auto res2 = match_element(pos+1, toks);
                    pos = res2.first;
                    json_variant memberValue(res2.second);
                    if (pos != 0) {
                        json_array arr;
                        arr.push_back(string_property);
                        arr.push_back(memberValue);
                        return {pos, arr};
                    }
                }
            }
        }
    }

    return {0, json_variant()};
}

json_parser::token_index json_parser::match_members(std::size_t pos, tokens *toks) {
    auto res = match_member(pos, toks);
    std::size_t pos2 = res.first;
    if (pos2 != 0 && toks->valid_pos(pos2)) {
        json_variant member = res.second;

        auto token = toks->at(pos2);
        if (token == ',') {
            res = match_members(pos2+1, toks);
            res.second.to_array().push_back(member);
            return res;
        }
        else {
            return {pos2, json_array({member})};
        }
    }
    return {0, json_variant()};
}

json_parser::token_index json_parser::match_object(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '{') {
        std::size_t pos2 = match_ws(pos+1, toks).first;

        if (!toks->valid_pos(pos2)) return {0, json_variant()};

        if (pos2 != 0) {
            token = toks->at(pos2);
            if (token == '}') {
                return {pos2+1, json_object()};
            }
            else {
                pos = pos2;
            }
        }

        auto res = match_members(pos, toks);
        pos2 = res.first;

        if (!toks->valid_pos(pos2)) return {0, json_variant()};

        if (pos2 != 0) {
            token = toks->at(pos2);
            if (token == '}') {
                json_array &arr = res.second.to_array();
                json_object obj;
                for (auto element : arr) {
                    json_array &pair = element.to_array();
                    obj.insert({pair[0].to_string(), pair[1]});
                }
                return {pos2+1, obj};
            }
            return {0, json_variant()};
        }
    }
    return {0, json_variant()};
}

json_parser::token_index json_parser::match_array(std::size_t pos, tokens *toks) {
    if (!toks->valid_pos(pos)) return {0, json_variant()};

    auto token = toks->at(pos);
    if (token == '[') {

        std::size_t pos2 = match_ws(pos+1, toks).first;

        if (!toks->valid_pos(pos2)) return {0, json_variant()};

        if (pos2 != 0) {
            token = toks->at(pos2);
            if (token == ']') {
                return {pos2+1, json_array()};
            }
            else {
                pos = pos2;
            }
        }

        auto res = match_elements(pos, toks);
        pos2 = res.first;

        if (!toks->valid_pos(pos2)) return {0, json_variant()};

        if (pos2 != 0) {
            token = toks->at(pos2);
            if (token == ']') {
                return {pos2+1, res.second};
            }
            return {0, json_variant()};
        }
    }
    return {0, json_variant()};
}

json_parser::tokens::tokens(char *tokens, std::size_t size) {
    this->toks = tokens;
    this->size = size;
}

char json_parser::tokens::at(std::size_t index) {
#ifdef JSONLIB_VERBOSE_DEBUG
    if (index == 0 || index >= size) {
        std::cerr << "json_parser::tokens::at: ERROR: index out of bounds: " << index << std::endl;
    }
#endif
    return toks[index];
}

bool json_parser::tokens::valid_pos(std::size_t index) {
    return (index > 0 && index < size);
}

json_document::json_document(const std::string &filename, const json_variant &json_variant)
    : json_root(json_variant) {
    this->filename = filename;
}

json_document::json_document(const std::string &filename)
    : json_document(filename, json_variant()) {
}

json_document::json_document() : json_document("") {}

bool json_document::open(const std::string &filename) {
    close();

    std::ifstream stream;
    stream.open(filename, std::ios::binary);

    if (!stream.is_open()) {
        return false;
    }

    std::ostringstream sstr;
    sstr << stream.rdbuf();

    return set_json(sstr.str());
}

bool json_document::open() {
    if (this->filename.empty()) {
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cout << "json_document::open: WARNING: unable to open file because no filename was specified." << std::endl;
#endif
        close();
        return false;
    }

    return open(this->filename);
}

bool json_document::save(const std::string &filename, const json_variant &json, int indent) {
    json_document doc(filename);
    doc.set_json(json);
    return doc.save(filename, indent);
}

bool json_document::save(const std::string &filename, int indent) const {
    if (this->json_root.is_invalid_json()) {
        return false;
    }

    std::ofstream out(filename);

    if (!out.is_open()) {
        return false;
    }

    out << this->json_root.dump(indent);
    out.close();

    return true;
}

bool json_document::save(int indent) const {
    if (this->filename.empty()) {
#ifdef JSONLIB_VERBOSE_DEBUG
        std::cout << "json_document::save: WARNING: unable to save file because no filename was specified." << std::endl;
#endif
        return false;
    }
    return save(this->filename, indent);
}

bool json_document::set_json(const std::string &raw_json_string) {
    this->json_root = json_parser::parse(raw_json_string);
    return this->json_root.is_valid_value();
}

void json_document::set_json(const json_variant &json_variant) {
    this->json_root = json_variant;
}

void json_document::set_filename(const std::string &filename) {
    this->filename = filename;
}

std::string json_document::get_filename() const {
    return this->filename;
}

json_variant &json_document::json() {
    return this->json_root;
}

json_variant json_document::json() const {
    return this->json_root;
}

void json_document::close() {
    set_json(json_variant());
}

} // namespace
