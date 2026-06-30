//
// Created by brick on 6/29/2026.
//
#include <memory>
#include <Node.h>
#pragma once


class WorkflowManager {
protected:
    std::vector<std::unique_ptr<Node> > nodes;
    int current_node = 0;
    nlohmann::json state = {};

public:
    WorkflowManager();

    void add_node(std::unique_ptr<Node> node);

    void run_next();

    void run_all();

    nlohmann::json get_state();
};
