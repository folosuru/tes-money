#pragma once
#ifndef TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_
#define TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_

#ifndef DEBUG_WITHOUT_LLAPI
#include <llapi/DynamicCommandAPI.h>
#endif

namespace tes {
class CurrencyCommandUpdater {

 public:
#ifndef DEBUG_WITHOUT_LLAPI
    CurrencyCommandUpdater(const DynamicCommandInstance *normal_command, const DynamicCommandInstance *operator_command)
        : normal_command(normal_command), operator_command(operator_command) {}
#elif
    CurrencyCommandUpdater(){}
#endif

    void updateCurrencyList(const std::vector<std::string>& new_currency_list);

 private:
#ifndef DEBUG_WITHOUT_LLAPI
    const DynamicCommandInstance *normal_command;
    const DynamicCommandInstance *operator_command;
#endif
};
}
#endif  // TES_MONEY_SRC_CURRENCY_CURRENCYCOMMANDUPDATER_HPP_
