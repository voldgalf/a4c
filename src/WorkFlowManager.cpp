//
// Created by brick on 6/29/2026.
//

#include "../include/WorkFlowManager.h"

WorkflowManager::WorkflowManager() {
    current_node = 0;
}

void WorkflowManager::add_node(std::unique_ptr<Node> node) {
    nodes.push_back(std::move(node));
}

void WorkflowManager::run_next() {
    std::unique_ptr<Node> &node = nodes[current_node];

    if (!node->is_executed) {
        node->run(state);

        if (current_node < nodes.size()) {
            current_node += 1;
        }
    }
}

void WorkflowManager::run_all() {
    for (std::unique_ptr<Node> &node: nodes) {
        node->run(state);
    }
}

nlohmann::json WorkflowManager::get_state() {
    return state;
}

