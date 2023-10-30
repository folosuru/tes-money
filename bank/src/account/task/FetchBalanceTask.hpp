
#ifndef TES_BANK_SRC_ACCOUNT_TASK_FETCHBALANCETASK_HPP
#define TES_BANK_SRC_ACCOUNT_TASK_FETCHBALANCETASK_HPP
namespace tes {
class FetchBalanceTask : public AsyncTaskBase {
public:
    FetchBalanceTask(int account_id_,
                     std::shared_ptr<BankAccount> account_/*,
                     std::function<void(std::shared_ptr<BankAccount>)>*/)
        : account_id(account_id), account(account_){}

    void onRun() override {
        "select account, currency, value from Balance where account = ?;"
        {

        }
    }

    void onComplete() override {
        // run callback...?
    }
private:
    int account_id;
    std::shared_ptr<BankAccount> account;
    std::unordered_map<currency,std::string> balance;
};
}

#endif  // TES_BANK_SRC_ACCOUNT_TASK_FETCHBALANCETASK_HPP
