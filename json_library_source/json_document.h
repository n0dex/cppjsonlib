#ifndef JSON_DOCUMENT_H
#define JSON_DOCUMENT_H

#include <fstream>
#include "json_defines.h"
#include "json_parser.h"
#include "json_variant.h"

namespace JSONLIB_NAMESPACE {

/**
 * @brief The json_document class provides an interface for convenient json I/O operations.
 */
class json_document {
public:
    /**
     * @brief   Initializes the json document with the passed values.
     * @param   filename needs to be a file path.
     * @param   json_variant can be any json_variant.
     * @see     save()
     * @see     json()
     */
    json_document(const std::string &filename, const json_variant &json_variant);

    /**
     * @brief   Initializes the json document and sets the json_documents \b filename to \p filename.
     * @see     set_json()
     * @see     open()
     */
    json_document(const std::string &filename);

    /**
     * @brief   Initializes the json document with the default values.
     * @see     set_json()
     * @see     set_filename()
     */
    json_document();

    /**
     * @brief   Opens the file specified with \p filename and tries to parse the content as json.
     *          The json content can be afterwards accessed with json().
     * @param   filename needs to be a file path.
     * @see     json()
     * @see     save()
     * @return  \b true if the file was opened successfully and the text content was successfully parsed. Otherwise \b false.
     */
    bool open(const std::string &filename);

    /**
     * @brief   Opens the file specified in the json_document attribute \p filename and
     *          tries to parse the content as json.
     *          The json content can be afterwards accessed with json().
     * @note    This function assumes that the \p filename was already set.
     *          If no \p filename was set the function will return \b false.
     * @see     json()
     * @see     save()
     * @see     set_filename()
     * @see     json_document(const std::string &)
     * @return  \b true if the file was opened successfully and the text content was successfully parsed. Otherwise \b false.
     */
    bool open();

    /**
     * @brief   Saves the passed json_variant \p json in the file called \p filename.
     * @param   filename needs to be a file path.
     * @param   json_variant can be any json_variant but must be a valid json object (must contain a value).
     * @param   indent defines the spaces used for indentation.
     *          If the indent is set to 0 then no indentation and new lines will be created.
     * @see     json_variant::is_valid_json()
     * @return  \b true if the json_variant is valid and the document was saved successfully. Otherwise \b false.
     */
    static bool save(const std::string &filename, const json_variant &json, int indent = 4);

    /**
     * @brief   Saves the current json_variant in the file referred in \p filename.
     * @param   filename needs to be a file path.
     * @param   indent defines the spaces used for indentation.
     *          If the indent is set to 0 then no indentation and no new lines will be created.
     * @see     is_valid_json()
     * @see     set_json()
     * @see     open()
     * @return  \b true if the json_variant is valid and the document was saved successfully. Otherwise \b false.
     */
    bool save(const std::string &filename, int indent = 4) const;

    /**
     * @brief   Saves the current json_variant under the current filename.
     * @param   indent defines the spaces used for indentation.
     *          If the indent is set to 0 then no indentation and no new lines will be created.
     * @see     is_valid_json()
     * @see     set_filename()
     * @see     set_json()
     * @see     open()
     * @return  \b true if the json_variant is valid and the document was saved successfully. Otherwise \b false.
     */
    bool save(int indent = 4) const;

    /**
     * @brief   Parses the passed string \p raw_json_string into a json_variant.
     *          The json_variant can be accessed afterwards with json().
     * @see     json()
     * @param   \b true if the passed string is valid json syntax. Otherwise \b false.
     */
    bool set_json(const std::string &raw_json_string);

    /**
     * @brief   Sets the internal json value to \p variant.
     * @see     json()
     * @param   json_variant can be any json_variant.
     */
    void set_json(const json_variant &variant);

    /**
     * @brief   Sets the json_documents \a filename to \p filename.
     * @param   filename needs to be a file path.
     * @see     open()
     * @see     save()
     */
    void set_filename(const std::string &filename);

    /**
     * @brief   Returns the current json_documents \a filename.
     * @return  The current json_documents \a filename.
     */
    std::string get_filename() const;

    /**
     * @brief   Returns a reference to the internally saved json_variant.
     * @return  A reference to the internally saved json_variant.
     */
    json_variant& json();

    /**
     * @brief   Returns a copy of the internally saved json_variant.
     * @return  A copy of the internally saved json_variant.
     */
    json_variant json() const;

    /**
     * @brief   Closes the json document by overwriting the json_variant accessible via json() with the standard json_variant.
     */
    void close();

private:
    /** Holds the json_variant value that's used for I/O operations and parsing. */
    json_variant json_root;

    /** Holds the filename used for I/O operations. */
    std::string filename;
};

} // namespace

#endif // JSON_DOCUMENT_H
