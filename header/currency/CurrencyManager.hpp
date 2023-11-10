#pragma once
#ifndef PLUGIN_CURRENCYMANAGER_HPP
#define PLUGIN_CURRENCYMANAGER_HPP
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <util/OptionalMessage.hpp>
#include <CppArrai18n/Arrai18n.hpp>
#include <currency/Currency.hpp>
#include <util/dll_declspec.hpp>
#include <misc/CurrencyCommandUpdater.hpp>
namespace tes {
class TES_DLL CurrencyManager {
public:
    CurrencyManager();

    static std::shared_ptr<CurrencyManager> get();

    void setCommandUpdater(CurrencyCommandUpdater*);

    /**
     * 入力に対応する通貨を返す
     * @throws std::out_of_range 存在しなかった場合
     */
    std::shared_ptr<Currency> getCurrency(std::string str);

    void addCurrency(const std::shared_ptr<Currency>& c, bool updateCommand = true);

    bool exists(std::string str) const noexcept;

    /**
     * 通貨の名前が列挙されたvectorを返す
     * @return e.g. {"JPY","USD",...}
     */
    const std::vector<std::string>& getAllCurrencyList();

    void loadAll();

    /**
     * 指定された名前の通貨の情報の保存をする
     * @note 全部を保存する関数がないのは、通貨の情報はそう頻繁に更新されないだろうと考えたから
     */
    void save(const std::string& key);

    [[nodiscard]]
    util::OptionalMessage<void,Arrai18n::trl_text> currencyNameValidation(const std::string&) const noexcept;

private:
    std::shared_ptr<CurrencyCommandUpdater> updater = nullptr;
    const std::string file_export_path = "plugins/tes/money/currency";
    std::unordered_map<std::string, std::shared_ptr<Currency>> cur;
    std::vector<std::string> currency_name_list;
};
}  // tes

#endif  // PLUGIN_CURRENCYMANAGER_HPP
