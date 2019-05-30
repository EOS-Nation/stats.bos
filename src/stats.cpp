#include "stats.hpp"

void stats::update() {

    auto global = _global.get_or_create(_self);

    uint32_t vote_count = 0;
    int64_t staked = 0;

    // Find all cases of delegated bandwidth and sum them up
    auto voters = _voters.begin();

    while (voters != _voters.end()) {
        staked += voters->staked;
        vote_count += 1;
        voters++;
    }

    global.modified_at = current_time_point();
    global.staked = staked;
    global.vote_count = vote_count;

    // Add `properties` table
    _global.set(global, _self);
}

void stats::remove() {
    _global.remove();
}
