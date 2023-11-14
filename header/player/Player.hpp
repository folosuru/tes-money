#ifndef TES_HEDER_PLAYER_PLAYER
#define TES_HEDER_PLAYER_PLAYER
#include <memory>

namespace tes {
// llapiにある::Playerと衝突するんだよね、これ
// 違う名前にするべきだよね
class Player {
public:
    const std::string name;

    const std::shared_ptr<PlayerMoney> money;

    [[nodiscard]]
    bool is_citizen() const noexcept;

    [[nodiscard]]
    const std::shared_ptr<Citizen>& getCitizenData() const noexcept;
private:
    std::shared_ptr<Citizen> citizen = nullptr;
};
}

#endif // TES_HEDER_PLAYER_PLAYER
