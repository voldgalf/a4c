//
// Created by brick on 6/25/2026.
//

#pragma once
#include <Node.h>

class AINode : public Node {
    // TODO Add custom interface systems for Anthropic, OpenAI, Groq, etc.
protected:
    std::string model;
    std::string prompt;

public:
    explicit AINode(const inja::json &properties);

    void run(inja::json &state) override;
};
