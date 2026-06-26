//
// Created by brick on 6/25/2026.
//

#include <../include/VariableNode.h>

VariableNode::VariableNode(const inja::json &properties) {
    variable_name = properties.value("/variable_name"_json_pointer, "");
    variable_value = properties.value("/variable_value"_json_pointer, "");
}

void VariableNode::run(inja::json &state) {
    try {
        if (variable_name.empty() || variable_value.empty()) {
            throw std::runtime_error("Missing variable name or value");
        }

        state["variable"][variable_name] = variable_value;
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}
