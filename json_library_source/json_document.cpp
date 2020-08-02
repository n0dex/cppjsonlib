#include "json_document.h"

namespace JSONLIB_NAMESPACE {

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
