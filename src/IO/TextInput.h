/**
 * @file TextInput.h
 * @author Owen McManus
 * @date 2025/5/16
 */

#pragma once
#include <string>

namespace OEngine::TextInput {
void Connect();
void Disconnect();
std::string GetText();

}; // namespace OEngine::TextInput
