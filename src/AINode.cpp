//
// Created by brick on 6/25/2026.
//
#include <../include/HTTPRequest.hpp>
#include <chrono>
#include <../include/AINode.h>

AINode::AINode(const inja::json &properties) {
    model = properties.value("/model_name"_json_pointer, "");
    prompt = properties.value("/prompt"_json_pointer, "");
}

void AINode::run(inja::json &state) {
    try {
        if (model.empty() || prompt.empty()) {
            throw std::runtime_error("Missing model name or prompt");
        }

        inja::json llm_request_body;
        llm_request_body["model"] = model;
        llm_request_body["input"] = inja::render(prompt, state);

        http::Request llm_request{"http://10.0.0.212:1234/v1/responses"};
        http::Response llm_response = llm_request.send("POST", llm_request_body.dump(),
                                                       {{"Content-Type", "application/json"}},
                                                       std::chrono::milliseconds(7000));

        inja::json llm_response_body = inja::json::parse(
            std::string{llm_response.body.begin(), llm_response.body.end()});
        std::string llm_response_output = llm_response_body.value("/output/0/content/0/text"_json_pointer,
                                                                  "");
        if (llm_response_output.empty()) {
            throw std::runtime_error("Invalid LLM Response");
        }

        state["ai_node"]["response"] = llm_response_output;
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}
