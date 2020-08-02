#include <QtTest>

// add necessary includes here

#include "../json_library_source/json_library.h"

using namespace JSONLIB_NAMESPACE;

/**
 * @brief The jsonlib_unit_tests class.
 * This class contains all test cases for the library.
 */
class jsonlib_unit_tests : public QObject
{
    Q_OBJECT

public:
    jsonlib_unit_tests();
    ~jsonlib_unit_tests();

private slots:
    /** json_variant type tests */
    void json_variant_type_test_case1();
    void json_variant_type_test_case2();
    void json_variant_type_test_case3();
    void json_variant_type_test_case4();
    void json_variant_type_test_case5();
    void json_variant_type_test_case6();
    void json_variant_type_test_case7();
    void json_variant_type_test_case8();

    /** json_variant cast tests */
    void json_variant_cast_test_case1();
    void json_variant_cast_test_case2();
    void json_variant_cast_test_case3();
    void json_variant_cast_test_case4();
    void json_variant_cast_test_case5();
    void json_variant_cast_test_case6();
    void json_variant_cast_test_case7();
    void json_variant_cast_test_case8();

    /** json_variant assign tests */
    void json_variant_assign_test_case1();
    void json_variant_assign_test_case2();
    void json_variant_assign_test_case3();
    void json_variant_assign_test_case4();
    void json_variant_assign_test_case5();
    void json_variant_assign_test_case6();

    /** json_variant equals() / == tests */
    void json_variant_equals_test_case1();
    void json_variant_equals_test_case2();
    void json_variant_equals_test_case3();
    void json_variant_equals_test_case4();
    void json_variant_equals_test_case5();
    void json_variant_equals_test_case6();
    void json_variant_equals_test_case7();
    void json_variant_equals_test_case8();
    void json_variant_equals_test_case9();
    void json_variant_equals_test_case10();
    void json_variant_equals_test_case11();
    void json_variant_equals_test_case12();
    void json_variant_equals_test_case13();
    void json_variant_equals_test_case14();

    /** json_variant dump tests */
    void json_variant_dump_test_case1();
    void json_variant_dump_test_case2();
    void json_variant_dump_test_case3();
    void json_variant_dump_test_case4();
    void json_variant_dump_test_case5();
    void json_variant_dump_test_case6();
    void json_variant_dump_test_case7();
    void json_variant_dump_test_case8();
    void json_variant_dump_test_case9();

    /** json_variant is_valid_json() tests */
    void json_variant_is_valid_json_test_case1();

    /** json_document I/O tests */
    void json_document_io_test_case1();
    void json_document_io_test_case2();
    void json_document_io_test_case3();
    void json_document_io_test_case4();
    void json_document_io_test_case5();
    void json_document_io_test_case6();
    void json_document_io_test_case7();
    void json_document_io_test_case8();
    void json_document_io_test_case9();
    void json_document_io_test_case10();

    /** json_parser parse() tests */
    void json_parser_parse_test_case1();
    void json_parser_parse_test_case2();
    void json_parser_parse_test_case3();
    void json_parser_parse_test_case4();
    void json_parser_parse_test_case5();
    void json_parser_parse_test_case6();
    void json_parser_parse_test_case7();
    void json_parser_parse_test_case8();
    void json_parser_parse_test_case9();
    void json_parser_parse_test_case10();
    void json_parser_parse_test_case11();
    void json_parser_parse_test_case12();
    void json_parser_parse_test_case13();

private:
    const std::string JSON_INVALID_DOC_PATH = "+?\"§:$//#///";
    const std::string JSON_VALID_DOC_PATH = "unit_test_file.json";

    void restore_original_valid_json_doc() {
        std::ofstream out(JSON_VALID_DOC_PATH);
        QVERIFY2(out.is_open(), "INFO: this is not an library error, check that 'unit_test_file.json' exists");
        out << R"({"value1":123,"value2":[null,"hello world"]})";
        out.close();
    }
};

jsonlib_unit_tests::jsonlib_unit_tests() {}

jsonlib_unit_tests::~jsonlib_unit_tests() {}

void jsonlib_unit_tests::json_variant_type_test_case1() {
    json_variant var = 1;
    QCOMPARE(var.is_int(), true);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case2() {
    json_variant var = 1.1;
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), true);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case3() {
    json_variant var = true;
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), true);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case4() {
    json_variant var = "hello world";
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), true);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case5() {
    json_variant var = json_array();
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), true);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case6() {
    json_variant var = json_object();
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), true);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case7() {
    json_variant var = json_variant::null;
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), true);
    QCOMPARE(var.is_valid_value(), true);
    QCOMPARE(var.is_invalid_value(), false);
}

void jsonlib_unit_tests::json_variant_type_test_case8() {
    json_variant var = json_variant();
    QCOMPARE(var.is_int(), false);
    QCOMPARE(var.is_array(), false);
    QCOMPARE(var.is_object(), false);
    QCOMPARE(var.is_bool(), false);
    QCOMPARE(var.is_double(), false);
    QCOMPARE(var.is_string(), false);
    QCOMPARE(var.is_null(), false);
    QCOMPARE(var.is_valid_value(), false);
    QCOMPARE(var.is_invalid_value(), true);
}

void jsonlib_unit_tests::json_variant_cast_test_case1() {
    json_variant var = 1;
    var.to_int();
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case2() {
    json_variant var = 1.1;
    var.to_double();
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case3() {
    json_variant var = "hello world";
    var.to_string();
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case4() {
    json_variant var = true;
    var.to_bool();
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case5() {
    json_variant var = json_array();
    var.to_array();
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case6() {
    json_variant var = json_object();
    var.to_object();
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case7() {
    json_variant var = json_variant::null;
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_cast_test_case8() {
    json_variant var = json_variant();
    QVERIFY_EXCEPTION_THROWN(var.to_object(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_bool(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_array(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_string(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_int(), std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(var.to_double(), std::runtime_error);
}

void jsonlib_unit_tests::json_variant_assign_test_case1() {
    json_variant var1 = 0;
    json_variant var2 = -100;

    QCOMPARE(var1.to_int(), 0);
    QCOMPARE(var2.to_int(), -100);

    var1 = var2;

    QCOMPARE(var1.to_int(), -100);
    QCOMPARE(var2.to_int(), -100);
}

void jsonlib_unit_tests::json_variant_assign_test_case2() {
    json_variant var1 = 0.0;
    json_variant var2 = -100.0;

    QCOMPARE(var1.to_double()+1, 0.0+1);
    QCOMPARE(var2.to_double()+1, -100.0+1);

    var1 = var2;

    QCOMPARE(var1.to_double()+1, -100.0+1);
    QCOMPARE(var2.to_double()+1, -100.0+1);
}

void jsonlib_unit_tests::json_variant_assign_test_case3() {
    std::string string1 = "string1";
    std::string string2 = "string2";

    json_variant var1 = "string1";
    json_variant var2 = "string2";

    QCOMPARE(var1.to_string(), string1);
    QCOMPARE(var2.to_string(), string2);

    var1 = var2;

    QCOMPARE(var1.to_string(), string2);
    QCOMPARE(var2.to_string(), string2);

    var1 = string1;
    var2 = string2;

    QCOMPARE(var1.to_string(), string1);
    QCOMPARE(var2.to_string(), string2);

    var1 = var2;

    QCOMPARE(var1.to_string(), string2);
    QCOMPARE(var2.to_string(), string2);
}

void jsonlib_unit_tests::json_variant_assign_test_case4() {
    bool bool1 = true;
    bool bool2 = false;

    json_variant var1 = true;
    json_variant var2 = false;

    QCOMPARE(var1.to_bool(), bool1);
    QCOMPARE(var2.to_bool(), bool2);

    var1 = var2;

    QCOMPARE(var1.to_bool(), bool2);
    QCOMPARE(var2.to_bool(), bool2);

    var1 = bool1;
    var2 = bool2;

    QCOMPARE(var1.to_bool(), bool1);
    QCOMPARE(var2.to_bool(), bool2);

    var1 = var2;

    QCOMPARE(var1.to_bool(), bool2);
    QCOMPARE(var2.to_bool(), bool2);
}

void jsonlib_unit_tests::json_variant_assign_test_case5() {
    json_array arr1 = json_array({123, "hello world", -1.4, json_variant::null});
    json_array arr2 = json_array({456, "array value", 8.5});

    json_variant var1 = arr1;
    json_variant var2 = arr2;

    QCOMPARE(var1.to_array()[0].to_int(), 123);
    QCOMPARE(var1.to_array()[1].to_string(), "hello world");
    QCOMPARE(var1.to_array()[2].to_double(), -1.4);
    QCOMPARE(var1.to_array()[3].is_null(), true);
    QCOMPARE(var2.to_array()[0].to_int(), 456);
    QCOMPARE(var2.to_array()[1].to_string(), "array value");
    QCOMPARE(var2.to_array()[2].to_double(), 8.5);

    QCOMPARE(var1.to_array().size(), 4);
    QCOMPARE(var2.to_array().size(), 3);

    var1 = var2;

    QCOMPARE(var1.to_array()[0].to_int(), 456);
    QCOMPARE(var1.to_array()[1].to_string(), "array value");
    QCOMPARE(var1.to_array()[2].to_double(), 8.5);
    QCOMPARE(var2.to_array()[0].to_int(), 456);
    QCOMPARE(var2.to_array()[1].to_string(), "array value");
    QCOMPARE(var2.to_array()[2].to_double(), 8.5);

    QCOMPARE(var1.to_array().size(), 3);
    QCOMPARE(var2.to_array().size(), 3);
}
void jsonlib_unit_tests::json_variant_assign_test_case6() {
    json_array arr1 = json_array({123, 456});
    json_object obj1 = { { "value1", json_variant::null }, { "value2", json_variant::null } };
    json_array arr2 = json_array({"array value", json_array({"sub array value 1", false}), obj1});

    json_variant var1 = arr1;
    json_variant var2 = arr2;

    json_array &arr = var1.to_array();
    arr.push_back(999);

    QCOMPARE(arr.size(), var1.to_array().size());
    QCOMPARE(&arr, &var1.to_array());
    QCOMPARE(var1.to_array()[2].to_int(), 999);

    var1 = var2;

    QCOMPARE(var1.to_array().size(), 3);

    QCOMPARE(var1.to_array()[1].is_array(), true);

    QVERIFY(&var1.to_array() != &var2.to_array());
    QVERIFY(&var1.to_array()[2].to_object() != &var2.to_array()[2].to_object());
}

void jsonlib_unit_tests::json_variant_equals_test_case1() {
    json_object obj1 = { { "value1", json_variant::null }, { "value2", json_variant::null } };
    json_object obj2 = { { "value1", json_variant::null }, { "value2", json_variant::null } };
    json_variant var1 = obj1;
    json_variant var2 = obj2;

    QVERIFY(obj1 == obj2);
    QVERIFY(var1 == var2);

    var2.to_object().at("value2") = 1231;

    QVERIFY(var1 != var2);
}

void jsonlib_unit_tests::json_variant_equals_test_case2() {
    json_variant var1 = 1;
    json_variant var2 = 1.0;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case3() {
    json_variant var1 = "";
    json_variant var2 = false;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case4() {
    json_variant var1;
    json_variant var2 = false;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case5() {
    json_variant var1 = json_array();
    json_variant var2 = json_object();

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case6() {
    json_variant var1;
    json_variant var2 = json_object();

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case7() {
    json_variant var1;
    json_variant var2 = json_array();

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case8() {
    json_variant var1 = json_array();
    json_variant var2 = json_array();

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case9() {
    json_variant var1 = json_object();
    json_variant var2 = json_object();

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case10() {
    json_variant var1 = 11;
    json_variant var2 = 11;

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));

    var2 = -11;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case11() {
    json_variant var1 = 1.5;
    json_variant var2 = 1.5;

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));

    var2 = 1.4;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case12() {
    json_variant var1 = false;
    json_variant var2 = false;

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));

    var2 = true;

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case13() {
    json_variant var1 = "json";
    json_variant var2 = "json";

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));

    var2 = "json2";

    QVERIFY(var1 != var2);
    QVERIFY(!(var1 == var2));
}

void jsonlib_unit_tests::json_variant_equals_test_case14() {
    json_variant var1 = json_array();
    json_variant var2 = json_array();

    QVERIFY(var1 == var2);
    QVERIFY(!(var1 != var2));
}

void jsonlib_unit_tests::json_variant_dump_test_case1() {
    json_variant var = json_object();
    json_object obj = { { "sample", -1 } };
    var.to_object().insert({"value", 1});
    var.to_object().insert({"name", json_variant::null});
    var.to_object().insert({"array", json_array({"array value 1", json_variant::null, true, false, 12, -324, obj, json_object()})});

    std::string str = R"({"array":["array value 1",null,true,false,12,-324,{"sample":-1},{}],"name":null,"value":1})";

    QVERIFY(str == var.dump(0));

    std::string str2 = "{\n  \"array\": [\n    \"array value 1\",\n    null,\n    true,\n    false,\n    12,\n    -324,\n    "
                       "{\n      \"sample\": -1\n    },\n    {\n\n    }\n  ],\n  \"name\": null,\n  \"value\": 1\n}";

    QVERIFY(str2 == var.dump(2));
}

void jsonlib_unit_tests::json_variant_dump_test_case2() {
    json_variant var = 123;
    QVERIFY(var.dump(0) == "123");
    var = -123;
    QVERIFY(var.dump(0) == "-123");
}

void jsonlib_unit_tests::json_variant_dump_test_case3() {
    json_variant var = 123.5;
    QVERIFY2(var.dump(0) == "123.5", "INFO: test may not work due to double conversion");
    var = -123.5;
    QVERIFY2(var.dump(0) == "-123.5", "INFO: test may not work due to double conversion");
    var = 2e-100;
    QVERIFY2(var.dump(0) == "2e-100", "INFO: test may not work due to double conversion");
    var = -2e-100;
    QVERIFY2(var.dump(0) == "-2e-100", "INFO: test may not work due to double conversion");
    var = 2E-100;
    QVERIFY2(var.dump(0) == "2e-100", "INFO: test may not work due to double conversion");
    var = -2E-100;
    QVERIFY2(var.dump(0) == "-2e-100", "INFO: test may not work due to double conversion");
}

void jsonlib_unit_tests::json_variant_dump_test_case4() {
    json_variant var = true;
    QVERIFY(var.dump(0) == "true");
    var = false;
    QVERIFY(var.dump(0) == "false");
}

void jsonlib_unit_tests::json_variant_dump_test_case5() {
    json_variant var = json_variant::null;
    QVERIFY(var.dump(0) == "null");
}

void jsonlib_unit_tests::json_variant_dump_test_case6() {
    json_variant var = "hello world";
    QVERIFY(var.dump(0) == "\"hello world\"");
}

void jsonlib_unit_tests::json_variant_dump_test_case7() {
    json_variant var = json_array();
    QVERIFY(var.dump(0) == "[]");

    var.to_array().push_back(123);
    QVERIFY(var.dump(0) == "[123]");

    var.to_array().push_back("string value");
    var.to_array().push_back(false);

    QVERIFY(var.dump(0) == "[123,\"string value\",false]");
}

void jsonlib_unit_tests::json_variant_dump_test_case8() {
    json_variant var = json_object();
    QVERIFY(var.dump(0) == "{}");

    var.to_object().insert({"var", json_variant::null});
    QVERIFY(var.dump(0) == "{\"var\":null}");

    var.to_object().insert({"var2", true});
    var.to_object().insert({"var3", -200});

    QVERIFY(var.dump(0) == "{\"var\":null,\"var2\":true,\"var3\":-200}");
}

void jsonlib_unit_tests::json_variant_dump_test_case9() {
    json_variant var;
    QVERIFY(var.dump() == "(invalid json variant)");
}

void jsonlib_unit_tests::json_variant_is_valid_json_test_case1() {
    json_variant var;
    QVERIFY(var.is_invalid_value());
    QVERIFY(var.is_invalid_json());

    var.set_value(json_array({1,2,3,json_object({{"x1", 1},{"x2", false}}),"w",json_variant::null}));

    QVERIFY(var.is_valid_value());
    QVERIFY(var.is_valid_json());

    var.to_array()[3].to_object().at("x2") = json_variant();

    QVERIFY(var.is_valid_value());
    QVERIFY(var.is_invalid_json());

    var.to_array()[3].to_object().at("x2") = "hello world";

    QVERIFY(var.is_valid_value());
    QVERIFY(var.is_valid_json());

    var.to_array()[1] = json_variant();

    QVERIFY(var.is_valid_value());
    QVERIFY(var.is_invalid_json());

    var.to_array()[1] = json_object();

    QVERIFY(var.is_valid_value());
    QVERIFY(var.is_valid_json());
}

void jsonlib_unit_tests::json_document_io_test_case1() {
    json_document doc;
    QVERIFY(doc.open() == false);
    QVERIFY(doc.json().is_invalid_value() == true);
    QVERIFY(doc.save() == false);
}

void jsonlib_unit_tests::json_document_io_test_case2() {
    restore_original_valid_json_doc();

    json_document doc(JSON_VALID_DOC_PATH);
    QVERIFY(doc.open() == true);
    QVERIFY(doc.json().is_valid_value() == true);

    doc.json().to_object().at("value1") = json_variant::null;
    QVERIFY(doc.json().to_object()["value1"].is_null() == true);

    QVERIFY(doc.save() == true);
    QVERIFY(doc.open() == true);

    QVERIFY(doc.json().to_object()["value1"].is_null() == true);

    doc.save();
}

void jsonlib_unit_tests::json_document_io_test_case3() {
    restore_original_valid_json_doc();

    json_document doc(JSON_VALID_DOC_PATH);
    QVERIFY(doc.open() == true);
    QVERIFY(doc.json().is_valid_value() == true);

    doc.json().to_object().at("value1") = json_variant();
    QVERIFY(doc.json().to_object()["value1"].is_invalid_value() == true);

    QVERIFY(doc.save() == false);
}

void jsonlib_unit_tests::json_document_io_test_case4() {
    json_document doc(JSON_INVALID_DOC_PATH);
    QVERIFY(doc.json().is_valid_value() == false);
    QVERIFY(doc.open() == false);
    QVERIFY(doc.json().is_valid_value() == false);
    QVERIFY(doc.save() == false);
}

void jsonlib_unit_tests::json_document_io_test_case5() {
    json_document doc;
    QVERIFY(doc.json().is_valid_value() == false);
    QVERIFY(doc.open(JSON_INVALID_DOC_PATH) == false);
    QVERIFY(doc.json().is_valid_value() == false);
    QVERIFY(doc.save(JSON_INVALID_DOC_PATH) == false);
}

void jsonlib_unit_tests::json_document_io_test_case6() {
    json_document doc;
    QVERIFY(doc.json().is_valid_value() == false);
    QVERIFY(doc.open(JSON_VALID_DOC_PATH) == true);
    QVERIFY(doc.json().is_valid_value() == true);
    QVERIFY(doc.save(JSON_VALID_DOC_PATH) == true);
}

void jsonlib_unit_tests::json_document_io_test_case7() {
    json_document doc;
    QVERIFY(doc.get_filename() == "");
    doc.set_filename(JSON_VALID_DOC_PATH);
    QVERIFY(doc.open() == true);
    QVERIFY(doc.json().is_valid_value() == true);
    QVERIFY(doc.save() == true);
}

void jsonlib_unit_tests::json_document_io_test_case8() {
    restore_original_valid_json_doc();

    json_document doc;
    doc.set_filename(JSON_VALID_DOC_PATH);
    QVERIFY(doc.open() == true);
    QVERIFY(doc.json().is_valid_value() == true);
    doc.set_json(json_object({{"value", json_variant::null}}));
    QVERIFY(doc.json().is_valid_value() == true);
    QVERIFY(doc.save() == true);

    QVERIFY(doc.open() == true);
    QVERIFY(doc.json().is_valid_value() == true);
    QVERIFY(doc.json().to_object()["value"].is_null() == true);

    doc.set_filename(JSON_INVALID_DOC_PATH);
    QVERIFY(doc.open() == false);
    QVERIFY(doc.json().is_valid_value() == false);
}

void jsonlib_unit_tests::json_document_io_test_case9() {
    restore_original_valid_json_doc();

    QVERIFY(json_document::save(JSON_VALID_DOC_PATH, json_variant::null, 0) == true);
    json_document doc(JSON_VALID_DOC_PATH);
    QVERIFY(doc.open(JSON_INVALID_DOC_PATH) == false);
    QVERIFY(doc.open() == true);
    QVERIFY(doc.open(JSON_VALID_DOC_PATH) == true);
    QVERIFY(doc.json().is_valid_value() == true);

    QVERIFY(doc.json().is_null() == true);
}

void jsonlib_unit_tests::json_document_io_test_case10() {
    return;

    restore_original_valid_json_doc();

    QVERIFY(json_document::save(JSON_INVALID_DOC_PATH, json_variant(5000), 0) == false);
    QVERIFY(json_document::save(JSON_VALID_DOC_PATH, json_variant()) == false);
}

void jsonlib_unit_tests::json_parser_parse_test_case1() {
    QVERIFY(json_parser::parse("null").is_valid_value());
    QVERIFY(json_parser::parse("false").is_valid_value());
    QVERIFY(json_parser::parse("true").is_valid_value());
    QVERIFY(json_parser::parse("100").is_valid_value());
    QVERIFY(json_parser::parse("-1").is_valid_value());
    QVERIFY(json_parser::parse("0").is_valid_value());
    QVERIFY(json_parser::parse("1").is_valid_value());
    QVERIFY(json_parser::parse("\"\"").is_valid_value());
    QVERIFY(json_parser::parse("\"string\"").is_valid_value());
    QVERIFY(json_parser::parse("\"string end\"").is_valid_value());
    QVERIFY(json_parser::parse("{}").is_valid_value());
    QVERIFY(json_parser::parse("{\"\":1}").is_valid_value());
    QVERIFY(json_parser::parse("[]").is_valid_value());
    QVERIFY(json_parser::parse("2e-100").is_valid_value());
    QVERIFY(json_parser::parse("2E-100").is_valid_value());
    QVERIFY(json_parser::parse("10000e-100").is_valid_value());
    QVERIFY(json_parser::parse("1000E-100").is_valid_value());
    QVERIFY(json_parser::parse("1000e+100").is_valid_value());
    QVERIFY(json_parser::parse("1000E+100").is_valid_value());
    QVERIFY(json_parser::parse("2e2").is_valid_value());
    QVERIFY(json_parser::parse("0e0").is_valid_value());
    QVERIFY(json_parser::parse("2E2").is_valid_value());
    QVERIFY(json_parser::parse("0E0").is_valid_value());
    QVERIFY(json_parser::parse("0.2e+100").is_valid_value());
    QVERIFY(json_parser::parse("0.2e-100").is_valid_value());
    QVERIFY(json_parser::parse("0.2E+100").is_valid_value());
    QVERIFY(json_parser::parse("0.2E-100").is_valid_value());
    QVERIFY(json_parser::parse("0.220000e+100").is_valid_value());
    QVERIFY(json_parser::parse("0.22000E+100").is_valid_value());
    QVERIFY(json_parser::parse("0.000002e-100").is_valid_value());
    QVERIFY(json_parser::parse("0.000002E-100").is_valid_value());
    QVERIFY(json_parser::parse("0.2e100").is_valid_value());
    QVERIFY(json_parser::parse("0.2e-100").is_valid_value());
    QVERIFY(json_parser::parse("0.2e+100").is_valid_value());
    QVERIFY(json_parser::parse("0.20e100").is_valid_value());
    QVERIFY(json_parser::parse("0.20e-100").is_valid_value());
    QVERIFY(json_parser::parse("0.20e+100").is_valid_value());
    QVERIFY(json_parser::parse("0.2E100").is_valid_value());
    QVERIFY(json_parser::parse("0.2E-100").is_valid_value());
    QVERIFY(json_parser::parse("0.2E+100").is_valid_value());
    QVERIFY(json_parser::parse("0.20E100").is_valid_value());
    QVERIFY(json_parser::parse("0.20E-100").is_valid_value());
    QVERIFY(json_parser::parse("0.20E+100").is_valid_value());
}

void jsonlib_unit_tests::json_parser_parse_test_case2() {
    QVERIFY(json_parser::parse("nulll").is_invalid_value());
    QVERIFY(json_parser::parse("nul").is_invalid_value());
    QVERIFY(json_parser::parse("nu").is_invalid_value());
    QVERIFY(json_parser::parse("n").is_invalid_value());
    QVERIFY(json_parser::parse("falsee").is_invalid_value());
    QVERIFY(json_parser::parse("fals").is_invalid_value());
    QVERIFY(json_parser::parse("fal").is_invalid_value());
    QVERIFY(json_parser::parse("fa").is_invalid_value());
    QVERIFY(json_parser::parse("f").is_invalid_value());
    QVERIFY(json_parser::parse("truee").is_invalid_value());
    QVERIFY(json_parser::parse("tru").is_invalid_value());
    QVERIFY(json_parser::parse("tr").is_invalid_value());
    QVERIFY(json_parser::parse("t").is_invalid_value());
    QVERIFY(json_parser::parse("null l").is_invalid_value());
    QVERIFY(json_parser::parse("false e").is_invalid_value());
    QVERIFY(json_parser::parse("true e").is_invalid_value());
    QVERIFY(json_parser::parse("nnull").is_invalid_value());
    QVERIFY(json_parser::parse("ffalse").is_invalid_value());
    QVERIFY(json_parser::parse("ttrue").is_invalid_value());
    QVERIFY(json_parser::parse("ff").is_invalid_value());
    QVERIFY(json_parser::parse("ttr").is_invalid_value());
    QVERIFY(json_parser::parse("--1").is_invalid_value());
    QVERIFY(json_parser::parse("-").is_invalid_value());
    QVERIFY(json_parser::parse("+").is_invalid_value());
    QVERIFY(json_parser::parse("u").is_invalid_value());
    QVERIFY(json_parser::parse("\\u").is_invalid_value());
    QVERIFY(json_parser::parse("\\u1").is_invalid_value());
    QVERIFY(json_parser::parse("\\u12").is_invalid_value());
    QVERIFY(json_parser::parse("\\u124").is_invalid_value());
    QVERIFY(json_parser::parse("\\u1245").is_invalid_value());
    QVERIFY(json_parser::parse("\\u12456").is_invalid_value());
    QVERIFY(json_parser::parse("\\u12f5").is_invalid_value());
    QVERIFY(json_parser::parse("").is_invalid_value());
    QVERIFY(json_parser::parse("+100").is_invalid_value());
    QVERIFY(json_parser::parse("{}}").is_invalid_value());
    QVERIFY(json_parser::parse("{{}").is_invalid_value());
    QVERIFY(json_parser::parse("[]]").is_invalid_value());
    QVERIFY(json_parser::parse("[[]").is_invalid_value());
    QVERIFY(json_parser::parse("{").is_invalid_value());
    QVERIFY(json_parser::parse("[").is_invalid_value());
    QVERIFY(json_parser::parse("}").is_invalid_value());
    QVERIFY(json_parser::parse("]").is_invalid_value());
    QVERIFY(json_parser::parse("\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string").is_invalid_value());
    QVERIFY(json_parser::parse("string\"").is_invalid_value());
    QVERIFY(json_parser::parse("e0").is_invalid_value());
    QVERIFY(json_parser::parse("0e").is_invalid_value());
    QVERIFY(json_parser::parse("E0").is_invalid_value());
    QVERIFY(json_parser::parse("0E").is_invalid_value());
    QVERIFY(json_parser::parse("2ee2").is_invalid_value());
    QVERIFY(json_parser::parse("2ee").is_invalid_value());
    QVERIFY(json_parser::parse("2e\\u1325").is_invalid_value());
    QVERIFY(json_parser::parse("2EE2").is_invalid_value());
    QVERIFY(json_parser::parse("2EE").is_invalid_value());
    QVERIFY(json_parser::parse("e+100").is_invalid_value());
    QVERIFY(json_parser::parse("E+100").is_invalid_value());
    QVERIFY(json_parser::parse("0.2e0.4").is_invalid_value());
    QVERIFY(json_parser::parse("0.2E0.4").is_invalid_value());
    QVERIFY(json_parser::parse("e-100").is_invalid_value());
    QVERIFY(json_parser::parse("E-100").is_invalid_value());
    QVERIFY(json_parser::parse("01").is_invalid_value());
    QVERIFY(json_parser::parse("001").is_invalid_value());
    QVERIFY(json_parser::parse("002").is_invalid_value());
    QVERIFY(json_parser::parse("00022").is_invalid_value());
    QVERIFY(json_parser::parse("0002.2").is_invalid_value());
    QVERIFY(json_parser::parse("0..432").is_invalid_value());
    QVERIFY(json_parser::parse("0..2e-100").is_invalid_value());
    QVERIFY(json_parser::parse("0..2e2").is_invalid_value());
    QVERIFY(json_parser::parse("0..2e2").is_invalid_value());
    QVERIFY(json_parser::parse("0..2E-100").is_invalid_value());
    QVERIFY(json_parser::parse("0..2E2").is_invalid_value());
    QVERIFY(json_parser::parse("0..2E2").is_invalid_value());
    QVERIFY(json_parser::parse(".5").is_invalid_value());
    QVERIFY(json_parser::parse(".05").is_invalid_value());
    QVERIFY(json_parser::parse("00.2e100").is_invalid_value());
    QVERIFY(json_parser::parse("00.2e-100").is_invalid_value());
    QVERIFY(json_parser::parse("00.2e+100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20e100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20e-100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20e+100").is_invalid_value());
    QVERIFY(json_parser::parse("000.2e+100").is_invalid_value());
    QVERIFY(json_parser::parse("00.2E100").is_invalid_value());
    QVERIFY(json_parser::parse("00.2E-100").is_invalid_value());
    QVERIFY(json_parser::parse("00.2E+100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20E100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20E-100").is_invalid_value());
    QVERIFY(json_parser::parse("00.20E+100").is_invalid_value());
    QVERIFY(json_parser::parse("000.2E+100").is_invalid_value());
    QVERIFY(json_parser::parse("0+1").is_invalid_value());
    QVERIFY(json_parser::parse("0+0").is_invalid_value());
    QVERIFY(json_parser::parse("1+0").is_invalid_value());
    QVERIFY(json_parser::parse("1+1").is_invalid_value());
}

void jsonlib_unit_tests::json_parser_parse_test_case3() {
    QVERIFY(json_parser::parse("null").is_null());
    QVERIFY(json_parser::parse("false").is_bool());
    QVERIFY(json_parser::parse("true").is_bool());
    QVERIFY(json_parser::parse("100").is_int());
    QVERIFY(json_parser::parse("-1").is_int());
    QVERIFY(json_parser::parse("0").is_int());
    QVERIFY(json_parser::parse("1").is_int());
    QVERIFY(json_parser::parse("\"\"").is_string());
    QVERIFY(json_parser::parse("\"string\"").is_string());
    QVERIFY(json_parser::parse("\"string end\"").is_string());
    QVERIFY(json_parser::parse("{}").is_object());
    QVERIFY(json_parser::parse("[]").is_array());
    QVERIFY(json_parser::parse("2e-100").is_double());
    QVERIFY(json_parser::parse("2E-100").is_double());
    QVERIFY(json_parser::parse("10000e-100").is_double());
    QVERIFY(json_parser::parse("1000E-100").is_double());
    QVERIFY(json_parser::parse("1000e+100").is_double());
    QVERIFY(json_parser::parse("1000E+100").is_double());
    QVERIFY(json_parser::parse("2e2").is_double());
    QVERIFY(json_parser::parse("0e0").is_double());
    QVERIFY(json_parser::parse("2E2").is_double());
    QVERIFY(json_parser::parse("0E0").is_double());
    QVERIFY(json_parser::parse("0.2e+100").is_double());
    QVERIFY(json_parser::parse("0.2e-100").is_double());
    QVERIFY(json_parser::parse("0.2E+100").is_double());
    QVERIFY(json_parser::parse("0.2E-100").is_double());
    QVERIFY(json_parser::parse("0.220000e+100").is_double());
    QVERIFY(json_parser::parse("0.22000E+100").is_double());
    QVERIFY(json_parser::parse("0.000002e-100").is_double());
    QVERIFY(json_parser::parse("0.000002E-100").is_double());
    QVERIFY(json_parser::parse("0.2e100").is_double());
    QVERIFY(json_parser::parse("0.2e-100").is_double());
    QVERIFY(json_parser::parse("0.2e+100").is_double());
    QVERIFY(json_parser::parse("0.20e100").is_double());
    QVERIFY(json_parser::parse("0.20e-100").is_double());
    QVERIFY(json_parser::parse("0.20e+100").is_double());
    QVERIFY(json_parser::parse("0.2E100").is_double());
    QVERIFY(json_parser::parse("0.2E-100").is_double());
    QVERIFY(json_parser::parse("0.2E+100").is_double());
    QVERIFY(json_parser::parse("0.20E100").is_double());
    QVERIFY(json_parser::parse("0.20E-100").is_double());
    QVERIFY(json_parser::parse("0.20E+100").is_double());
}

void jsonlib_unit_tests::json_parser_parse_test_case4() {
    QVERIFY(json_parser::parse("false").to_bool() == false);
    QVERIFY(json_parser::parse("true").to_bool() == true);
    QVERIFY(json_parser::parse("100").to_int() == 100);
    QVERIFY(json_parser::parse("-1").to_int() == -1);
    QVERIFY(json_parser::parse("0").to_int() == 0);
    QVERIFY(json_parser::parse("1").to_int() == 1);
    QVERIFY(json_parser::parse("\"\"").to_string() == "");
    QVERIFY(json_parser::parse("\"string\"").to_string() == "string");
    QVERIFY(json_parser::parse("\"string end\"").to_string() == "string end");
    QVERIFY(json_parser::parse("{}").to_object() == json_object());
    QVERIFY(json_parser::parse("[]").to_array() == json_array());
    QCOMPARE(json_parser::parse("2e-1").to_double()+1, (2e-1)+1);
    QCOMPARE(json_parser::parse("2E-1").to_double()+1, (2E-1)+1);
    QCOMPARE(json_parser::parse("100e-1").to_double()+1, (100e-1)+1);
    QCOMPARE(json_parser::parse("10E-1").to_double()+1, (10E-1)+1);
    QCOMPARE(json_parser::parse("10e+1").to_double()+1, (10e+1)+1);
    QCOMPARE(json_parser::parse("10E+1").to_double()+1, (10E+1)+1);
    QCOMPARE(json_parser::parse("2e2").to_double()+1, (2e2)+1);
    QCOMPARE(json_parser::parse("0e0").to_double()+1, (0e0)+1);
    QCOMPARE(json_parser::parse("2E2").to_double()+1, (2E2)+1);
    QCOMPARE(json_parser::parse("0E0").to_double()+1, (0E0)+1);
    QCOMPARE(json_parser::parse("0.2e+1").to_double()+1, (0.2e+1)+1);
    QCOMPARE(json_parser::parse("0.2e-1").to_double()+1, (0.2e-1)+1);
    QCOMPARE(json_parser::parse("0.2E+1").to_double()+1, (0.2E+1)+1);
    QCOMPARE(json_parser::parse("0.2E-1").to_double()+1, (0.2E-1)+1);
    QCOMPARE(json_parser::parse("0.220000e+1").to_double()+1, (0.220000e+1)+1);
    QCOMPARE(json_parser::parse("0.22000E+1").to_double()+1, (0.22000E+1)+1);
    QCOMPARE(json_parser::parse("0.000002e-1").to_double()+1, (0.000002e-1)+1);
    QCOMPARE(json_parser::parse("0.000002E-1").to_double()+1, (0.000002E-1)+1);
    QCOMPARE(json_parser::parse("0.2e1").to_double()+1, (0.2e1)+1);
    QCOMPARE(json_parser::parse("0.2e-1").to_double()+1, (0.2e-1)+1);
    QCOMPARE(json_parser::parse("0.2e+1").to_double()+1, (0.2e+1)+1);
    QCOMPARE(json_parser::parse("0.20e1").to_double()+1, (0.20e1)+1);
    QCOMPARE(json_parser::parse("0.20e-1").to_double()+1, (0.20e-1)+1);
    QCOMPARE(json_parser::parse("0.20e+1").to_double()+1, (0.20e+1)+1);
    QCOMPARE(json_parser::parse("0.2E1").to_double()+1, (0.2E1)+1);
    QCOMPARE(json_parser::parse("0.2E-1").to_double()+1, (0.2E-1)+1);
    QCOMPARE(json_parser::parse("0.2E+1").to_double()+1, (0.2E+1)+1);
    QCOMPARE(json_parser::parse("0.20E1").to_double()+1, (0.20E1)+1);
    QCOMPARE(json_parser::parse("0.20E-1").to_double()+1, (0.20E-1)+1);
    QCOMPARE(json_parser::parse("0.20E+1").to_double()+1, (0.20E+1)+1);
}

void jsonlib_unit_tests::json_parser_parse_test_case5() {
    json_variant expected = json_object();
    json_object obj = { { "sample", -1 } };
    expected.to_object().insert({"value", 1});
    expected.to_object().insert({"name", json_variant::null});
    expected.to_object().insert({"array", json_array({"array value 1", json_variant::null, true, false, 12, -324, obj, json_object()})});

    json_variant actual = json_parser::parse(R"({"array":["array value 1",null,true,false,12,-324,{"sample":-1},{}],"name":null,"value":1})");

    QVERIFY(expected == actual);

    actual = json_parser::parse("{\n  \"array\": [\n    \"array value 1\",\n    null,\n    true,\n    false,\n    12,\n    -324,\n    "
                                "{\n      \"sample\": -1\n    },\n    {\n\n    }\n  ],\n  \"name\": null,\n  \"value\": 1\n}");

    QVERIFY(expected == actual);
}

void jsonlib_unit_tests::json_parser_parse_test_case6() {
    json_variant parsed = json_parser::parse(R"([])");

    QVERIFY(parsed == json_array());

    parsed = json_parser::parse(R"([100])");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_array().size() == 1);
    QVERIFY(parsed.to_array()[0] == 100);

    parsed = json_parser::parse(R"([100,null])");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_array().size() == 2);
    QVERIFY(parsed.to_array()[0] == 100);
    QVERIFY(parsed.to_array()[1].is_null());

    parsed = json_parser::parse(R"([100,null,{},[],[],{}])");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_array().size() == 6);
    QVERIFY(parsed.to_array()[0] == 100);
    QVERIFY(parsed.to_array()[1].is_null());
    QVERIFY(parsed.to_array()[2] == json_object());
    QVERIFY(parsed.to_array()[3] == json_array());
    QVERIFY(parsed.to_array()[4] == json_array());
    QVERIFY(parsed.to_array()[5] == json_object());

    parsed = json_parser::parse(R"([100,null,{},[],["string 1","string 2"],{"property 1":false,"property 2":0.4}])");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_array().size() == 6);
    QVERIFY(parsed.to_array()[0] == 100);
    QVERIFY(parsed.to_array()[1].is_null());
    QVERIFY(parsed.to_array()[2] == json_object());
    QVERIFY(parsed.to_array()[3] == json_array());
    QVERIFY(parsed.to_array()[4] == json_array({"string 1","string 2"}));
    QVERIFY(parsed.to_array()[5] == json_object({{ "property 1", false }, { "property 2", 0.4 }}));
}

void jsonlib_unit_tests::json_parser_parse_test_case7() {
    QVERIFY(json_parser::parse("[\"").is_invalid_value());
    QVERIFY(json_parser::parse("[\"1").is_invalid_value());
    QVERIFY(json_parser::parse("[\"+").is_invalid_value());
    QVERIFY(json_parser::parse("[\"-").is_invalid_value());
    QVERIFY(json_parser::parse("[\"0").is_invalid_value());
    QVERIFY(json_parser::parse("[\"2e").is_invalid_value());
    QVERIFY(json_parser::parse("[\"\\u").is_invalid_value());
    QVERIFY(json_parser::parse("[\"").is_invalid_value());
    QVERIFY(json_parser::parse("[\"]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"1]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"+]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"-]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"0]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"2e]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"\\u]").is_invalid_value());
    QVERIFY(json_parser::parse("[\"]").is_invalid_value());
    QVERIFY(json_parser::parse("[123,345,]").is_invalid_value());
    QVERIFY(json_parser::parse("[123,345,").is_invalid_value());
    QVERIFY(json_parser::parse("[123,345,[]").is_invalid_value());
    QVERIFY(json_parser::parse("[[[[[{\"\":[[\\u2344]]}]]]]]").is_invalid_value());
}

void jsonlib_unit_tests::json_parser_parse_test_case8() {
    json_variant parsed = json_parser::parse(R"({})");

    QVERIFY(parsed == json_object());

    parsed = json_parser::parse(R"({"v1":100})");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_object().size() == 1);
    QVERIFY(parsed.to_object().at("v1") == 100);

    parsed = json_parser::parse(R"({"v1":100,"v2":null})");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_object().size() == 2);
    QVERIFY(parsed.to_object().at("v1") == 100);
    QVERIFY(parsed.to_object().at("v2").is_null());

    parsed = json_parser::parse(R"({"v1":100,"v2":null,"v3":[],"v4":{}})");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_object().size() == 4);
    QVERIFY(parsed.to_object().at("v1") == 100);
    QVERIFY(parsed.to_object().at("v2").is_null());
    QVERIFY(parsed.to_object().at("v3") == json_array());
    QVERIFY(parsed.to_object().at("v4") == json_object());

    parsed = json_parser::parse(R"({"v1":100,"v2":null,"v3":["string 1","string 2"],"v4":{"property 1":false,"property 2":0.4}})");

    QVERIFY(parsed.is_valid_json());
    QVERIFY(parsed.to_object().size() == 4);
    QVERIFY(parsed.to_object().at("v1") == 100);
    QVERIFY(parsed.to_object().at("v2").is_null());
    QVERIFY(parsed.to_object().at("v3") == json_array({"string 1","string 2"}));
    QVERIFY(parsed.to_object().at("v4") == json_object({{ "property 1", false }, { "property 2", 0.4 }}));
}

void jsonlib_unit_tests::json_parser_parse_test_case9() {
    QVERIFY(json_parser::parse("{\"").is_invalid_value());
    QVERIFY(json_parser::parse("{\"a").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,\"a\"").is_invalid_value());
    QVERIFY(json_parser::parse("{\"}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"a}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":,\"a\"}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":1,2:\"a\"}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"\":1,\"a\":{}").is_invalid_value());
    QVERIFY(json_parser::parse("{\"v1\":{\"v1\":{\"v1\":{\"v1\":{\"v1\":{").is_invalid_value());
    QVERIFY(json_parser::parse("{\"v1\":{\"v1\":{\"v1\":{\"v1\":{\"v1\":2.0e2.0}}}}}").is_invalid_value());
}

void jsonlib_unit_tests::json_parser_parse_test_case10() {
    QVERIFY(json_parser::parse(R"("string")").is_valid_value());
    QVERIFY(json_parser::parse("\"string with \\\" \\\\ \\/ \\b \\f \\n \\r \\t \\u1234 \\uabcd \\uAFaf \\u1afF \\u99aF all valid escapes\"").is_valid_value());
    QVERIFY(json_parser::parse("\"string with \\\" \\\\ \\/ \\bb \\ff \\nn \\rr \\tt \\u12344 \\uabcdd \\uAFaf \\u1afF \\u99aFF all valid escapes\"").is_valid_value());
    QVERIFY(json_parser::parse("\"stringwith\\\"\\\\\\/\\b\\f\\n\\r\\t\\u1234\\uabcd\\uAFaf\\u1afF\\u99aFallvalidescapes\"").is_valid_value());
    QVERIFY(json_parser::parse("\"string with \\\" \\\\ \\/ \\b \\f \\n \\r \\\t \\u1234 \\uabcd \\uAFaf \\u1afF \\u99aF all valid escapes\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string with \\\"\" escapes\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string \\uFFFG\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string \\uFFFg\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string \\ugfff\"").is_invalid_value());
    QVERIFY(json_parser::parse("\"string \\ 2345\"").is_invalid_value());
}

void jsonlib_unit_tests::json_parser_parse_test_case11() {
    json_variant actual = json_parser::parse(R"([{"string\"\\\/\b\f\n\r\t\u1234\uabcd":324,"v2":0.234,"v3":2e2,"v4":3e-32,"v5":0.4e-123,
                                               "v6":2e+23,"v7":false,"v8":true,"v9":null,"v10":{},"v11":[],"v12":-123,"v13":"value"}])");



    json_variant expected = json_array();
    expected.to_array().push_back(json_object({ { R"(string\"\\\/\b\f\n\r\t\u1234\uabcd)", 324 }, { "v2", 0.234 }, { "v3", 2e2 },
                                                { "v4", 3e-32 }, { "v5", 0.4e-123 }, { "v6", 2e+23 }, { "v7", false }, { "v8",true},
                                                { "v9",json_variant::null }, { "v10", json_object() }, { "v11", json_array() }, {"v12",-123}, {"v13","value" }
                                              }));


    QVERIFY(actual.is_valid_json());
    QVERIFY(expected.is_valid_json());
    QVERIFY(actual == expected);

    actual = json_parser::parse(R"(  [   {   "string\"\\\/\b\f\n\r\t\u1234\uabcd"   :   324   ,   "v2"   :
                                0.234   ,   "v3"   :   2e2   ,   "v4"   :   3e-32,   "v5"   :   0.4e-123   ,
                                "v6"   :   2e+23   ,   "v7"   :   false   ,   "v8"   :   true,"v9"   :   null,
                                "v10"   :   {   }   ,   "v11"   :   [   ]   ,   "v12"   :   -123,   "v13"
                                :   "value"}   ]   )");

    QVERIFY(actual.is_valid_json());
    QVERIFY(actual == expected);

    QVERIFY(json_parser::parse("\n\r\\ null").is_null());
    QVERIFY(json_parser::parse("null\n\r\\ ").is_null());
    QVERIFY(json_parser::parse("\n\r\\ null\n\r\\ ").is_null());
}

void jsonlib_unit_tests::json_parser_parse_test_case12() {
    json_variant var = R"(raw json string with \" very \ illegal / \\ \t "" characters")";

    std::string escaped = R"("raw json string with \u005c\u0022 very \u005c illegal / \u005c\u005c \u005ct \u0022\u0022 characters\u0022")";
    std::string unescaped = R"("raw json string with \" very \ illegal / \\ \t "" characters"")";

    QVERIFY(var.dump() == escaped);
    QVERIFY(json_variant::unescape_string(var.dump()) == unescaped);
}

void jsonlib_unit_tests::json_parser_parse_test_case13() {
    json_variant var = R"(raw json string \u3093with \" very \ illegal / \\ \t "" characters")";

    std::string escaped = R"("raw json string \u005cu3093with \u005c\u0022 very \u005c illegal / \u005c\u005c \u005ct \u0022\u0022 characters\u0022")";
    std::string unescaped = R"("raw json string \u3093with \" very \ illegal / \\ \t "" characters"")";

    QVERIFY(var.dump() == escaped);
    QVERIFY(json_variant::unescape_string(var.dump()) == unescaped);
}

QTEST_APPLESS_MAIN(jsonlib_unit_tests)

#include "tst_json_library_tests.moc"
