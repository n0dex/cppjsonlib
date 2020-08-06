#ifndef JSON_VARIANT_H
#define JSON_VARIANT_H

#include <map>
#include <vector>
#include <limits>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "json_defines.h"

namespace JSONLIB_NAMESPACE {

class json_variant;

/** \typedef json_array defines a std::vector that is usable in a json context. */
typedef std::vector<json_variant> json_array;

/** \typedef json_object defines a std::map that is usable in a json context. */
typedef std::map<std::string, json_variant> json_object;

/** \typedef json_int defines the int type used to store json integers. */
typedef JSONLIB_INT_TYPE json_int;

/**
 * @brief The json_variant class provides an interface for storing json values in a c++ environment.
 *
 * The json_variant can hold all necessary json values:
 *  - json_int
 *  - double
 *  - bool
 *  - std::string
 *  - json_object
 *  - json_array
 *  - json_null_type
 *
 * A json file can be accurately represented by combining
 * those json_variant values into a tree structure.
 */

class json_variant {
public:
    /**
     * @brief   The json_null_type enum represents the json "null" value.
     *          This enum has to be used when assigning a null value to a json_variant.
     * @see     set_value(json_variant::json_null_type)
     * @see     json_variant(json_variant::json_null_type)
     */
    enum json_null_type { null };

    /** @brief Initializes the json_variant with \p value. */
    json_variant(int value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(json_int value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(double value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(bool value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const char *value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const std::string &value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const json_array &value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const json_object &value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const json_array *value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(const json_object *value);

    /** @brief Initializes the json_variant with \p value. */
    json_variant(json_variant::json_null_type);

    /** @brief Initializes the json_variant by copying the values from \p other. */
    json_variant(const json_variant &other);

    /**
     * @brief Initializes the json_variant with the standard value.
     *        As long as no value is set the json_variant will be invalid.
     * @see is_valid_json()
     * @see set_value()
     * @see operator=()
     * @see operator==()
     * @see operator=(const json_variant &)
     */
    json_variant();

    /** @brief Destroys json_variant and frees the internal memory. */
    ~json_variant();

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(int value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(json_int value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(double value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(bool value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(const char *value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(const std::string &value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(const json_array &value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(const json_object &value);

    /** @brief Sets the json_variant internal value to \p value. */
    void set_value(json_null_type);

    /** @brief Copies the json_variant values from \p other. */
    void set_value(const json_variant &other);

    /**
     * @brief   Checks if the json_variant value is of the type \a json_int.
     * @return  \b true if the json_variant value is of the type \a json_int. Otherwise \b false.
     */
    bool is_int() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a double.
     * @return  \b true if the json_variant value is of the type \a double. Otherwise \b false.
     */
    bool is_double() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a bool.
     * @return  \b true if the json_variant value is of the type \a bool. Otherwise \b false.
     */
    bool is_bool() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a std::string.
     * @return  \b true if the json_variant value is of the type \a std::string. Otherwise \b false.
     */
    bool is_string() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a json_array.
     * @return  \b true if the json_variant value is of the type \a json_array. Otherwise \b false.
     */
    bool is_array() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a json_array.
     * @return  \b true if the json_variant value is of the type \a json_array. Otherwise \b false.
     */
    bool is_object() const;

    /**
     * @brief   Checks if the json_variant value is of the type \a is_object.
     * @return  \b true if the json_variant value is of the type \a is_object. Otherwise \b false.
     */
    bool is_null() const;

    /**
     * @brief   Checks if the json_variant value is valid. json_variant variables that hold values (null included) are valid.
     * @note    This function only checks this json_variants value validity.
     *          To ensure that all child variants are valid you should consider using is_valid_json().
     * @see     is_invalid_value()
     * @see     is_valid_json()
     * @see     is_invalid_json()
     * @return  \b true if the json_variant value is valid. Otherwise \b false.
     */
    bool is_valid_value() const;

    /**
     * @brief   Checks if the json_variant value is invalid. json_variant variables that hold no values are invalid (standard initialization).
     * @note    This function only checks this json_variants values invalidity.
     *          To ensure that no child variant is invalid you should consider using is_invalid_json().
     * @see     is_valid_value()
     * @see     is_valid_json()
     * @see     is_invalid_json()
     * @return  \b true if the json_variant value is invalid. Otherwise \b false.
     */
    bool is_invalid_value() const;

    /**
     * @brief   Checks if the json_variant and all its children variants are valid.
     *          This function will recursively  check that the json_variant itself
     *          and all its children are valid json_variants.
     * @see     is_invalid_json()
     * @see     is_valid_value()
     * @see     is_invalid_value()
     * @return  \b true if the json_variant and all its child variants values are valid. Otherwise \b false.
     */
    bool is_valid_json() const;

    /**
     * @brief   Checks if the json_variant or one its child variants is invalid.
     *          This function will recursively check if the json_variant itself
     *          or one of its child variants is an invalid json_variant.
     * @see     is_valid_json()
     * @see     is_valid_value()
     * @see     is_invalid_value()
     * @return  \b true if the json_variant or one it's child variants is invalid. Otherwise \b false.
     */
    bool is_invalid_json() const;

    /**
     * @brief   Casts the json_variant value to \a json_int.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a json_int.
     * @see     is_int()
     * @return  \a json_int if the json_variant value is actually a \a json_int.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    json_int to_int() const;

    /**
     * @brief   Casts the json_variant value to \a double.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a double.
     * @see     is_double() const
     * @return  \a double if the json_variant value is actually a \a double.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    double to_double() const;

    /**
     * @brief   Casts the json_variant value to \a bool.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a bool.
     * @see     is_bool() const
     * @return  \a bool if the json_variant value is actually a \a bool.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    bool to_bool() const;

    /**
     * @brief   Casts the json_variant value to \a std::string.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a std::string.
     * @see     is_string() const
     * @return  \a std::string if the json_variant value is actually a \a std::string.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    std::string to_string() const;

    /**
     * @brief   Casts the json_variant value to \a json_array.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a json_array.
     * @see     is_array() const
     * @return  \a json_array copy if the json_variant value is actually a \a json_array.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    json_array to_array() const;

    /**
     * @brief   Casts the json_variant value to \a json_array.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a json_array.
     * @see     is_array() const
     * @return  \a json_array reference if the json_variant value is actually a \a json_array.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    json_array &to_array();

    /**
     * @brief   Casts the json_variant value to \a json_object.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a json_object.
     * @see     is_object() const
     * @return  \a json_object copy if the json_variant value is actually a \a json_object.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    json_object to_object() const;

    /**
     * @brief   Casts the json_variant value to \a json_object.
     * @throw   std::runtime_error if the json_variant value isn't actually a \a json_object.
     * @see     is_object() const
     * @return  \a json_object reference if the json_variant value is actually a \a json_object.
     *          Otherwise a \a std::runtime_error will be thrown.
     */
    json_object &to_object();

    /**
     * @brief   Compares the json_variant with another json_variant.
     *          Calling this function is the same as using the \a == \a operator.
     * @param   other must be another json_variant.
     * @see     operator==()
     * @see     operator!=()
     * @return  \b true if the to objects are the same. Otherwise \b false.
     */
    bool equals(const json_variant &other) const;

    /**
     * @brief   Creates a string representation of the json_variant and its children.
     *          This may be just a simple value such as "null" or a more complex construct like "{ "value": [] }".
     *          The returned string will be valid json if the json_variant and all its children are valid values.
     * @param   indent defines the spaces used for indentation.
     *          If the indent is set to 0 then no indentation and no new lines will be created.
     * @see     is_valid_json() const
     * @return  A string representation of the json_variant.
     */
    std::string dump(int indent=4) const;

    /**
     * @brief   Parses the passed std::string \p json_string and interprets it into json_variants.
     * @param   json should be a valid json text.
     * @see     json_parser::parse()
     * @see     is_valid_json()
     * @see     is_valid_value()
     * @return  <b>on success:</b> valid json_variant object that represents the passed string value \p json. \n
     *          <b>on error:</b> an invalid json_variant.
     */
    static json_variant parse(const std::string &json_string);

    /**
     * @brief   Unicode escapes the passed string \p str and escapes all occurrences of \b " and \b \ to ensure \p str is a valid json string.
     *          The string escaping will be automatically handled when calling dump().
     * @note    This function only escapes \b " and \b \ since those are the only illegal characters in a json string.
     * @param   str should be a simple string.
     * @see     unescape_string()
     * @return  The unicode escaped version of \p str.
     */
    static std::string escape_string(const std::string& str);

    /**
     * @brief   Unescapes all unicode occurrences in \p str of ASCII-characters.
     * @note    Non-ASCII characters won't be converted to prevent a encoding mess.
     * @param   str should be a simple string.
     * @see     escape_string()
     * @see     dump()
     * @return  The ASCII-unescaped version of \p str.
     */
    static std::string unescape_string(std::string str);

    /**
     * @brief   Copies the json_variant values from \p other.
     * @see     set_value(const json_variant &)
     */
    inline void operator=(const json_variant &other) { this->set_value(other); }

    /**
     * @brief   Compares the json_variant with \p other.
     * @param   variant has to be another json_variant.
     * @see     equals()
     * @see     operator!=()
     * @return  \b true if the to objects are equal. Otherwise \b false.
     */
    inline bool operator==(const json_variant &other) const { return this->equals(other); }

    /**
     * @brief   Compares the json_variant with \p other.
     * @param   variant has to be another json_variant.
     * @see     equals()
     * @see     operator==()
     * @return  \b true if the to objects are unequal. Otherwise \b false.
     */
    inline bool operator!=(const json_variant &other) const { return !this->equals(other); }

    friend std::ostream& operator<<(std::ostream& os, const json_variant& variant);

private:
    /** Writes the string representation of variant and all its children into the stream. */
    void dump(const json_variant &variant, std::stringstream &stream, int current_indent, int indent_increase) const;

    /** Creates a space filled string that's as long as specified in indent. */
    std::string fill_indent(int indent) const;

    /** Frees all memory currently allocated. */
    void free_memory();

    /** Possible types of the json_variant. */
    enum json_variant_type {
        json_int_variant,
        json_double_variant,
        json_bool_variant,
        json_string_variant,
        json_array_variant,
        json_object_variant,
        json_null_variant,
        json_invalid_variant
    } type;

    /** Pointer that holds the address to the stored value. */
    void *value;
};

/**
 * @brief   Writes a string representation of the json_variant \p variant into the std::ostream \p os.
 * @see     dump()
 */
inline std::ostream& operator<<(std::ostream& os, const json_variant& variant) {
    os << variant.dump();
    return os;
}

} // namespace

#endif // JSON_VARIANT_H
