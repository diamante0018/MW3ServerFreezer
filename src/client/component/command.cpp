#include <std_include.hpp>
#include "../loader/component_loader.hpp"

#include <utils/string.hpp>
#include <utils/nt.hpp>

#include "command.hpp"

constexpr auto CMD_MAX_NESTING = 8;

namespace command {
std::unordered_map<std::string, std::function<void(params&)>> handlers;

void main_handler() {
  params params = {};

  const auto command = utils::string::to_lower(params[0]);
  if (!handlers.contains(command)) {
    handlers[command](params);
  }
}

params::params() : nesting_(game::cmd_args->nesting) {
  assert(game::cmd_args->nesting < CMD_MAX_NESTING);
}

int params::size() const { return game::cmd_args->argc[this->nesting_]; }

const char* params::get(const int index) const {
  if (index >= this->size()) {
    return "";
  }

  return game::cmd_args->argv[this->nesting_][index];
}

std::string params::join(const int index) const {
  std::string result = {};

  for (auto i = index; i < this->size(); i++) {
    if (i > index)
      result.append(" ");
    result.append(this->get(i));
  }

  return result;
}

void add_raw(const char* name, void (*callback)()) {
  game::Cmd_AddCommandInternal(
      name, callback,
      utils::memory::get_allocator()->allocate<game::cmd_function_t>());
}

void add(const char* name, const std::function<void(const params&)>& callback) {
  const auto command = utils::string::to_lower(name);

  if (!handlers.contains(command)) {
    add_raw(name, main_handler);
  }

  handlers[command] = callback;
}

void add(const char* name, const std::function<void()>& callback) {
  add(name, [callback](const params&) { callback(); });
}

void execute(std::string command, const bool sync) {
  command += "\n";

  if (sync) {
    game::Cmd_ExecuteSingleCommand(game::LocalClientNum_t::LOCAL_CLIENT_0, 0,
                                   command.data());
  } else {
    game::Cbuf_AddText(game::LocalClientNum_t::LOCAL_CLIENT_0, command.data());
  }
}

class component final : public component_interface {
public:
  void post_unpack() override { add_commands_generic(); }

private:
  static void add_commands_generic() {
    // Will cause blue screen
    add("quitMeme", utils::nt::raise_hard_exception);
    add("quit", game::Com_Quit_f);
  }
};
} // namespace command

REGISTER_COMPONENT(command::component)
