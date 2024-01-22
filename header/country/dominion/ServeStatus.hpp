#pragma once
#define TES_HEADER_COUNTRY_DOMINION_SERVESTATUS_HPP_
#ifndef TES_HEADER_COUNTRY_DOMINION_SERVESTATUS_HPP_
class Dominion;
namespace tes {
using progress_type = int;
class DominionServeStatus {
public:
    DominionServeStatus() = delete;
    DominionServeStatus(const Dominion& dominion_)
       : dominion(dominion), completely_serve(false) {}
    explicit DominionServeStatus(progress_type progress_)
       : completely_serve(false), progress(progress_) {}

    void increase(std::shared_ptr<Country>);

    [[nodiscard]]
    bool isCompletelyServed() const noexcept;

    [[nodiscard]]
    progress_type getServeProgress();

private:
    bool completely_serve;
    progress_type progress;
    const Dominion& dominion;

    static inline progress_max = 100;  // draft
};
}

#endif  // TES_HEADER_COUNTRY_DOMINION_SERVESTATUS_HPP_
