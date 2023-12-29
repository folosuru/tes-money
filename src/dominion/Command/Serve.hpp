#ifndef TES_SRC_DOMINION_COMMAND_SERVE_HPP
#define TES_SRC_DOMINION_COMMAND_SERVE_HPP
#include <llapi/DynamicCommandAPI.h>
#include <llapi/mc/CommandOutput.hpp>

namespace tes {
namespace dominion {
namespace command {
    using ParamType = DynamicCommand::ParameterType;
    using Param = DynamicCommand::ParameterData;
    void Serve(DynamicCommand const& command,
        CommandOrigin const& origin,
        CommandOutput& output,
        std::unordered_map<std::string, DynamicCommand::Result>& results);
}
}
}



#endif // TES_SRC_DOMINION_COMMAND_SERVE_HPP
