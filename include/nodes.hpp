#include <inja.hpp>
#include <HTTPRequest.hpp>

class Node {
public:
    virtual void run(inja::json &state) = 0;
};

class VariableNode : public Node {
protected:
    std::string variable_name;
    std::string variable_value;

public:
    explicit VariableNode(const inja::json &properties) {
        variable_name = properties.value("/variable_name"_json_pointer, "");
        variable_value = properties.value("/variable_value"_json_pointer, "");
    }

    void run(inja::json &state) override {
        try {
            if (variable_name.empty() || variable_value.empty()) {
                throw std::runtime_error("Missing variable name or value");
            }

            state["variable"][variable_name] = variable_value;
        } catch (std::exception &e) {
            std::cerr << e.what() << "\n";
        }
    }
};

class AINode : public Node {
    // TODO Add custom interface systems for Anthropic, OpenAI, Groq, etc.
protected:
    std::string model;
    std::string prompt;

public:
    explicit AINode(const inja::json &properties) {
        model = properties.value("/model_name"_json_pointer, "");
        prompt = properties.value("/prompt"_json_pointer, "");
    }

    void run(inja::json &state) override {
        try {
            if (model.empty() || prompt.empty()) {
                throw std::runtime_error("Missing model name or prompt");
            }

            inja::json llm_request_body;
            llm_request_body["model"] = model;
            llm_request_body["input"] = inja::render(prompt, state);

            http::Request llm_request{"http://10.0.0.212:1234/v1/responses"};
            http::Response llm_response = llm_request.send("POST", llm_request_body.dump(),
                                                           {{"Content-Type", "application/json"}});

            inja::json llm_response_body = inja::json::parse(std::string{
                llm_response.body.begin(), llm_response.body.end()
            });
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
};
