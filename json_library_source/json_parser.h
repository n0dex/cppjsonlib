#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <cstring>
#include "json_defines.h"
#include "json_variant.h"

namespace JSONLIB_NAMESPACE {

/**
 * @brief The json_parser class provides an interface for
 * interpreting strings into json_variant values.
 */
class json_parser {
public:
    /**
     * @brief   Parses the passed std::string \p json_string and interprets it into json_variants.
     * @param   json should be a valid json text.
     * @see     json_variant::json_variant()
     * @see     json_variant::is_valid_json()
     * @see     json_variant::is_valid_value()
     * @return  <b>on success:</b> valid json_variant object that represents the passed string value \p json. \n
     *          <b>on error:</b> an invalid json_variant.
     */
    static json_variant parse(const std::string &json_string);

private:
    /** Force static parse() call. */
    json_parser();

    /** Typedef token_index defines the result type of the grammar matching functions. */
    typedef std::pair<std::size_t, json_variant> token_index;

    /** Class tokens contains all characters that must be parsed for a successful string interpretation. */
    class tokens {
    public:
        tokens(char *tokens, std::size_t size);
        char at(std::size_t index);
        bool valid_pos(std::size_t index);
        char *toks;
        std::size_t size;
    };

    /** Starts the json matching on tokens. */
    static json_variant match_json(tokens *toks);

    // **** helper functions ***

    /** Combines the tokens from start_token to end_token into a string. */
    static std::string combine_tokens_to_string(std::size_t start_token, std::size_t end_token, tokens *toks);

    /** Tests whether the string number is an int. */
    static bool is_int(const std::string &number);

    /** Converts the string number to json_int. */
    static json_int string_to_int(const std::string &number);

    /** Converts the string number to double. */
    static double string_to_double(const std::string &number);

    // *** json grammar implementation ***

    static token_index match_ws(std::size_t pos, tokens *toks);
    static token_index match_sign(std::size_t pos, tokens *toks);
    static token_index match_exponent(std::size_t pos, tokens *toks);
    static token_index match_onenine(std::size_t pos, tokens *toks);
    static token_index match_digit(std::size_t pos, tokens *toks);
    static token_index match_digits(std::size_t pos, tokens *toks);
    static token_index match_integer(std::size_t pos, tokens *toks);
    static token_index match_fraction(std::size_t pos, tokens *toks);
    static token_index match_number(std::size_t pos, tokens *toks);
    static token_index match_hex(std::size_t pos, tokens *toks);
    static token_index match_escape(std::size_t pos, tokens *toks);
    static token_index match_character(std::size_t pos, tokens *toks);
    static token_index match_characters(std::size_t pos, tokens *toks);
    static token_index match_string(std::size_t pos, tokens *toks);
    static token_index match_true(std::size_t pos, tokens *toks);
    static token_index match_false(std::size_t pos, tokens *toks);
    static token_index match_null(std::size_t pos, tokens *toks);
    static token_index match_value(std::size_t pos, tokens *toks);
    static token_index match_element(std::size_t pos, tokens *toks);
    static token_index match_elements(std::size_t pos, tokens *toks);
    static token_index match_member(std::size_t pos, tokens *toks);
    static token_index match_members(std::size_t pos, tokens *toks);
    static token_index match_object(std::size_t pos, tokens *toks);
    static token_index match_array(std::size_t pos, tokens *toks);
};

} // namespace

#endif // JSONPARSER_H
