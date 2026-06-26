//
// Created by brick on 6/25/2026.
//

#include "../include/ParseJSONNode.h"

ParseJSONNode::ParseJSONNode(const inja::json &properties) {
    variable_template = properties.value("/input_template"_json_pointer, "");
    output_variable = properties.value("/output_template"_json_pointer, "");
}

void ParseJSONNode::run(inja::json &state) {
    try {
        std::string json_to_parse = inja::render(variable_template, state);

        inja::json parsed_json = inja::json::parse(json_to_parse);

        state["json"][output_variable] = parsed_json;
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

