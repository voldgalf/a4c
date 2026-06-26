//
// Created by brick on 6/25/2026.
//
#pragma once
#include <inja.hpp>

class Node {
public:
    virtual void run(inja::json &state) = 0;
};
