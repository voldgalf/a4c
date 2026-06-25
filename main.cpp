#include <iostream>
#include <inja.hpp>
#include <HTTPRequest.hpp>

using namespace inja;

void variable_node(json &dict, const json &properties) {
    const std::string variable_name = properties.value("/variable_name"_json_pointer, json(nullptr));
    const std::string variable_value = properties.value("/variable_value"_json_pointer, json(nullptr));

    if (variable_name.empty() || variable_value.empty()) {
        throw 1;
    }

    dict["variable"][variable_name] = variable_value;
}

void ai_node(json &dict, const json &properties) {
    try {
        const std::string properties_model = properties.value("/model_name"_json_pointer, json(nullptr));
        const std::string properties_question_template = properties.value(
            "/question_prompt"_json_pointer, json(nullptr));

        if (properties_model.empty() || properties_question_template.empty()) {
            throw 1;
        }

        json llm_request_body;
        llm_request_body["model"] = properties_model;
        llm_request_body["input"] = inja::render(properties_question_template, dict);

        http::Request llm_request{"http://10.0.0.212:1234/v1/responses"};
        http::Response llm_response = llm_request.send("POST", llm_request_body.dump(),
                                                       {{"Content-Type", "application/json"}});

        json llm_response_body = json::parse(std::string{llm_response.body.begin(), llm_response.body.end()});
        std::string llm_response_output = llm_response_body.value("/output/0/content/0/text"_json_pointer,
                                                                  json(nullptr));
        if (llm_response_output.empty()) {
            throw 1;
        }

        dict["ai_node"]["response"] = llm_response_output;
    } catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
}

int main() {
    json properties;
    properties["variable_name"] = "question_prompt";
    properties["variable_value"] = "Hello, who are you?";

    json dict = {};

    std::cout << "Running Variable Node\n";

    variable_node(dict, properties);

    std::cout << dict.dump(4) << "\n";

    std::cout << "Running AI Node\n";

    json llm_properties;
    properties["model_name"] = "google/gemma-3-1b";
    properties["question_prompt"] = "{{ variable.question_prompt }}";

    ai_node(dict, properties);

    std::cout << dict.dump(4) << "\n";
}
