#include "json_parser.h"

namespace JSONLIB_NAMESPACE {

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
        std::cerr << "json_parser::combine_tokens_to_string: ERROR: invalid startToken" << std::endl;
    }
    if (!toks->valid_pos(end_token)) {
        std::cerr << "json_parser::combine_tokens_to_string: ERROR: invalid endToken" << std::endl;
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
        auto res = match_string(pos, toks);
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

} // namespace
