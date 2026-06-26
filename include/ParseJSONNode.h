//
// Created by brick on 6/25/2026.
//

#pragma once
#include <Node.h>

class ParseJSONNode : public Node {
protected:
    std::string variable_template;
    std::string output_variable;

public:
    explicit ParseJSONNode(const inja::json &properties);

    void run(inja::json &state) override;
};
