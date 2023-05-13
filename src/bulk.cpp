#include "bulk.h"
#include <imgui.h>

Bulk::Bulk()
  : m_enabled{false},
    m_size{0},
    m_count{0}, 
    m_average{0}, 
    m_min{0}, 
    m_max{0} {}

void Bulk::recordRun(
  const std::string &numbers,
  const std::list<std::string> &commands
) {
  if (!this->isEnabled())
    return;
  this->m_runs.push_back(std::make_unique<Run>(numbers, commands));
  this->computeStats();
}

void Bulk::clear() {
  this->m_runs.clear();
  this->computeStats();
}

void Bulk::computeStats() {
  this->m_average = 0;
  this->m_min = 0;
  this->m_max = 0;
  for (const auto &run : this->m_runs) {
    this->m_average += run->commands.size();
    if (this->m_min == 0 || run->commands.size() < this->m_min)
      this->m_min = run->commands.size();
    if (this->m_max == 0 || run->commands.size() > this->m_max)
      this->m_max = run->commands.size();
  }
  if (this->m_runs.size() > 0)
    this->m_average /= this->m_runs.size();
}

void Bulk::onImGuiRender() {
  ImGui::Checkbox("Bulk Testing", &this->m_enabled);
  if (!this->m_enabled)
    return;
  if (ImGui::Begin("Bulk Tester", &this->m_enabled)) {
    ImGui::InputInt("Amount of runs", &this->m_size);
    ImGui::Text("Runs recorded: %zu", this->m_runs.size());
    ImGui::Text("Runs left: %zu", this->m_count);
    ImGui::Text("Average: %d", this->m_average);
    ImGui::Text("Min: %d", this->m_min);
    ImGui::Text("Max: %d", this->m_max);
    if (ImGui::Button("Clear"))
      this->clear();
    ImGui::SameLine();
    if (ImGui::Button("Start"))
      this->start();
    if (ImGui::CollapsingHeader("Runs")) {
      ImGui::BeginChild("runs");
      for (uint32_t i = 0; i < this->m_runs.size(); i++) {
        auto& run = this->m_runs[i];
        ImGui::Text("#%d -> %d", i, run->commands.size());
      }
      ImGui::EndChild();
    }
  }
  ImGui::End();
}

void Bulk::start() {
  this->m_count = this->m_size;
}