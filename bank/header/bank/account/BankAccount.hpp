#ifndef TES_BANK_HEADER_ACCOUNT_BANKACCOUNT_HPP
#define TES_BANK_HEADER_ACCOUNT_BANKACCOUNT_HPP
#include <memory>
#include <money/money/Money.hpp>
#include <money/money/MoneyAccount.hpp>
#include <money/Util/MoneyTypes.hpp>

namespace tes {
class BankAccount : public MoneyAccount, public std::enable_shared_from_this<BankAccount> {
public:
    std::string getName() override;

    /**
     *
     */
    void updatePreview();

    std::string getBalancePreview(Types::currency) const noexcept;

    const std::unordered_map<Types::currency, std::string>& getAllBalancePreview() const noexcept;

    void setBalance();

    void send(const MoneyAccount* from,
              const Money& money_,
              std::function<void(MoneySendStatus)> callback) override;

    void receive(const MoneyAccount* from, const Money& money_) override;

    Money get(const Types::currency& cur) const noexcept override;

private:
    /*
     * BalancePreview
     * ある時点での所持金の文字列
     * example: "1234.567"
     */
    std::unordered_map<Types::currency, std::string> BalancePreview;
};
}


#endif  // TES_BANK_HEADER_ACCOUNT_BANKACCOUNT_HPP
