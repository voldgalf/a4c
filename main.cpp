#include <iostream>
#include <nodes.hpp>

int main() {
    VariableNode variable_node({
        {"variable_name", "prompt"},
        {"variable_value", "Hello, who are you?"},
    });

    AINode ai_node({
        {"model_name", "google/gemma-3-1b"},
        {"prompt", "{{ variable.prompt }}"},
    });

    inja::json state = {};

    std::cout << "Running Variable Node\n";

    variable_node.run(state);

    std::cout << state.dump(4) << "\n";

    std::cout << "Running AI Node\n";


    ai_node.run(state);

    std::cout << state.dump(4) << "\n";
}
