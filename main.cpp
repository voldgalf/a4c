#include <iostream>
#include <memory>
#include <WorkFlowManager.h>
#include <Node.h>

class Node_HelloWorld : public Node {
protected:
    std::string variable_template;
    std::string output_variable;

public:
    Node_HelloWorld() = default;

    explicit Node_HelloWorld(const nlohmann::json &properties);

    void run(nlohmann::json &state) override {
        is_executed = true;


        std::cout << "Hello World!\n";
    };
};

/*
void AINode::run(nlohmann::json &state) {
    try {
        if (model.empty() || prompt.empty()) {
            throw std::runtime_error("Missing model name or prompt");
        }

        nlohmann::json llm_request_body;
        llm_request_body["model"] = model;
        llm_request_body["input"] = inja::render(prompt, state);

        http::Request llm_request{"http://10.0.0.212:1234/v1/responses"};
        http::Response llm_response = llm_request.send("POST", llm_request_body.dump(),
                                                       {{"Content-Type", "application/json"}},
                                                       std::chrono::milliseconds(7000));

        nlohmann::json llm_response_body = nlohmann::json::parse(
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
*/

int main() {
    WorkflowManager manager = WorkflowManager();

    std::unique_ptr<Node> hello_world = std::make_unique<Node_HelloWorld>();

    manager.add_node(std::move(hello_world));

    manager.run_all();
}
