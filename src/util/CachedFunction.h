//
// Created by patryk on 19/07/2021.
//

#pragma once

#include <map>
#include <functional>

template<typename Input, typename Output, typename Container=std::unordered_map<Input, Output>>
class CachedFunction {
    std::function<Output(Input)> m_func;

    Container map;
public:
    template <typename ... ContainerArgs>
    CachedFunction(const std::function<Output(Input)>& func, ContainerArgs&& ... args): m_func(func), map(args ...){}

    Output& operator()(const Input& input) {
        if (!map.contains(input)) map[input] = m_func(input);

        return map[input];
    }
};
