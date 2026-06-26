//
// Created by brick on 6/25/2026.
//

#pragma once
#include <Node.h>

class VariableNode : public Node {
protected:
    std::string variable_name;
    std::string variable_value;

public:
    explicit VariableNode(const inja::json &properties);

    void run(inja::json &state) override;
};
